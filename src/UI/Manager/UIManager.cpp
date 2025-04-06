#include "UIManager.hpp"
#include "Game.hpp"

// Include UI components
#include "../Components/ResourcePanel/ResourcePanel.hpp"
#include "../Components/UnitInfoPanel/UnitInfoPanel.hpp"
#include "../Components/CityPanel/CityPanel.hpp"
#include "../Components/HeroPanel/HeroPanel.hpp"
#include "../Components/ArmyPanel/ArmyPanel.hpp"
#include "../Components/MerchantPanel/MerchantPanel.hpp"
#include "../Components/Modal/Modal.hpp"
#include "../Components/Menu/Menu.hpp"

// Game entity includes
#include "Unit.hpp"
#include "City.hpp"
#include "Hero.hpp"
#include "Army.hpp"
#include "Merchant.hpp"

UIManager::UIManager(Game* game)
    : game(game),
      inMenu(true)
{
    // Initialize default views
    gameView = sf::View(sf::FloatRect(0, 0, 800, 600));
    uiView = sf::View(sf::FloatRect(0, 0, 800, 600));
}

UIManager::~UIManager()
{
    // Components are cleaned up automatically through unique_ptr
}

bool UIManager::initialize()
{
    // Load resources
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        return false;
    }
    
    // Initialize all UI components
    initializeResourcePanel();
    initializeUnitInfoPanel();
    initializeCityPanel();
    initializeHeroPanel();
    initializeArmyPanel();
    initializeMerchantPanel();
    initializeModal();
    initializeMenu();
    
    return true;
}

void UIManager::initializeResourcePanel()
{
    resourcePanel = std::make_unique<ui::ResourcePanel>(font);
    resourcePanel->initialize();
}

void UIManager::initializeUnitInfoPanel()
{
    unitInfoPanel = std::make_unique<ui::UnitInfoPanel>(font);
    unitInfoPanel->initialize();
}

void UIManager::initializeCityPanel()
{
    cityPanel = std::make_unique<ui::CityPanel>(font);
    cityPanel->initialize();
}

void UIManager::initializeHeroPanel()
{
    heroPanel = std::make_unique<ui::HeroPanel>(font);
    heroPanel->initialize();
}

void UIManager::initializeArmyPanel()
{
    armyPanel = std::make_unique<ui::ArmyPanel>(font);
    armyPanel->initialize();
}

void UIManager::initializeMerchantPanel()
{
    merchantPanel = std::make_unique<ui::MerchantPanel>(font);
    merchantPanel->initialize();
}

void UIManager::initializeModal()
{
    modal = std::make_unique<ui::Modal>(font);
    modal->initialize();
}

void UIManager::initializeMenu()
{
    menu = std::make_unique<ui::Menu>(font);
    menu->initialize();
}

void UIManager::setupViews(sf::RenderWindow& window)
{
    // Set up game view (world view) - this will be transformed by camera movement
    gameView.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    gameView.setCenter(0.f, 0.f);
    
    // Set up UI view (fixed to screen coordinates)
    uiView.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    uiView.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

void UIManager::updateViews(sf::RenderWindow& window)
{
    // Update UI view if window size changes
    uiView.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    uiView.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

sf::Vector2f UIManager::screenToWorld(const sf::Vector2i& screenPos, const sf::RenderWindow& window) const
{
    return window.mapPixelToCoords(screenPos, gameView);
}

void UIManager::draw(sf::RenderWindow& window)
{
    // Draw game elements (using game view)
    window.setView(gameView);
    // Game drawing is handled by Game class
    
    // Draw UI elements (using UI view)
    window.setView(uiView);
    
    // Draw menu if active
    if (inMenu) {
        menu->draw(window);
        return;
    }
    
    // Draw all UI components
    resourcePanel->draw(window);
    
    // Draw panels if visible
    if (unitInfoPanel->isShown()) {
        unitInfoPanel->draw(window);
    }
    
    if (cityPanel->isPanelVisible()) {
        cityPanel->draw(window);
    }
    
    if (heroPanel->isPanelVisible()) {
        heroPanel->draw(window);
    }
    
    if (armyPanel->isPanelVisible()) {
        armyPanel->draw(window);
    }
    
    if (merchantPanel->isPanelVisible()) {
        merchantPanel->draw(window);
    }
    
    // Draw modal if visible
    if (modal->isModalVisible()) {
        modal->draw(window);
    }
}

void UIManager::update(float deltaTime)
{
    if (inMenu) {
        menu->update(deltaTime);
        return;
    }
    
    // Update components that need per-frame updates
    resourcePanel->update(deltaTime);
    
    if (unitInfoPanel->isShown()) {
        unitInfoPanel->update(deltaTime);
    }
    
    if (cityPanel->isPanelVisible()) {
        cityPanel->update(deltaTime);
    }
    
    if (heroPanel->isPanelVisible()) {
        heroPanel->update(deltaTime);
    }
    
    if (armyPanel->isPanelVisible()) {
        armyPanel->update(deltaTime);
    }
    
    if (merchantPanel->isPanelVisible()) {
        merchantPanel->update(deltaTime);
    }
    
    if (modal->isModalVisible()) {
        modal->update(deltaTime);
    }
}

void UIManager::handleMouseClick(sf::Vector2i mousePos, sf::RenderWindow& window)
{
    // Convert to UI coordinates
    sf::Vector2f uiCoords = window.mapPixelToCoords(mousePos, uiView);
    
    // If in menu, check menu buttons
    if (inMenu) {
        if (menu->isStartButtonClicked(uiCoords)) {
            hideMenu();
            return;
        }
        
        if (menu->isQuitButtonClicked(uiCoords)) {
            window.close();
            return;
        }
        
        // Other menu buttons...
        return;
    }
    
    // Check if clicked on a modal first (modals have highest priority)
    if (modal->isModalVisible()) {
        if (modal->isCloseButtonClicked(uiCoords)) {
            modal->hideModal();
            return;
        }
        // Modal is open, ignore other clicks
        return;
    }
    
    // Check if clicked on city panel
    if (cityPanel->isPanelVisible()) {
        if (cityPanel->isBackButtonClicked(uiCoords)) {
            cityPanel->hidePanel();
            return;
        }
        
        if (cityPanel->isSettlerButtonClicked(uiCoords)) {
            // Handle settler production
            // game->startSettlerProduction(cityPanel->getSelectedCity());
            return;
        }
        
        if (cityPanel->isWarriorButtonClicked(uiCoords)) {
            // Handle warrior production
            return;
        }
        
        // Other city panel buttons...
        return;
    }
    
    // Check if clicked on hero panel
    if (heroPanel->isPanelVisible()) {
        if (heroPanel->isBackButtonClicked(uiCoords)) {
            heroPanel->hidePanel();
            return;
        }
        
        int slotIndex = -1;
        if (heroPanel->isInventorySlotClicked(uiCoords, slotIndex)) {
            // Handle inventory slot click
            return;
        }
        
        if (heroPanel->isSkillSlotClicked(uiCoords, slotIndex)) {
            // Handle skill slot click
            return;
        }
        
        return;
    }
    
    // Check if clicked on army panel
    if (armyPanel->isPanelVisible()) {
        if (armyPanel->isBackButtonClicked(uiCoords)) {
            armyPanel->hidePanel();
            return;
        }
        
        int slotIndex = -1;
        if (armyPanel->isUnitSlotClicked(uiCoords, slotIndex)) {
            // Handle unit slot click
            return;
        }
        
        return;
    }
    
    // Check if clicked on merchant panel
    if (merchantPanel->isPanelVisible()) {
        if (merchantPanel->isBackButtonClicked(uiCoords)) {
            merchantPanel->hidePanel();
            return;
        }
        
        if (merchantPanel->isPurchaseButtonClicked(uiCoords)) {
            // Handle purchase
            return;
        }
        
        if (merchantPanel->isSellButtonClicked(uiCoords)) {
            // Handle sell
            return;
        }
        
        int slotIndex = -1;
        if (merchantPanel->isItemSlotClicked(uiCoords, slotIndex)) {
            // Handle item selection
            return;
        }
        
        if (merchantPanel->isUnitSlotClicked(uiCoords, slotIndex)) {
            // Handle unit selection
            return;
        }
        
        return;
    }
    
    // If no UI panel is active, pass click to game for map interaction
    if (!isAnyPanelVisible()) {
        sf::Vector2f worldCoords = screenToWorld(mousePos, window);
        // Forward to game for map handling
        // game->handleMapClick(worldCoords);
    }
}

void UIManager::handleMouseMove(sf::Vector2i mousePos, sf::RenderWindow& window)
{
    // Convert to world coordinates for game logic
    sf::Vector2f worldCoords = screenToWorld(mousePos, window);
    
    // Forward to game for hover effects on map
    // if (!isAnyPanelVisible() && !inMenu) {
    //     game->handleMapHover(worldCoords);
    // }
    
    // No specific UI hover handling implemented yet
}

void UIManager::handleMouseScroll(float delta, sf::Vector2i mousePos, sf::RenderWindow& window)
{
    // Ignore scrolling if a panel is open
    if (isAnyPanelVisible() || inMenu) {
        return;
    }
    
    // Apply zoom to game view (camera zoom)
    float zoomFactor = 1.f + delta * 0.1f;
    gameView.zoom(zoomFactor);
}

void UIManager::handleKeyPress(sf::Keyboard::Key key)
{
    // Handle escape key to close panels or show menu
    if (key == sf::Keyboard::Escape) {
        if (modal->isModalVisible()) {
            modal->hideModal();
            return;
        }
        
        if (cityPanel->isPanelVisible()) {
            cityPanel->hidePanel();
            return;
        }
        
        if (heroPanel->isPanelVisible()) {
            heroPanel->hidePanel();
            return;
        }
        
        if (armyPanel->isPanelVisible()) {
            armyPanel->hidePanel();
            return;
        }
        
        if (merchantPanel->isPanelVisible()) {
            merchantPanel->hidePanel();
            return;
        }
        
        // If no panels are open, show the menu
        if (!isAnyPanelVisible() && !inMenu) {
            showMenu();
            return;
        }
    }
    
    // Handle M key to toggle menu
    if (key == sf::Keyboard::M) {
        if (inMenu) {
            hideMenu();
        } else if (!isAnyPanelVisible()) {
            showMenu();
        }
    }
}

void UIManager::showUnitInfo(Unit* unit)
{
    if (!unit || inMenu) return;
    
    closeAllPanels();
    unitInfoPanel->showInfo(unit);
}

void UIManager::showCityPanel(GameCity* city)
{
    if (!city || inMenu) return;
    
    closeAllPanels();
    cityPanel->showCityInfo(city);
}

void UIManager::showHeroPanel(Hero* hero)
{
    if (!hero || inMenu) return;
    
    closeAllPanels();
    heroPanel->showHeroInfo(hero);
}

void UIManager::showArmyPanel(Army* army)
{
    if (!army || inMenu) return;
    
    closeAllPanels();
    armyPanel->showArmyInfo(army);
}

void UIManager::showMerchantPanel(Merchant* merchant, Hero* hero)
{
    if (!merchant || !hero || inMenu) return;
    
    closeAllPanels();
    merchantPanel->showMerchantShop(merchant, hero);
}

void UIManager::showTileInfo(const std::string& title, const std::string& content)
{
    if (inMenu) return;
    
    modal->showInfo(title, content);
}

void UIManager::updateResourceDisplay(int gold, int food, int production, int science)
{
    resourcePanel->updateResources(gold, food, production, science);
}

void UIManager::showMenu()
{
    closeAllPanels();
    menu->showMainMenu();
    inMenu = true;
}

void UIManager::hideMenu()
{
    menu->hideMenu();
    inMenu = false;
}

void UIManager::closeAllPanels()
{
    // Hide all panels
    unitInfoPanel->hide();
    cityPanel->hidePanel();
    heroPanel->hidePanel();
    armyPanel->hidePanel();
    merchantPanel->hidePanel();
    modal->hideModal();
}

bool UIManager::isAnyPanelVisible() const
{
    return unitInfoPanel->isShown() ||
           cityPanel->isPanelVisible() ||
           heroPanel->isPanelVisible() ||
           armyPanel->isPanelVisible() ||
           merchantPanel->isPanelVisible() ||
           modal->isModalVisible();
}
