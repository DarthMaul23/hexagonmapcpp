#include "UnitManager.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>

UnitManager::UnitManager() : selectedUnit(nullptr) {
    // Empty constructor
}

void UnitManager::addUnit(const sf::Vector2f& position, UnitType type) {
    units.push_back(PlayerUnit(position, type));
}

bool UnitManager::trySelectUnitAt(const sf::Vector2f& position) {
    // Deselect current unit
    deselectUnit();
    
    // Try to select a unit at the clicked position
    for (auto& unit : units) {
        if (unit.contains(position)) {
            std::cout << "Unit selected!" << std::endl;
            selectedUnit = &unit;
            selectedUnit->setSelected(true);
            return true;
        }
    }
    return false;
}

void UnitManager::tryMoveSelectedUnit(const sf::Vector2f& target, const std::vector<std::vector<game::Tile>>& tileMap) {
    if (!selectedUnit) {
        std::cout << "No unit selected!" << std::endl;
        return;
    }
    
    // Clear the current path
    currentPath.clear();
    
    // Convert start and target positions to tile grid coordinates
    sf::Vector2i startTilePos = worldPosToTilePos(selectedUnit->getPosition(), tileMap);
    sf::Vector2i targetTilePos = worldPosToTilePos(target, tileMap);
    
    // Check if target tile is valid for movement
    if (targetTilePos.x >= 0 && targetTilePos.x < tileMap.size() &&
        targetTilePos.y >= 0 && targetTilePos.y < tileMap[0].size()) {
        
        // Check if target tile is walkable
        game::TileType targetType = tileMap[targetTilePos.x][targetTilePos.y].type;
        if (targetType == game::TileType::Water || targetType == game::TileType::Mountain) {
            std::cout << "Cannot move to water or mountain tiles!" << std::endl;
            return;
        }
        
        // Use the PathFinder to find a path - now directly returns world coordinates
        int maxMovementPoints = 100; // Large enough for most paths, adjust as needed
        std::vector<sf::Vector2f> worldPath = game::PathFinder::findPath(
            tileMap, 
            startTilePos, 
            targetTilePos, 
            maxMovementPoints
        );
        
        if (worldPath.empty()) {
            std::cout << "No valid path found!" << std::endl;
            return;
        }
        
        // Store the path for visualization
        currentPath = worldPath;
        
        // Set the path for the unit to follow
        selectedUnit->setPath(worldPath);
        
        std::cout << "Moving unit along path with " << worldPath.size() << " waypoints" << std::endl;
    } else {
        std::cout << "Target position is outside the map boundaries!" << std::endl;
    }
}

void UnitManager::update(float deltaTime) {
    for (auto& unit : units) {
        unit.update(deltaTime);
    }
}

void UnitManager::draw(sf::RenderWindow& window) {
    // Draw the current path if one exists
    if (!currentPath.empty() && selectedUnit) {
        // Draw thicker lines connecting path points
        for (size_t i = 0; i < currentPath.size() - 1; ++i) {
            // Create a thicker line using multiple vertex arrays
            for (int offset = -2; offset <= 2; offset++) {
                sf::VertexArray line(sf::PrimitiveType::Lines, 2);
                
                // Calculate offset for thicker line
                sf::Vector2f dir = currentPath[i+1] - currentPath[i];
                float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
                sf::Vector2f perpendicular(-dir.y/len, dir.x/len);
                sf::Vector2f offsetVec = perpendicular * static_cast<float>(offset);
                
                // Set positions and colors
                line[0].position = currentPath[i] + offsetVec;
                line[0].color = sf::Color(255, 255, 0, 128); // Semi-transparent yellow
                
                line[1].position = currentPath[i+1] + offsetVec;
                line[1].color = sf::Color(255, 255, 0, 128);
                
                window.draw(line);
            }
        }
        
        // Draw larger dots at each waypoint
        for (const auto& point : currentPath) {
            sf::CircleShape waypoint(6.0f); // Larger radius
            waypoint.setOrigin(sf::Vector2f(6.0f, 6.0f));
            waypoint.setPosition(point);
            waypoint.setFillColor(sf::Color(255, 255, 0, 200)); // More opaque yellow
            waypoint.setOutlineColor(sf::Color::Black);
            waypoint.setOutlineThickness(1.0f);
            window.draw(waypoint);
        }
    }
    
    // Draw all units
    for (auto& unit : units) {
        unit.draw(window);
    }
}

void UnitManager::deselectUnit() {
    if (selectedUnit) {
        selectedUnit->setSelected(false);
        selectedUnit = nullptr;
        currentPath.clear(); // Clear the path when deselecting
    }
}

PlayerUnit* UnitManager::getSelectedUnit() {
    return selectedUnit;
}

void UnitManager::removeSelectedUnit() {
    if (!selectedUnit) return;
    
    // Find the unit in the vector
    for (auto it = units.begin(); it != units.end(); ++it) {
        if (&(*it) == selectedUnit) {
            // Remove it
            units.erase(it);
            selectedUnit = nullptr;
            currentPath.clear(); // Clear the path
            return;
        }
    }
}

sf::Vector2i UnitManager::worldPosToTilePos(const sf::Vector2f& worldPos, const std::vector<std::vector<game::Tile>>& tileMap) {
    // Find the closest tile center to the given world position
    float minDistance = std::numeric_limits<float>::max();
    sf::Vector2i closestTile(0, 0);
    
    for (size_t x = 0; x < tileMap.size(); ++x) {
        for (size_t y = 0; y < tileMap[x].size(); ++y) {
            float dx = worldPos.x - tileMap[x][y].center.x;
            float dy = worldPos.y - tileMap[x][y].center.y;
            float distSquared = dx*dx + dy*dy;
            
            if (distSquared < minDistance) {
                minDistance = distSquared;
                closestTile = sf::Vector2i(x, y);
            }
        }
    }
    
    return closestTile;
}

sf::Vector2f UnitManager::tilePosToWorldPos(const sf::Vector2i& tilePos, const std::vector<std::vector<game::Tile>>& tileMap) {
    if (tilePos.x >= 0 && tilePos.x < tileMap.size() &&
        tilePos.y >= 0 && tilePos.y < tileMap[0].size()) {
        return tileMap[tilePos.x][tilePos.y].center;
    }
    return sf::Vector2f(0, 0); // Fallback
}