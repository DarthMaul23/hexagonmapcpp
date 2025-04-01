#include "City.hpp"
#include <iostream>

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
      currentProduction(ProductionItem::SETTLER),
      productionProgress(0),
      productionNeeded(50)
{
    // Setup visual representation with larger, more visible city
    cityShape.setRadius(20.0f);  // Increased from 12.0f for better visibility
    cityShape.setOrigin(sf::Vector2f(20.0f, 20.0f)); // Match the radius
    cityShape.setFillColor(sf::Color(255, 215, 0));  // Gold color for better visibility
    cityShape.setOutlineColor(sf::Color::Black);
    cityShape.setOutlineThickness(3.0f);  // Thicker outline
    cityShape.setPosition(position);
    
    std::cout << "City created at position: " << position.x << ", " << position.y << std::endl;
}

void GameCity::addPopulation(int amount) {
    population += amount;
    if (population < 1) population = 1;
    
    // Update city production based on population
    food = 2 + (population - 1);
    production = 2 + (population - 1);
    goldPerTurn = 1 + (population / 2);
}

void GameCity::addFood(int amount) {
    storedFood += amount;
    
    // Check if we can grow the city
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

void GameCity::setProductionItem(ProductionItem item) {
    // Save progress if switching items
    if (currentProduction != item) {
        // For simplicity we're not saving progress between items
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

bool GameCity::processTurn() {
    // Process production
    productionProgress += production;
    
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
    
    return false; // No item completed
}

void GameCity::draw(sf::RenderWindow& window) {
    // Debug output
    std::cout << "Drawing city at position: " << position.x << ", " << position.y << std::endl;
    
    // Draw the city shape
    window.draw(cityShape);
    
    // Draw a label with population
    // You could add text display here if you want
}

bool GameCity::contains(const sf::Vector2f& point) const {
    // Expand hitbox a bit for easier selection
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

} // namespace game