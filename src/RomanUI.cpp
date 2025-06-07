#include "RomanUI.hpp"
#include <cmath>

namespace RomanUI {
    
    sf::RectangleShape createRomanButton(float x, float y, float width, float height) {
        sf::RectangleShape button;
        button.setPosition(sf::Vector2f(x, y));
        button.setSize(sf::Vector2f(width, height));
        button.setFillColor(Colors::BUTTON_NORMAL);
        button.setOutlineThickness(2.0f);
        button.setOutlineColor(Colors::BRONZE);
        return button;
    }
    
    sf::Text createRomanText(const std::string& text, const sf::Font& font, unsigned int size) {
        sf::Text romanText(font);
        romanText.setString(text);
        romanText.setCharacterSize(size);
        romanText.setFillColor(Colors::TEXT_PRIMARY);
        romanText.setOutlineThickness(1.0f);
        romanText.setOutlineColor(sf::Color::Black);
        return romanText;
    }
    
    sf::RectangleShape createRomanPanel(float x, float y, float width, float height) {
        sf::RectangleShape panel;
        panel.setPosition(sf::Vector2f(x, y));
        panel.setSize(sf::Vector2f(width, height));
        panel.setFillColor(Colors::PANEL_BACKGROUND);
        panel.setOutlineThickness(3.0f);
        panel.setOutlineColor(Colors::BRONZE);
        return panel;
    }
    
    sf::RectangleShape createModal(float x, float y, float width, float height) {
        sf::RectangleShape modal;
        modal.setPosition(sf::Vector2f(x, y));
        modal.setSize(sf::Vector2f(width, height));
        modal.setFillColor(Colors::MODAL_BACKGROUND);
        modal.setOutlineThickness(4.0f);
        modal.setOutlineColor(Colors::ROMAN_GOLD);
        return modal;
    }
    
    void drawRomanBorder(sf::RenderWindow& window, float x, float y, float width, float height) {
        // Outer border - Roman red
        sf::RectangleShape outerBorder(sf::Vector2f(width, height));
        outerBorder.setPosition(sf::Vector2f(x, y));
        outerBorder.setFillColor(sf::Color::Transparent);
        outerBorder.setOutlineThickness(4.0f);
        outerBorder.setOutlineColor(Colors::ROMAN_RED);
        window.draw(outerBorder);
        
        // Inner border - Roman gold
        sf::RectangleShape innerBorder(sf::Vector2f(width - 8, height - 8));
        innerBorder.setPosition(sf::Vector2f(x + 4, y + 4));
        innerBorder.setFillColor(sf::Color::Transparent);
        innerBorder.setOutlineThickness(2.0f);
        innerBorder.setOutlineColor(Colors::ROMAN_GOLD);
        window.draw(innerBorder);
        
        // Corner decorations (Roman eagles)
        for (int i = 0; i < 4; ++i) {
            float cornerX = (i % 2 == 0) ? x - 8 : x + width - 8;
            float cornerY = (i < 2) ? y - 8 : y + height - 8;
            drawEagleEmblem(window, cornerX, cornerY, 16);
        }
    }
    
    void drawRomanColumn(sf::RenderWindow& window, float x, float y, float height) {
        // Column base
        sf::RectangleShape base(sf::Vector2f(20, 8));
        base.setPosition(sf::Vector2f(x - 2, y + height - 8));
        base.setFillColor(Colors::MARBLE_WHITE);
        window.draw(base);
        
        // Column shaft
        sf::RectangleShape shaft(sf::Vector2f(16, height - 16));
        shaft.setPosition(sf::Vector2f(x, y + 8));
        shaft.setFillColor(Colors::MARBLE_WHITE);
        shaft.setOutlineThickness(1.0f);
        shaft.setOutlineColor(Colors::BRONZE);
        window.draw(shaft);
        
        // Column capital
        sf::RectangleShape capital(sf::Vector2f(20, 8));
        capital.setPosition(sf::Vector2f(x - 2, y));
        capital.setFillColor(Colors::MARBLE_WHITE);
        window.draw(capital);
    }
    
    void drawEagleEmblem(sf::RenderWindow& window, float x, float y, float size) {
        // Eagle body (simplified)
        sf::CircleShape body(size * 0.4f);
        body.setPosition(sf::Vector2f(x, y));
        body.setFillColor(Colors::ROMAN_GOLD);
        body.setOutlineThickness(1.0f);
        body.setOutlineColor(Colors::BRONZE);
        window.draw(body);
        
        // Eagle wings (triangles)
        sf::ConvexShape leftWing;
        leftWing.setPointCount(3);
        leftWing.setPoint(0, sf::Vector2f(x - size * 0.3f, y + size * 0.2f));
        leftWing.setPoint(1, sf::Vector2f(x, y + size * 0.1f));
        leftWing.setPoint(2, sf::Vector2f(x - size * 0.1f, y + size * 0.5f));
        leftWing.setFillColor(Colors::ROMAN_GOLD);
        window.draw(leftWing);
        
        sf::ConvexShape rightWing;
        rightWing.setPointCount(3);
        rightWing.setPoint(0, sf::Vector2f(x + size * 0.8f + size * 0.3f, y + size * 0.2f));
        rightWing.setPoint(1, sf::Vector2f(x + size * 0.8f, y + size * 0.1f));
        rightWing.setPoint(2, sf::Vector2f(x + size * 0.8f + size * 0.1f, y + size * 0.5f));
        rightWing.setFillColor(Colors::ROMAN_GOLD);
        window.draw(rightWing);
    }
    
    void drawRomanHexagon(sf::RenderWindow& window, const game::Tile& tile, float hexSize) {
        const sf::Vector2f& center = tile.center;
        
        // Create hexagon with 6 points
        sf::ConvexShape hexagon;
        hexagon.setPointCount(6);
        
        for (int i = 0; i < 6; ++i) {
            float angle_rad = M_PI / 180.f * (60 * i + 30);
            float x = center.x + hexSize * std::cos(angle_rad);
            float y = center.y + hexSize * std::sin(angle_rad);
            hexagon.setPoint(i, sf::Vector2f(x, y));
        }
        
        // Set Roman-themed colors based on terrain
        sf::Color tileColor;
        switch (tile.type) {
            case game::TileType::Plains:
                tileColor = Colors::ROMAN_FIELDS;
                break;
            case game::TileType::Hills:
                tileColor = Colors::ROMAN_HILLS;
                break;
            case game::TileType::Mountain:
                tileColor = sf::Color(105, 105, 105);
                break;
            case game::TileType::Forest:
                tileColor = sf::Color(85, 107, 47);
                break;
            case game::TileType::Water:
                tileColor = Colors::MEDITERRANEAN_BLUE;
                break;
            default:
                tileColor = Colors::ROMAN_FIELDS;
                break;
        }
        
        hexagon.setFillColor(tileColor);
        hexagon.setOutlineThickness(1.5f);
        hexagon.setOutlineColor(sf::Color(80, 60, 40, 180));
        window.draw(hexagon);
        
        // Add Roman-themed terrain details
        if (tile.type == game::TileType::Plains) {
            // Draw Roman roads (if applicable)
            sf::RectangleShape road(sf::Vector2f(hexSize * 1.2f, 3.0f));
            road.setPosition(sf::Vector2f(center.x - hexSize * 0.6f, center.y - 1.5f));
            road.setFillColor(Colors::ROMAN_ROADS);
            window.draw(road);
        } else if (tile.type == game::TileType::Hills) {
            // Draw Roman watchtower
            sf::RectangleShape tower(sf::Vector2f(6, 12));
            tower.setPosition(sf::Vector2f(center.x - 3, center.y - 6));
            tower.setFillColor(Colors::MARBLE_WHITE);
            tower.setOutlineThickness(1.0f);
            tower.setOutlineColor(Colors::BRONZE);
            window.draw(tower);
        }
        
        // Draw resource indicator if tile has resources
        if (tile.resource.hasResource) {
            sf::CircleShape resourceIcon(5.0f);
            resourceIcon.setPosition(sf::Vector2f(center.x + hexSize * 0.5f - 5, center.y - hexSize * 0.5f - 5));
            resourceIcon.setFillColor(Colors::ROMAN_GOLD);
            resourceIcon.setOutlineThickness(1.0f);
            resourceIcon.setOutlineColor(sf::Color::Black);
            window.draw(resourceIcon);
        }
    }
    
    void drawRomanCity(sf::RenderWindow& window, const sf::Vector2f& position, 
                       const std::string& name, const sf::Font& font, bool isPlayerNear) {
        // City walls (Roman architecture)
        sf::RectangleShape cityWalls(sf::Vector2f(50, 50));
        cityWalls.setPosition(sf::Vector2f(position.x - 25, position.y - 25));
        cityWalls.setFillColor(Colors::MARBLE_WHITE);
        cityWalls.setOutlineThickness(3.0f);
        cityWalls.setOutlineColor(isPlayerNear ? Colors::ROMAN_GOLD : Colors::BRONZE);
        window.draw(cityWalls);
        
        // Roman temple/forum in center
        sf::RectangleShape forum(sf::Vector2f(25, 25));
        forum.setPosition(sf::Vector2f(position.x - 12.5f, position.y - 12.5f));
        forum.setFillColor(Colors::ROMAN_RED);
        forum.setOutlineThickness(2.0f);
        forum.setOutlineColor(Colors::ROMAN_GOLD);
        window.draw(forum);
        
        // Roman columns at corners
        for (int i = 0; i < 4; ++i) {
            float angle = i * 90.0f * M_PI / 180.0f;
            float columnX = position.x + 20 * std::cos(angle) - 4;
            float columnY = position.y + 20 * std::sin(angle) - 15;
            drawRomanColumn(window, columnX, columnY, 30);
        }
        
        // Entry indicator when player is near
        if (isPlayerNear) {
            sf::Text enterText = createRomanText("Press E to Enter", font, 12);
            sf::FloatRect textBounds = enterText.getLocalBounds();
            enterText.setPosition(sf::Vector2f(position.x - textBounds.size.x / 2, position.y + 35));
            enterText.setFillColor(Colors::ROMAN_GOLD);
            window.draw(enterText);
        }
        
        // City name
        sf::Text cityName = createRomanText(name, font, 14);
        sf::FloatRect textBounds = cityName.getLocalBounds();
        cityName.setPosition(sf::Vector2f(position.x - textBounds.size.x / 2, position.y - 45));
        window.draw(cityName);
    }
    
    void drawSidebar(sf::RenderWindow& window, float windowWidth, float windowHeight, 
                     const sf::Font& font, const sf::Vector2f& playerPos) {
        float sidebarX = windowWidth - Layout::SIDEBAR_WIDTH;
        
        // Sidebar background
        sf::RectangleShape sidebar = createRomanPanel(sidebarX, 0, Layout::SIDEBAR_WIDTH, windowHeight);
        window.draw(sidebar);
        
        // Sidebar decorative border
        drawRomanBorder(window, sidebarX + 5, 5, Layout::SIDEBAR_WIDTH - 10, windowHeight - 10);
        
        float currentY = 20;
        
        // Minimap section
        sf::Text minimapTitle = createRomanText("IMPERIUM MAP", font, 16);
        minimapTitle.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(minimapTitle);
        currentY += 30;
        
        drawMinimap(window, sidebarX + 20, currentY, Layout::MINIMAP_SIZE, 
                   playerPos, sf::Vector2f(240, 180));
        currentY += Layout::MINIMAP_SIZE + 20;
        
        // Character management section
        sf::Text charTitle = createRomanText("CHARACTER", font, 16);
        charTitle.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(charTitle);
        currentY += 30;
        
        // Character management buttons
        sf::RectangleShape charButton = createRomanButton(sidebarX + 20, currentY, 
                                                         Layout::SIDEBAR_WIDTH - 40, Layout::BUTTON_HEIGHT);
        sf::Text charButtonText = createRomanText("Manage Character", font, 14);
        charButtonText.setPosition(sf::Vector2f(sidebarX + 30, currentY + 8));
        window.draw(charButton);
        window.draw(charButtonText);
        currentY += Layout::BUTTON_HEIGHT + 10;
        
        sf::RectangleShape skillsButton = createRomanButton(sidebarX + 20, currentY, 
                                                           Layout::SIDEBAR_WIDTH - 40, Layout::BUTTON_HEIGHT);
        sf::Text skillsButtonText = createRomanText("Skills & Abilities", font, 14);
        skillsButtonText.setPosition(sf::Vector2f(sidebarX + 30, currentY + 8));
        window.draw(skillsButton);
        window.draw(skillsButtonText);
        currentY += Layout::BUTTON_HEIGHT + 20;
        
        // Army management section
        sf::Text armyTitle = createRomanText("LEGION", font, 16);
        armyTitle.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(armyTitle);
        currentY += 30;
        
        sf::RectangleShape armyButton = createRomanButton(sidebarX + 20, currentY, 
                                                         Layout::SIDEBAR_WIDTH - 40, Layout::BUTTON_HEIGHT);
        sf::Text armyButtonText = createRomanText("Manage Legion", font, 14);
        armyButtonText.setPosition(sf::Vector2f(sidebarX + 30, currentY + 8));
        window.draw(armyButton);
        window.draw(armyButtonText);
        currentY += Layout::BUTTON_HEIGHT + 20;
        
        // Resource display
        sf::Text resourceTitle = createRomanText("RESOURCES", font, 16);
        resourceTitle.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(resourceTitle);
        currentY += 30;
        
        // Display resources with Roman names
        sf::Text goldText = createRomanText("Aurum: 1500", font, 12);
        goldText.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(goldText);
        currentY += 20;
        
        sf::Text stoneText = createRomanText("Lapis: 800", font, 12);
        stoneText.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(stoneText);
        currentY += 20;
        
        sf::Text woodText = createRomanText("Lignum: 600", font, 12);
        woodText.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(woodText);
        currentY += 20;
        
        sf::Text foodText = createRomanText("Frumentum: 400", font, 12);
        foodText.setPosition(sf::Vector2f(sidebarX + 20, currentY));
        window.draw(foodText);
    }
    
    void drawMinimap(sf::RenderWindow& window, float x, float y, float size, 
                     const sf::Vector2f& playerPosition, const sf::Vector2f& mapSize) {
        // Minimap background
        sf::RectangleShape minimapBg(sf::Vector2f(size, size));
        minimapBg.setPosition(sf::Vector2f(x, y));
        minimapBg.setFillColor(sf::Color(50, 50, 50, 200));
        minimapBg.setOutlineThickness(2.0f);
        minimapBg.setOutlineColor(Colors::BRONZE);
        window.draw(minimapBg);
        
        // Simple terrain representation
        int gridSize = 12;
        float cellSize = size / gridSize;
        
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                sf::RectangleShape terrainPixel(sf::Vector2f(cellSize - 1, cellSize - 1));
                terrainPixel.setPosition(sf::Vector2f(x + i * cellSize, y + j * cellSize));
                
                // Roman terrain representation
                int terrainType = (i + j) % 5;
                switch (terrainType) {
                    case 0: terrainPixel.setFillColor(Colors::ROMAN_FIELDS); break;
                    case 1: terrainPixel.setFillColor(Colors::ROMAN_HILLS); break;
                    case 2: terrainPixel.setFillColor(sf::Color(85, 107, 47)); break; // Forest
                    case 3: terrainPixel.setFillColor(Colors::MEDITERRANEAN_BLUE); break;
                    case 4: terrainPixel.setFillColor(sf::Color(105, 105, 105)); break; // Mountains
                }
                window.draw(terrainPixel);
            }
        }
        
        // Player position indicator (Roman eagle)
        float playerX = x + (playerPosition.x / mapSize.x) * size - 8;
        float playerY = y + (playerPosition.y / mapSize.y) * size - 8;
        drawEagleEmblem(window, playerX, playerY, 8);
    }
    
    void drawCharacterModal(sf::RenderWindow& window, const sf::Font& font) {
        float modalX = (window.getSize().x - Layout::MODAL_WIDTH) / 2;
        float modalY = (window.getSize().y - Layout::MODAL_HEIGHT) / 2;
        
        // Modal background
        sf::RectangleShape modal = createModal(modalX, modalY, Layout::MODAL_WIDTH, Layout::MODAL_HEIGHT);
        window.draw(modal);
        
        // Modal decorative border
        drawRomanBorder(window, modalX + 10, modalY + 10, Layout::MODAL_WIDTH - 20, Layout::MODAL_HEIGHT - 20);
        
        // Title
        sf::Text title = createRomanText("CHARACTER MANAGEMENT", font, 20);
        title.setPosition(sf::Vector2f(modalX + 30, modalY + 30));
        title.setFillColor(Colors::ROMAN_GOLD);
        window.draw(title);
        
        float currentY = modalY + 70;
        
        // Character stats
        sf::Text levelText = createRomanText("Level: 5 (Centurion)", font, 14);
        levelText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(levelText);
        currentY += 25;
        
        sf::Text expText = createRomanText("Experience: 1250 / 2000", font, 14);
        expText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(expText);
        currentY += 25;
        
        sf::Text healthText = createRomanText("Health: 150 / 150", font, 14);
        healthText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(healthText);
        currentY += 40;
        
        // Attributes section
        sf::Text attributesTitle = createRomanText("ATTRIBUTES", font, 16);
        attributesTitle.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(attributesTitle);
        currentY += 30;
        
        sf::Text strText = createRomanText("Strength: 12", font, 12);
        strText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(strText);
        
        sf::Text intText = createRomanText("Intelligence: 8", font, 12);
        intText.setPosition(sf::Vector2f(modalX + 200, currentY));
        window.draw(intText);
        currentY += 20;
        
        sf::Text dexText = createRomanText("Dexterity: 10", font, 12);
        dexText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(dexText);
        
        sf::Text wisText = createRomanText("Wisdom: 9", font, 12);
        wisText.setPosition(sf::Vector2f(modalX + 200, currentY));
        window.draw(wisText);
        
        // Close button
        sf::RectangleShape closeButton = createRomanButton(modalX + Layout::MODAL_WIDTH - 120, 
                                                          modalY + Layout::MODAL_HEIGHT - 50, 100, 30);
        sf::Text closeText = createRomanText("Close", font, 14);
        closeText.setPosition(sf::Vector2f(modalX + Layout::MODAL_WIDTH - 90, modalY + Layout::MODAL_HEIGHT - 42));
        window.draw(closeButton);
        window.draw(closeText);
    }
    
    void drawArmyModal(sf::RenderWindow& window, const sf::Font& font) {
        float modalX = (window.getSize().x - Layout::MODAL_WIDTH) / 2;
        float modalY = (window.getSize().y - Layout::MODAL_HEIGHT) / 2;
        
        // Modal background
        sf::RectangleShape modal = createModal(modalX, modalY, Layout::MODAL_WIDTH, Layout::MODAL_HEIGHT);
        window.draw(modal);
        
        // Modal decorative border
        drawRomanBorder(window, modalX + 10, modalY + 10, Layout::MODAL_WIDTH - 20, Layout::MODAL_HEIGHT - 20);
        
        // Title
        sf::Text title = createRomanText("LEGION MANAGEMENT", font, 20);
        title.setPosition(sf::Vector2f(modalX + 30, modalY + 30));
        title.setFillColor(Colors::ROMAN_GOLD);
        window.draw(title);
        
        float currentY = modalY + 70;
        
        // Army units display
        std::vector<std::string> units = {"Legionnaire x15", "Archer x8", "Cavalry x5", "Siege Engine x2"};
        
        for (size_t i = 0; i < units.size(); ++i) {
            sf::RectangleShape unitSlot = createRomanPanel(modalX + 30, currentY, 200, 30);
            window.draw(unitSlot);
            
            sf::Text unitText = createRomanText(units[i], font, 12);
            unitText.setPosition(sf::Vector2f(modalX + 40, currentY + 8));
            window.draw(unitText);
            
            // Unit management buttons
            sf::RectangleShape upgradeBtn = createRomanButton(modalX + 250, currentY + 2, 80, 26);
            sf::Text upgradeText = createRomanText("Upgrade", font, 10);
            upgradeText.setPosition(sf::Vector2f(modalX + 260, currentY + 8));
            window.draw(upgradeBtn);
            window.draw(upgradeText);
            
            sf::RectangleShape dismissBtn = createRomanButton(modalX + 340, currentY + 2, 80, 26);
            sf::Text dismissText = createRomanText("Dismiss", font, 10);
            dismissText.setPosition(sf::Vector2f(modalX + 350, currentY + 8));
            window.draw(dismissBtn);
            window.draw(dismissText);
            
            currentY += 40;
        }
        
        // Close button
        sf::RectangleShape closeButton = createRomanButton(modalX + Layout::MODAL_WIDTH - 120, 
                                                          modalY + Layout::MODAL_HEIGHT - 50, 100, 30);
        sf::Text closeText = createRomanText("Close", font, 14);
        closeText.setPosition(sf::Vector2f(modalX + Layout::MODAL_WIDTH - 90, modalY + Layout::MODAL_HEIGHT - 42));
        window.draw(closeButton);
        window.draw(closeText);
    }
    
    void drawCityModal(sf::RenderWindow& window, const sf::Font& font) {
        float modalX = (window.getSize().x - Layout::MODAL_WIDTH) / 2;
        float modalY = (window.getSize().y - Layout::MODAL_HEIGHT) / 2;
        
        // Modal background
        sf::RectangleShape modal = createModal(modalX, modalY, Layout::MODAL_WIDTH, Layout::MODAL_HEIGHT);
        window.draw(modal);
        
        // Modal decorative border
        drawRomanBorder(window, modalX + 10, modalY + 10, Layout::MODAL_WIDTH - 20, Layout::MODAL_HEIGHT - 20);
        
        // Title
        sf::Text title = createRomanText("CITY OF ROME", font, 20);
        title.setPosition(sf::Vector2f(modalX + 30, modalY + 30));
        title.setFillColor(Colors::ROMAN_GOLD);
        window.draw(title);
        
        float currentY = modalY + 70;
        
        // City info
        sf::Text populationText = createRomanText("Population: 25,000", font, 14);
        populationText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(populationText);
        currentY += 25;
        
        sf::Text prosperityText = createRomanText("Prosperity: High", font, 14);
        prosperityText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(prosperityText);
        currentY += 40;
        
        // Building management
        sf::Text buildingTitle = createRomanText("BUILDINGS", font, 16);
        buildingTitle.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(buildingTitle);
        currentY += 30;
        
        std::vector<std::string> buildings = {"Forum", "Barracks", "Market", "Temple", "Aqueduct"};
        
        int col = 0;
        float startY = currentY;
        for (size_t i = 0; i < buildings.size(); ++i) {
            float btnX = modalX + 30 + (col * 120);
            float btnY = startY + ((i / 4) * 50);
            
            sf::RectangleShape buildingBtn = createRomanButton(btnX, btnY, 100, 35);
            sf::Text buildingText = createRomanText(buildings[i], font, 12);
            buildingText.setPosition(sf::Vector2f(btnX + 10, btnY + 10));
            window.draw(buildingBtn);
            window.draw(buildingText);
            
            col = (col + 1) % 4;
        }
        
        // Close button
        sf::RectangleShape closeButton = createRomanButton(modalX + Layout::MODAL_WIDTH - 120, 
                                                          modalY + Layout::MODAL_HEIGHT - 50, 100, 30);
        sf::Text closeText = createRomanText("Close", font, 14);
        closeText.setPosition(sf::Vector2f(modalX + Layout::MODAL_WIDTH - 90, modalY + Layout::MODAL_HEIGHT - 42));
        window.draw(closeButton);
        window.draw(closeText);
    }
    
    void drawSkillsModal(sf::RenderWindow& window, const sf::Font& font) {
        float modalX = (window.getSize().x - Layout::MODAL_WIDTH) / 2;
        float modalY = (window.getSize().y - Layout::MODAL_HEIGHT) / 2;
        
        // Modal background
        sf::RectangleShape modal = createModal(modalX, modalY, Layout::MODAL_WIDTH, Layout::MODAL_HEIGHT);
        window.draw(modal);
        
        // Modal decorative border
        drawRomanBorder(window, modalX + 10, modalY + 10, Layout::MODAL_WIDTH - 20, Layout::MODAL_HEIGHT - 20);
        
        // Title
        sf::Text title = createRomanText("SKILLS & ABILITIES", font, 20);
        title.setPosition(sf::Vector2f(modalX + 30, modalY + 30));
        title.setFillColor(Colors::ROMAN_GOLD);
        window.draw(title);
        
        float currentY = modalY + 70;
        
        // Skill points available
        sf::Text skillPointsText = createRomanText("Skill Points Available: 3", font, 14);
        skillPointsText.setPosition(sf::Vector2f(modalX + 30, currentY));
        window.draw(skillPointsText);
        currentY += 40;
        
        // Skills list
        std::vector<std::pair<std::string, int>> skills = {
            {"Leadership", 3}, {"Tactics", 2}, {"Archery", 1}, {"Engineering", 2}, {"Diplomacy", 1}
        };
        
        for (size_t i = 0; i < skills.size(); ++i) {
            sf::Text skillText = createRomanText(skills[i].first + ": Level " + std::to_string(skills[i].second), font, 12);
            skillText.setPosition(sf::Vector2f(modalX + 30, currentY));
            window.draw(skillText);
            
            // Upgrade button
            sf::RectangleShape upgradeBtn = createRomanButton(modalX + 300, currentY - 5, 80, 25);
            sf::Text upgradeText = createRomanText("Upgrade", font, 10);
            upgradeText.setPosition(sf::Vector2f(modalX + 310, currentY));
            window.draw(upgradeBtn);
            window.draw(upgradeText);
            
            currentY += 30;
        }
        
        // Close button
        sf::RectangleShape closeButton = createRomanButton(modalX + Layout::MODAL_WIDTH - 120, 
                                                          modalY + Layout::MODAL_HEIGHT - 50, 100, 30);
        sf::Text closeText = createRomanText("Close", font, 14);
        closeText.setPosition(sf::Vector2f(modalX + Layout::MODAL_WIDTH - 90, modalY + Layout::MODAL_HEIGHT - 42));
        window.draw(closeButton);
        window.draw(closeText);
    }
    
    void drawBuildingModal(sf::RenderWindow& window, const sf::Font& font, const std::string& buildingType) {
        float modalX = (window.getSize().x - Layout::MODAL_WIDTH) / 2;
        float modalY = (window.getSize().y - Layout::MODAL_HEIGHT) / 2;
        
        // Modal background
        sf::RectangleShape modal = createModal(modalX, modalY, Layout::MODAL_WIDTH, Layout::MODAL_HEIGHT);
        window.draw(modal);
        
        // Modal decorative border
        drawRomanBorder(window, modalX + 10, modalY + 10, Layout::MODAL_WIDTH - 20, Layout::MODAL_HEIGHT - 20);
        
        // Title
        sf::Text title = createRomanText(buildingType + " OF ROME", font, 20);
        title.setPosition(sf::Vector2f(modalX + 30, modalY + 30));
        title.setFillColor(Colors::ROMAN_GOLD);
        window.draw(title);
        
        float currentY = modalY + 70;
        
        if (buildingType == "BARRACKS") {
            // Recruit soldiers
            sf::Text recruitTitle = createRomanText("RECRUIT LEGIONS", font, 16);
            recruitTitle.setPosition(sf::Vector2f(modalX + 30, currentY));
            window.draw(recruitTitle);
            currentY += 30;
            
            std::vector<std::pair<std::string, int>> units = {
                {"Legionnaire", 50}, {"Archer", 75}, {"Cavalry", 150}, {"Siege Engine", 300}
            };
            
            for (size_t i = 0; i < units.size(); ++i) {
                sf::Text unitText = createRomanText(units[i].first + " - " + std::to_string(units[i].second) + " Gold", font, 12);
                unitText.setPosition(sf::Vector2f(modalX + 30, currentY));
                window.draw(unitText);
                
                sf::RectangleShape recruitBtn = createRomanButton(modalX + 300, currentY - 5, 80, 25);
                sf::Text recruitText = createRomanText("Recruit", font, 10);
                recruitText.setPosition(sf::Vector2f(modalX + 310, currentY));
                window.draw(recruitBtn);
                window.draw(recruitText);
                
                currentY += 30;
            }
        } else if (buildingType == "MARKET") {
            // Buy/sell items
            sf::Text tradeTitle = createRomanText("TRADE GOODS", font, 16);
            tradeTitle.setPosition(sf::Vector2f(modalX + 30, currentY));
            window.draw(tradeTitle);
            currentY += 30;
            
            std::vector<std::pair<std::string, int>> items = {
                {"Iron Sword", 100}, {"Shield", 50}, {"Healing Potion", 25}, {"Map Scroll", 75}
            };
            
            for (size_t i = 0; i < items.size(); ++i) {
                sf::Text itemText = createRomanText(items[i].first + " - " + std::to_string(items[i].second) + " Gold", font, 12);
                itemText.setPosition(sf::Vector2f(modalX + 30, currentY));
                window.draw(itemText);
                
                sf::RectangleShape buyBtn = createRomanButton(modalX + 300, currentY - 5, 80, 25);
                sf::Text buyText = createRomanText("Buy", font, 10);
                buyText.setPosition(sf::Vector2f(modalX + 320, currentY));
                window.draw(buyBtn);
                window.draw(buyText);
                
                currentY += 30;
            }
        }
        
        // Close button
        sf::RectangleShape closeButton = createRomanButton(modalX + Layout::MODAL_WIDTH - 120, 
                                                          modalY + Layout::MODAL_HEIGHT - 50, 100, 30);
        sf::Text closeText = createRomanText("Close", font, 14);
        closeText.setPosition(sf::Vector2f(modalX + Layout::MODAL_WIDTH - 90, modalY + Layout::MODAL_HEIGHT - 42));
        window.draw(closeButton);
        window.draw(closeText);
    }
    
    // 2.5D Enhanced rendering functions
    void drawRomanHexagon2D5(sf::RenderWindow& window, const game::Tile& tile, float hexSize) {
        const sf::Vector2f& center = tile.center;
        
        // Create main hexagon with 6 points
        sf::ConvexShape hexagon;
        hexagon.setPointCount(6);
        
        // Create shadow hexagon (depth effect)
        sf::ConvexShape shadowHex;
        shadowHex.setPointCount(6);
        
        for (int i = 0; i < 6; ++i) {
            float angle_rad = M_PI / 180.f * (60 * i + 30);
            float x = center.x + hexSize * std::cos(angle_rad);
            float y = center.y + hexSize * std::sin(angle_rad);
            hexagon.setPoint(i, sf::Vector2f(x, y));
            
            // Shadow offset for 2.5D effect
            shadowHex.setPoint(i, sf::Vector2f(x + Layout::SHADOW_OFFSET, y + Layout::SHADOW_OFFSET));
        }
        
        // Set Roman-themed colors based on terrain with enhanced shading
        sf::Color tileColor, shadowColor;
        switch (tile.type) {
            case game::TileType::Plains:
                tileColor = Colors::ROMAN_FIELDS;
                shadowColor = sf::Color(Colors::ROMAN_FIELDS.r * 0.6f, Colors::ROMAN_FIELDS.g * 0.6f, Colors::ROMAN_FIELDS.b * 0.6f, 120);
                break;
            case game::TileType::Hills:
                tileColor = Colors::ROMAN_HILLS;
                shadowColor = sf::Color(Colors::ROMAN_HILLS.r * 0.6f, Colors::ROMAN_HILLS.g * 0.6f, Colors::ROMAN_HILLS.b * 0.6f, 120);
                break;
            case game::TileType::Mountain:
                tileColor = sf::Color(105, 105, 105);
                shadowColor = sf::Color(60, 60, 60, 120);
                break;
            case game::TileType::Forest:
                tileColor = sf::Color(85, 107, 47);
                shadowColor = sf::Color(50, 64, 28, 120);
                break;
            case game::TileType::Water:
                tileColor = Colors::MEDITERRANEAN_BLUE;
                shadowColor = sf::Color(Colors::MEDITERRANEAN_BLUE.r * 0.5f, Colors::MEDITERRANEAN_BLUE.g * 0.5f, Colors::MEDITERRANEAN_BLUE.b * 0.5f, 120);
                break;
            default:
                tileColor = Colors::ROMAN_FIELDS;
                shadowColor = sf::Color(Colors::ROMAN_FIELDS.r * 0.6f, Colors::ROMAN_FIELDS.g * 0.6f, Colors::ROMAN_FIELDS.b * 0.6f, 120);
                break;
        }
        
        // Draw shadow first
        shadowHex.setFillColor(shadowColor);
        window.draw(shadowHex);
        
        // Draw main hexagon with enhanced appearance
        hexagon.setFillColor(tileColor);
        hexagon.setOutlineThickness(1.5f);
        hexagon.setOutlineColor(sf::Color(80, 60, 40, 180));
        window.draw(hexagon);
        
        // Add terrain-specific 2.5D details
        if (tile.type == game::TileType::Hills || tile.type == game::TileType::Mountain) {
            // Add elevated effect with gradient
            sf::ConvexShape highlight;
            highlight.setPointCount(3);
            highlight.setPoint(0, sf::Vector2f(center.x - hexSize * 0.5f, center.y - hexSize * 0.3f));
            highlight.setPoint(1, sf::Vector2f(center.x, center.y - hexSize * 0.8f));
            highlight.setPoint(2, sf::Vector2f(center.x + hexSize * 0.5f, center.y - hexSize * 0.3f));
            highlight.setFillColor(sf::Color(255, 255, 255, 60));
            window.draw(highlight);
        }
        
        // Draw resource indicator if tile has resources with glow effect
        if (tile.resource.hasResource) {
            // Glow effect
            sf::CircleShape resourceGlow(8.0f);
            resourceGlow.setPosition(sf::Vector2f(center.x + hexSize * 0.5f - 8, center.y - hexSize * 0.5f - 8));
            resourceGlow.setFillColor(sf::Color(Colors::ROMAN_GOLD.r, Colors::ROMAN_GOLD.g, Colors::ROMAN_GOLD.b, 80));
            window.draw(resourceGlow);
            
            // Main resource icon
            sf::CircleShape resourceIcon(5.0f);
            resourceIcon.setPosition(sf::Vector2f(center.x + hexSize * 0.5f - 5, center.y - hexSize * 0.5f - 5));
            resourceIcon.setFillColor(Colors::ROMAN_GOLD);
            resourceIcon.setOutlineThickness(1.0f);
            resourceIcon.setOutlineColor(sf::Color::Black);
            window.draw(resourceIcon);
        }
    }
    
    void drawRomanCity2D5(sf::RenderWindow& window, const sf::Vector2f& position, 
                          const std::string& name, const sf::Font& font, bool isPlayerNear) {
        // City shadow for depth
        sf::RectangleShape cityShadow(sf::Vector2f(50, 50));
        cityShadow.setPosition(sf::Vector2f(position.x - 25 + Layout::SHADOW_OFFSET, position.y - 25 + Layout::SHADOW_OFFSET));
        cityShadow.setFillColor(sf::Color(0, 0, 0, 100));
        window.draw(cityShadow);
        
        // City walls (Roman architecture) with enhanced 3D effect
        sf::RectangleShape cityWalls(sf::Vector2f(50, 50));
        cityWalls.setPosition(sf::Vector2f(position.x - 25, position.y - 25));
        cityWalls.setFillColor(Colors::MARBLE_WHITE);
        cityWalls.setOutlineThickness(3.0f);
        cityWalls.setOutlineColor(isPlayerNear ? Colors::ROMAN_GOLD : Colors::BRONZE);
        window.draw(cityWalls);
        
        // Wall highlight for 3D effect
        sf::RectangleShape wallHighlight(sf::Vector2f(50, 8));
        wallHighlight.setPosition(sf::Vector2f(position.x - 25, position.y - 25));
        wallHighlight.setFillColor(sf::Color(255, 255, 255, 120));
        window.draw(wallHighlight);
        
        // Roman temple/forum in center with shadow
        sf::RectangleShape forumShadow(sf::Vector2f(25, 25));
        forumShadow.setPosition(sf::Vector2f(position.x - 12.5f + 2, position.y - 12.5f + 2));
        forumShadow.setFillColor(sf::Color(0, 0, 0, 120));
        window.draw(forumShadow);
        
        sf::RectangleShape forum(sf::Vector2f(25, 25));
        forum.setPosition(sf::Vector2f(position.x - 12.5f, position.y - 12.5f));
        forum.setFillColor(Colors::ROMAN_RED);
        forum.setOutlineThickness(2.0f);
        forum.setOutlineColor(Colors::ROMAN_GOLD);
        window.draw(forum);
        
        // Roman columns at corners with enhanced 3D effect
        for (int i = 0; i < 4; ++i) {
            float angle = i * 90.0f * M_PI / 180.0f;
            float columnX = position.x + 20 * std::cos(angle) - 4;
            float columnY = position.y + 20 * std::sin(angle) - 15;
            
            // Column shadow
            sf::RectangleShape columnShadow(sf::Vector2f(8, 30));
            columnShadow.setPosition(sf::Vector2f(columnX + 2, columnY + 2));
            columnShadow.setFillColor(sf::Color(0, 0, 0, 100));
            window.draw(columnShadow);
            
            drawRomanColumn(window, columnX, columnY, 30);
        }
        
        // Enhanced entry indicator with glow effect
        if (isPlayerNear) {
            // Glow background
            sf::RectangleShape glowBg(sf::Vector2f(140, 25));
            glowBg.setPosition(sf::Vector2f(position.x - 70, position.y + 30));
            glowBg.setFillColor(sf::Color(Colors::ROMAN_GOLD.r, Colors::ROMAN_GOLD.g, Colors::ROMAN_GOLD.b, 100));
            window.draw(glowBg);
            
            sf::Text enterText = createRomanText("Press E to Enter", font, 12);
            sf::FloatRect actualBounds = enterText.getLocalBounds();
            enterText.setPosition(sf::Vector2f(position.x - actualBounds.size.x / 2, position.y + 35));
            enterText.setFillColor(Colors::ROMAN_GOLD);
            enterText.setOutlineThickness(1.0f);
            enterText.setOutlineColor(sf::Color::Black);
            window.draw(enterText);
        }
        
        // City name with shadow
        sf::Text cityNameShadow = createRomanText(name, font, 14);
        sf::FloatRect shadowBounds = cityNameShadow.getLocalBounds();
        cityNameShadow.setPosition(sf::Vector2f(position.x - shadowBounds.size.x / 2 + 2, position.y - 43));
        cityNameShadow.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(cityNameShadow);
        
        sf::Text cityName = createRomanText(name, font, 14);
        sf::FloatRect textBounds = cityName.getLocalBounds();
        cityName.setPosition(sf::Vector2f(position.x - textBounds.size.x / 2, position.y - 45));
        window.draw(cityName);
    }
    
    void drawSpriteCharacter(sf::RenderWindow& window, const sf::Vector2f& position, 
                            const sf::Texture& spriteTexture, bool isSelected) {
        // Character shadow for depth
        sf::CircleShape shadow(16.0f);
        shadow.setPosition(sf::Vector2f(position.x - 16 + Layout::SHADOW_OFFSET, position.y - 16 + Layout::SHADOW_OFFSET));
        shadow.setFillColor(sf::Color(0, 0, 0, 120));
        window.draw(shadow);
        
        // Main character sprite
        sf::Sprite characterSprite(spriteTexture);
        
        // Scale the sprite to appropriate size
        sf::Vector2u textureSize = spriteTexture.getSize();
        float scaleX = (32.0f * Layout::SPRITE_SCALE) / textureSize.x;
        float scaleY = (32.0f * Layout::SPRITE_SCALE) / textureSize.y;
        characterSprite.setScale(sf::Vector2f(scaleX, scaleY));
        
        // Center the sprite
        characterSprite.setPosition(sf::Vector2f(position.x - 16, position.y - 16));
        
        window.draw(characterSprite);
        
        // Selection indicator with glow effect
        if (isSelected) {
            drawGlow(window, position, 25.0f, Colors::ROMAN_GOLD);
            
            // Selection ring
            sf::CircleShape selectionRing(20.0f);
            selectionRing.setPosition(sf::Vector2f(position.x - 20, position.y - 20));
            selectionRing.setFillColor(sf::Color::Transparent);
            selectionRing.setOutlineThickness(3.0f);
            selectionRing.setOutlineColor(Colors::ROMAN_GOLD);
            window.draw(selectionRing);
        }
    }
    
    void drawShadow(sf::RenderWindow& window, const sf::Vector2f& position, float size) {
        sf::CircleShape shadow(size);
        shadow.setPosition(sf::Vector2f(position.x - size + Layout::SHADOW_OFFSET, 
                                       position.y - size + Layout::SHADOW_OFFSET));
        shadow.setFillColor(sf::Color(0, 0, 0, 100));
        window.draw(shadow);
    }
    
    void drawGlow(sf::RenderWindow& window, const sf::Vector2f& position, float radius, const sf::Color& color) {
        sf::CircleShape glow(radius);
        glow.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
        sf::Color glowColor = color;
        glowColor.a = 60;  // Semi-transparent
        glow.setFillColor(glowColor);
        window.draw(glow);
    }
}
