#pragma once

#include "PlayerUnit.hpp"
#include "GameEntities.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace game {

class UnitManager {
public:
    // Unit management
    void addUnit(UnitType type, const sf::Vector2i& position);
    void removeUnit(size_t index);
    void clear();

    // Selection
    bool trySelectUnitAt(const sf::Vector2f& worldPos);
    void deselectAll();

    // Movement
    bool tryMoveSelectedUnit(const sf::Vector2f& worldPos, 
                          const std::vector<std::vector<Tile>>& tileMap);

    // Update and render
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    std::vector<std::unique_ptr<PlayerUnit>> units;
    PlayerUnit* selectedUnit = nullptr;

    // Helper functions
    sf::Vector2i worldToGrid(const sf::Vector2f& worldPos) const;
    bool isValidPosition(const sf::Vector2i& pos) const;
    bool isUnitAtPosition(const sf::Vector2i& pos) const;
    std::vector<sf::Vector2i> findPath(const sf::Vector2i& start, 
                                     const sf::Vector2i& end,
                                     const std::vector<std::vector<Tile>>& tileMap) const;
};

} // namespace game

