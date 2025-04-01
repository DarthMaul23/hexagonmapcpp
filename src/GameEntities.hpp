#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace game {

// Resource types
enum class ResourceType {
    Food,
    Wood,
    Stone,
    Gold
};

// Resource quantity structure
struct Resource {
    ResourceType type;
    int quantity = 0;
};

// Tile resource properties
struct TileResource {
    bool hasResource = false;
    ResourceType resourceType;
    int baseProduction = 0;
};

// Tile statistics
struct TileStats {
    float movementCost = 1.0f;
    int defense = 0;
    int food = 0;
    int production = 0;
};

// Tile types
enum class TileType {
    Plains,
    Hills,
    Mountain,
    Forest,
    Water
};

// Complete tile structure
struct Tile {
    TileType type = TileType::Plains;
    TileStats stats;
    TileResource resource;
    sf::Vector2f center;    // Pixel coordinates for the center of the hexagon
    bool revealed = false;
    bool visible = false;
    
    // Base resource production based on tile type
    Resource getBaseProduction() const {
        Resource baseResource;
        switch(type) {
            case TileType::Water:
                baseResource.type = ResourceType::Food;
                baseResource.quantity = 1;
                break;
            case TileType::Mountain:
                baseResource.type = ResourceType::Stone;
                baseResource.quantity = 1;
                break;
            case TileType::Forest:
                baseResource.type = ResourceType::Wood;
                baseResource.quantity = 2;
                break;
            case TileType::Plains:
                baseResource.type = ResourceType::Food;
                baseResource.quantity = 2;
                break;
            case TileType::Hills:
                baseResource.type = ResourceType::Stone;
                baseResource.quantity = 1;
                break;
        }
        return baseResource;
    }
};

struct InventoryItem {
    std::string name;
    std::string description;
    int value;
    bool isEquipped;

    InventoryItem(const std::string& n, const std::string& desc, int val)
        : name(n), description(desc), value(val), isEquipped(false) {}
};

// Unit types
enum class UnitType {
    Settler,
    Warrior,
    Builder
};

// City structure
struct City {
    std::string name;
    sf::Vector2i position;  // Grid position
    Resource resources[4];  // Array to hold quantities of each resource type
};
} // namespace game

// Use the game namespace in the global scope
using game::TileStats;
using game::TileType;
using game::UnitType;
using game::Tile;
using game::ResourceType;

#endif // GAME_ENTITIES_HPP
