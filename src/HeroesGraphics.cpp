#include "HeroesGraphics.hpp"
#include <cmath>

namespace HeroesGraphics {
    
    sf::Color getTileColor(game::TileType type, bool isShaded) {
        sf::Color baseColor;
        
        switch (type) {
            case game::TileType::Plains:
                baseColor = Colors::GRASS_GREEN;
                break;
            case game::TileType::Hills:
                baseColor = Colors::DIRT_BROWN;
                break;
            case game::TileType::Mountain:
                baseColor = Colors::MOUNTAIN_GRAY;
                break;
            case game::TileType::Forest:
                baseColor = Colors::FOREST_DARK_GREEN;
                break;
            case game::TileType::Water:
                baseColor = Colors::WATER_BLUE;
                break;
            default:
                baseColor = Colors::GRASS_GREEN;
                break;
        }
        
        if (isShaded) {
            // Darken the color for shading effect
            return sf::Color(
                static_cast<uint8_t>(baseColor.r * 0.7f),
                static_cast<uint8_t>(baseColor.g * 0.7f),
                static_cast<uint8_t>(baseColor.b * 0.7f),
                baseColor.a
            );
        }
        
        return baseColor;
    }
    
    sf::Color getResourceColor(game::ResourceType type) {
        switch (type) {
            case game::ResourceType::Gold:
                return Colors::GOLD;
            case game::ResourceType::Wood:
                return Colors::WOOD;
            case game::ResourceType::Stone:
                return Colors::STONE;
            case game::ResourceType::Food:
                return Colors::FOOD;
            default:
                return sf::Color::White;
        }
    }
    
    void drawDetailedHexagon(sf::RenderWindow& window, const game::Tile& tile, float hexSize) {
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
        
        // Set base color
        hexagon.setFillColor(getTileColor(tile.type));
        hexagon.setOutlineThickness(2.0f);
        hexagon.setOutlineColor(sf::Color(50, 50, 50, 180));
        
        window.draw(hexagon);
        
        // Add texture effect with smaller shapes
        if (tile.type == game::TileType::Forest) {
            // Draw small circles to represent trees
            for (int i = 0; i < 3; ++i) {
                sf::CircleShape tree(3.0f);
                float treeAngle = i * 120.0f * M_PI / 180.0f;
                float treeRadius = hexSize * 0.4f;
                tree.setPosition(sf::Vector2f(
                    center.x + treeRadius * std::cos(treeAngle) - 3.0f,
                    center.y + treeRadius * std::sin(treeAngle) - 3.0f
                ));
                tree.setFillColor(sf::Color(20, 100, 20));
                window.draw(tree);
            }
        } else if (tile.type == game::TileType::Hills) {
            // Draw small triangles to represent hills
            sf::ConvexShape hill;
            hill.setPointCount(3);
            hill.setPoint(0, sf::Vector2f(center.x - 5, center.y + 3));
            hill.setPoint(1, sf::Vector2f(center.x, center.y - 5));
            hill.setPoint(2, sf::Vector2f(center.x + 5, center.y + 3));
            hill.setFillColor(sf::Color(120, 100, 80));
            window.draw(hill);
        } else if (tile.type == game::TileType::Mountain) {
            // Draw jagged mountain shape
            sf::ConvexShape mountain;
            mountain.setPointCount(5);
            mountain.setPoint(0, sf::Vector2f(center.x - 8, center.y + 5));
            mountain.setPoint(1, sf::Vector2f(center.x - 3, center.y - 8));
            mountain.setPoint(2, sf::Vector2f(center.x, center.y - 6));
            mountain.setPoint(3, sf::Vector2f(center.x + 3, center.y - 8));
            mountain.setPoint(4, sf::Vector2f(center.x + 8, center.y + 5));
            mountain.setFillColor(sf::Color(80, 80, 80));
            window.draw(mountain);
        } else if (tile.type == game::TileType::Water) {
            // Draw animated wave effect with multiple layers
            for (int i = 0; i < 3; ++i) {
                sf::CircleShape wave(6.0f + i * 2, 6);
                wave.setPosition(sf::Vector2f(center.x - 6 + i * 4, center.y - 4 + i * 2));
                sf::Color waveColor = sf::Color(30 + i * 10, 120 + i * 15, 200 + i * 10, 80 + i * 20);
                wave.setFillColor(waveColor);
                window.draw(wave);
            }
            
            // Add sparkle effect on water
            sf::CircleShape sparkle(1.5f);
            sparkle.setPosition(sf::Vector2f(center.x + hexSize * 0.3f, center.y - hexSize * 0.2f));
            sparkle.setFillColor(sf::Color(255, 255, 255, 150));
            window.draw(sparkle);
        }
        
        // Draw resource indicator if tile has resources
        if (tile.resource.hasResource) {
            sf::CircleShape resourceIcon(4.0f);
            resourceIcon.setPosition(sf::Vector2f(center.x + hexSize * 0.6f - 4, center.y - hexSize * 0.6f - 4));
            resourceIcon.setFillColor(getResourceColor(tile.resource.resourceType));
            resourceIcon.setOutlineThickness(1.0f);
            resourceIcon.setOutlineColor(sf::Color::Black);
            window.draw(resourceIcon);
        }
    }
    
    sf::RectangleShape createHeroesPanel(float x, float y, float width, float height) {
        sf::RectangleShape panel;
        panel.setPosition(sf::Vector2f(x, y));
        panel.setSize(sf::Vector2f(width, height));
        panel.setFillColor(Colors::UI_BACKGROUND);
        panel.setOutlineThickness(3.0f);
        panel.setOutlineColor(Colors::UI_BORDER);
        return panel;
    }
    
    sf::Text createHeroesText(const std::string& text, const sf::Font& font, unsigned int size) {
        sf::Text heroesText(font);
        heroesText.setString(text);
        heroesText.setCharacterSize(size);
        heroesText.setFillColor(Colors::UI_TEXT);
        heroesText.setOutlineThickness(1.0f);
        heroesText.setOutlineColor(sf::Color::Black);
        return heroesText;
    }
    
    sf::RectangleShape createHeroesButton(float x, float y, float width, float height) {
        sf::RectangleShape button;
        button.setPosition(sf::Vector2f(x, y));
        button.setSize(sf::Vector2f(width, height));
        button.setFillColor(Colors::UI_BUTTON);
        button.setOutlineThickness(2.0f);
        button.setOutlineColor(Colors::UI_BORDER);
        return button;
    }
    
    void drawResourceIcon(sf::RenderWindow& window, game::ResourceType type, const sf::Vector2f& position, int amount, const sf::Font& font) {
        // Draw resource icon background
        sf::CircleShape icon(12.0f);
        icon.setPosition(sf::Vector2f(position.x - 12, position.y - 12));
        icon.setFillColor(getResourceColor(type));
        icon.setOutlineThickness(2.0f);
        icon.setOutlineColor(sf::Color::Black);
        window.draw(icon);
        
        // Draw resource symbol
        sf::Text symbol = createHeroesText("", font, 12);
        symbol.setPosition(sf::Vector2f(position.x - 5, position.y - 8));
        
        switch (type) {
            case game::ResourceType::Gold:
                symbol.setString("G");
                break;
            case game::ResourceType::Wood:
                symbol.setString("W");
                break;
            case game::ResourceType::Stone:
                symbol.setString("S");
                break;
            case game::ResourceType::Food:
                symbol.setString("F");
                break;
        }
        
        window.draw(symbol);
        
        // Draw amount text
        sf::Text amountText = createHeroesText(std::to_string(amount), font, 10);
        amountText.setPosition(sf::Vector2f(position.x + 15, position.y - 5));
        window.draw(amountText);
    }
    
    void drawUnit(sf::RenderWindow& window, const sf::Vector2f& position, UnitType type, bool isSelected) {
        // Draw unit base
        sf::CircleShape unitBase(15.0f);
        unitBase.setPosition(sf::Vector2f(position.x - 15, position.y - 15));
        
        // Set color based on unit type
        switch (type) {
            case UnitType::Settler:
                unitBase.setFillColor(sf::Color(160, 82, 45)); // Brown
                break;
            case UnitType::Warrior:
                unitBase.setFillColor(sf::Color(139, 0, 0)); // Dark red
                break;
            case UnitType::Builder:
                unitBase.setFillColor(sf::Color(184, 134, 11)); // Dark yellow
                break;
        }
        
        if (isSelected) {
            unitBase.setOutlineThickness(3.0f);
            unitBase.setOutlineColor(sf::Color::Yellow);
        } else {
            unitBase.setOutlineThickness(2.0f);
            unitBase.setOutlineColor(sf::Color::Black);
        }
        
        window.draw(unitBase);
        
        // Draw unit symbol
        sf::RectangleShape symbol(sf::Vector2f(10, 10));
        symbol.setPosition(sf::Vector2f(position.x - 5, position.y - 5));
        symbol.setFillColor(sf::Color::White);
        window.draw(symbol);
    }
    
    void drawHero(sf::RenderWindow& window, const sf::Vector2f& position, bool isSelected) {
        // Draw hero base (larger than regular units)
        sf::CircleShape heroBase(20.0f);
        heroBase.setPosition(sf::Vector2f(position.x - 20, position.y - 20));
        heroBase.setFillColor(sf::Color(25, 25, 112)); // Midnight blue
        
        if (isSelected) {
            heroBase.setOutlineThickness(4.0f);
            heroBase.setOutlineColor(Colors::GOLD);
        } else {
            heroBase.setOutlineThickness(3.0f);
            heroBase.setOutlineColor(sf::Color(192, 192, 192)); // Silver color
        }
        
        window.draw(heroBase);
        
        // Draw hero crown/symbol
        sf::ConvexShape crown;
        crown.setPointCount(5);
        crown.setPoint(0, sf::Vector2f(position.x - 8, position.y + 2));
        crown.setPoint(1, sf::Vector2f(position.x - 5, position.y - 5));
        crown.setPoint(2, sf::Vector2f(position.x, position.y - 8));
        crown.setPoint(3, sf::Vector2f(position.x + 5, position.y - 5));
        crown.setPoint(4, sf::Vector2f(position.x + 8, position.y + 2));
        crown.setFillColor(Colors::GOLD);
        crown.setOutlineThickness(1.0f);
        crown.setOutlineColor(sf::Color::Black);
        window.draw(crown);
    }
    
    void drawCity(sf::RenderWindow& window, const sf::Vector2f& position, const std::string& name, const sf::Font& font) {
        // Draw city base (larger hexagonal foundation)
        sf::ConvexShape cityBase;
        cityBase.setPointCount(6);
        float baseSize = 25.0f;
        for (int i = 0; i < 6; ++i) {
            float angle_rad = M_PI / 180.f * (60 * i + 30);
            float x = position.x + baseSize * std::cos(angle_rad);
            float y = position.y + baseSize * std::sin(angle_rad);
            cityBase.setPoint(i, sf::Vector2f(x, y));
        }
        cityBase.setFillColor(sf::Color(101, 67, 33)); // Heroes brown
        cityBase.setOutlineThickness(3.0f);
        cityBase.setOutlineColor(sf::Color(139, 69, 19));
        window.draw(cityBase);
        
        // Draw main castle structure
        sf::RectangleShape mainKeep(sf::Vector2f(30, 35));
        mainKeep.setPosition(sf::Vector2f(position.x - 15, position.y - 20));
        mainKeep.setFillColor(sf::Color(160, 82, 45)); // Saddle brown
        mainKeep.setOutlineThickness(2.0f);
        mainKeep.setOutlineColor(sf::Color::Black);
        window.draw(mainKeep);
        
        // Draw castle towers (4 corners)
        for (int i = 0; i < 4; ++i) {
            sf::CircleShape tower(8.0f);
            float towerX = position.x + (i % 2 == 0 ? -18 : 18);
            float towerY = position.y + (i < 2 ? -25 : 15);
            tower.setPosition(sf::Vector2f(towerX - 8, towerY - 8));
            tower.setFillColor(sf::Color(105, 105, 105)); // Dark gray
            tower.setOutlineThickness(2.0f);
            tower.setOutlineColor(sf::Color::Black);
            window.draw(tower);
            
            // Add tower tops (conic roofs)
            sf::ConvexShape roof;
            roof.setPointCount(3);
            roof.setPoint(0, sf::Vector2f(towerX - 6, towerY));
            roof.setPoint(1, sf::Vector2f(towerX, towerY - 12));
            roof.setPoint(2, sf::Vector2f(towerX + 6, towerY));
            roof.setFillColor(sf::Color(139, 0, 0)); // Dark red
            window.draw(roof);
        }
        
        // Draw castle gate
        sf::RectangleShape gate(sf::Vector2f(12, 16));
        gate.setPosition(sf::Vector2f(position.x - 6, position.y + 4));
        gate.setFillColor(sf::Color(69, 39, 19)); // Dark brown
        gate.setOutlineThickness(1.0f);
        gate.setOutlineColor(sf::Color::Black);
        window.draw(gate);
        
        // Draw banner/flag
        sf::ConvexShape banner;
        banner.setPointCount(4);
        banner.setPoint(0, sf::Vector2f(position.x + 10, position.y - 30));
        banner.setPoint(1, sf::Vector2f(position.x + 25, position.y - 28));
        banner.setPoint(2, sf::Vector2f(position.x + 22, position.y - 20));
        banner.setPoint(3, sf::Vector2f(position.x + 10, position.y - 22));
        banner.setFillColor(Colors::GOLD);
        banner.setOutlineThickness(1.0f);
        banner.setOutlineColor(sf::Color::Black);
        window.draw(banner);
        
        // Draw flag pole
        sf::RectangleShape flagPole(sf::Vector2f(2, 20));
        flagPole.setPosition(sf::Vector2f(position.x + 9, position.y - 30));
        flagPole.setFillColor(sf::Color(139, 69, 19));
        window.draw(flagPole);
        
        // Draw city name with enhanced styling
        sf::Text cityName = createHeroesText(name, font, 14);
        sf::FloatRect textBounds = cityName.getLocalBounds();
        cityName.setPosition(sf::Vector2f(position.x - textBounds.size.x / 2, position.y + 30));
        
        // Add text shadow for better readability
        sf::Text shadow = cityName;
        shadow.setPosition(sf::Vector2f(position.x - textBounds.size.x / 2 + 1, position.y + 31));
        shadow.setFillColor(sf::Color::Black);
        window.draw(shadow);
        window.draw(cityName);
    }
    
    void drawHeroesBorder(sf::RenderWindow& window, float x, float y, float width, float height) {
        // Outer border - dark brown
        sf::RectangleShape outerBorder(sf::Vector2f(width, height));
        outerBorder.setPosition(sf::Vector2f(x, y));
        outerBorder.setFillColor(sf::Color::Transparent);
        outerBorder.setOutlineThickness(4.0f);
        outerBorder.setOutlineColor(sf::Color(69, 39, 19));
        window.draw(outerBorder);
        
        // Inner border - lighter brown with gold accents
        sf::RectangleShape innerBorder(sf::Vector2f(width - 8, height - 8));
        innerBorder.setPosition(sf::Vector2f(x + 4, y + 4));
        innerBorder.setFillColor(sf::Color::Transparent);
        innerBorder.setOutlineThickness(2.0f);
        innerBorder.setOutlineColor(Colors::GOLD);
        window.draw(innerBorder);
        
        // Corner decorations
        for (int i = 0; i < 4; ++i) {
            sf::CircleShape cornerDecor(8.0f);
            float cornerX = (i % 2 == 0) ? x : x + width - 16;
            float cornerY = (i < 2) ? y : y + height - 16;
            cornerDecor.setPosition(sf::Vector2f(cornerX, cornerY));
            cornerDecor.setFillColor(Colors::GOLD);
            cornerDecor.setOutlineThickness(2.0f);
            cornerDecor.setOutlineColor(sf::Color(139, 69, 19));
            window.draw(cornerDecor);
        }
    }
    
    void drawMinimap(sf::RenderWindow& window, float x, float y, float size, const sf::Vector2f& playerPosition) {
        // Minimap background
        sf::RectangleShape minimapBg(sf::Vector2f(size, size));
        minimapBg.setPosition(sf::Vector2f(x, y));
        minimapBg.setFillColor(sf::Color(50, 50, 50, 200));
        minimapBg.setOutlineThickness(2.0f);
        minimapBg.setOutlineColor(Colors::UI_BORDER);
        window.draw(minimapBg);
        
        // Simple terrain representation (placeholder)
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                sf::RectangleShape terrainPixel(sf::Vector2f(size/8, size/8));
                terrainPixel.setPosition(sf::Vector2f(x + i * size/8, y + j * size/8));
                
                // Random terrain colors for demo
                int terrainType = (i + j) % 4;
                switch (terrainType) {
                    case 0: terrainPixel.setFillColor(Colors::GRASS_GREEN); break;
                    case 1: terrainPixel.setFillColor(Colors::DIRT_BROWN); break;
                    case 2: terrainPixel.setFillColor(Colors::FOREST_DARK_GREEN); break;
                    case 3: terrainPixel.setFillColor(Colors::WATER_BLUE); break;
                }
                window.draw(terrainPixel);
            }
        }
        
        // Player position indicator
        sf::CircleShape playerIndicator(3.0f);
        playerIndicator.setPosition(sf::Vector2f(x + size/2 - 3, y + size/2 - 3));
        playerIndicator.setFillColor(sf::Color::Red);
        playerIndicator.setOutlineThickness(1.0f);
        playerIndicator.setOutlineColor(sf::Color::White);
        window.draw(playerIndicator);
    }
    
    void drawTerrainTransition(sf::RenderWindow& window, const game::Tile& tile, const std::vector<std::vector<game::Tile>>& tileMap, int x, int y, float hexSize) {
        // Check neighboring tiles for terrain transitions
        const sf::Vector2f& center = tile.center;
        
        // Define hexagon neighbor offsets (for hexagonal grid)
        std::vector<std::pair<int, int>> neighbors = {
            {0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}
        };
        
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int nx = x + neighbors[i].first;
            int ny = y + neighbors[i].second;
            
            // Check bounds
            if (nx >= 0 && nx < static_cast<int>(tileMap.size()) && 
                ny >= 0 && ny < static_cast<int>(tileMap[0].size())) {
                
                if (tileMap[nx][ny].type != tile.type) {
                    // Draw transition edge
                    sf::ConvexShape transitionEdge;
                    transitionEdge.setPointCount(3);
                    
                    float angle = i * 60.0f * M_PI / 180.0f;
                    float nextAngle = ((i + 1) % 6) * 60.0f * M_PI / 180.0f;
                    
                    transitionEdge.setPoint(0, sf::Vector2f(center.x, center.y));
                    transitionEdge.setPoint(1, sf::Vector2f(
                        center.x + hexSize * 0.8f * std::cos(angle + M_PI / 6.0f),
                        center.y + hexSize * 0.8f * std::sin(angle + M_PI / 6.0f)
                    ));
                    transitionEdge.setPoint(2, sf::Vector2f(
                        center.x + hexSize * 0.8f * std::cos(nextAngle + M_PI / 6.0f),
                        center.y + hexSize * 0.8f * std::sin(nextAngle + M_PI / 6.0f)
                    ));
                    
                    // Blend colors based on neighboring terrain
                    sf::Color neighborColor = getTileColor(tileMap[nx][ny].type);
                    sf::Color blendColor = sf::Color(
                        (getTileColor(tile.type).r + neighborColor.r) / 2,
                        (getTileColor(tile.type).g + neighborColor.g) / 2,
                        (getTileColor(tile.type).b + neighborColor.b) / 2,
                        150
                    );
                    
                    transitionEdge.setFillColor(blendColor);
                    window.draw(transitionEdge);
                }
            }
        }
    }
    
    void drawResourceDeposit(sf::RenderWindow& window, const sf::Vector2f& position, game::ResourceType type, float hexSize) {
        // Draw larger, more prominent resource deposits
        sf::ConvexShape deposit;
        
        switch (type) {
            case game::ResourceType::Gold: {
                // Draw gold mine entrance
                deposit.setPointCount(4);
                deposit.setPoint(0, sf::Vector2f(position.x - 8, position.y + 4));
                deposit.setPoint(1, sf::Vector2f(position.x - 4, position.y - 8));
                deposit.setPoint(2, sf::Vector2f(position.x + 4, position.y - 8));
                deposit.setPoint(3, sf::Vector2f(position.x + 8, position.y + 4));
                deposit.setFillColor(sf::Color(255, 215, 0));
                break;
            }
            case game::ResourceType::Wood: {
                // Draw multiple trees
                for (int i = 0; i < 5; ++i) {
                    sf::CircleShape tree(2.0f + i);
                    float treeAngle = i * 72.0f * M_PI / 180.0f;
                    float treeRadius = hexSize * 0.3f;
                    tree.setPosition(sf::Vector2f(
                        position.x + treeRadius * std::cos(treeAngle) - (2.0f + i),
                        position.y + treeRadius * std::sin(treeAngle) - (2.0f + i)
                    ));
                    tree.setFillColor(sf::Color(34, 139, 34));
                    window.draw(tree);
                }
                return; // Don't draw the standard deposit shape
            }
            case game::ResourceType::Stone: {
                // Draw stone quarry
                deposit.setPointCount(6);
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 60.0f * M_PI / 180.0f;
                    deposit.setPoint(i, sf::Vector2f(
                        position.x + 6 * std::cos(angle),
                        position.y + 6 * std::sin(angle)
                    ));
                }
                deposit.setFillColor(sf::Color(128, 128, 128));
                break;
            }
            case game::ResourceType::Food: {
                // Draw windmill or farm
                deposit.setPointCount(4);
                deposit.setPoint(0, sf::Vector2f(position.x - 6, position.y - 6));
                deposit.setPoint(1, sf::Vector2f(position.x + 6, position.y - 6));
                deposit.setPoint(2, sf::Vector2f(position.x + 6, position.y + 6));
                deposit.setPoint(3, sf::Vector2f(position.x - 6, position.y + 6));
                deposit.setFillColor(sf::Color(255, 140, 0));
                break;
            }
        }
        
        deposit.setOutlineThickness(2.0f);
        deposit.setOutlineColor(sf::Color::Black);
        window.draw(deposit);
        
        // Add sparkle effect for magical resources
        if (type == game::ResourceType::Gold) {
            for (int i = 0; i < 3; ++i) {
                sf::CircleShape sparkle(1.0f);
                float sparkleAngle = i * 120.0f * M_PI / 180.0f;
                sparkle.setPosition(sf::Vector2f(
                    position.x + 10 * std::cos(sparkleAngle),
                    position.y + 10 * std::sin(sparkleAngle)
                ));
                sparkle.setFillColor(sf::Color(255, 255, 0, 200));
                window.draw(sparkle);
            }
        }
    }
}
