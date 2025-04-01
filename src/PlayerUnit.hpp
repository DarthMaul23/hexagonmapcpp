#ifndef PLAYER_UNIT_HPP
#define PLAYER_UNIT_HPP

#include "GameEntities.hpp"
#include <SFML/Graphics.hpp>

class PlayerUnit {
private:
    sf::Vector2f position;
    UnitType type;
    bool isSelected;
    
    // Protected access to shape for derived classes
protected:
    sf::CircleShape& getShape() { return shape; }
    const sf::CircleShape& getShape() const { return shape; }

    sf::CircleShape shape;
    
    // Path-related members for movement
    std::vector<sf::Vector2f> path;
    float moveProgress;
    float moveSpeed;
    bool isMoving;
    size_t currentPathIndex;
    int movementPoints;
    
public:
    PlayerUnit(const sf::Vector2f& pos, UnitType unitType);
    
    void setPosition(const sf::Vector2f& pos);
    const sf::Vector2f& getPosition() const;
    
    void setSelected(bool selected);
    bool getSelected() const;
    
    void setPath(const std::vector<sf::Vector2f>& newPath);
    void update(float deltaTime);
    
    void draw(sf::RenderWindow& window);
    bool contains(const sf::Vector2f& point) const;
    
    UnitType getType() const;
    bool isOnPath() const;
    
    float getMoveSpeed() const;
    void setMoveSpeed(float speed);
    
    const std::vector<sf::Vector2f>& getPath() const;
    size_t getCurrentPathIndex() const;
    int getRemainingMovementPoints() const;
};

#endif // PLAYER_UNIT_HPP