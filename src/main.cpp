#include "GameEntities.hpp"
#include "PlayerUnit.hpp"
#include "UIManager.hpp"
#include "CityManager.hpp"
#include "UnitManager.hpp"
#include "PathFinder.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <optional> // Needed for std::optional in SFML 3.0
#include <limits>  // For std::numeric_limits

// Use the game namespace if desired (be cautious with duplicate using declarations)
using namespace game;

// Constants
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;
const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 30;
const float HEX_SIZE = 30.f;
const float HEX_WIDTH = std::sqrt(3.f) * HEX_SIZE;
const float HEX_HEIGHT = 2.0f * HEX_SIZE;

// Global function to convert screen coordinates to tile coordinates.
// This uses axial coordinates and rounds to the nearest hex.
sf::Vector2i screenToTile(const sf::Vector2f& screenPos) {
    float q = (screenPos.x * std::sqrt(3.f) / 3.f - screenPos.y / 3.f) / HEX_SIZE;
    float r = (screenPos.y * 2.f / 3.f) / HEX_SIZE;
    
    float x = q;
    float z = r;
    float y = -x - z;
    
    int rx = std::round(x);
    int ry = std::round(y);
    int rz = std::round(z);
    
    float x_diff = std::abs(rx - x);
    float y_diff = std::abs(ry - y);
    float z_diff = std::abs(rz - z);
    
    if (x_diff > y_diff && x_diff > z_diff) {
        rx = -ry - rz;
    } else if (y_diff > z_diff) {
        ry = -rx - rz;
    } else {
        rz = -rx - ry;
    }
    
    return sf::Vector2i(rx, rz);
}

// Creates a pointy-topped hexagon shape given a center.
sf::ConvexShape createPointyHex(const sf::Vector2f& center) {
    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);
    for (int i = 0; i < 6; ++i) {
        float angle_rad = M_PI / 180.f * (60 * i + 30);
        float x = center.x + HEX_SIZE * std::cos(angle_rad);
        float y = center.y + HEX_SIZE * std::sin(angle_rad);
        hexagon.setPoint(i, sf::Vector2f(x, y));
    }
    return hexagon;
}

// Forward declaration for a function to draw a tile
void drawHexagon(sf::RenderWindow& window, const Tile& tile) {
    sf::ConvexShape hex = createPointyHex(tile.center);
    
    // Set color based on tile type
    switch (tile.type) {
        case TileType::Plains:
            hex.setFillColor(sf::Color(180, 230, 130)); // Light green
            break;
        case TileType::Hills:
            hex.setFillColor(sf::Color(200, 180, 120)); // Tan
            break;
        case TileType::Mountain:
            hex.setFillColor(sf::Color(160, 160, 160)); // Gray
            break;
        case TileType::Forest:
            hex.setFillColor(sf::Color(34, 139, 34)); // Forest green
            break;
        case TileType::Water:
            hex.setFillColor(sf::Color(65, 105, 225)); // Blue
            break;
    }
    
    hex.setOutlineThickness(1.0f);
    hex.setOutlineColor(sf::Color(100, 100, 100));
    
    window.draw(hex);
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create the main window using sf::VideoMode with a Vector2u.
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Hexagon Map Game");
    window.setFramerateLimit(60);

    // Create the UI Manager
    UIManager uiManager(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!uiManager.initialize()) {
        std::cerr << "Failed to initialize UI Manager!" << std::endl;
        return -1;
    }

    // Create game and UI views
    sf::View& gameView = uiManager.getGameView();
    sf::View& uiView = uiManager.getUIView();
    window.setView(gameView);

    // Create the tile map
    std::vector<std::vector<Tile>> tileMap(MAP_WIDTH, std::vector<Tile>(MAP_HEIGHT));

    // Initialize the UnitManager and CityManager
    UnitManager unitManager;
    CityManager cityManager;
    
    // Initialize the GameManager for hero, army, and merchants
    GameManager gameManager;
    
    // Set up each tile's center and randomly assign a tile type.
    // Using an odd-r layout for zig-zag tiling:
    for (int r = 0; r < MAP_HEIGHT; ++r) {
        for (int q = 0; q < MAP_WIDTH; ++q) {
            // Compute pixel positions
            float xPos = HEX_SIZE * std::sqrt(3.f) * (q + 0.5f * (r % 2));
            float yPos = HEX_SIZE * 1.5f * r;
            tileMap[q][r].center = sf::Vector2f(xPos, yPos);

            // Assign tile type randomly (example)
            int tileRand = std::rand() % 100;
            if (tileRand < 60) {
                tileMap[q][r].type = TileType::Plains;
                tileMap[q][r].stats.movementCost = 1.0f;
            } else if (tileRand < 75) {
                tileMap[q][r].type = TileType::Forest;
                tileMap[q][r].stats.movementCost = 1.5f;
            } else if (tileRand < 85) {
                tileMap[q][r].type = TileType::Hills;
                tileMap[q][r].stats.movementCost = 2.0f;
            } else if (tileRand < 95) {
                tileMap[q][r].type = TileType::Water;
                tileMap[q][r].stats.movementCost = 3.0f;
            } else {
                tileMap[q][r].type = TileType::Mountain;
                tileMap[q][r].stats.movementCost = 4.0f;
            }
        }
    }

    // Place units at specific tile positions
    sf::Vector2f initialPos = tileMap[5][5].center;
    
    // Place basic units with the UnitManager
    unitManager.addUnit(initialPos, UnitType::Settler);
    unitManager.addUnit(tileMap[7][5].center, UnitType::Warrior);
    
    // Initialize the game manager and hero at the starting position
    gameManager.initialize(initialPos, uiManager.getFont());

    // Add pre-generated cities at strategic locations using the same coordinate system
    cityManager.addCity(tileMap[10][10].center);
    std::cout << "Added city 1 at position: " << tileMap[10][10].center.x << ", " << tileMap[10][10].center.y << std::endl;

    cityManager.addCity(tileMap[15][8].center);
    std::cout << "Added city 2 at position: " << tileMap[15][8].center.x << ", " << tileMap[15][8].center.y << std::endl;

    cityManager.addCity(tileMap[20][15].center);
    std::cout << "Added city 3 at position: " << tileMap[20][15].center.x << ", " << tileMap[20][15].center.y << std::endl;

    cityManager.addCity(tileMap[12][20].center);
    std::cout << "Added city 4 at position: " << tileMap[12][20].center.x << ", " << tileMap[12][20].center.y << std::endl;

    // Print the total number of cities
    std::cout << "Total cities: " << cityManager.getCityCount() << std::endl;

    // Define game state.
    enum class GameState { 
        MainMenu, 
        Playing, 
        CityView,
        HeroView,
        ArmyView,
        MerchantView
    };
    GameState gameState = GameState::MainMenu;  // Start with menu

    // View movement variables.
    sf::Vector2f viewVelocity(0.f, 0.f);
    const float VIEW_SPEED = 500.f;

    // Variables for tile selection
    int selectedCol = -1, selectedRow = -1;

    // Game timer for turns
    sf::Clock gameClock;
    const float TURN_LENGTH = 10.0f;  // 10 seconds per turn
    float turnTimer = TURN_LENGTH;

    sf::Clock clock;
    // SFML 3.0: pollEvent returns a std::optional<sf::Event>
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Update turn timer if in playing state
        if (gameState == GameState::Playing) {
            turnTimer -= deltaTime;
            if (turnTimer <= 0.0f) {
                // Process turn for cities
                cityManager.update();
                
                // Reset timer
                turnTimer = TURN_LENGTH;
            }
        }
        
        // Update game manager
        gameManager.update(deltaTime);

        std::optional<sf::Event> eventOpt;
        while ((eventOpt = window.pollEvent())) {
            sf::Event& event = *eventOpt;
            
            // SFML 3.0 event handling
            if (auto closeEvent = event.getIf<sf::Event::Closed>()) {
                window.close();
            }
            else if (auto mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    if (gameState == GameState::MainMenu) {
                        // Check if start button was clicked
                        sf::Vector2f menuPos = window.mapPixelToCoords(pixelPos, uiView);
                        if (uiManager.isStartButtonClicked(menuPos)) {
                            gameState = GameState::Playing;
                            window.setView(gameView);
                        }
                    }
                    else if (gameState == GameState::Playing) {
                        // Handle UI interactions
                        sf::Vector2f uiPos = window.mapPixelToCoords(pixelPos, uiView);
                        
                        // Check for UI button clicks
                        if (uiManager.isHeroButtonClicked(uiPos)) {
                            if (gameManager.getPlayerHero()) {
                                uiManager.showHeroInfo(gameManager.getPlayerHero());
                                gameState = GameState::HeroView;
                            }
                        }
                        else if (uiManager.isArmyButtonClicked(uiPos)) {
                            if (gameManager.getPlayerArmy()) {
                                uiManager.showArmyInfo(gameManager.getPlayerArmy());
                                gameState = GameState::ArmyView;
                            }
                        }
                        else if (uiManager.isModalVisible()) {
                            // Check if the close button was clicked using the UI view.
                            if (uiManager.isCloseButtonClicked(uiPos)) {
                                uiManager.hideModal();
                            }
                        }
                        else {
                            // Check for world object interactions
                            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, gameView);
                            
                            // Debug output for clicking
                            std::cout << "Click at world position: " << worldPos.x << ", " << worldPos.y << std::endl;
                            
                            // Try to select the hero or a merchant
                            if (gameManager.trySelectEntityAt(worldPos)) {
                                if (gameManager.isMerchantSelected()) {
                                    uiManager.showMerchantInfo(gameManager.getSelectedMerchant());
                                    gameState = GameState::MerchantView;
                                }
                            }
                            // If not selecting hero/merchant, try to select a unit
                            else if (!unitManager.trySelectUnitAt(worldPos)) {
                                // Try to select a city
                                if (cityManager.selectCityAt(worldPos)) {
                                    GameCity* selectedCity = cityManager.getSelectedCity();
                                    std::cout << "Selected city: " << selectedCity->getName() << std::endl;
                                    uiManager.showCityInfo(selectedCity);
                                    gameState = GameState::CityView;
                                } else {
                                    // If no unit or city, check if a tile was clicked
                                    sf::Vector2i tilePos = screenToTile(worldPos);
                                    if (tilePos.x >= 0 && tilePos.x < MAP_WIDTH &&
                                        tilePos.y >= 0 && tilePos.y < MAP_HEIGHT) {
                                        selectedCol = tilePos.x;
                                        selectedRow = tilePos.y;
                                        uiManager.showTileInfo(tileMap[selectedCol][selectedRow], selectedCol, selectedRow);
                                    }
                                }
                            }
                        }
                    }
                    else if (gameState == GameState::CityView) {
                        sf::Vector2f uiPos = window.mapPixelToCoords(pixelPos, uiView);
                        if (uiManager.isCloseButtonClicked(uiPos)) {
                            uiManager.hideCityPanel();
                            cityManager.deselectCity();
                            gameState = GameState::Playing;
                        }
                        else if (uiManager.isSettlerButtonClicked(uiPos)) {
                            if (cityManager.getSelectedCity()) {
                                cityManager.getSelectedCity()->setProductionItem(GameCity::ProductionItem::SETTLER);
                            }
                        }
                        else if (uiManager.isWarriorButtonClicked(uiPos)) {
                            if (cityManager.getSelectedCity()) {
                                cityManager.getSelectedCity()->setProductionItem(GameCity::ProductionItem::WARRIOR);
                            }
                        }
                        else if (uiManager.isBuilderButtonClicked(uiPos)) {
                            if (cityManager.getSelectedCity()) {
                                cityManager.getSelectedCity()->setProductionItem(GameCity::ProductionItem::BUILDER);
                            }
                        }
                    }
                    else if (gameState == GameState::HeroView) {
                        sf::Vector2f uiPos = window.mapPixelToCoords(pixelPos, uiView);
                        if (uiManager.isBackButtonClicked(uiPos)) {
                            uiManager.hideHeroPanel();
                            gameState = GameState::Playing;
                        } else {
                            // Check for inventory slot clicks
                            int slotIndex = -1;
                            if (uiManager.isInventorySlotClicked(uiPos, slotIndex)) {
                                Hero* hero = gameManager.getPlayerHero();
                                if (hero && slotIndex >= 0 && slotIndex < hero->getInventory().size()) {
                                    // Toggle equipped state
                                    bool isEquipped = hero->getInventory()[slotIndex].isEquipped;
                                    hero->equipItem(slotIndex, !isEquipped);
                                    uiManager.updateHeroDisplay(hero);
                                }
                            }
                            
                            // Check for skill slot clicks
                            if (uiManager.isSkillSlotClicked(uiPos, slotIndex)) {
                                Hero* hero = gameManager.getPlayerHero();
                                if (hero && slotIndex >= 0 && slotIndex < hero->getSkills().size()) {
                                    // Upgrade skill if possible
                                    hero->upgradeSkill(slotIndex);
                                    uiManager.updateHeroDisplay(hero);
                                }
                            }
                        }
                    }
                    else if (gameState == GameState::ArmyView) {
                        sf::Vector2f uiPos = window.mapPixelToCoords(pixelPos, uiView);
                        if (uiManager.isBackButtonClicked(uiPos)) {
                            uiManager.hideArmyPanel();
                            gameState = GameState::Playing;
                        }
                    }
                    else if (gameState == GameState::MerchantView) {
                        sf::Vector2f uiPos = window.mapPixelToCoords(pixelPos, uiView);
                        if (uiManager.isBackButtonClicked(uiPos)) {
                            uiManager.hideMerchantPanel();
                            gameManager.deselectAll();
                            gameState = GameState::Playing;
                        } else {
                            // Check for shop item clicks
                            int itemIndex = -1;
                            if (uiManager.isShopItemClicked(uiPos, itemIndex)) {
                                // Try to purchase the item
                                if (gameManager.purchaseItemFromMerchant(itemIndex)) {
                                    // Update UI if purchase successful
                                    uiManager.updateMerchantDisplay(gameManager.getSelectedMerchant());
                                }
                            }
                            
                            // Check for shop unit clicks
                            int unitIndex = -1;
                            if (uiManager.isShopUnitClicked(uiPos, unitIndex)) {
                                // Try to purchase the unit
                                if (gameManager.purchaseUnitFromMerchant(unitIndex)) {
                                    // Update UI if purchase successful
                                    uiManager.updateMerchantDisplay(gameManager.getSelectedMerchant());
                                }
                            }
                        }
                    }
                }
                else if (mouseEvent->button == sf::Mouse::Button::Right && gameState == GameState::Playing) {
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, gameView);
                    
                    // If hero is selected, move the hero (which moves the army with it)
                    if (gameManager.isHeroSelected()) {
                        Hero* hero = gameManager.getPlayerHero();
                        if (hero) {
                            // Find a path through walkable tiles and set it for the hero
                            sf::Vector2i startTilePos = screenToTile(hero->getPosition());
                            sf::Vector2i targetTilePos = screenToTile(worldPos);
                            
                            if (targetTilePos.x >= 0 && targetTilePos.x < MAP_WIDTH &&
                                targetTilePos.y >= 0 && targetTilePos.y < MAP_HEIGHT) {
                                
                                // Check if target tile is walkable
                                TileType targetType = tileMap[targetTilePos.x][targetTilePos.y].type;
                                if (targetType != TileType::Water && targetType != TileType::Mountain) {
                                    // Get a path to the target position
                                    std::vector<sf::Vector2f> path = PathFinder::findPath(
                                        tileMap, startTilePos, targetTilePos, 100
                                    );
                                    
                                    if (!path.empty()) {
                                        hero->setPath(path);
                                    }
                                }
                            }
                        }
                    }
                    // Otherwise try to move a regular unit
                    else {
                        unitManager.tryMoveSelectedUnit(worldPos, tileMap);
                    }
                }
            }
            else if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
                if (gameState == GameState::Playing || 
                    gameState == GameState::CityView ||
                    gameState == GameState::HeroView ||
                    gameState == GameState::ArmyView ||
                    gameState == GameState::MerchantView) {
                    
                    if (keyEvent->code == sf::Keyboard::Key::W) viewVelocity.y = -VIEW_SPEED;
                    if (keyEvent->code == sf::Keyboard::Key::S) viewVelocity.y = VIEW_SPEED;
                    if (keyEvent->code == sf::Keyboard::Key::A) viewVelocity.x = -VIEW_SPEED;
                    if (keyEvent->code == sf::Keyboard::Key::D) viewVelocity.x = VIEW_SPEED;
                    if (keyEvent->code == sf::Keyboard::Key::Escape) {
                        // Handle escape key based on current state
                        switch (gameState) {
                            case GameState::CityView:
                                uiManager.hideCityPanel();
                                cityManager.deselectCity();
                                gameState = GameState::Playing;
                                break;
                                
                            case GameState::HeroView:
                                uiManager.hideHeroPanel();
                                gameState = GameState::Playing;
                                break;
                                
                            case GameState::ArmyView:
                                uiManager.hideArmyPanel();
                                gameState = GameState::Playing;
                                break;
                                
                            case GameState::MerchantView:
                                uiManager.hideMerchantPanel();
                                gameManager.deselectAll();
                                gameState = GameState::Playing;
                                break;
                                
                            case GameState::Playing:
                                if (uiManager.isModalVisible()) {
                                    uiManager.hideModal();
                                } else {
                                    // Return to main menu
                                    gameState = GameState::MainMenu;
                                    window.setView(uiView);
                                }
                                break;
                                
                            default:
                                break;
                        }
                    }
                    
                    // Quick keys for hero and army panels
                    if (keyEvent->code == sf::Keyboard::Key::H) {
                        if (gameState == GameState::Playing && gameManager.getPlayerHero()) {
                            uiManager.showHeroInfo(gameManager.getPlayerHero());
                            gameState = GameState::HeroView;
                        }
                    }
                    
                    if (keyEvent->code == sf::Keyboard::Key::M) {
                        if (gameState == GameState::Playing && gameManager.getPlayerArmy()) {
                            uiManager.showArmyInfo(gameManager.getPlayerArmy());
                            gameState = GameState::ArmyView;
                        }
                    }
                    
                    // Handle founding a city with a Settler
                    if (keyEvent->code == sf::Keyboard::Key::F) {
                        PlayerUnit* selectedUnit = unitManager.getSelectedUnit();
                        if (selectedUnit && selectedUnit->getType() == UnitType::Settler) {
                            // Create a new city at the settler's position
                            sf::Vector2f pos = selectedUnit->getPosition();
                            cityManager.addCity(pos);
                            std::cout << "New city founded at position: " << pos.x << ", " << pos.y << std::endl;
                            std::cout << "Total cities: " << cityManager.getCityCount() << std::endl;
                            
                            // Remove the settler unit (consume it)
                            unitManager.removeSelectedUnit();
                        }
                    }
                    
                    // Debug - press C to print city info
                    if (keyEvent->code == sf::Keyboard::Key::C) {
                        std::cout << "City count: " << cityManager.getCityCount() << std::endl;
                    }
                }
            }
            else if (auto keyEvent = event.getIf<sf::Event::KeyReleased>()) {
                if (keyEvent->code == sf::Keyboard::Key::W && viewVelocity.y < 0) viewVelocity.y = 0;
                if (keyEvent->code == sf::Keyboard::Key::S && viewVelocity.y > 0) viewVelocity.y = 0;
                if (keyEvent->code == sf::Keyboard::Key::A && viewVelocity.x < 0) viewVelocity.x = 0;
                if (keyEvent->code == sf::Keyboard::Key::D && viewVelocity.x > 0) viewVelocity.x = 0;
            }
        }

        if (gameState == GameState::Playing || 
            gameState == GameState::CityView ||
            gameState == GameState::HeroView ||
            gameState == GameState::ArmyView ||
            gameState == GameState::MerchantView) {
            
            unitManager.update(deltaTime);
            gameView.move(viewVelocity * deltaTime);
            window.setView(gameView);
        }

        window.clear(sf::Color(30, 30, 30));
        
        if (gameState == GameState::MainMenu) {
            window.setView(uiView);
            uiManager.drawMenu(window);
        } else {
            // Calculate visible area
            sf::Vector2f viewCenter = gameView.getCenter();
            sf::Vector2f viewSize = gameView.getSize();
            float left = viewCenter.x - viewSize.x / 2.f - HEX_SIZE;
            float right = viewCenter.x + viewSize.x / 2.f + HEX_SIZE;
            float top = viewCenter.y - viewSize.y / 2.f - HEX_SIZE;
            float bottom = viewCenter.y + viewSize.y / 2.f + HEX_SIZE;
            
            // Draw only tiles in the visible area
            for (int x = 0; x < MAP_WIDTH; ++x) {
                for (int y = 0; y < MAP_HEIGHT; ++y) {
                    const sf::Vector2f& center = tileMap[x][y].center;
                    
                    // Only draw if in visible area
                    if (center.x >= left && center.x <= right && 
                        center.y >= top && center.y <= bottom) {
                        drawHexagon(window, tileMap[x][y]);
                    }
                }
            }
            
            // Draw game entities
            gameManager.draw(window);
            
            // Draw cities - debug output
            std::cout << "Drawing " << cityManager.getCityCount() << " cities." << std::endl;
            cityManager.draw(window);
            
            // Draw units
            unitManager.draw(window);

            // Draw UI elements
            window.setView(uiView);
            uiManager.drawResourcePanel(window);
            uiManager.drawUnitInfo(window, unitManager.getSelectedUnit());
            
            // Draw toggle buttons for hero and army
            uiManager.drawToggleButtons(window);
            
            // Draw panel based on current state
            switch (gameState) {
                case GameState::CityView:
                    uiManager.drawCityInfo(window, cityManager.getSelectedCity());
                    break;
                case GameState::HeroView:
                    uiManager.drawHeroInfo(window, gameManager.getPlayerHero());
                    break;
                case GameState::ArmyView:
                    uiManager.drawArmyInfo(window, gameManager.getPlayerArmy());
                    break;
                case GameState::MerchantView:
                    uiManager.drawMerchantInfo(window, gameManager.getSelectedMerchant());
                    break;
                default:
                    break;
            }
            
            uiManager.drawModal(window);
            window.setView(gameView);
        }

        window.display();
    }

    return 0;
}