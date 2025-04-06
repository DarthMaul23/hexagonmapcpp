#ifndef ARMY_PANEL_HPP
#define ARMY_PANEL_HPP

#include "../../Common/Panel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

// Forward declarations
class Army;

/**
 * ArmyPanel component that displays army information and unit management.
 * Extracted from UIManager to follow component-based architecture.
 */
class ArmyPanel : public Panel {
private:
    // Army management panel
    bool showArmyPanel;
    sf::RectangleShape armyPanel;
    sf::Text armyTitle;
    sf::Text armyCounts;
    
    // Unit slots for displaying army units
    std::vector<sf::RectangleShape> unitSlots;
    std::vector<sf::Text> unitTexts;
    
    // Button for returning to game
    sf::RectangleShape backButton;
    sf::Text backText;
    
    // Reference to the currently selected army (or nullptr if none)
    Army* selectedArmy;

public:
    ArmyPanel(const sf::Font& font);
    ~ArmyPanel() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // ArmyPanel specific methods
    void showArmyInfo(Army* army);
    void hidePanel() { showArmyPanel = false; }
    bool isPanelVisible() const { return showArmyPanel; }
    
    // Interaction handlers
    bool isBackButtonClicked(const sf::Vector2f& position) const;
    bool isUnitSlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    
private:
    // Helper methods
    void updateArmyDisplay();
    void positionElements(float windowWidth, float windowHeight);
    void initializeUnitSlots();
};

#endif // ARMY_PANEL_HPP

