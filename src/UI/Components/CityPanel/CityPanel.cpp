#include "CityPanel.hpp"
#include "GameCity.hpp"
#include <iostream>

namespace ui {

CityPanel::CityPanel(const sf::Font& font)
    : Panel(font),
      showCityPanel(false),
      selectedCity(nullptr)
{
    // Initialize text elements with font
    cityTitle.setFont(font);
    cityPopulation.setFont(font);
    cityFood.setFont(font);
    cityProduction.setFont(font);
    cityGold.setFont(font);
    settlerText.setFont(font);
    warriorText.setFont(font);
    builderText.setFont(font);
    buildingText.setFont(font);
    backText.setFont(font);
}

bool CityPanel::initialize()
{
    // Set up city panel background
    cityPanel.setSize(sf::Vector2f(400.f, 300.f));
    cityPanel.setFillColor(sf::Color(40, 40, 60, 230));
    cityPanel.setOutlineColor(sf::Color(100, 100, 150));
    cityPanel.setOutlineThickness(2.f);
    
    // Initialize city info text properties
    cityTitle.setCharacterSize(24);
    cityTitle.setFillColor(sf::Color::White);
    cityTitle.setStyle(sf::Text::Bold);
    
    cityPopulation.setCharacterSize(16);
    cityPopulation.setFillColor(sf::Color::White);
    
    cityFood.setCharacterSize(16);
    cityFood.setFillColor(sf::Color(200, 230, 150));  // Light green
    
    cityProduction.setCharacterSize(16);
    cityProduction.setFillColor(sf::Color(180, 180, 180));  // Light gray
    
    cityGold.setCharacterSize(16);
    cityGold.setFillColor(sf::Color(255, 215, 0));  // Gold
    
    // Initialize production buttons
    settlerButton.setSize(sf::Vector2f(180.f, 40.f));
    settlerButton.setFillColor(sf::Color(60, 60, 100));
    settlerButton.setOutlineColor(sf::Color(100, 100, 150));
    settlerButton.setOutlineThickness(1.f);
    
    warriorButton.setSize(sf::Vector2f(180.f, 40.f));
    warriorButton.setFillColor(sf::Color(60, 60, 100));
    warriorButton.setOutlineColor(sf::Color(100, 100, 150));
    warriorButton.setOutlineThickness(1.f);
    
    builderButton.setSize(sf::Vector2f(180.f, 40.f));
    builderButton.setFillColor(sf::Color(60, 60, 100));
    builderButton.setOutlineColor(sf::Color(100, 100, 150));
    builderButton.setOutlineThickness(1.f);
    
    buildingButton.setSize(sf::Vector2f(180.f, 40.f));
    buildingButton.setFillColor(sf::Color(60, 60, 100));
    buildingButton.setOutlineColor(sf::Color(100, 100, 150));
    buildingButton.setOutlineThickness(1.f);
    
    // Initialize button text
    settlerText.setString("Settler (50 Production)");
    settlerText.setCharacterSize(16);
    settlerText.setFillColor(sf::Color::White);
    
    warriorText.setString("Warrior (30 Production)");
    warriorText.setCharacterSize(16);
    warriorText.setFillColor(sf::Color::White);
    
    builderText.setString("Builder (20 Production)");
    builderText.setCharacterSize(16);
    builderText.setFillColor(sf::Color::White);
    
    buildingText.setString("Granary (40 Production)");
    buildingText.setCharacterSize(16);
    buildingText.setFillColor(sf::Color::White);
    
    // Initialize back button
    backButton.setSize(sf::Vector2f(100.f, 40.f));
    backButton.setFillColor(sf::Color(100, 60, 60));
    backButton.setOutlineColor(sf::Color(150, 100, 100));
    backButton.setOutlineThickness(1.f);
    
    backText.setString("Back");
    backText.setCharacterSize(16);
    backText.setFillColor(sf::Color::White);
    
    return true;
}

void CityPanel::showCityInfo(game::GameCity* city)
{
    if (!city) return;
    
    selectedCity = city;
    showCityPanel = true;
    updateCityDisplay();
}

void CityPanel::updateCityDisplay()
{
    if (!selectedCity) return;
    
    cityTitle.setString(selectedCity->getName());
    cityPopulation.setString("Population: " + std::to_string(selectedCity->getPopulation()));
    cityFood.setString("Food: " + std::to_string(selectedCity->getFood()) + " (+" + 
                      std::to_string(selectedCity->getFoodPerTurn()) + ")");
    cityProduction.setString("Production: " + std::to_string(selectedCity->getProduction()) + " (+" + 
                           std::to_string(selectedCity->getProductionPerTurn()) + ")");
    cityGold.setString("Gold: " + std::to_string(selectedCity->getGold()) + " (+" + 
                      std::to_string(selectedCity->getGoldPerTurn()) + ")");
}

void CityPanel::positionElements(float windowWidth, float windowHeight)
{
    // Center the panel on the screen
    float panelX = (windowWidth - cityPanel.getSize().x) / 2.f;
    float panelY = (windowHeight - cityPanel.getSize().y) / 2.f;
    cityPanel.setPosition(panelX, panelY);
    
    // Position city info text
    float textX = panelX + 20.f;
    float currentY = panelY + 20.f;
    float lineSpacing = 25.f;
    
    // City info section
    cityTitle.setPosition(textX, currentY);
    currentY += lineSpacing * 1.5f;
    
    cityPopulation.setPosition(textX, currentY);
    currentY += lineSpacing;
    
    cityFood.setPosition(textX, currentY);
    currentY += lineSpacing;
    
    cityProduction.setPosition(textX, currentY);
    currentY += lineSpacing;
    
    cityGold.setPosition(textX, currentY);
    currentY += lineSpacing * 1.5f;
    
    // Production buttons section - arrange in two columns
    float leftColumnX = panelX + 20.f;
    float rightColumnX = panelX + 220.f;
    float buttonY = currentY;
    
    // Left column buttons
    settlerButton.setPosition(leftColumnX, buttonY);
    centerTextInButton(settlerText, settlerButton);
    
    builderButton.setPosition(leftColumnX, buttonY + 50.f);
    centerTextInButton(builderText, builderButton);
    
    // Right column buttons
    warriorButton.setPosition(rightColumnX, buttonY);
    centerTextInButton(warriorText, warriorButton);
    
    buildingButton.setPosition(rightColumnX, buttonY + 50.f);
    centerTextInButton(buildingText, buildingButton);
    
    // Back button at the bottom right
    backButton.setPosition(
        panelX + cityPanel.getSize().x - backButton.getSize().x - 20.f,
        panelY + cityPanel.getSize().y - backButton.getSize().y - 20.f
    );
    centerTextInButton(backText, backButton);
}

void CityPanel::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        button.getPosition().x + (button.getSize().x - textBounds.width) / 2.f,
        button.getPosition().y + (button.getSize().y - textBounds.height) / 2.f - 5.f
    );
}

void CityPanel::draw(sf::RenderWindow& window)
{
    if (!showCityPanel) return;
    
    // Position elements before drawing
    positionElements(window.getSize().x, window.getSize().y);
    
    // Draw panel background
    window.draw(cityPanel);
    
    // Draw city info
    window.draw(cityTitle);
    window.draw(cityPopulation);
    window.draw(cityFood);
    window.draw(cityProduction);
    window.draw(cityGold);
    
    // Draw production buttons
    window.draw(settlerButton);
    window.draw(settlerText);
    window.draw(warriorButton);
    window.draw(warriorText);
    window.draw(builderButton);
    window.draw(builderText);
    window.draw(buildingButton);
    window.draw(buildingText);
    
    // Draw back button
    window.draw(backButton);
    window.draw(backText);
}

void CityPanel::update(float deltaTime)
{
    if (showCityPanel && selectedCity) {
        updateCityDisplay();
    }
}

bool CityPanel::isSettlerButtonClicked(const sf::Vector2f& position) const
{
    return showCityPanel && settlerButton.getGlobalBounds().contains(position);
}

bool CityPanel::isWarriorButtonClicked(const sf::Vector2f& position) const
{
    return showCityPanel && warriorButton.getGlobalBounds().contains(position);
}

bool CityPanel::isBuilderButtonClicked(const sf::Vector2f& position) const
{
    return showCityPanel && builderButton.getGlobalBounds().contains(position);
}

bool CityPanel::isBuildingButtonClicked(const sf::Vector2f& position) const
{
    return showCityPanel && buildingButton.getGlobalBounds().contains(position);
}

bool CityPanel::isBackButtonClicked(const sf::Vector2f& position) const
{
    return showCityPanel && backButton.getGlobalBounds().contains(position);
}

} // namespace ui
