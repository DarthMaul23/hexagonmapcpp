#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <memory>

// Forward declarations for game entities
class Game;
class Unit;
class GameCity;
class Hero;
class Army;
class Merchant;

// UI Component forward declarations
namespace ui {
    class ResourcePanel;
    class UnitInfoPanel;
    class CityPanel;
    class HeroPanel;
    class ArmyPanel;
    class MerchantPanel;
    class Modal;
    class Menu;
}

/**
 * UIManager class that coordinates all UI components.
 * Central controller for the UI system, handling component coordination,
 * event routing, view management, and game interface.
 */
class UIManager {
private:
    // Game reference
    Game* game;
    
    // UI components
    std::unique_ptr<ui::ResourcePanel> resourcePanel;
    std::unique_ptr<ui::UnitInfoPanel> unitInfoPanel;
    std::unique_ptr<ui::CityPanel> cityPanel;
    std::unique_ptr<ui::HeroPanel> heroPanel;
    std::unique_ptr<ui::ArmyPanel> armyPanel;
    std::unique_ptr<ui::MerchantPanel> merchantPanel;
    std::unique_ptr<ui::Modal> modal;
    std::unique_ptr<ui::Menu> menu;
    
    // Resources
    sf::Font font;
    
    // Views
    sf::View gameView;     // View for the game world
    sf::View uiView;       // View for the UI layer
    
    // State tracking
    bool inMenu;
    
public:
    // Constructor/Destructor
    UIManager(Game* game);
    ~UIManager();
    
    // Initialization
    bool initialize();
    
    // Drawing and Updates
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    
    // Event handling
    void handleMouseClick(sf::Vector2i mousePos, sf::RenderWindow& window);
    void handleMouseMove(sf::Vector2i mousePos, sf::RenderWindow& window);
    void handleMouseScroll(float delta, sf::Vector2i mousePos, sf::RenderWindow& window);
    void handleKeyPress(sf::Keyboard::Key key);
    
    // View management
    void setupViews(sf::RenderWindow& window);
    void updateViews(sf::RenderWindow& window);
    sf::Vector2f screenToWorld(const sf::Vector2i& screenPos, const sf::RenderWindow& window) const;
    
    // Game UI interaction methods
    void showUnitInfo(Unit* unit);
    void showCityPanel(GameCity* city);
    void showHeroPanel(Hero* hero);
    void showArmyPanel(Army* army);
    void showMerchantPanel(Merchant* merchant, Hero* hero);
    void showTileInfo(const std::string& title, const std::string& content);
    void updateResourceDisplay(int gold, int food, int production, int science);
    
    // Menu control
    void showMenu();
    void hideMenu();
    bool isInMenu() const { return inMenu; }
    
private:
    // Component initialization methods
    void initializeResourcePanel();
    void initializeUnitInfoPanel();
    void initializeCityPanel();
    void initializeHeroPanel();
    void initializeArmyPanel();
    void initializeMerchantPanel();
    void initializeModal();
    void initializeMenu();
    
    // Helper methods
    void closeAllPanels();
    bool isAnyPanelVisible() const;
};

#endif // UI_MANAGER_HPP
