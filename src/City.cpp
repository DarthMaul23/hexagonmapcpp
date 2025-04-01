#include "City.hpp"
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

namespace game {

GameCity::GameCity(const std::string& cityName, const sf::Vector2f& pos)
    : name(cityName),
      position(pos),
      population(1),
      food(2),
      production(2),
      goldPerTurn(1),
      storedFood(0),
      storedProduction(0),
      storedGold(0),
      happiness(50),
      maxHappiness(100),
      science(0),
      scientistsCount(0),
      currentProduction(ProductionItem::SETTLER),
      productionProgress(0),
      productionNeeded(50),
      maxBuildings(5)
{
    // Setup visual representation with larger, more visible city
    cityShape.setRadius(20.0f);  // Increased for better visibility
    cityShape.setOrigin(sf::Vector2f(20.0f, 20.0f)); 
    cityShape.setFillColor(sf::Color(255, 215, 0));  // Gold color
    cityShape.setOutlineColor(sf::Color::Black);
    cityShape.setOutlineThickness(3.0f);
    cityShape.setPosition(position);
    
    std::cout << "City created: " << name << " at position: " 
              << position.x << ", " << position.y << std::endl;
}

void GameCity::addPopulation(int amount) {
    population += amount;
    if (population < 1) population = 1;
    
    // Update city production based on population
    food = 2 + (population - 1);
    production = 2 + (population - 1);
    goldPerTurn = 1 + (population / 2);
    
    // Adjust happiness
    happiness = std::min(happiness + (amount > 0 ? 5 : -5), maxHappiness);
}

void GameCity::addFood(int amount) {
    storedFood += amount;
    
    // Growth mechanics
    int foodNeeded = population * 10;
    if (storedFood >= foodNeeded) {
        storedFood -= foodNeeded;
        addPopulation(1);
    }
}

void GameCity::addProduction(int amount) {
    storedProduction += amount;
    
    // Add to production progress
    productionProgress += storedProduction;
    storedProduction = 0;
}

void GameCity::addGold(int amount) {
    storedGold += amount;
}

void GameCity::addScience(int amount) {
    science += amount * scientistsCount;
}

void GameCity::setProductionItem(ProductionItem item) {
    // Save progress if switching items
    if (currentProduction != item) {
        productionProgress = 0;
    }
    
    currentProduction = item;
    
    // Set production needed based on item
    switch (item) {
        case ProductionItem::SETTLER:
            productionNeeded = 50;
            break;
        case ProductionItem::WARRIOR:
            productionNeeded = 30;
            break;
        case ProductionItem::BUILDER:
            productionNeeded = 20;
            break;
        case ProductionItem::GRANARY:
            productionNeeded = 40;
            break;
        case ProductionItem::WORKSHOP:
            productionNeeded = 60;
            break;
        case ProductionItem::WALLS:
            productionNeeded = 80;
            break;
    }
}

void GameCity::addBuilding(BuildingType building) {
    // Check if city can add more buildings
    if (buildingTypes.size() >= maxBuildings) {
        std::cout << "Cannot add more buildings to " << name << std::endl;
        return;
    }
    
    // Check if building already exists
    if (std::find(buildingTypes.begin(), buildingTypes.end(), building) 
        != buildingTypes.end()) {
        std::cout << "Building already exists in " << name << std::endl;
        return;
    }
    
    // Add building and apply its effects
    buildingTypes.push_back(building);
    
    // Apply building bonuses
    switch (building) {
        case BuildingType::GRANARY:
            food += 2;
            happiness += 5;
            break;
        case BuildingType::WORKSHOP:
            production += 2;
            break;
        case BuildingType::MARKETPLACE:
            goldPerTurn += 2;
            break;
        case BuildingType::LIBRARY:
            science += 1;
            scientistsCount++;
            break;
        case BuildingType::WALLS:
            // Increase city's defensive capabilities
            break;
    }
}

bool GameCity::processTurn() {
    // Process production
    productionProgress += production;
    
    // Process science
    addScience(1);
    
    // Check if production is complete
    if (productionProgress >= productionNeeded) {
        productionProgress -= productionNeeded;
        
        // Check if there's another item in the queue
        if (!productionQueue.empty()) {
            currentProduction = productionQueue.front();
            productionQueue.erase(productionQueue.begin());
            return true;
        }
        
        return true; // Item completed
    }
    
    // Process food and gold
    addFood(food);
    addGold(goldPerTurn);
    
    // Happiness mechanics
    if (food < population) {
        happiness -= 2;
    }
    
    if (happiness < 20) {
        // Negative effects when happiness is low
        production = std::max(0, production - 1);
        goldPerTurn = std::max(0, goldPerTurn - 1);
    }
    
    return false; // No item completed
}

void GameCity::draw(sf::RenderWindow& window) {
    // Draw the city shape
    window.draw(cityShape);
    
    // Optional: Draw city name or population
    static sf::Font font;
    static bool fontLoaded = false;
    
    if (!fontLoaded) {
        // Try multiple font paths
        const std::vector<std::string> fontPaths = {
            "arial.ttf",                  // Current directory
            "../assets/arial.ttf",        // Parent directory's assets folder
            "assets/arial.ttf",           // Assets folder in current directory
            "../fonts/OpenSans-Regular.ttf", // Parent directory's fonts folder
            "fonts/OpenSans-Regular.ttf", // Fonts folder in current directory
            "/System/Library/Fonts/Supplemental/Arial.ttf" // macOS system font
        };
        
        for (const auto& path : fontPaths) {
            if (font.openFromFile(path)) {
                fontLoaded = true;
                break;
            }
        }
    }
    
    if (fontLoaded) {
        sf::Text cityText(font, name + "\nPop: " + std::to_string(population), 12);
        cityText.setFillColor(sf::Color::Black);
        cityText.setPosition(sf::Vector2f(position.x - 20, position.y + 25));
        window.draw(cityText);
    } else {
        std::cerr << "Failed to load font for city text" << std::endl;
    }
}

bool GameCity::contains(const sf::Vector2f& point) const {
    // Expand hitbox for easier selection
    float expansionFactor = 1.5f;
    float radius = cityShape.getRadius() * expansionFactor;
    
    // Distance check
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    float distanceSquared = dx*dx + dy*dy;
    
    return distanceSquared <= radius*radius;
}

std::string GameCity::getItemName(ProductionItem item) {
    switch (item) {
        case ProductionItem::SETTLER: return "Settler";
        case ProductionItem::WARRIOR: return "Warrior";
        case ProductionItem::BUILDER: return "Builder";
        case ProductionItem::GRANARY: return "Granary";
        case ProductionItem::WORKSHOP: return "Workshop";
        case ProductionItem::WALLS: return "Walls";
        default: return "Unknown";
    }
}

std::string GameCity::getBuildingName(BuildingType building) {
    switch (building) {
        case BuildingType::GRANARY: return "Granary";
        case BuildingType::WORKSHOP: return "Workshop";
        case BuildingType::MARKETPLACE: return "Marketplace";
        case BuildingType::LIBRARY: return "Library";
        case BuildingType::WALLS: return "Walls";
        default: return "Unknown";
    }
}

} // namespace game