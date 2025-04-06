#include "Modal.hpp"
#include <iostream>

Modal::Modal(const sf::Font& font)
    : showModal(false),
      font(font)
{
    // Initialize text elements with the font
    modalTitle.setFont(font);
    modalContent.setFont(font);
    closeText.setFont(font);
}

bool Modal::initialize()
{
    // Set up modal background
    modalBackground.setSize(sf::Vector2f(400.f, 300.f));
    modalBackground.setFillColor(sf::Color(40, 40, 60, 230));
    modalBackground.setOutlineColor(sf::Color(100, 100, 150));
    modalBackground.setOutlineThickness(2.f);
    
    // Initialize text properties
    modalTitle.setCharacterSize(24);
    modalTitle.setFillColor(sf::Color::White);
    
    modalContent.setCharacterSize(16);
    modalContent.setFillColor(sf::Color::White);
    
    // Initialize close button
    closeButton.setSize(sf::Vector2f(80.f, 30.f));
    closeButton.setFillColor(sf::Color(80, 80, 120));
    closeButton.setOutlineColor(sf::Color(120, 120, 180));
    closeButton.setOutlineThickness(1.f);
    
    closeText.setString("Close");
    closeText.setCharacterSize(16);
    closeText.setFillColor(sf::Color::White);
    
    return true;
}

void Modal::showInfo(const std::string& title, const std::string& content)
{
    modalTitle.setString(title);
    modalContent.setString(content);
    showModal = true;
}

void Modal::positionElements(float windowWidth, float windowHeight)
{
    // Center modal on screen
    modalBackground.setPosition(sf::Vector2f(windowWidth / 2.f - 200.f, windowHeight / 2.f - 150.f));
    
    // Position title and content
    modalTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f - 140.f));
    modalContent.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f - 100.f));
    
    // Position close button at bottom of modal
    closeButton.setPosition(sf::Vector2f(windowWidth / 2.f - 40.f, windowHeight / 2.f + 110.f));
    closeText.setPosition(sf::Vector2f(windowWidth / 2.f - 30.f, windowHeight / 2.f + 115.f));
}

void Modal::draw(sf::RenderWindow& window)
{
    if (!showModal) return;
    
    // Get window dimensions for proper positioning
    float windowWidth = window.getView().getSize().x;
    float windowHeight = window.getView().getSize().y;
    
    // Position elements before drawing
    positionElements(windowWidth, windowHeight);
    
    // Draw all modal elements
    window.draw(modalBackground);
    window.draw(modalTitle);
    window.draw(modalContent);
    window.draw(closeButton);
    window.draw(closeText);
}

void Modal::update(float deltaTime)
{
    // Currently no animation or time-based updates needed
    // This method is here to fulfill the UIComponent interface
}

bool Modal::isCloseButtonClicked(const sf::Vector2f& position) const
{
    return showModal && closeButton.getGlobalBounds().contains(position);
}

