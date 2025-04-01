#pragma once

#include "PlayerUnit.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Forward declaration for circular reference
class Hero;

// Unit type for armies
enum class ArmyUnitType {
    Infantry,
    Archer,
    Cavalry,
    Mage
};

// Unit structure for army units (not to be confused with PlayerUnit)
struct ArmyUnit {
    std::string name;
    ArmyUnitType type;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int cost;
    
    ArmyUnit(const std::string& n, ArmyUnitType t, int h, int a, int d, int c) 
        : name(n), type(t), health(h), maxHealth(h), attack(a), defense(d), cost(c) {}
};

// Army class to manage a collection of units that follow the hero
class Army {
private:
    std::vector<ArmyUnit> units;
    Hero* leader;
    
    // Maximum unit capacity
    int maxUnits;
    
    // Army formation information
    std::vector<sf::Vector2f> formationOffsets;
    
    // Visual representations
    std::vector<sf::CircleShape> unitShapes;
    
public:
    Army(Hero* heroLeader, int capacity = 8);
    
    // Unit management
    bool addUnit(const ArmyUnit& unit);
    void removeUnit(int index);
    void healUnit(int index, int amount);
    
    // Army info
    int getSize() const { return units.size(); }
    int getCapacity() const { return maxUnits; }
    const std::vector<ArmyUnit>& getUnits() const { return units; }
    
    // Get leader
    Hero* getLeader() const { return leader; }
    void setLeader(Hero* newLeader) { leader = newLeader; }
    
    // Calculate army strength
    int getTotalAttack() const;
    int getTotalDefense() const;
    
    // Update formation positions based on hero position
    void updateFormation(const sf::Vector2f& leaderPos);
    
    // Drawing
    void draw(sf::RenderWindow& window);
    
    // Calculate cost of all units
    int getTotalCost() const;
    
    // Create default unit shapes
    void createUnitShapes();
};