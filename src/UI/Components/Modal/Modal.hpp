#ifndef MODAL_HPP
#define MODAL_HPP

#include "../../Common/UIComponent.hpp"
#include <SFML/Graphics.hpp>
#include <string>

/**
 * Modal component that displays information in a popup dialog.
 * Extracted from UIManager to follow component-based architecture.
 */
class Modal : public UIComponent {
private:
    // Modal elements
    bool showModal;
    sf::RectangleShape modalBackground;
    sf::Text modalTitle;
    sf::Text modalContent;
    
    // Close button
    sf::RectangleShape closeButton;
    sf::Text closeText;
    
    // Font reference
    const sf::Font& font;

public:
    Modal(const sf::Font& font);
    ~Modal() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // Modal specific methods
    void showInfo(const std::string& title, const std::string& content);
    void hideModal() { showModal = false; }
    bool isModalVisible() const { return showModal; }
    
    // Interaction handlers
    bool isCloseButtonClicked(const sf::Vector2f& position) const;
    
private:
    // Helper methods
    void positionElements(float windowWidth, float windowHeight);
};

#endif // MODAL_HPP

