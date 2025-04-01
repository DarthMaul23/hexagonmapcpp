#ifndef UNIT_MANAGER_HPP
#define UNIT_MANAGER_HPP

#include "GameEntities.hpp"
#include "PlayerUnit.hpp"
#include "PathFinder.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class UnitManager {
private:
    std::vector<PlayerUnit> units;
    PlayerUnit* selectedUnit;
    
    // Store current path for visualization
    std::vector<sf::Vector2f> currentPath;
    
    // Helper function to convert screen/world position to tile grid position
    sf::Vector2i worldPosToTilePos(const sf::Vector2f& worldPos, const std::vector<std::vector<game::Tile>>& tileMap);
    
    // Helper function to convert tile grid position to world position
    sf::Vector2f tilePosToWorldPos(const sf::Vector2i& tilePos, const std::vector<std::vector<game::Tile>>& tileMap);
    
public:
    UnitManager();
    
    void addUnit(const sf::Vector2f& position, UnitType type);
    
    bool trySelectUnitAt(const sf::Vector2f& position);
    void tryMoveSelectedUnit(const sf::Vector2f& target, const std::vector<std::vector<game::Tile>>& tileMap);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    void deselectUnit();
    PlayerUnit* getSelectedUnit();
    
    void removeSelectedUnit();
};

#endif // UNIT_MANAGER_HPP