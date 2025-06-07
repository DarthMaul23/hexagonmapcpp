#ifndef HEROES_GRAPHICS_HPP
#define HEROES_GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "GameEntities.hpp"

namespace HeroesGraphics {
    // Heroes of Might and Magic 3 inspired color palette
    namespace Colors {
        const sf::Color GRASS_GREEN(102, 153, 51);
        const sf::Color DIRT_BROWN(139, 119, 101);
        const sf::Color MOUNTAIN_GRAY(105, 105, 105);
        const sf::Color FOREST_DARK_GREEN(34, 139, 34);
        const sf::Color WATER_BLUE(30, 144, 255);
        const sf::Color SWAMP_DARK_GREEN(85, 107, 47);
        const sf::Color DESERT_YELLOW(238, 203, 173);
        const sf::Color SNOW_WHITE(248, 248, 255);
        
        // UI Colors
        const sf::Color UI_BACKGROUND(101, 67, 33);
        const sf::Color UI_BORDER(139, 69, 19);
        const sf::Color UI_HIGHLIGHT(205, 133, 63);
        const sf::Color UI_TEXT(255, 248, 220);
        const sf::Color UI_BUTTON(160, 82, 45);
        const sf::Color UI_BUTTON_HOVER(210, 180, 140);
        
        // Resource Colors
        const sf::Color GOLD(255, 215, 0);
        const sf::Color WOOD(139, 69, 19);
        const sf::Color STONE(128, 128, 128);
        const sf::Color FOOD(255, 140, 0);
    }
    
    // Panel colors for UI consistency
    const sf::Color PANEL_BACKGROUND(101, 67, 33, 230);      // Semi-transparent brown
    const sf::Color PANEL_BORDER(139, 69, 19);               // Darker brown border
    const sf::Color SUBPANEL_BACKGROUND(85, 55, 28, 200);    // Darker sub-panel background
    
    // Texture patterns for different tile types
    sf::Color getTileColor(game::TileType type, bool isShaded = false);
    sf::Color getResourceColor(game::ResourceType type);
    
    // Create detailed hexagon with texture-like appearance
    void drawDetailedHexagon(sf::RenderWindow& window, const game::Tile& tile, float hexSize);
    
    // Create UI elements with HoMM3 style
    sf::RectangleShape createHeroesPanel(float x, float y, float width, float height);
    sf::Text createHeroesText(const std::string& text, const sf::Font& font, unsigned int size = 14);
    sf::RectangleShape createHeroesButton(float x, float y, float width, float height);
    
    // Draw resource icons
    void drawResourceIcon(sf::RenderWindow& window, game::ResourceType type, const sf::Vector2f& position, int amount, const sf::Font& font);
    
    // Enhanced unit/hero graphics
    void drawUnit(sf::RenderWindow& window, const sf::Vector2f& position, UnitType type, bool isSelected = false);
    void drawHero(sf::RenderWindow& window, const sf::Vector2f& position, bool isSelected = false);
    void drawCity(sf::RenderWindow& window, const sf::Vector2f& position, const std::string& name, const sf::Font& font);
    
    // UI enhancements
    void drawHeroesBorder(sf::RenderWindow& window, float x, float y, float width, float height);
    void drawMinimap(sf::RenderWindow& window, float x, float y, float size, const sf::Vector2f& playerPosition);
    void drawTerrainTransition(sf::RenderWindow& window, const game::Tile& tile, const std::vector<std::vector<game::Tile>>& tileMap, int x, int y, float hexSize);
    void drawResourceDeposit(sf::RenderWindow& window, const sf::Vector2f& position, game::ResourceType type, float hexSize);
}

#endif // HEROES_GRAPHICS_HPP
