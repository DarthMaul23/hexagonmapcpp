#include "NPCMerchant.hpp"
#include "Hero.hpp"
#include <iostream>

NPCMerchant::NPCMerchant(const std::string& merchantName, const sf::Vector2f& pos, const sf::Font& font)
    : name(merchantName), position(pos), nameText(font) {
    
    // Circle setup
    shape.setRadius(15.0f);
    shape.setOrigin(sf::Vector2f(15.0f, 15.0f));
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

    // Center the text without using FloatRect properties
    // Calculate an approximate width based on the character size and string length
    float approxWidth = nameText.getString().getSize() * nameText.getCharacterSize() * 0.6f; // Estimate width
    float approxHeight = nameText.getCharacterSize() * 1.2f; // Estimate height

    nameText.setOrigin(sf::Vector2f(approxWidth / 2.f, approxHeight / 2.f));
    nameText.setPosition(sf::Vector2f(position.x, position.y - 35.f));

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

    // Center the text without using FloatRect properties
    float approxWidth = nameText.getString().getSize() * nameText.getCharacterSize() * 0.6f; // Estimate width
    float approxHeight = nameText.getCharacterSize() * 1.2f; // Estimate height

    nameText.setOrigin(sf::Vector2f(approxWidth / 2.f, approxHeight / 2.f));
    nameText.setPosition(sf::Vector2f(position.x, position.y - 35.f));
}

bool NPCMerchant::sellItemTo(Hero* hero, int itemIndex) {
    if (!hero || itemIndex < 0 || itemIndex >= static_cast<int>(availableItems.size())) {
        return false;
    }
    
    const game::InventoryItem& gameItem = availableItems[itemIndex];
    
    // Check if hero has enough gold
    if (hero->getGold() < gameItem.value) {
        std::cout << "Not enough gold to purchase " << gameItem.name << std::endl;
        return false;
    }
    
    // Deduct gold from hero
    hero->spendGold(gameItem.value);
    
    // Add item to hero's inventory - convert from game::InventoryItem to InventoryItem
    InventoryItem heroItem(gameItem.name, gameItem.description, gameItem.value);
    hero->addItem(heroItem);
    
    std::cout << "Purchased " << gameItem.name << " for " << gameItem.value << " gold" << std::endl;
    return true;
}

bool NPCMerchant::sellUnitTo(Hero* hero, int unitIndex) {
    if (!hero || unitIndex < 0 || unitIndex >= static_cast<int>(availableUnits.size())) {
        return false;
    }
    
    const ArmyUnit& unit = availableUnits[unitIndex];
    
    // Check if hero has enough gold
    if (hero->getGold() < unit.cost) {
        std::cout << "Not enough gold to purchase " << unit.name << std::endl;
        return false;
    }
    
    // Check if hero has an army
    Army* heroArmy = hero->getArmy();
    if (!heroArmy) {
        std::cout << "Hero has no army to add unit to" << std::endl;
        return false;
    }
    
    // Check if army has space
    if (heroArmy->getSize() >= heroArmy->getCapacity()) {
        std::cout << "Army is at full capacity" << std::endl;
        return false;
    }
    
    // Deduct gold from hero
    hero->spendGold(unit.cost);
    
    // Add unit to hero's army
    heroArmy->addUnit(unit);
    
    std::cout << "Purchased " << unit.name << " for " << unit.cost << " gold" << std::endl;
    return true;
}

// MerchantManager implementation
MerchantManager::MerchantManager() : selectedMerchant(nullptr) {
    // Constructor implementation
}

void MerchantManager::addMerchant(const NPCMerchant& merchant) {
    merchants.push_back(merchant);
}

NPCMerchant* MerchantManager::getMerchantAt(const sf::Vector2f& position) {
    for (auto& merchant : merchants) {
        if (merchant.contains(position)) {
            return &merchant;
        }
    }
    return nullptr;
}

bool MerchantManager::selectMerchantAt(const sf::Vector2f& position) {
    NPCMerchant* merchant = getMerchantAt(position);
    if (merchant) {
        selectedMerchant = merchant;
        return true;
    }
    return false;
}

void MerchantManager::deselectMerchant() {
    selectedMerchant = nullptr;
}

void MerchantManager::update(float deltaTime) {
    // Update logic for merchants if needed
    // For now, merchants are static
    (void)deltaTime; // Avoid unused parameter warning
}

void MerchantManager::draw(sf::RenderWindow& window) {
    for (auto& merchant : merchants) {
        merchant.draw(window);
    }
}

void MerchantManager::setFontForAllMerchants(const sf::Font& font) {
    for (auto& merchant : merchants) {
        merchant.setFont(font);
    }
}