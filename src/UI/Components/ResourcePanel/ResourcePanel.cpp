#include "ResourcePanel.hpp"
#include <iostream>

namespace ui {

ResourcePanel::ResourcePanel(const sf::Font& font)
    : Panel(font),
      playerResources{0, 0, 0, 0} // Start with zero resources
{
    // Initialize text elements with the font
    resourceTitle.setFont(font);
    foodText.setFont(font);
    woodText.setFont(font);
    stoneText.setFont(font);
    goldText.setFont(font);
}

bool ResourcePanel::initialize()
{
    // Set up resource panel background
    resourcePanel.setSize(sf::Vector2f(200.f, 120.f));
    resourcePanel.setFillColor(sf::Color(40, 40, 60, 230));
    resourcePanel.setOutlineColor(sf::Color(100, 100, 150));
    resourcePanel.setOutlineThickness(2.f);
    
    // Initialize text properties
    resourceTitle.setString("Resources");
    resourceTitle.setCharacterSize(18);
    resourceTitle.setFillColor(sf::Color::White);
    
    foodText.setCharacterSize(14);
    foodText.setFillColor(sf::Color(200, 230, 150));  // Softer green
    
    woodText.setCharacterSize(14);
    woodText.setFillColor(sf::Color(160, 120, 80));   // Brown
    
    stoneText.setCharacterSize(14);
    stoneText.setFillColor(sf::Color(180, 180, 180)); // Light gray
    
    goldText.setCharacterSize(14);
    goldText.setFillColor(sf::Color(255, 215, 0));    // Gold
    
    updateResourceDisplay();
    return true;
}

void ResourcePanel::updateResources(const PlayerResources& resources)
{
    playerResources = resources;
    updateResourceDisplay();
}

void ResourcePanel::updateResourceDisplay()
{
    foodText.setString("Food: " + std::to_string(playerResources.food));
    woodText.setString("Wood: " + std::to_string(playerResources.wood));
    stoneText.setString("Stone: " + std::to_string(playerResources.stone));
    goldText.setString("Gold: " + std::to_string(playerResources.gold));
}

void ResourcePanel::positionElements()
{
    // Position resource panel in top-left corner
    resourcePanel.setPosition(sf::Vector2f(10.f, 10.f));
    
    // Position text elements with proper spacing
    resourceTitle.setPosition(sf::Vector2f(20.f, 15.f));
    foodText.setPosition(sf::Vector2f(20.f, 40.f));
    woodText.setPosition(sf::Vector2f(20.f, 60.f));
    stoneText.setPosition(sf::Vector2f(20.f, 80.f));
    goldText.setPosition(sf::Vector2f(20.f, 100.f));
}

void ResourcePanel::draw(sf::RenderWindow& window)
{
    if (!isShown()) return;
    
    // Position elements before drawing
    positionElements();
    
    // Draw all elements
    window.draw(resourcePanel);
    window.draw(resourceTitle);
    window.draw(foodText);
    window.draw(woodText);
    window.draw(stoneText);
    window.draw(goldText);
}

void ResourcePanel::update(float deltaTime)
{
    // No dynamic updates needed for resource panel
    // Resources are updated through updateResources method
}

} // namespace ui
