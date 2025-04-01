#pragma once

#include "Tile.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <limits>

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
    // Main pathfinding function
    static std::vector<sf::Vector2f> findPath(
        const std::vector<std::vector<Tile>>& tileMap,
        const sf::Vector2i& start,
        const sf::Vector2i& goal,
        int maxMovementPoints);

private:
    // Heuristic function for hex grid distance
    static float hexDistance(const sf::Vector2i& a, const sf::Vector2i& b);
    
    // Check if a tile is walkable
    static bool isWalkableTile(
        const std::vector<std::vector<Tile>>& tileMap, 
        const sf::Vector2i& pos);
    
    // Get valid neighboring tiles
    static std::vector<sf::Vector2i> getWalkableNeighbors(
        const std::vector<std::vector<Tile>>& tileMap,
        const sf::Vector2i& current);
    
    // Calculate movement cost for a tile
    static float getMovementCost(
        const std::vector<std::vector<Tile>>& tileMap, 
        const sf::Vector2i& pos);
    
    // Reconstruct path from A* algorithm results
    static std::vector<sf::Vector2f> reconstructPath(
        const std::vector<std::vector<Tile>>& tileMap,
        const std::unordered_map<int, PathNode>& nodes,
        std::function<int(const sf::Vector2i&)> coordToKey,
        const sf::Vector2i& start,
        const sf::Vector2i& goal);
};

} // namespace game