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
    
    // Production queue
    std::vector<ProductionItem> productionQueue;
    ProductionItem currentProduction;
    int productionProgress;
    int productionNeeded;
    
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
    
    void setProductionItem(ProductionItem item);
    ProductionItem getCurrentProduction() const { return currentProduction; }
    int getProductionProgress() const { return productionProgress; }
    int getProductionNeeded() const { return productionNeeded; }
    
    // Returns true if an item was completed
    bool processTurn();
    
    void draw(sf::RenderWindow& window);
    bool contains(const sf::Vector2f& point) const;
    
    // Utility
    static std::string getItemName(ProductionItem item);
};

} // namespace game

#endif // CITY_HPP