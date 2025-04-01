#include "PathFinder.hpp"
#include <cmath>
#include <iostream>

namespace game {

// Array of hex neighbor offsets for even and odd columns
const std::vector<std::vector<sf::Vector2i>> HEX_NEIGHBORS = {
    // Even column offsets
    {{1, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}, {1, 1}},
    // Odd column offsets
    {{1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}}
};

float PathFinder::heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    // Use a more accurate hex grid distance for better path estimation
    int dx = std::abs(a.x - b.x);
    int dy = std::abs(a.y - b.y);
    // For hex grids, diagonal movement allows reducing one of the coordinates
    return std::max(dx, dy) + 0.5f * std::min(dx, dy);
}

bool PathFinder::isValidPosition(const std::vector<std::vector<Tile>>& tileMap, const sf::Vector2i& pos) {
    return pos.x >= 0 && pos.x < tileMap.size() &&
           pos.y >= 0 && pos.y < tileMap[0].size();
}

std::vector<sf::Vector2i> PathFinder::getNeighbors(
    const std::vector<std::vector<Tile>>& tileMap,
    const sf::Vector2i& current) {
    
    std::vector<sf::Vector2i> neighbors;
    bool isEvenCol = current.x % 2 == 0;
    const auto& offsets = HEX_NEIGHBORS[isEvenCol ? 0 : 1];
    
    for (const auto& offset : offsets) {
        sf::Vector2i neighbor(current.x + offset.x, current.y + offset.y);
        if (isValidPosition(tileMap, neighbor)) {
            // Check if the tile type is walkable (not Water or Mountain)
            TileType neighborType = tileMap[neighbor.x][neighbor.y].type;
            if (neighborType != TileType::Water && neighborType != TileType::Mountain) {
                neighbors.push_back(neighbor);
            }
        }
    }
    
    return neighbors;
}

// Function to smooth the path by adding intermediate points between sharp turns
std::vector<sf::Vector2f> PathFinder::smoothPath(
    const std::vector<sf::Vector2i>& path,
    const std::vector<std::vector<Tile>>& tileMap) {
    
    if (path.size() <= 1) {
        return {}; // Empty or single point path, nothing to smooth
    }
    
    std::vector<sf::Vector2f> smoothedPath;
    
    // Always include the first tile's center
    smoothedPath.push_back(tileMap[path[0].x][path[0].y].center);
    
    // For middle points in path (all except first and last)
    for (size_t i = 1; i < path.size() - 1; ++i) {
        sf::Vector2f currentCenter = tileMap[path[i].x][path[i].y].center;
        
        // Add the current tile center
        smoothedPath.push_back(currentCenter);
    }
    
    // Always include the last tile's center
    smoothedPath.push_back(tileMap[path.back().x][path.back().y].center);
    
    return smoothedPath;
}

std::vector<sf::Vector2i> PathFinder::reconstructPath(
    const std::unordered_map<int, PathNode>& nodes,
    const sf::Vector2i& goal) {
    
    std::vector<sf::Vector2i> path;
    sf::Vector2i current = goal;
    
    while (true) {
        path.push_back(current);
        auto it = nodes.find(positionToKey(current));
        if (it == nodes.end()) break;
        
        if (current == it->second.parent) break;
        current = it->second.parent;
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<sf::Vector2f> PathFinder::findPath(
    const std::vector<std::vector<Tile>>& tileMap,
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    int maxMovementPoints) {
    
    // Check if start and goal are valid positions
    if (!isValidPosition(tileMap, start) || !isValidPosition(tileMap, goal)) {
        std::cout << "Invalid start or goal position." << std::endl;
        return std::vector<sf::Vector2f>();
    }
    
    // Check if the goal is walkable
    if (tileMap[goal.x][goal.y].type == TileType::Water || 
        tileMap[goal.x][goal.y].type == TileType::Mountain) {
        std::cout << "Goal position is not walkable (water or mountain)." << std::endl;
        return std::vector<sf::Vector2f>();
    }
    
    // Priority queue for A* open set
    std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>> openSet;
    std::unordered_map<int, PathNode> allNodes;
    
    // Initialize start node
    PathNode startNode{start, 0.0f, heuristic(start, goal), start};
    openSet.push(startNode);
    allNodes[positionToKey(start)] = startNode;
    
    while (!openSet.empty()) {
        auto current = openSet.top();
        openSet.pop();
        
        // Goal reached
        if (current.pos == goal) {
            std::cout << "Path found!" << std::endl;
            auto path = reconstructPath(allNodes, goal);
            return smoothPath(path, tileMap);
        }
        
        // Get neighbors
        for (const auto& neighborPos : getNeighbors(tileMap, current.pos)) {
            // Calculate movement cost based on terrain type
            float movementCost = 1.0f; // Default cost
            
            TileType tileType = tileMap[neighborPos.x][neighborPos.y].type;
            if (tileType == TileType::Hills) {
                movementCost = 2.0f; // Hills are harder to traverse
            } else if (tileType == TileType::Forest) {
                movementCost = 1.5f; // Forests are slightly harder to traverse
            }
            
            float newCost = current.g_cost + movementCost;
            
            // Skip if exceeds movement points
            if (newCost > maxMovementPoints) continue;
            
            int neighborKey = positionToKey(neighborPos);
            auto existingNode = allNodes.find(neighborKey);
            
            if (existingNode == allNodes.end() || newCost < existingNode->second.g_cost) {
                // Create or update node
                PathNode newNode{
                    neighborPos,
                    newCost,
                    heuristic(neighborPos, goal),
                    current.pos
                };
                
                allNodes[neighborKey] = newNode;
                openSet.push(newNode);
            }
        }
    }
    
    // No path found
    std::cout << "No path found!" << std::endl;
    return std::vector<sf::Vector2f>();
}

} // namespace game