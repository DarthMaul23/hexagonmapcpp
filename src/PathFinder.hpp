#pragma once

#include "Tile.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>

namespace game {

// Helper struct for A* node
struct PathNode {
    sf::Vector2i pos;
    float g_cost = 0.0f;  // Cost from start to current node
    float h_cost = 0.0f;  // Estimated cost from current node to goal
    float f_cost() const { return g_cost + h_cost; }
    sf::Vector2i parent;
    
    bool operator>(const PathNode& other) const {
        return f_cost() > other.f_cost();
    }
};

class PathFinder {
public:
    // Main pathfinding function - now returns world coordinates directly
    static std::vector<sf::Vector2f> findPath(
        const std::vector<std::vector<Tile>>& tileMap,
        const sf::Vector2i& start,
        const sf::Vector2i& goal,
        int maxMovementPoints);

private:
    // Heuristic function for A* (Manhattan distance)
    static float heuristic(const sf::Vector2i& a, const sf::Vector2i& b);
    
    // Get valid neighboring tiles
    static std::vector<sf::Vector2i> getNeighbors(
        const std::vector<std::vector<Tile>>& tileMap,
        const sf::Vector2i& current);
        
    // Check if position is within map bounds
    static bool isValidPosition(
        const std::vector<std::vector<Tile>>& tileMap,
        const sf::Vector2i& pos);
        
    // Reconstruct path from A* result
    static std::vector<sf::Vector2i> reconstructPath(
        const std::unordered_map<int, PathNode>& nodes,
        const sf::Vector2i& goal);
    
    // Smooth the path by adding intermediate points
    static std::vector<sf::Vector2f> smoothPath(
        const std::vector<sf::Vector2i>& path,
        const std::vector<std::vector<Tile>>& tileMap);
        
    // Hash function for sf::Vector2i to use with unordered_map
    static int positionToKey(const sf::Vector2i& pos) {
        return pos.x * 10000 + pos.y;  // Assumes map size < 10000
    }
};

} // namespace game