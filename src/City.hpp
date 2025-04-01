#ifndef CITY_HPP
#define CITY_HPP

#include "GameEntities.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Place City class in the game namespace to avoid conflict with game::City
namespace game {

class GameCity {
public:
    // Production queue
    enum class ProductionItem {
        SETTLER,
        WARRIOR,
        BUILDER,
        GRANARY,
        WORKSHOP,
        WALLS
    };

    // Building types
    enum class BuildingType {
        GRANARY,
        WORKSHOP,
        MARKETPLACE,
        LIBRARY,
        WALLS
    };
    
private:
    std::string name;
    sf::Vector2f position;
    int population;
    int food;
    int production;
    int goldPerTurn;
    
    // Resources stored in the city
    int storedFood;
    int storedProduction;
    int storedGold;
    
    // Happiness and growth
    int happiness;
    int maxHappiness;
    
    // Science mechanics
    int science;
    int scientistsCount;
    
    // Production queue
    std::vector<ProductionItem> productionQueue;
    ProductionItem currentProduction;
    int productionProgress;
    int productionNeeded;
    
    // Buildings
    std::vector<BuildingType> buildingTypes;
    int maxBuildings;
    
    // Visual representation
    sf::CircleShape cityShape;
    
public:
    GameCity(const std::string& cityName, const sf::Vector2f& pos);
    
    const std::string& getName() const { return name; }
    const sf::Vector2f& getPosition() const { return position; }
    int getPopulation() const { return population; }
    int getFood() const { return food; }
    int getProduction() const { return production; }
    int getGoldPerTurn() const { return goldPerTurn; }
    
    void setName(const std::string& newName) { name = newName; }
    void addPopulation(int amount);
    void addFood(int amount);
    void addProduction(int amount);
    void addGold(int amount);
    void addScience(int amount);
    
    void addBuilding(BuildingType building);
    
    void setProductionItem(ProductionItem item);
    ProductionItem getCurrentProduction() const { return currentProduction; }
    int getProductionProgress() const { return productionProgress; }
    int getProductionNeeded() const { return productionNeeded; }
    
    // Returns true if an item was completed
    bool processTurn();
    
    void draw(sf::RenderWindow& window);
    bool contains(const sf::Vector2f& point) const;
    
    // Utility methods
    static std::string getItemName(ProductionItem item);
    static std::string getBuildingName(BuildingType building);
};

} // namespace game

#endif // CITY_HPP