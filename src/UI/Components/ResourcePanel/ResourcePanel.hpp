#ifndef RESOURCE_PANEL_HPP
#define RESOURCE_PANEL_HPP

#include "../../Common/Panel.hpp"
#include "../../Types/UITypes.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace ui {

/**
 * ResourcePanel component that displays player resources.
 * Extracted from UIManager to follow component-based architecture.
 */
class ResourcePanel : public Panel {
private:
    // Player resources
    PlayerResources playerResources;
    
    // Resource panel elements
    sf::RectangleShape resourcePanel;
    sf::Text resourceTitle;
    sf::Text foodText;
    sf::Text woodText;
    sf::Text stoneText;
    sf::Text goldText;

public:
    ResourcePanel(const sf::Font& font);
    ~ResourcePanel() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // ResourcePanel specific methods
    void updateResources(const PlayerResources& resources);
    const PlayerResources& getResources() const { return playerResources; }
    
private:
    // Helper methods
    void updateResourceDisplay();
    void positionElements();
};

} // namespace ui

#endif // RESOURCE_PANEL_HPP
