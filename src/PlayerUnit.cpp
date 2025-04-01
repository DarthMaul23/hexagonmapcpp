#include "PlayerUnit.hpp"
#include <cmath>

PlayerUnit::PlayerUnit(const sf::Vector2f& pos, UnitType unitType) 
    : position(pos), type(unitType), isSelected(false), moveProgress(0.f), moveSpeed(2.0f) {
    
    // Initialize visual representation
    shape.setRadius(15.f);  // Size that fits well within hex tiles
    shape.setOrigin(sf::Vector2f(15.f, 15.f));  // Center the shape - SFML 3.0 syntax
    
    // Set color based on unit type
    sf::Color unitColor;
    switch(type) {
        case UnitType::Settler:
            unitColor = sf::Color(255, 255, 150);  // Light yellow
            break;
        case UnitType::Warrior:
            unitColor = sf::Color(255, 100, 100);  // Light red
            break;
        default:
            unitColor = sf::Color::White;
    }
    
    unitColor.a = 220;  // Slightly transparent when not selected
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
    // Only process a path with at least two points (start and end)
    if (newPath.size() < 2) {
        path.clear();
        return;
    }
    
    // Make a copy of the original path
    path = newPath;
    
    // Remove the first waypoint if it's the current position (to avoid stalling)
    float minDistanceThreshold = 0.5f;
    if (!path.empty()) {
        float dx = path[0].x - position.x;
        float dy = path[0].y - position.y;
        float distSquared = dx*dx + dy*dy;
        
        if (distSquared < minDistanceThreshold * minDistanceThreshold) {
            path.erase(path.begin());
        }
    }
    
    // If after cleaning there's only one point, clear the path
    if (path.size() < 2) {
        path.clear();
        return;
    }
    
    // Reset movement progress
    moveProgress = 0.0f;
}

void PlayerUnit::update(float deltaTime) {
    // If there's no path or just one point, there's nothing to update
    if (path.size() < 2) {
        return;
    }
    
    // Get current segment start and end points
    sf::Vector2f startPos = path[0];
    sf::Vector2f targetPos = path[1];
    
    // Calculate distance to the next position
    float dx = targetPos.x - position.x;
    float dy = targetPos.y - position.y;
    float distance = std::sqrt(dx*dx + dy*dy);
    
    // Movement threshold to consider a point "reached"
    float reachThreshold = 5.0f; // Larger threshold to prevent twerking
    
    // Move towards the next position
    if (distance > reachThreshold) {
        // Calculate direction vector
        sf::Vector2f direction = {dx / distance, dy / distance};
        
        // Move in the direction at the move speed
        position.x += direction.x * moveSpeed * deltaTime * 100.f;
        position.y += direction.y * moveSpeed * deltaTime * 100.f;
        
        // Update the shape position
        shape.setPosition(position);
    } else {
        // Consider the waypoint reached, remove it
        path.erase(path.begin());
        
        // If we've reached the last waypoint, clear the path
        if (path.size() < 2) {
            path.clear();
            return;
        }
        
        // If there's still a path, we want to smoothly transition to the next segment
        // Don't snap directly to the waypoint, but continue from current position
    }
}

void PlayerUnit::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool PlayerUnit::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

UnitType PlayerUnit::getType() const {
    return type;
}