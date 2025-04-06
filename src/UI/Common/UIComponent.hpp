#ifndef UI_COMPONENT_HPP
#define UI_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace ui {

class UIComponent {
public:
    virtual ~UIComponent() = default;
    
    // Core interface that all UI components must implement
    virtual bool initialize() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    
    // Common functionality
    virtual void show() { isVisible = true; }
    virtual void hide() { isVisible = false; }
    virtual bool isShown() const { return isVisible; }

protected:
    bool isVisible = true;
};

} // namespace ui

#endif // UI_COMPONENT_HPP
