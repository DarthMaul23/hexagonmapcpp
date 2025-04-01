#include "Tile.hpp"
#include <cmath>

// Constants for hexagon dimensions
const float HEX_SIZE = 30.0f;
const float HEX_HEIGHT = HEX_SIZE * 2;
const float HEX_WIDTH = static_cast<float>(sqrt(3) * HEX_SIZE);

// Default constructor
HexTile::HexTile() : game::Tile() {
    // Initialize the SFML hexagon shape
    hexagon.setPointCount(6);
    hexagon.setFillColor(sf::Color::Green);
    hexagon.setOutlineThickness(1.0f);
    hexagon.setOutlineColor(sf::Color(100, 100, 100));
    
    // Set hexagon points
    for (int i = 0; i < 6; ++i) {
        float angle = i * 60.0f - 30.0f;
        float radian = angle * M_PI / 180.0f;
        float x = HEX_SIZE * cos(radian);
        float y = HEX_SIZE * sin(radian);
        hexagon.setPoint(i, sf::Vector2f(x, y));
    }
    
    // Initialize game::Tile members with default values
    type = TileType::Plains;
    stats.movementCost = 1.0f;
    stats.defense = 0;
    stats.food = 0;
    stats.production = 0;
    revealed = false;
    visible = false;
    
    // Initialize the position
    position = sf::Vector2f(0.0f, 0.0f);
    center = position;
    hexagon.setPosition(position);
}

// Constructor with parameters
HexTile::HexTile(const sf::Vector2f& pos, TileType tileType) : game::Tile() {
    // Initialize the SFML hexagon shape
    hexagon.setPointCount(6);
    hexagon.setOutlineThickness(1.0f);
    hexagon.setOutlineColor(sf::Color(100, 100, 100));
    
    // Set hexagon points
    for (int i = 0; i < 6; ++i) {
        float angle = i * 60.0f - 30.0f;
        float radian = angle * M_PI / 180.0f;
        float x = HEX_SIZE * cos(radian);
        float y = HEX_SIZE * sin(radian);
        hexagon.setPoint(i, sf::Vector2f(x, y));
    }
    
    // Initialize game::Tile members
    type = tileType;
    
    // Set tile stats based on type
    switch(tileType) {
        case TileType::Plains:
            stats.movementCost = 1.0f;
            stats.defense = 0;
            stats.food = 2;
            stats.production = 0;
            hexagon.setFillColor(sf::Color(180, 230, 130)); // Light green
            break;
        case TileType::Hills:
            stats.movementCost = 2.0f;
            stats.defense = 3;
            stats.food = 1;
            stats.production = 1;
            hexagon.setFillColor(sf::Color(200, 180, 120)); // Tan
            break;
        case TileType::Mountain:
            stats.movementCost = 3.0f;
            stats.defense = 5;
            stats.food = 0;
            stats.production = 2;
            hexagon.setFillColor(sf::Color(160, 160, 160)); // Gray
            break;
        case TileType::Forest:
            stats.movementCost = 2.0f;
            stats.defense = 2;
            stats.food = 1;
            stats.production = 1;
            hexagon.setFillColor(sf::Color(34, 139, 34)); // Forest green
            break;
        case TileType::Water:
            stats.movementCost = 4.0f;
            stats.defense = 0;
            stats.food = 1;
            stats.production = 0;
            hexagon.setFillColor(sf::Color(65, 105, 225)); // Blue
            break;
    }
    
    revealed = false;
    visible = false;
    
    // Set position
    setPosition(pos);
}

void HexTile::setPosition(const sf::Vector2f& pos) {
    position = pos;
    center = pos; // Update game::Tile's center property
    hexagon.setPosition(pos);
}

const sf::Vector2f& HexTile::getPosition() const {
    return position;
}

void HexTile::setType(TileType tileType) {
    // Update base class type
    type = tileType;
    
    // Update appearance based on the new type
    switch(tileType) {
        case TileType::Plains:
            hexagon.setFillColor(sf::Color(180, 230, 130)); // Light green
            break;
        case TileType::Hills:
            hexagon.setFillColor(sf::Color(200, 180, 120)); // Tan
            break;
        case TileType::Mountain:
            hexagon.setFillColor(sf::Color(160, 160, 160)); // Gray
            break;
        case TileType::Forest:
            hexagon.setFillColor(sf::Color(34, 139, 34)); // Forest green
            break;
        case TileType::Water:
            hexagon.setFillColor(sf::Color(65, 105, 225)); // Blue
            break;
    }
}

TileType HexTile::getType() const {
    return type; // Return the base class type
}

const TileStats& HexTile::getStats() const {
    return stats; // Return the base class stats
}

void HexTile::setStats(const TileStats& newStats) {
    stats = newStats; // Update the base class stats
}

void HexTile::draw(sf::RenderWindow& window) {
    // Only draw revealed tiles
    if (revealed) {
        // Fog of war effect for non-visible tiles
        if (!visible) {
            sf::ConvexShape fogHexagon = hexagon;
            sf::Color fogColor = hexagon.getFillColor();
            fogColor.a = 128; // Semi-transparent
            fogHexagon.setFillColor(fogColor);
            window.draw(fogHexagon);
        } else {
            window.draw(hexagon);
        }
    }
}

