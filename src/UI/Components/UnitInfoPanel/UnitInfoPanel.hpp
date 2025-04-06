#ifndef UNIT_INFO_PANEL_HPP
#define UNIT_INFO_PANEL_HPP

#include "../../Common/Panel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// Forward declarations
class PlayerUnit;

namespace ui {

/**
 * UnitInfoPanel component that displays information about a selected unit.
 * Extracted from UIManager to follow component-based architecture.
 */
class UnitInfoPanel : public Panel {
private:
    // Unit info panel elements
    sf::RectangleShape unitInfoPanel;
    sf::Text unitTitle;
    sf::Text unitTypeText;
    sf::Text unitHealthText;
    sf::Text unitMovementText;
    sf::Text unitActionText;
    
    // Reference to the currently selected unit (or nullptr if none)
    PlayerUnit* selectedUnit;

public:
    UnitInfoPanel(const sf::Font& font);
    ~UnitInfoPanel() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // UnitInfoPanel specific methods
    void setSelectedUnit(PlayerUnit* unit);
    PlayerUnit* getSelectedUnit() const { return selectedUnit; }
    void clearSelection() { selectedUnit = nullptr; }
    
private:
    // Helper methods
    void updateUnitInfoDisplay();
    void positionElements(float windowHeight);
};

} // namespace ui

#endif // UNIT_INFO_PANEL_HPP
