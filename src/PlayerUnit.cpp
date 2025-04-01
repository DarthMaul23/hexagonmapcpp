#include "PlayerUnit.hpp"
#include <cmath>
#include <iostream>

PlayerUnit::PlayerUnit(const sf::Vector2f& pos, UnitType unitType) 
    : position(pos), 
      type(unitType), 
      isSelected(false), 
      moveProgress(0.f), 
      moveSpeed(100.0f),  // Adjusted for smoother movement
      isMoving(false), 
      currentPathIndex(0),
      movementPoints(100)  // Total movement points
{
    // Initialize visual representation with more distinctive styling
    shape.setRadius(15.f);  
    shape.setOrigin(sf::Vector2f(15.f, 15.f));
    
    // Color-coded unit types
    sf::Color unitColor;
    switch(type) {
        case UnitType::Settler:
            unitColor = sf::Color(255, 255, 150);  // Light yellow
            break;
        case UnitType::Warrior:
            unitColor = sf::Color(255, 100, 100);  // Light red
            break;
        case UnitType::Builder:
            unitColor = sf::Color(150, 255, 150);  // Light green
            break;
        default:
            unitColor = sf::Color::White;
    }
    
    // Slight transparency when not selected
    unitColor.a = 220;
    shape.setFillColor(unitColor);
    shape.setPosition(position);
}

void PlayerUnit::setPosition(const sf::Vector2f& pos) {
    position = pos;
    shape.setPosition(position);
}

const sf::Vector2f& PlayerUnit::getPosition() const {
    return position;
}

void PlayerUnit::setSelected(bool selected) {
    isSelected = selected;
    
    // Update appearance based on selection state
    sf::Color unitColor = shape.getFillColor();
    
    if (isSelected) {
        unitColor.a = 255;  // Full opacity when selected
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color::Yellow);
    } else {
        unitColor.a = 220;  // Slightly transparent when not selected
        shape.setOutlineThickness(0.f);
    }
    
    shape.setFillColor(unitColor);
}

bool PlayerUnit::getSelected() const {
    return isSelected;
}

void PlayerUnit::setPath(const std::vector<sf::Vector2f>& newPath) {
    // Validate path
    if (newPath.size() < 2) {
        path.clear();
        isMoving = false;
        currentPathIndex = 0;
        return;
    }
    
    // Copy path, removing initial position if very close
    path = newPath;
    
    // Remove first waypoint if it's essentially the current position
    float minDistanceThreshold = 5.0f;
    if (!path.empty()) {
        float dx = path[0].x - position.x;
        float dy = path[0].y - position.y;
        float distSquared = dx*dx + dy*dy;
        
        if (distSquared < minDistanceThreshold * minDistanceThreshold) {
            path.erase(path.begin());
        }
    }
    
    // Reset movement state
    if (!path.empty()) {
        isMoving = true;
        currentPathIndex = 0;
        movementPoints = 100;  // Reset movement points
    }
}

void PlayerUnit::update(float deltaTime) {
    // No path or not moving
    if (path.empty() || !isMoving) {
        return;
    }
    
    // Get current waypoint
    sf::Vector2f targetPos = path[currentPathIndex];
    
    // Calculate distance to the current waypoint
    float dx = targetPos.x - position.x;
    float dy = targetPos.y - position.y;
    float distance = std::sqrt(dx*dx + dy*dy);
    
    // Movement threshold
    float reachThreshold = 10.0f;
    
    // Move towards the next position
    if (distance > reachThreshold) {
        // Normalize direction vector
        sf::Vector2f direction = {dx / distance, dy / distance};
        
        // Move in the direction at the move speed
        float moveAmount = moveSpeed * deltaTime;
        position.x += direction.x * moveAmount;
        position.y += direction.y * moveAmount;
        
        // Reduce movement points
        movementPoints -= moveAmount;
        
        // Update shape position
        shape.setPosition(position);
    } else {
        // Waypoint reached
        currentPathIndex++;
        
        // Check if path is complete
        if (currentPathIndex >= path.size()) {
            path.clear();
            isMoving = false;
            currentPathIndex = 0;
        }
    }
}

void PlayerUnit::draw(sf::RenderWindow& window) {
    // Draw path if selected and has a path
    if (isSelected && !path.empty() && currentPathIndex < path.size()) {
        // Draw path segments
        for (size_t i = currentPathIndex; i < path.size() - 1; ++i) {
            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0].position = path[i];
            line[0].color = sf::Color(255, 255, 0, 128); // Semi-transparent yellow
            line[1].position = path[i+1];
            line[1].color = sf::Color(255, 255, 0, 128);
            window.draw(line);
            
            // Draw small waypoint markers
            sf::CircleShape waypoint(4.0f);
            waypoint.setFillColor(sf::Color(255, 255, 0, 200));
            waypoint.setOrigin(sf::Vector2f(4.0f, 4.0f));
            waypoint.setPosition(path[i]);
            window.draw(waypoint);
        }
        
        // Draw final waypoint
        if (!path.empty()) {
            sf::CircleShape finalWaypoint(6.0f);
            finalWaypoint.setFillColor(sf::Color(255, 200, 0, 200));
            finalWaypoint.setOrigin(sf::Vector2f(6.0f, 6.0f));
            finalWaypoint.setPosition(path.back());
            window.draw(finalWaypoint);
        }
    }
    
    // Draw the unit itself
    window.draw(shape);
}

bool PlayerUnit::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

UnitType PlayerUnit::getType() const {
    return type;
}

bool PlayerUnit::isOnPath() const {
    return isMoving && !path.empty();
}

float PlayerUnit::getMoveSpeed() const {
    return moveSpeed;
}

void PlayerUnit::setMoveSpeed(float speed) {
    moveSpeed = speed;
}

const std::vector<sf::Vector2f>& PlayerUnit::getPath() const {
    return path;
}

size_t PlayerUnit::getCurrentPathIndex() const {
    return currentPathIndex;
}

int PlayerUnit::getRemainingMovementPoints() const {
    return movementPoints;
}