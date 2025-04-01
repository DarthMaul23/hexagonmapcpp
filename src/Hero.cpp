#include <SFML/Graphics.hpp>
#include "Hero.hpp"
#include "Army.hpp"
#include <iostream>
#include <cmath>

Hero::Hero(const sf::Vector2f& pos, const std::string& heroName, const sf::Font& font)
    : PlayerUnit(pos, UnitType::Warrior), // Heroes are special warriors
      name(heroName),
      level(1),
      experience(0),
      experienceToNextLevel(calculateExperienceForLevel(1)),
      gold(100),
      army(nullptr),
      levelText(font, "", 14),  // Initialize with the provided font
      goldText(font, "", 14)    // Initialize with the provided font
{
    // Get a reference to the base class shape (assuming a protected getter exists)
    sf::CircleShape& shape = getShape(); 
    
    // Setup hero appearance - override the base PlayerUnit
    sf::Color heroColor = sf::Color(50, 150, 255); // Blue for heroes
    shape.setFillColor(heroColor);
    shape.setOutlineThickness(3.0f);
    shape.setOutlineColor(sf::Color::White);
    
    // Initialize attributes
    attributes[HeroAttribute::Strength] = 5;
    attributes[HeroAttribute::Intelligence] = 5;
    attributes[HeroAttribute::Dexterity] = 5;
    attributes[HeroAttribute::Vitality] = 5;
    
    // Initialize default skills and items
    initializeDefaults();
}

void Hero::setFont(const sf::Font& font) {
    levelText.setFont(font);
    levelText.setCharacterSize(14);
    levelText.setFillColor(sf::Color::White);
    levelText.setOutlineColor(sf::Color::Black);
    levelText.setOutlineThickness(1.0f);
    
    goldText.setFont(font);
    goldText.setCharacterSize(14);
    goldText.setFillColor(sf::Color::Yellow);
    goldText.setOutlineColor(sf::Color::Black);
    goldText.setOutlineThickness(1.0f);
}

void Hero::draw(sf::RenderWindow& window) {
    // Draw the hero unit (via base class)
    PlayerUnit::draw(window);

    // Draw level and gold info above hero
    sf::Vector2f pos = getPosition();

    // Update level text
    /*
    levelText.setString("Lvl " + std::to_string(level));
    sf::FloatRect levelBounds = levelText.getLocalBounds();
    levelText.setPosition(pos.x - (2.0f), pos.y - 40.f);
    window.draw(levelText);

    // Update gold text
    goldText.setString(std::to_string(gold) + " gold");
    sf::FloatRect goldBounds = goldText.getLocalBounds();
    goldText.setPosition(pos.x - ( 2.0f), pos.y - 25.f);
    window.draw(goldText);
    */
}

