#ifndef TILE_HPP
#define TILE_HPP

#include "GameEntities.hpp"
#include <SFML/Graphics.hpp>

// HexTile extends game::Tile with SFML rendering capabilities
class HexTile : public game::Tile {
private:
    sf::ConvexShape hexagon;
    sf::Vector2f position;

public:
    HexTile();
    HexTile(const sf::Vector2f& pos, TileType tileType);
    
    void setPosition(const sf::Vector2f& pos);
    const sf::Vector2f& getPosition() const;
    
    void setType(TileType tileType);
    TileType getType() const;
    
    const TileStats& getStats() const;
    void setStats(const TileStats& newStats);
    
    void draw(sf::RenderWindow& window);
};

#endif // TILE_HPP

