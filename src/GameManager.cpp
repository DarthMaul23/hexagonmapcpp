#include "GameManager.hpp"
#include <iostream>

GameManager::GameManager()
    : playerHero(nullptr), playerArmy(nullptr), selectedType(SelectedEntityType::None) {
}

GameManager::~GameManager() {
    // Clean up dynamically allocated objects
    if (playerHero) {
        delete playerHero;
        playerHero = nullptr;
    }
    
    if (playerArmy) {
        delete playerArmy;
        playerArmy = nullptr;
    }
}

// Added implementation of this method to fix the "const" issue
NPCMerchant* GameManager::getSelectedMerchant() const {
    return isMerchantSelected() ? merchantManager.getSelectedMerchant() : nullptr;
}

void GameManager::initialize(const sf::Vector2f& startPosition, const sf::Font& font) {
    // Load textures first
    if (!loadTextures()) {
        std::cerr << "Failed to load game textures!" << std::endl;
    }
    
    playerHero = new Hero(startPosition, "Aragorn", font);
    playerArmy = new Army(playerHero);
    playerArmy->addUnit(ArmyUnit("Footman", ArmyUnitType::Infantry, 100, 10, 8, 50));
    playerArmy->addUnit(ArmyUnit("Archer", ArmyUnitType::Archer, 80, 15, 5, 70));

    addMerchant("Blacksmith", sf::Vector2f(startPosition.x + 200, startPosition.y - 150), font);
    addMerchant("Armorer", sf::Vector2f(startPosition.x - 250, startPosition.y + 100), font);
    addMerchant("Arcane Goods", sf::Vector2f(startPosition.x + 300, startPosition.y + 300), font);

    merchantManager.setFontForAllMerchants(font);
}

bool GameManager::loadTextures() {
    // Load soldier sprite texture
    if (!soldierTexture.loadFromFile("../src/assets/soldier.png")) {
        std::cerr << "Failed to load soldier.png texture!" << std::endl;
        return false;
    }
    
    std::cout << "Successfully loaded soldier sprite texture" << std::endl;
    return true;
}

void GameManager::setFont(const sf::Font& font) {
    // Set font for the hero
    if (playerHero) {
        playerHero->setFont(font);
    }
    
    // Set font for merchants
    merchantManager.setFontForAllMerchants(font);
}

void GameManager::addMerchant(const std::string& name, const sf::Vector2f& position, const sf::Font& font) {
    NPCMerchant merchant(name, position, font);
    merchantManager.addMerchant(merchant);
}

bool GameManager::trySelectEntityAt(const sf::Vector2f& position) {
    // Deselect current selection
    deselectAll();
    
    // Try to select the hero
    if (playerHero && playerHero->contains(position)) {
        selectedType = SelectedEntityType::Hero;
        playerHero->setSelected(true);
        std::cout << "Selected player hero." << std::endl;
        return true;
    }
    
    // Try to select a merchant
    if (merchantManager.selectMerchantAt(position)) {
        selectedType = SelectedEntityType::Merchant;
        std::cout << "Selected merchant: " << merchantManager.getSelectedMerchant()->getName() << std::endl;
        return true;
    }
    
    // Note: Army selection is handled through UI buttons rather than clicking
    // on individual units since they move in formation with the hero
    
    return false;
}

void GameManager::deselectAll() {
    // Reset selection state
    if (isHeroSelected() && playerHero) {
        playerHero->setSelected(false);
    }
    
    if (isMerchantSelected()) {
        merchantManager.deselectMerchant();
    }
    
    selectedType = SelectedEntityType::None;
}

bool GameManager::purchaseUnitFromMerchant(int unitIndex) {
    if (!isMerchantSelected() || !playerHero) {
        return false;
    }
    
    NPCMerchant* merchant = merchantManager.getSelectedMerchant();
    if (merchant) {
        return merchant->sellUnitTo(playerHero, unitIndex);
    }
    
    return false;
}

bool GameManager::purchaseItemFromMerchant(int itemIndex) {
    if (!isMerchantSelected() || !playerHero) {
        return false;
    }
    
    NPCMerchant* merchant = merchantManager.getSelectedMerchant();
    if (merchant) {
        return merchant->sellItemTo(playerHero, itemIndex);
    }
    
    return false;
}

void GameManager::update(float deltaTime) {
    // Update hero
    if (playerHero) {
        playerHero->update(deltaTime);
        
        // If hero moved, update army formation
        if (playerArmy) {
            playerArmy->updateFormation(playerHero->getPosition());
        }
    }
    
    // Update merchants
    merchantManager.update(deltaTime);
}

void GameManager::draw(sf::RenderWindow& window) {
    // Draw merchants
    merchantManager.draw(window);
    
    // Draw army if exists (drawn before hero so hero is on top)
    if (playerArmy) {
        playerArmy->draw(window);
    }
    
    // Draw hero with sprite texture if exists
    if (playerHero) {
        playerHero->drawSprite(window, soldierTexture);
    }
}