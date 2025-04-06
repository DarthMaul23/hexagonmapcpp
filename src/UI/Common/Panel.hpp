#ifndef PANEL_HPP
#define PANEL_HPP

#include "UIComponent.hpp"
#include <SFML/Graphics.hpp>

namespace ui {

class Panel : public UIComponent {
public:
    explicit Panel(const sf::Font& font) : font(font) {}
    virtual ~Panel() = default;

    // Common panel functionality
    virtual void setPosition(const sf::Vector2f& pos) { position = pos; }
    virtual void setSize(const sf::Vector2f& size) { dimensions = size; }
    virtual const sf::Vector2f& getPosition() const { return position; }
    virtual const sf::Vector2f& getSize() const { return dimensions; }

protected:
    const sf::Font& font;
    sf::Vector2f position;
    sf::Vector2f dimensions;
};

} // namespace ui

#endif // PANEL_HPP
