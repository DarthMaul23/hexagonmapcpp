#include "Menu.hpp"
#include <iostream>

namespace ui {

Menu::Menu(const sf::Font& font)
    : UIComponent(),
      showMenu(true),  // Start with menu visible
      font(font)
{
    // Initialize text elements with the font
    gameTitle.setFont(font);
    startText.setFont(font);
    optionsText.setFont(font);
    quitText.setFont(font);
}

bool Menu::initialize()
{
    // Set up menu background
    menuBackground.setSize(sf::Vector2f(800.f, 600.f));
    menuBackground.setFillColor(sf::Color(20, 20, 40, 230));
    
    // Initialize game title
    gameTitle.setString("Hexagon Strategy Game");
    gameTitle.setCharacterSize(48);
    gameTitle.setFillColor(sf::Color::White);
    gameTitle.setStyle(sf::Text::Bold);
    
    // Initialize start button
    startButton.setSize(sf::Vector2f(200.f, 60.f));
    startButton.setFillColor(sf::Color(60, 60, 100));
    startButton.setOutlineColor(sf::Color(100, 100, 150));
    startButton.setOutlineThickness(2.f);
    
    startText.setString("Start Game");
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);
    
    // Initialize options button
    optionsButton.setSize(sf::Vector2f(200.f, 60.f));
    optionsButton.setFillColor(sf::Color(60, 60, 100));
    optionsButton.setOutlineColor(sf::Color(100, 100, 150));
    optionsButton.setOutlineThickness(2.f);
    
    optionsText.setString("Options");
    optionsText.setCharacterSize(24);
    optionsText.setFillColor(sf::Color::White);
    
    // Initialize quit button
    quitButton.setSize(sf::Vector2f(200.f, 60.f));
    quitButton.setFillColor(sf::Color(100, 60, 60)); // Reddish for quit
    quitButton.setOutlineColor(sf::Color(150, 100, 100));
    quitButton.setOutlineThickness(2.f);
    
    quitText.setString("Quit");
    quitText.setCharacterSize(24);
    quitText.setFillColor(sf::Color::White);
    
    return true;
}

void Menu::positionElements(float windowWidth, float windowHeight)
{
    // Fill the entire window
    menuBackground.setSize(sf::Vector2f(windowWidth, windowHeight));
    menuBackground.setPosition(0.f, 0.f);
    
    // Center the title at the top
    sf::FloatRect titleBounds = gameTitle.getLocalBounds();
    gameTitle.setPosition(
        (windowWidth - titleBounds.width) / 2.f,
        windowHeight * 0.2f
    );
    
    // Position buttons vertically with spacing
    float buttonY = windowHeight * 0.4f;
    float buttonSpacing = 80.f;
    float buttonX = (windowWidth - startButton.getSize().x) / 2.f;
    
    // Start button
    startButton.setPosition(buttonX, buttonY);
    sf::FloatRect startBounds = startText.getLocalBounds();
    startText.setPosition(
        buttonX + (startButton.getSize().x - startBounds.width) / 2.f,
        buttonY + (startButton.getSize().y - startBounds.height) / 2.f - 5.f
    );
    
    // Options button
    buttonY += buttonSpacing;
    optionsButton.setPosition(buttonX, buttonY);
    sf::FloatRect optionsBounds = optionsText.getLocalBounds();
    optionsText.setPosition(
        buttonX + (optionsButton.getSize().x - optionsBounds.width) / 2.f,
        buttonY + (optionsButton.getSize().y - optionsBounds.height) / 2.f - 5.f
    );
    
    // Quit button
    buttonY += buttonSpacing;
    quitButton.setPosition(buttonX, buttonY);
    sf::FloatRect quitBounds = quitText.getLocalBounds();
    quitText.setPosition(
        buttonX + (quitButton.getSize().x - quitBounds.width) / 2.f,
        buttonY + (quitButton.getSize().y - quitBounds.height) / 2.f - 5.f
    );
}

void Menu::draw(sf::RenderWindow& window)
{
    if (!showMenu) return;
    
    // Get window dimensions for proper positioning
    float windowWidth = window.getView().getSize().x;
    float windowHeight = window.getView().getSize().y;
    
    // Position elements before drawing
    positionElements(windowWidth, windowHeight);
    
    // Draw all menu elements
    window.draw(menuBackground);
    window.draw(gameTitle);
    window.draw(startButton);
    window.draw(startText);
    window.draw(optionsButton);
    window.draw(optionsText);
    window.draw(quitButton);
    window.draw(quitText);
}

void Menu::update(float deltaTime)
{
    // Currently no animation or time-based updates needed
}

bool Menu::isStartButtonClicked(const sf::Vector2f& position) const
{
    return showMenu && startButton.getGlobalBounds().contains(position);
}

bool Menu::isOptionsButtonClicked(const sf::Vector2f& position) const
{
    return showMenu && optionsButton.getGlobalBounds().contains(position);
}

bool Menu::isQuitButtonClicked(const sf::Vector2f& position) const
{
    return showMenu && quitButton.getGlobalBounds().contains(position);
}

} // namespace ui
