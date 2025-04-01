#include "PathFinder.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <unordered_set>

namespace game {

// Hex neighbor offsets for both even and odd columns
const std::vector<std::vector<sf::Vector2i>> HEX_NEIGHBORS = {
    // Even column offsets (even columns)
    {{1, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}, {1, 1}},
    // Odd column offsets (odd columns)
    {{1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}}
};

// Advanced heuristic for hex grid - uses hex distance
float PathFinder::hexDistance(const sf::Vector2i& a, const sf::Vector2i& b) {
    int dx = std::abs(a.x - b.x);
    int dy = std::abs(a.y - b.y);
    return std::max(dx, dy) + 0.5f * std::min(dx, dy);
}

// Check if a position is walkable
bool PathFinder::isWalkableTile(const std::vector<std::vector<Tile>>& tileMap, const sf::Vector2i& pos) {
    if (pos.x < 0 || pos.x >= static_cast<int>(tileMap.size()) || 
        pos.y < 0 || pos.y >= static_cast<int>(tileMap[0].size())) {
        return false;
    }
    
    TileType tileType = tileMap[pos.x][pos.y].type;
    return tileType != TileType::Water && 
           tileType != TileType::Mountain;
}

// Get valid neighboring tiles
std::vector<sf::Vector2i> PathFinder::getWalkableNeighbors(
    const std::vector<std::vector<Tile>>& tileMap,
    const sf::Vector2i& current) {
    
    std::vector<sf::Vector2i> walkableNeighbors;
    bool isEvenCol = current.x % 2 == 0;
    
    // Select appropriate neighbor offsets based on column parity
    const auto& offsets = HEX_NEIGHBORS[isEvenCol ? 0 : 1];
    
    for (const auto& offset : offsets) {
        sf::Vector2i neighbor(current.x + offset.x, current.y + offset.y);
        
        // Check if neighbor is walkable
        if (isWalkableTile(tileMap, neighbor)) {
            walkableNeighbors.push_back(neighbor);
        }
    }
    
    return walkableNeighbors;
}

// Calculate movement cost based on tile type
float PathFinder::getMovementCost(const std::vector<std::vector<Tile>>& tileMap, const sf::Vector2i& pos) {
    if (pos.x < 0 || pos.x >= static_cast<int>(tileMap.size()) || 
        pos.y < 0 || pos.y >= static_cast<int>(tileMap[0].size())) {
        return std::numeric_limits<float>::max();
    }
    
    TileType tileType = tileMap[pos.x][pos.y].type;
    switch (tileType) {
        case TileType::Plains: return 1.0f;
        case TileType::Forest: return 1.5f;
        case TileType::Hills: return 2.0f;
        case TileType::Water: return std::numeric_limits<float>::max();
        case TileType::Mountain: return std::numeric_limits<float>::max();
        default: return 1.0f;
    }
}

std::vector<sf::Vector2f> PathFinder::findPath(
    const std::vector<std::vector<Tile>>& tileMap,
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    int maxMovementPoints) {
    
    // Validate start and goal
    if (!isWalkableTile(tileMap, start) || !isWalkableTile(tileMap, goal)) {
        std::cout << "Invalid start or goal tile" << std::endl;
        return {};
    }
    
    // A* algorithm with hex grid specifics
    std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>> openSet;
    std::unordered_map<int, PathNode> allNodes;
    std::unordered_set<int> closedSet;
    
    // Hash function for tile coordinates
    auto coordToKey = [](const sf::Vector2i& pos) {
        return pos.x * 10000 + pos.y;
    };
    
    // Initialize start node
    PathNode startNode{
        start, 
        0.0f,  // Initial cost
        hexDistance(start, goal),  // Heuristic
        start  // Parent (self for start)
    };
    
    openSet.push(startNode);
    allNodes[coordToKey(start)] = startNode;
    
    while (!openSet.empty()) {
        auto current = openSet.top();
        openSet.pop();
        
        // Check if goal reached
        if (current.pos == goal) {
            return reconstructPath(tileMap, allNodes, coordToKey, start, goal);
        }
        
        // Mark as closed
        closedSet.insert(coordToKey(current.pos));
        
        // Explore neighbors
        for (const auto& neighborPos : getWalkableNeighbors(tileMap, current.pos)) {
            int neighborKey = coordToKey(neighborPos);
            
            // Skip if already closed
            if (closedSet.count(neighborKey)) continue;
            
            // Calculate movement cost
            float movementCost = getMovementCost(tileMap, neighborPos);
            float newCost = current.g_cost + movementCost;
            
            // Skip if exceeds movement points
            if (newCost > maxMovementPoints) continue;
            
            // Create neighbor node
            PathNode neighborNode{
                neighborPos,
                newCost,
                hexDistance(neighborPos, goal),
                current.pos
            };
            
            // Check if node is better than existing
            auto existingNode = allNodes.find(neighborKey);
            if (existingNode == allNodes.end() || newCost < existingNode->second.g_cost) {
                allNodes[neighborKey] = neighborNode;
                openSet.push(neighborNode);
            }
        }
    }
    
    // No path found
    std::cout << "No path found between tiles" << std::endl;
    return {};
}

std::vector<sf::Vector2f> PathFinder::reconstructPath(
    const std::vector<std::vector<Tile>>& tileMap,
    const std::unordered_map<int, PathNode>& nodes,
    std::function<int(const sf::Vector2i&)> coordToKey,
    const sf::Vector2i& start,
    const sf::Vector2i& goal) {
    
    std::vector<sf::Vector2i> tilePath;
    sf::Vector2i current = goal;
    
    // Reconstruct path by tracking parents
    while (current != start) {
        tilePath.push_back(current);
        
        auto it = nodes.find(coordToKey(current));
        if (it == nodes.end()) break;
        
        current = it->second.parent;
    }
    tilePath.push_back(start);
    
    // Reverse to get from start to goal
    std::reverse(tilePath.begin(), tilePath.end());
    
    // Convert to world coordinates (tile centers)
    std::vector<sf::Vector2f> worldPath;
    for (const auto& tilePos : tilePath) {
        worldPath.push_back(tileMap[tilePos.x][tilePos.y].center);
    }
    
    return worldPath;
}

} // namespace game