#include "Army.hpp"
#include "Hero.hpp"
#include <iostream>

Army::Army(Hero* heroLeader, int capacity)
    : leader(heroLeader), maxUnits(capacity) {
    
    // Create formation offsets for units (in a semi-circle behind the leader)
    formationOffsets.resize(maxUnits);
    const float radius = 40.0f; // Distance from hero
    const float spreadFactor = 40.0f; // How far apart units are
    
    for (int i = 0; i < maxUnits; i++) {
        float angle = 3.14159f + (i - maxUnits/2.0f) * 0.3f;
        formationOffsets[i] = sf::Vector2f(
            std::cos(angle) * radius + (i % 2) * spreadFactor,
            std::sin(angle) * radius
        );
    }
    
    // Initialize the visual representations for units
    unitShapes.resize(maxUnits);
    createUnitShapes();
    
    // Link back to the hero if provided
    if (leader) {
        leader->setArmy(this);
    }
}

bool Army::addUnit(const ArmyUnit& unit) {
    if (units.size() >= maxUnits) {
        std::cout << "Army is at full capacity!" << std::endl;
        return false;
    }
    
    units.push_back(unit);
    std::cout << "Added " << unit.name << " to army. Total units: " << units.size() << std::endl;
    return true;
}

void Army::removeUnit(int index) {
    if (index >= 0 && index < units.size()) {
        std::cout << "Removed " << units[index].name << " from army." << std::endl;
        units.erase(units.begin() + index);
    }
}

void Army::healUnit(int index, int amount) {
    if (index >= 0 && index < units.size()) {
        units[index].health = std::min(units[index].health + amount, units[index].maxHealth);
        std::cout << "Healed " << units[index].name << " by " << amount 
                  << ". Current health: " << units[index].health << "/" << units[index].maxHealth << std::endl;
    }
}

int Army::getTotalAttack() const {
    int total = 0;
    for (const auto& unit : units) {
        total += unit.attack;
    }
    
    // If there's a hero leader, add a bonus based on strength
    if (leader) {
        total += leader->getAttribute(HeroAttribute::Strength) / 2;
    }
    
    return total;
}

int Army::getTotalDefense() const {
    int total = 0;
    for (const auto& unit : units) {
        total += unit.defense;
    }
    
    // If there's a hero leader, add a bonus based on vitality
    if (leader) {
        total += leader->getAttribute(HeroAttribute::Vitality) / 2;
    }
    
    return total;
}

void Army::updateFormation(const sf::Vector2f& leaderPos) {
    // Only update visuals for units that actually exist
    for (size_t i = 0; i < units.size(); i++) {
        unitShapes[i].setPosition(leaderPos + formationOffsets[i]);
    }
}

void Army::draw(sf::RenderWindow& window) {
    // Draw all units in the army formation
    for (size_t i = 0; i < units.size(); i++) {
        window.draw(unitShapes[i]);
    }
}

int Army::getTotalCost() const {
    int total = 0;
    for (const auto& unit : units) {
        total += unit.cost;
    }
    return total;
}

void Army::createUnitShapes() {
    for (int i = 0; i < maxUnits; i++) {
        unitShapes[i].setRadius(10.0f);
        unitShapes[i].setOrigin(sf::Vector2f(10.0f, 10.0f));
        unitShapes[i].setOutlineThickness(1.0f);
        unitShapes[i].setOutlineColor(sf::Color::Black);
    }
}