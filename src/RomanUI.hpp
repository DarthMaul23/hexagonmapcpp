#ifndef ROMAN_UI_HPP
#define ROMAN_UI_HPP

#include <SFML/Graphics.hpp>
#include "GameEntities.hpp"

namespace RomanUI {
    // Roman Empire inspired color palette
    namespace Colors {
        // Primary Roman Colors
        const sf::Color ROMAN_RED(139, 0, 0);           // Dark red for banners
        const sf::Color ROMAN_GOLD(218, 165, 32);       // Imperial gold
        const sf::Color ROMAN_PURPLE(75, 0, 130);       // Imperial purple
        const sf::Color MARBLE_WHITE(248, 248, 255);    // Marble white
        const sf::Color BRONZE(205, 127, 50);           // Bronze accents
        
        // UI Framework Colors
        const sf::Color SIDEBAR_BACKGROUND(101, 67, 33, 240);     // Dark brown sidebar
        const sf::Color PANEL_BACKGROUND(139, 119, 101, 230);     // Stone-like panels
        const sf::Color MODAL_BACKGROUND(160, 82, 45, 250);       // Modal backgrounds
        const sf::Color BUTTON_NORMAL(184, 134, 11);              // Golden buttons
        const sf::Color BUTTON_HOVER(218, 165, 32);               // Bright gold hover
        const sf::Color BUTTON_PRESSED(139, 105, 20);             // Darker gold pressed
        
        // Text Colors
        const sf::Color TEXT_PRIMARY(255, 248, 220);              // Cream text
        const sf::Color TEXT_SECONDARY(205, 133, 63);             // Sandy brown
        const sf::Color TEXT_ACCENT(218, 165, 32);                // Golden accent
        
        // Terrain (Roman lands)
        const sf::Color MEDITERRANEAN_BLUE(30, 144, 255);
        const sf::Color ROMAN_FIELDS(154, 205, 50);               // Olive green fields
        const sf::Color ROMAN_HILLS(160, 82, 45);                 // Brown hills
        const sf::Color ROMAN_ROADS(139, 69, 19);                 // Stone roads
    }
    
    // UI Layout Constants
    namespace Layout {
        const float SIDEBAR_WIDTH = 280.0f;
        const float PANEL_MARGIN = 10.0f;
        const float BUTTON_HEIGHT = 35.0f;
        const float MINIMAP_SIZE = 120.0f;
        const float MODAL_WIDTH = 600.0f;
        const float MODAL_HEIGHT = 450.0f;
        
        // 2.5D Visual Constants
        const float HEX_DEPTH = 8.0f;          // 3D depth effect for hexagons
        const float SPRITE_SCALE = 0.5f;       // Sprite scaling factor
        const float SHADOW_OFFSET = 3.0f;      // Shadow offset for depth
    }
    
    // Modal Types
    enum class ModalType {
        None,
        CharacterManagement,
        ArmyManagement,
        CityManagement,
        SkillsManagement,
        BuildingManagement,
        Barracks,
        Market,
        Temple
    };
    
    // Button creation functions
    sf::RectangleShape createRomanButton(float x, float y, float width, float height);
    sf::Text createRomanText(const std::string& text, const sf::Font& font, unsigned int size = 14);
    sf::RectangleShape createRomanPanel(float x, float y, float width, float height);
    sf::RectangleShape createModal(float x, float y, float width, float height);
    
    // Decorative elements
    void drawRomanBorder(sf::RenderWindow& window, float x, float y, float width, float height);
    void drawRomanColumn(sf::RenderWindow& window, float x, float y, float height);
    void drawEagleEmblem(sf::RenderWindow& window, float x, float y, float size);
    
    // Enhanced terrain for Roman theme
    void drawRomanHexagon(sf::RenderWindow& window, const game::Tile& tile, float hexSize);
    void drawRomanCity(sf::RenderWindow& window, const sf::Vector2f& position, 
                       const std::string& name, const sf::Font& font, bool isPlayerNear = false);
    
    // 2.5D Enhanced rendering functions
    void drawRomanHexagon2D5(sf::RenderWindow& window, const game::Tile& tile, float hexSize);
    void drawRomanCity2D5(sf::RenderWindow& window, const sf::Vector2f& position, 
                          const std::string& name, const sf::Font& font, bool isPlayerNear = false);
    void drawSpriteCharacter(sf::RenderWindow& window, const sf::Vector2f& position, 
                            const sf::Texture& spriteTexture, bool isSelected = false);
    
    // Enhanced visual effects
    void drawShadow(sf::RenderWindow& window, const sf::Vector2f& position, float size);
    void drawGlow(sf::RenderWindow& window, const sf::Vector2f& position, float radius, const sf::Color& color);
    
    // UI Components
    void drawSidebar(sf::RenderWindow& window, float windowWidth, float windowHeight, 
                     const sf::Font& font, const sf::Vector2f& playerPos);
    void drawMinimap(sf::RenderWindow& window, float x, float y, float size, 
                     const sf::Vector2f& playerPosition, const sf::Vector2f& mapSize);
    
    // Modal rendering
    void drawCharacterModal(sf::RenderWindow& window, const sf::Font& font);
    void drawArmyModal(sf::RenderWindow& window, const sf::Font& font);
    void drawCityModal(sf::RenderWindow& window, const sf::Font& font);
    void drawSkillsModal(sf::RenderWindow& window, const sf::Font& font);
    void drawBuildingModal(sf::RenderWindow& window, const sf::Font& font, const std::string& buildingType);
}

#endif // ROMAN_UI_HPP
