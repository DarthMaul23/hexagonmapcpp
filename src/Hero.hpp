#pragma once

#include "GameEntities.hpp"
#include "PlayerUnit.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

// Forward declaration
class Army;

// Item structure for hero inventory
struct InventoryItem {
    std::string name;
    std::string description;
    int value;
    bool isEquipped;
    
    InventoryItem(const std::string& n, const std::string& d, int v) 
        : name(n), description(d), value(v), isEquipped(false) {}
};

// Skill structure for hero abilities
struct Skill {
    std::string name;
    std::string description;
    int level;
    int maxLevel;
    
    Skill(const std::string& n, const std::string& d, int l = 1, int ml = 5) 
        : name(n), description(d), level(l), maxLevel(ml) {}
};

// Hero attributes
enum class HeroAttribute {
    Strength,
    Intelligence,
    Dexterity,
    Vitality
};

// Hero class
class Hero : public PlayerUnit {
private:
    std::string name;
    int level;
    int experience;
    int experienceToNextLevel;
    
    // Resources
    int gold;
    
    // Attributes
    std::map<HeroAttribute, int> attributes;
    
    // Skills and inventory
    std::vector<Skill> skills;
    std::vector<InventoryItem> inventory;
    
    // Army reference
    Army* army;
    
    // UI elements
    sf::Text levelText;
    sf::Text goldText;
    
    // Method to calculate experience needed for next level
    int calculateExperienceForLevel(int level);
    
public:
    // Updated constructor to take a font
    Hero(const sf::Vector2f& pos, const std::string& heroName, const sf::Font& font);
    
    // Basic getters and setters
    const std::string& getName() const { return name; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    int getExperienceToNextLevel() const { return experienceToNextLevel; }
    int getGold() const { return gold; }
    
    // Attribute methods
    int getAttribute(HeroAttribute attr) const;
    void increaseAttribute(HeroAttribute attr, int amount = 1);
    
    // Experience and leveling
    void addExperience(int exp);
    void levelUp();
    
    // Inventory management
    void addItem(const InventoryItem& item);
    void removeItem(int index);
    const std::vector<InventoryItem>& getInventory() const { return inventory; }
    void equipItem(int index, bool equip);
    
    // Skill management
    void addSkill(const Skill& skill);
    void upgradeSkill(int index);
    const std::vector<Skill>& getSkills() const { return skills; }
    
    // Gold management
    void addGold(int amount);
    bool spendGold(int amount);
    
    // Army management
    void setArmy(Army* newArmy) { army = newArmy; }
    Army* getArmy() const { return army; }
    
    // Draw hero with UI elements - virtual from PlayerUnit
    void draw(sf::RenderWindow& window);
    
    // Draw hero with sprite texture for 2.5D rendering
    void drawSprite(sf::RenderWindow& window, const sf::Texture& spriteTexture);

    // Set font for UI elements
    void setFont(const sf::Font& font);
    
    // Initialize with default skills and attributes
    void initializeDefaults();
};