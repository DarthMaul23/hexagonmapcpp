#include "UnitInfoPanel.hpp"
#include "PlayerUnit.hpp"
#include <iostream>

namespace ui {

UnitInfoPanel::UnitInfoPanel(const sf::Font& font)
    : Panel(font),
      selectedUnit(nullptr)
{
    // Initialize text elements with the font
    unitTitle.setFont(font);
    unitTypeText.setFont(font);
    unitHealthText.setFont(font);
    unitMovementText.setFont(font);
    unitActionText.setFont(font);
}

bool UnitInfoPanel::initialize()
{
    // Set up unit info panel
    unitInfoPanel.setSize(sf::Vector2f(200.f, 150.f));
    unitInfoPanel.setFillColor(sf::Color(40, 40, 60, 230));
    unitInfoPanel.setOutlineColor(sf::Color(100, 100, 150));
    unitInfoPanel.setOutlineThickness(2.f);
    
    // Initialize text properties
    unitTitle.setString("Selected Unit");
    unitTitle.setCharacterSize(18);
    unitTitle.setFillColor(sf::Color::White);
    
    unitTypeText.setCharacterSize(14);
    unitTypeText.setFillColor(sf::Color::White);
    
    unitHealthText.setCharacterSize(14);
    unitHealthText.setFillColor(sf::Color::White);
    
    unitMovementText.setCharacterSize(14);
    unitMovementText.setFillColor(sf::Color::White);
    
    unitActionText.setCharacterSize(14);
    unitActionText.setFillColor(sf::Color::White);
    
    return true;
}

void UnitInfoPanel::setSelectedUnit(PlayerUnit* unit)
{
    selectedUnit = unit;
    if (unit) {
        show();
        updateUnitInfoDisplay();
    } else {
        hide();
    }
}

void UnitInfoPanel::updateUnitInfoDisplay()
{
    if (!selectedUnit) return;
    
    unitTitle.setString(selectedUnit->getName());
    unitTypeText.setString("Type: " + selectedUnit->getTypeString());
    unitHealthText.setString("Health: " + std::to_string(selectedUnit->getHealth()) + "/" + 
                           std::to_string(selectedUnit->getMaxHealth()));
    unitMovementText.setString("Movement: " + std::to_string(selectedUnit->getMovement()) + "/" + 
                             std::to_string(selectedUnit->getMaxMovement()));
    
    // Set action text based on unit type
    switch(selectedUnit->getType()) {
        case UnitType::Settler:
            unitActionText.setString("[F] - Found City");
            break;
        case UnitType::Warrior:
            unitActionText.setString("[A] - Attack");
            break;
        default:
            unitActionText.setString("");
    }
}

void UnitInfoPanel::positionElements(float windowHeight)
{
    // Position unit info panel in bottom-left
    unitInfoPanel.setPosition(sf::Vector2f(10.f, windowHeight - 160.f));
    unitTitle.setPosition(sf::Vector2f(20.f, windowHeight - 155.f));
    unitTypeText.setPosition(sf::Vector2f(20.f, windowHeight - 130.f));
    unitHealthText.setPosition(sf::Vector2f(20.f, windowHeight - 110.f));
    unitMovementText.setPosition(sf::Vector2f(20.f, windowHeight - 90.f));
    unitActionText.setPosition(sf::Vector2f(20.f, windowHeight - 70.f));
}

void UnitInfoPanel::draw(sf::RenderWindow& window)
{
    if (!isShown() || !selectedUnit) return;
    
    // Get the window height for proper positioning
    float windowHeight = window.getView().getSize().y;
    
    // Position elements before drawing
    positionElements(windowHeight);
    
    // Draw all elements
    window.draw(unitInfoPanel);
    window.draw(unitTitle);
    window.draw(unitTypeText);
    window.draw(unitHealthText);
    window.draw(unitMovementText);
    window.draw(unitActionText);
}

void UnitInfoPanel::update(float deltaTime)
{
    if (isShown() && selectedUnit) {
        updateUnitInfoDisplay();
    }
}

} // namespace ui
