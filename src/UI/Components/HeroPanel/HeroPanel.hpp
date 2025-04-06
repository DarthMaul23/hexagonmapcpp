#ifndef HERO_PANEL_HPP
#define HERO_PANEL_HPP

#include "../../Common/Panel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

// Forward declarations
class Hero;
enum class HeroAttribute;

namespace ui {

/**
 * HeroPanel component that displays hero information, inventory, and skills.
 * Extracted from UIManager to follow component-based architecture.
 */
class HeroPanel : public Panel {
private:
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
    
    // Button for returning to game
    sf::RectangleShape backButton;
    sf::Text backText;
    
    // Reference to the currently selected hero (or nullptr if none)
    Hero* selectedHero;

public:
    HeroPanel(const sf::Font& font);
    ~HeroPanel() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // HeroPanel specific methods
    void showHeroInfo(Hero* hero);
    void hidePanel() { showHeroPanel = false; }
    bool isPanelVisible() const { return showHeroPanel; }
    
    // Interaction handlers
    bool isBackButtonClicked(const sf::Vector2f& position) const;
    bool isInventorySlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    bool isSkillSlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    
private:
    // Helper methods
    void updateHeroDisplay();
    void positionElements(float windowWidth, float windowHeight);
    void initializeInventorySlots();
    void initializeSkillSlots();
};

} // namespace ui

#endif // HERO_PANEL_HPP
