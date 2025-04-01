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
      experienceToNextLevel(calculateExperienceForLevel(2)),
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

void Hero::initializeDefaults() {
    // Add basic skills
    skills.push_back(Skill("Strength", "Increases physical damage", 1));
    skills.push_back(Skill("Defense", "Reduces damage taken", 1));
    skills.push_back(Skill("Leadership", "Improves army performance", 1));
    
    // Add starting inventory
    inventory.push_back(InventoryItem("Bronze Sword", "A basic sword", 50));
    inventory.push_back(InventoryItem("Leather Armor", "Basic armor", 75));
    inventory.push_back(InventoryItem("Health Potion", "Restores 50 health", 25));
}

int Hero::calculateExperienceForLevel(int targetLevel) {
    // Simple exponential formula: level^2 * 100
    return targetLevel * targetLevel * 100;
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
    goldText.setPosition(pos.x - (2.0f), pos.y - 25.f);
    window.draw(goldText);
    */
}

void Hero::addExperience(int exp) {
    experience += exp;
    
    // Check for level up
    while (experience >= experienceToNextLevel) {
        levelUp();
    }
}

void Hero::levelUp() {
    level++;
    
    // Calculate new experience threshold
    experienceToNextLevel = calculateExperienceForLevel(level + 1);
    
    // Increase attributes slightly
    attributes[HeroAttribute::Strength]++;
    attributes[HeroAttribute::Vitality]++;
    
    std::cout << name << " leveled up to level " << level << "!" << std::endl;
}

void Hero::addItem(const InventoryItem& item) {
    inventory.push_back(item);
}

void Hero::removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        inventory.erase(inventory.begin() + index);
    }
}

void Hero::addGold(int amount) {
    gold += amount;
}

bool Hero::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

void Hero::addSkill(const Skill& skill) {
    skills.push_back(skill);
}

void Hero::increaseAttribute(HeroAttribute attr, int amount) {
    attributes[attr] += amount;
}

int Hero::getAttribute(HeroAttribute attr) const {
    auto it = attributes.find(attr);
    if (it != attributes.end()) {
        return it->second;
    }
    return 0;
}

void Hero::upgradeSkill(int index) {
    if (index < 0 || index >= static_cast<int>(skills.size())) {
        std::cout << "Invalid skill index." << std::endl;
        return;
    }
    
    Skill& skill = skills[index];
    
    if (skill.level >= skill.maxLevel) {
        std::cout << "Skill already at maximum level." << std::endl;
        return;
    }
    
    // Increase skill level
    skill.level++;
    
    std::cout << "Upgraded " << skill.name << " to level " << skill.level << "." << std::endl;
}

void Hero::equipItem(int index, bool equip) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) {
        std::cout << "Invalid inventory index." << std::endl;
        return;
    }
    
    inventory[index].isEquipped = equip;
    
    if (equip) {
        std::cout << "Equipped " << inventory[index].name << "." << std::endl;
    } else {
        std::cout << "Unequipped " << inventory[index].name << "." << std::endl;
    }
}