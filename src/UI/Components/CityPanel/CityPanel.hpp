#ifndef CITY_PANEL_HPP
#define CITY_PANEL_HPP

#include "../../Common/Panel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

// Forward declaration to avoid circular dependency
namespace game {
    class GameCity;
}

namespace ui {

/**
 * CityPanel component that displays city information and production options.
 * Extracted from UIManager to follow component-based architecture.
 */
class CityPanel : public Panel {
private:
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
    
    // Button for returning to game
    sf::RectangleShape backButton;
    sf::Text backText;
    
    // Reference to the currently selected city (or nullptr if none)
    game::GameCity* selectedCity;

public:
    CityPanel(const sf::Font& font);
    ~CityPanel() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // CityPanel specific methods
    void showCityInfo(game::GameCity* city);
    void hidePanel() { showCityPanel = false; }
    bool isPanelVisible() const { return showCityPanel; }
    
    // Button click handlers
    bool isSettlerButtonClicked(const sf::Vector2f& position) const;
    bool isWarriorButtonClicked(const sf::Vector2f& position) const;
    bool isBuilderButtonClicked(const sf::Vector2f& position) const;
    bool isBuildingButtonClicked(const sf::Vector2f& position) const;
    bool isBackButtonClicked(const sf::Vector2f& position) const;
    
private:
    // Helper methods
    void updateCityDisplay();
    void positionElements(float windowWidth, float windowHeight);
};

} // namespace ui

#endif // CITY_PANEL_HPP
