#pragma once

#include "GameEntities.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace game {

class PlayerUnit {
public:
    PlayerUnit(UnitType type, const sf::Vector2i& startPos);
    
    // Core functionality
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    // Movement
    void setPath(const std::vector<sf::Vector2i>& newPath);
    bool isMoving() const { return !path.empty(); }
    const sf::Vector2i& getPosition() const { return position; }
    
    // Selection
    void select();
    void deselect();
    bool isSelected() const { return selected; }
    bool containsPoint(const sf::Vector2f& point) const;
    
    // Movement points system
    int currentMovementPoints;
    int maxMovementPoints;
    void resetMovementPoints() { currentMovementPoints = maxMovementPoints; }
    
private:
    UnitType type;
    sf::Vector2i position;
    bool selected = false;
    
    // Movement
    std::vector<sf::Vector2i> path;
    float moveProgress = 0.f;
    static constexpr float MOVE_SPEED = 2.0f;  // Units per second
    
    // Visual representation
    sf::CircleShape shape;
    void updateVisuals();
    sf::Vector2f gridToWorld(const sf::Vector2i& gridPos) const;
};

} // namespace game

