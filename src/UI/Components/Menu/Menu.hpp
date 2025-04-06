#ifndef MENU_HPP
#define MENU_HPP

#include "../../Common/UIComponent.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace ui {

/**
 * Menu component that displays the game's main menu.
 * Extracted from UIManager to follow component-based architecture.
 */
class Menu : public UIComponent {
private:
    // Menu elements
    bool showMenu;
    sf::RectangleShape menuBackground;
    sf::Text gameTitle;
    
    // Menu buttons
    sf::RectangleShape startButton;
    sf::Text startText;
    sf::RectangleShape optionsButton;
    sf::Text optionsText;
    sf::RectangleShape quitButton;
    sf::Text quitText;
    
    // Font reference
    const sf::Font& font;

public:
    Menu(const sf::Font& font);
    ~Menu() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // Menu specific methods
    void showMainMenu() { showMenu = true; }
    void hideMenu() { showMenu = false; }
    bool isMenuVisible() const { return showMenu; }
    
    // Interaction handlers
    bool isStartButtonClicked(const sf::Vector2f& position) const;
    bool isOptionsButtonClicked(const sf::Vector2f& position) const;
    bool isQuitButtonClicked(const sf::Vector2f& position) const;
    
private:
    // Helper methods
    void positionElements(float windowWidth, float windowHeight);
};

} // namespace ui

#endif // MENU_HPP
