#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include "GameEntities.hpp"
#include "PlayerUnit.hpp"
#include "Hero.hpp"
#include "Army.hpp"
#include "NPCMerchant.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// Forward declaration to avoid circular dependency
namespace game {
    class GameCity;
}

// Player resources structure
struct PlayerResources {
    int food = 100;
    int wood = 50;
    int stone = 25;
    int gold = 10;
};

// UI Manager class to handle all user interface elements
class UIManager {
private:
    // Font for all text elements
    sf::Font font;
    bool fontLoaded;
    
    // Views
    sf::View gameView;
    sf::View uiView;
    
    // Player resources
    PlayerResources playerResources;
    
    // Resource panel elements
    sf::RectangleShape resourcePanel;
    sf::Text resourceTitle;
    sf::Text foodText;
    sf::Text woodText;
    sf::Text stoneText;
    sf::Text goldText;
    
    // Selected unit panel
    sf::RectangleShape unitInfoPanel;
    sf::Text unitTitle;
    sf::Text unitTypeText;
    sf::Text unitHealthText;
    sf::Text unitMovementText;
    sf::Text unitActionText;
    
    // City management panel
    bool showCityPanel;
    sf::RectangleShape cityPanel;
    sf::Text cityTitle;
    sf::Text cityPopulation;
    sf::Text cityFood;
    sf::Text cityProduction;
    sf::Text cityGold;
    
    // City production buttons
    sf::RectangleShape settlerButton;
    sf::Text settlerText;
    sf::RectangleShape warriorButton;
    sf::Text warriorText;
    sf::RectangleShape builderButton;
    sf::Text builderText;
    sf::RectangleShape buildingButton;
    sf::Text buildingText;
    
    // Hero management panel
    bool showHeroPanel;
    sf::RectangleShape heroPanel;
    sf::Text heroTitle;
    sf::Text heroLevel;
    sf::Text heroExp;
    sf::Text heroGold;
    sf::Text heroAttributes;
    
    // Hero inventory section
    sf::RectangleShape inventoryPanel;
    sf::Text inventoryTitle;
    std::vector<sf::RectangleShape> inventorySlots;
    std::vector<sf::Text> inventoryTexts;
    
    // Hero skills section
    sf::RectangleShape skillPanel;
    sf::Text skillTitle;
    std::vector<sf::RectangleShape> skillSlots;
    std::vector<sf::Text> skillTexts;
    
    // Army management panel
    bool showArmyPanel;
    sf::RectangleShape armyPanel;
    sf::Text armyTitle;
    sf::Text armyCounts;
    std::vector<sf::RectangleShape> unitSlots;
    std::vector<sf::Text> unitTexts;
    
    // Merchant shop panel
    bool showMerchantPanel;
    sf::RectangleShape merchantPanel;
    sf::Text merchantTitle;
    sf::Text merchantDescription;
    
    // Merchant shop items section
    sf::RectangleShape shopItemsPanel;
    sf::Text shopItemsTitle;
    std::vector<sf::RectangleShape> shopItemSlots;
    std::vector<sf::Text> shopItemTexts;
    
    // Merchant shop units section
    sf::RectangleShape shopUnitsPanel;
    sf::Text shopUnitsTitle;
    std::vector<sf::RectangleShape> shopUnitSlots;
    std::vector<sf::Text> shopUnitTexts;
    
    // Button for returning to game from panels
    sf::RectangleShape backButton;
    sf::Text backText;
    
    // Buttons for toggling hero and army panels
    sf::RectangleShape heroButton;
    sf::Text heroButtonText;
    sf::RectangleShape armyButton;
    sf::Text armyButtonText;
    
    // Tile info modal
    bool showModal;
    sf::RectangleShape modalBackground;
    sf::Text modalTitle;
    sf::Text modalContent;
    sf::Text closeButton;
    
    // Menu elements
    sf::RectangleShape menuBackground;
    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::Text startText;
    
public:
    UIManager(unsigned int windowWidth, unsigned int windowHeight);
    ~UIManager();
    
    // Initialization
    bool initialize();
    
    // Helper methods made public for error fix
    void updateResourceDisplay();
    void updateUnitInfoDisplay(PlayerUnit* unit);
    void updateCityDisplay(game::GameCity* city);
    void updateHeroDisplay(Hero* hero);
    void updateArmyDisplay(Army* army);
    void updateMerchantDisplay(NPCMerchant* merchant);
    
    // View management
    sf::View& getGameView() { return gameView; }
    sf::View& getUIView() { return uiView; }
    
    // Resource management
    void updateResources(const PlayerResources& resources);
    PlayerResources& getResources() { return playerResources; }
    
    // Modal management
    void showTileInfo(const game::Tile& tile, int col, int row);
    void hideModal() { showModal = false; }
    bool isModalVisible() const { return showModal; }
    bool isCloseButtonClicked(const sf::Vector2f& position) const;
    
    // City panel management
    void showCityInfo(game::GameCity* city);
    void hideCityPanel() { showCityPanel = false; }
    bool isCityPanelVisible() const { return showCityPanel; }
    bool isSettlerButtonClicked(const sf::Vector2f& position) const;
    bool isWarriorButtonClicked(const sf::Vector2f& position) const;
    bool isBuilderButtonClicked(const sf::Vector2f& position) const;
    bool isBuildingButtonClicked(const sf::Vector2f& position) const;
    
    // Hero panel management
    void showHeroInfo(Hero* hero);
    void hideHeroPanel() { showHeroPanel = false; }
    bool isHeroPanelVisible() const { return showHeroPanel; }
    bool isInventorySlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    bool isSkillSlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    
    // Army panel management
    void showArmyInfo(Army* army);
    void hideArmyPanel() { showArmyPanel = false; }
    bool isArmyPanelVisible() const { return showArmyPanel; }
    bool isUnitSlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    
    // Merchant panel management
    void showMerchantInfo(NPCMerchant* merchant);
    void hideMerchantPanel() { showMerchantPanel = false; }
    bool isMerchantPanelVisible() const { return showMerchantPanel; }
    bool isShopItemClicked(const sf::Vector2f& position, int& itemIndex) const;
    bool isShopUnitClicked(const sf::Vector2f& position, int& unitIndex) const;
    
    // Back button management
    bool isBackButtonClicked(const sf::Vector2f& position) const;
    
    // Hero/Army toggle buttons
    bool isHeroButtonClicked(const sf::Vector2f& position) const;
    bool isArmyButtonClicked(const sf::Vector2f& position) const;
    
    // Menu management
    bool isStartButtonClicked(const sf::Vector2f& position) const;
    
    // Rendering methods
    void drawResourcePanel(sf::RenderWindow& window);
    void drawUnitInfo(sf::RenderWindow& window, PlayerUnit* selectedUnit);
    void drawCityInfo(sf::RenderWindow& window, game::GameCity* selectedCity);
    void drawHeroInfo(sf::RenderWindow& window, Hero* hero);
    void drawArmyInfo(sf::RenderWindow& window, Army* army);
    void drawMerchantInfo(sf::RenderWindow& window, NPCMerchant* merchant);
    void drawToggleButtons(sf::RenderWindow& window);
    void drawModal(sf::RenderWindow& window);
    void drawMenu(sf::RenderWindow& window);
    
    // Get font for other UI elements
    const sf::Font& getFont() const { return font; }
};

#endif // UI_MANAGER_HPP