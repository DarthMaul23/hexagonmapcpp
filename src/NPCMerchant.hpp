#pragma once
#include "GameEntities.hpp"
#include "Army.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class NPCMerchant {
private:
    std::string name;
    sf::Vector2f position;
    std::vector<ArmyUnit> availableUnits;
    std::vector<game::InventoryItem> availableItems;
    sf::CircleShape shape;
    sf::Text nameText;

public:
    NPCMerchant(const std::string& merchantName, const sf::Vector2f& pos, const sf::Font& font);

    const std::string& getName() const { return name; }
    const sf::Vector2f& getPosition() const { return position; }

    void addUnitForSale(const ArmyUnit& unit);
    void addItemForSale(const game::InventoryItem& item);

    const std::vector<ArmyUnit>& getAvailableUnits() const { return availableUnits; }
    const std::vector<game::InventoryItem>& getAvailableItems() const { return availableItems; }

    bool sellUnitTo(Hero* hero, int unitIndex);
    bool sellItemTo(Hero* hero, int itemIndex);

    bool contains(const sf::Vector2f& point) const;
    void draw(sf::RenderWindow& window);
    void setFont(const sf::Font& font);
};

// Manager class to handle multiple merchants
class MerchantManager {
private:
    std::vector<NPCMerchant> merchants;
    NPCMerchant* selectedMerchant;
    
public:
    MerchantManager();
    
    // Add a new merchant
    void addMerchant(const NPCMerchant& merchant);
    
    // Check if a merchant is at a position
    NPCMerchant* getMerchantAt(const sf::Vector2f& position);
    
    // Selection management
    bool selectMerchantAt(const sf::Vector2f& position);
    void deselectMerchant();
    NPCMerchant* getSelectedMerchant() const { return selectedMerchant; }
    
    // Update and draw merchants
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    // Set font for all merchants
    void setFontForAllMerchants(const sf::Font& font);
};