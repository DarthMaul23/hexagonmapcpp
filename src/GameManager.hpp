#pragma once

#include "Hero.hpp"
#include "Army.hpp"
#include "NPCMerchant.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// Central class to manage game elements
class GameManager {
private:
    // The player's hero
    Hero* playerHero;
    
    // The player's army
    Army* playerArmy;
    
    // Merchant manager to handle all merchants
    MerchantManager merchantManager;
    
    // Sprite textures for 2.5D rendering
    sf::Texture soldierTexture;
    
    // Selected game element
    enum class SelectedEntityType {
        None,
        Hero,
        Army,
        Merchant
    };
    
    SelectedEntityType selectedType;
    
public:
    GameManager();
    ~GameManager();
    
    // Initialization
    void initialize(const sf::Vector2f& startPosition, const sf::Font& font);
    
    // Texture management
    const sf::Texture& getSoldierTexture() const { return soldierTexture; }
    bool loadTextures();
    
    // Hero management
    Hero* getPlayerHero() const { return playerHero; }
    
    // Army management
    Army* getPlayerArmy() const { return playerArmy; }
    
    // Merchant management
    MerchantManager& getMerchantManager() { return merchantManager; }
    
    // Adds a merchant at the specified position
    void addMerchant(const std::string& name, const sf::Vector2f& position, const sf::Font& font);
    
    // Check for interactions at a position
    bool trySelectEntityAt(const sf::Vector2f& position);
    
    // Entity deselection
    void deselectAll();
    
    // Check what kind of entity is selected
    bool isHeroSelected() const { return selectedType == SelectedEntityType::Hero; }
    bool isArmySelected() const { return selectedType == SelectedEntityType::Army; }
    bool isMerchantSelected() const { return selectedType == SelectedEntityType::Merchant; }
    
    // Selection getters
    Hero* getSelectedHero() const { return isHeroSelected() ? playerHero : nullptr; }
    Army* getSelectedArmy() const { return isArmySelected() ? playerArmy : nullptr; }
    NPCMerchant* getSelectedMerchant() const; // Implementation moved to cpp file
    
    // Handle unit purchases from merchants
    bool purchaseUnitFromMerchant(int unitIndex);
    
    // Handle item purchases from merchants
    bool purchaseItemFromMerchant(int itemIndex);
    
    // Update game state
    void update(float deltaTime);
    
    // Render game entities
    void draw(sf::RenderWindow& window);
    
    // Set font for merchants
    void setFont(const sf::Font& font);
};