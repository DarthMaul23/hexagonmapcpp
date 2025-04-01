#include "NPCMerchant.hpp"
#include "Hero.hpp"
#include <iostream>

NPCMerchant::NPCMerchant(const std::string& merchantName, const sf::Vector2f& pos, const sf::Font& font)
    : name(merchantName), position(pos), nameText(font) {
    
    // Circle setup
    shape.setRadius(15.0f);
    shape.setOrigin(15.0f, 15.0f);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(160, 82, 45));
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::Yellow);

    // Text setup
    nameText.setString(merchantName);
    nameText.setCharacterSize(14);
    nameText.setFillColor(sf::Color::White);
    nameText.setOutlineColor(sf::Color::Black);
    nameText.setOutlineThickness(1.0f);

    sf::FloatRect bounds = nameText.getLocalBounds();
    nameText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    nameText.setPosition(position.x, position.y - 35.f);

    // Add units and items
    addUnitForSale(ArmyUnit("Footman", ArmyUnitType::Infantry, 100, 10, 8, 50));
    addUnitForSale(ArmyUnit("Archer", ArmyUnitType::Archer, 80, 15, 5, 70));
    addItemForSale(game::InventoryItem("Health Potion", "Restores 50 health", 25));
    addItemForSale(game::InventoryItem("Mana Potion", "Restores 30 mana", 30));
}

void NPCMerchant::addUnitForSale(const ArmyUnit& unit) {
    availableUnits.push_back(unit);
}

void NPCMerchant::addItemForSale(const game::InventoryItem& item) {
    availableItems.push_back(item);
}

bool NPCMerchant::contains(const sf::Vector2f& point) const {
    float radius = shape.getRadius() * 1.5f;
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

void NPCMerchant::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(nameText);
}

void NPCMerchant::setFont(const sf::Font& font) {
    nameText.setFont(font);

    sf::FloatRect bounds = nameText.getLocalBounds();
    nameText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    nameText.setPosition(position.x, position.y - 35.f);
}