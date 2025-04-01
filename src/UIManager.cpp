#include "UIManager.hpp"
#include "City.hpp"  // Include full definition of GameCity
#include <iostream>

UIManager::UIManager(unsigned int windowWidth, unsigned int windowHeight) 
    : fontLoaded(false), 
      showModal(false),
      showCityPanel(false),
      showHeroPanel(false),
      showArmyPanel(false),
      showMerchantPanel(false),
      // Initialize all sf::Text objects with dummy font - will be properly set in initialize()
      resourceTitle(font, ""),
      foodText(font, ""),
      woodText(font, ""),
      stoneText(font, ""),
      goldText(font, ""),
      unitTitle(font, ""),
      unitTypeText(font, ""),
      unitHealthText(font, ""),
      unitMovementText(font, ""),
      unitActionText(font, ""),
      cityTitle(font, ""),
      cityPopulation(font, ""),
      cityFood(font, ""),
      cityProduction(font, ""),
      cityGold(font, ""),
      settlerText(font, ""),
      warriorText(font, ""),
      builderText(font, ""),
      buildingText(font, ""),
      heroTitle(font, ""),
      heroLevel(font, ""),
      heroExp(font, ""),
      heroGold(font, ""),
      heroAttributes(font, ""),
      inventoryTitle(font, ""),
      skillTitle(font, ""),
      armyTitle(font, ""),
      armyCounts(font, ""),
      merchantTitle(font, ""),
      merchantDescription(font, ""),
      shopItemsTitle(font, ""),
      shopUnitsTitle(font, ""),
      backText(font, ""),
      heroButtonText(font, ""),
      armyButtonText(font, ""),
      modalTitle(font, ""),
      modalContent(font, ""),
      closeButton(font, ""),
      titleText(font, ""),
      startText(font, "")
{
    // Initialize views
    gameView.setCenter(sf::Vector2f(0.f, 0.f));
    gameView.setSize(sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
    
    uiView.setCenter(sf::Vector2f(static_cast<float>(windowWidth/2), static_cast<float>(windowHeight/2)));
    uiView.setSize(sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
    
    // Set up resource panel
    resourcePanel.setSize(sf::Vector2f(200.f, 120.f));
    resourcePanel.setFillColor(sf::Color(40, 40, 60, 200));
    resourcePanel.setOutlineColor(sf::Color(80, 80, 100));
    resourcePanel.setOutlineThickness(2.f);
    
    // Set up unit info panel
    unitInfoPanel.setSize(sf::Vector2f(200.f, 150.f));
    unitInfoPanel.setFillColor(sf::Color(40, 40, 60, 200));
    unitInfoPanel.setOutlineColor(sf::Color(80, 80, 100));
    unitInfoPanel.setOutlineThickness(2.f);
    
    // Set up city panel
    cityPanel.setSize(sf::Vector2f(400.f, 300.f));
    cityPanel.setFillColor(sf::Color(40, 40, 60, 230));
    cityPanel.setOutlineColor(sf::Color(100, 100, 150));
    cityPanel.setOutlineThickness(2.f);
    
    // Hero panel
    heroPanel.setSize(sf::Vector2f(500.f, 400.f));
    heroPanel.setFillColor(sf::Color(40, 40, 60, 230));
    heroPanel.setOutlineColor(sf::Color(100, 100, 150));
    heroPanel.setOutlineThickness(2.f);
    
    // Hero inventory panel (sub-panel)
    inventoryPanel.setSize(sf::Vector2f(240.f, 280.f));
    inventoryPanel.setFillColor(sf::Color(50, 50, 70, 200));
    inventoryPanel.setOutlineColor(sf::Color(100, 100, 150));
    inventoryPanel.setOutlineThickness(1.f);
    
    // Hero skills panel (sub-panel)
    skillPanel.setSize(sf::Vector2f(240.f, 280.f));
    skillPanel.setFillColor(sf::Color(50, 50, 70, 200));
    skillPanel.setOutlineColor(sf::Color(100, 100, 150));
    skillPanel.setOutlineThickness(1.f);
    
    // Army panel
    armyPanel.setSize(sf::Vector2f(500.f, 400.f));
    armyPanel.setFillColor(sf::Color(40, 40, 60, 230));
    armyPanel.setOutlineColor(sf::Color(100, 100, 150));
    armyPanel.setOutlineThickness(2.f);
    
    // Merchant panel
    merchantPanel.setSize(sf::Vector2f(550.f, 450.f));
    merchantPanel.setFillColor(sf::Color(40, 40, 60, 230));
    merchantPanel.setOutlineColor(sf::Color(100, 100, 150));
    merchantPanel.setOutlineThickness(2.f);
    
    // Shop items panel (sub-panel)
    shopItemsPanel.setSize(sf::Vector2f(260.f, 380.f));
    shopItemsPanel.setFillColor(sf::Color(50, 50, 70, 200));
    shopItemsPanel.setOutlineColor(sf::Color(100, 100, 150));
    shopItemsPanel.setOutlineThickness(1.f);
    
    // Shop units panel (sub-panel)
    shopUnitsPanel.setSize(sf::Vector2f(260.f, 380.f));
    shopUnitsPanel.setFillColor(sf::Color(50, 50, 70, 200));
    shopUnitsPanel.setOutlineColor(sf::Color(100, 100, 150));
    shopUnitsPanel.setOutlineThickness(1.f);
    
    // City production buttons
    settlerButton.setSize(sf::Vector2f(180.f, 40.f));
    settlerButton.setFillColor(sf::Color(60, 60, 100));
    settlerButton.setOutlineColor(sf::Color(100, 100, 150));
    settlerButton.setOutlineThickness(1.f);
    
    warriorButton.setSize(sf::Vector2f(180.f, 40.f));
    warriorButton.setFillColor(sf::Color(60, 60, 100));
    warriorButton.setOutlineColor(sf::Color(100, 100, 150));
    warriorButton.setOutlineThickness(1.f);
    
    builderButton.setSize(sf::Vector2f(180.f, 40.f));
    builderButton.setFillColor(sf::Color(60, 60, 100));
    builderButton.setOutlineColor(sf::Color(100, 100, 150));
    builderButton.setOutlineThickness(1.f);
    
    buildingButton.setSize(sf::Vector2f(180.f, 40.f));
    buildingButton.setFillColor(sf::Color(60, 60, 100));
    buildingButton.setOutlineColor(sf::Color(100, 100, 150));
    buildingButton.setOutlineThickness(1.f);
    
    // Back button
    backButton.setSize(sf::Vector2f(100.f, 40.f));
    backButton.setFillColor(sf::Color(80, 80, 120));
    backButton.setOutlineColor(sf::Color(120, 120, 180));
    backButton.setOutlineThickness(1.f);
    
    // Hero button
    heroButton.setSize(sf::Vector2f(120.f, 40.f));
    heroButton.setFillColor(sf::Color(50, 100, 150));
    heroButton.setOutlineColor(sf::Color(100, 150, 200));
    heroButton.setOutlineThickness(1.f);
    
    // Army button
    armyButton.setSize(sf::Vector2f(120.f, 40.f));
    armyButton.setFillColor(sf::Color(150, 50, 50));
    armyButton.setOutlineColor(sf::Color(200, 100, 100));
    armyButton.setOutlineThickness(1.f);
    
    // Set up modal
    modalBackground.setSize(sf::Vector2f(300.f, 200.f));
    modalBackground.setFillColor(sf::Color(50, 50, 50, 200));
    modalBackground.setOutlineColor(sf::Color::White);
    modalBackground.setOutlineThickness(2.f);
    
    // Set up menu
    menuBackground.setSize(sf::Vector2f(windowWidth, windowHeight));
    menuBackground.setFillColor(sf::Color(20, 20, 50, 220));
    
    startButton.setSize(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color(80, 80, 180));
}

UIManager::~UIManager() {
    // No dynamic allocations to clean up
}

bool UIManager::initialize() {
    // Try different possible paths to find the font
    const std::vector<std::string> fontPaths = {
        "arial.ttf",                  // Current directory
        "../assets/arial.ttf",        // Parent directory's assets folder
        "assets/arial.ttf",           // Assets folder in current directory
        "../fonts/OpenSans-Regular.ttf", // Parent directory's fonts folder
        "fonts/OpenSans-Regular.ttf", // Fonts folder in current directory
        "/System/Library/Fonts/Supplemental/Arial.ttf" // macOS system font
    };
    
    for (const auto& path : fontPaths) {
        if (font.openFromFile(path)) {
            std::cout << "Successfully loaded font from: " << path << std::endl;
            fontLoaded = true;
            break;
        }
    }
    
    if (!fontLoaded) {
        std::cerr << "ERROR: Failed to load any font!" << std::endl;
        return false;
    }
    
    // Reinitialize text objects with the loaded font
    resourceTitle.setFont(font);
    resourceTitle.setString("Resources");
    resourceTitle.setCharacterSize(18);
    resourceTitle.setFillColor(sf::Color::White);
    
    foodText.setFont(font);
    foodText.setCharacterSize(14);
    foodText.setFillColor(sf::Color(200, 230, 150));
    
    woodText.setFont(font);
    woodText.setCharacterSize(14);
    woodText.setFillColor(sf::Color(160, 120, 80));
    
    stoneText.setFont(font);
    stoneText.setCharacterSize(14);
    stoneText.setFillColor(sf::Color(180, 180, 180));
    
    goldText.setFont(font);
    goldText.setCharacterSize(14);
    goldText.setFillColor(sf::Color(255, 215, 0));
    
    // Unit info texts
    unitTitle.setFont(font);
    unitTitle.setString("Selected Unit");
    unitTitle.setCharacterSize(18);
    unitTitle.setFillColor(sf::Color::White);
    
    unitTypeText.setFont(font);
    unitTypeText.setCharacterSize(14);
    unitTypeText.setFillColor(sf::Color::White);
    
    unitHealthText.setFont(font);
    unitHealthText.setCharacterSize(14);
    unitHealthText.setFillColor(sf::Color::White);
    
    unitMovementText.setFont(font);
    unitMovementText.setCharacterSize(14);
    unitMovementText.setFillColor(sf::Color::White);
    
    unitActionText.setFont(font);
    unitActionText.setCharacterSize(14);
    unitActionText.setFillColor(sf::Color::White);
    
    // City info texts
    cityTitle.setFont(font);
    cityTitle.setCharacterSize(22);
    cityTitle.setFillColor(sf::Color::White);
    
    cityPopulation.setFont(font);
    cityPopulation.setCharacterSize(16);
    cityPopulation.setFillColor(sf::Color::White);
    
    cityFood.setFont(font);
    cityFood.setCharacterSize(16);
    cityFood.setFillColor(sf::Color(200, 230, 150));
    
    cityProduction.setFont(font);
    cityProduction.setCharacterSize(16);
    cityProduction.setFillColor(sf::Color(150, 180, 230));
    
    cityGold.setFont(font);
    cityGold.setCharacterSize(16);
    cityGold.setFillColor(sf::Color(255, 215, 0));
    
    // Production buttons text
    settlerText.setFont(font);
    settlerText.setString("Settler");
    settlerText.setCharacterSize(16);
    settlerText.setFillColor(sf::Color::White);
    
    warriorText.setFont(font);
    warriorText.setString("Warrior");
    warriorText.setCharacterSize(16);
    warriorText.setFillColor(sf::Color::White);
    
    builderText.setFont(font);
    builderText.setString("Builder");
    builderText.setCharacterSize(16);
    builderText.setFillColor(sf::Color::White);
    
    buildingText.setFont(font);
    buildingText.setString("Granary");
    buildingText.setCharacterSize(16);
    buildingText.setFillColor(sf::Color::White);
    
    // Hero panel texts
    heroTitle.setFont(font);
    heroTitle.setCharacterSize(24);
    heroTitle.setFillColor(sf::Color::White);
    
    heroLevel.setFont(font);
    heroLevel.setCharacterSize(18);
    heroLevel.setFillColor(sf::Color::White);
    
    heroExp.setFont(font);
    heroExp.setCharacterSize(16);
    heroExp.setFillColor(sf::Color(150, 220, 255));
    
    heroGold.setFont(font);
    heroGold.setCharacterSize(16);
    heroGold.setFillColor(sf::Color(255, 215, 0));
    
    heroAttributes.setFont(font);
    heroAttributes.setCharacterSize(16);
    heroAttributes.setFillColor(sf::Color::White);
    
    // Inventory panel
    inventoryTitle.setFont(font);
    inventoryTitle.setString("Inventory");
    inventoryTitle.setCharacterSize(18);
    inventoryTitle.setFillColor(sf::Color::White);
    
    // Skill panel
    skillTitle.setFont(font);
    skillTitle.setString("Skills");
    skillTitle.setCharacterSize(18);
    skillTitle.setFillColor(sf::Color::White);
    
    // Army panel
    armyTitle.setFont(font);
    armyTitle.setCharacterSize(24);
    armyTitle.setFillColor(sf::Color::White);
    
    armyCounts.setFont(font);
    armyCounts.setCharacterSize(16);
    armyCounts.setFillColor(sf::Color::White);
    
    // Merchant panel
    merchantTitle.setFont(font);
    merchantTitle.setCharacterSize(24);
    merchantTitle.setFillColor(sf::Color::White);
    
    merchantDescription.setFont(font);
    merchantDescription.setCharacterSize(16);
    merchantDescription.setFillColor(sf::Color::White);
    
    // Shop panels
    shopItemsTitle.setFont(font);
    shopItemsTitle.setString("Items for Sale");
    shopItemsTitle.setCharacterSize(18);
    shopItemsTitle.setFillColor(sf::Color::White);
    
    shopUnitsTitle.setFont(font);
    shopUnitsTitle.setString("Units for Sale");
    shopUnitsTitle.setCharacterSize(18);
    shopUnitsTitle.setFillColor(sf::Color::White);
    
    // Back button
    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(16);
    backText.setFillColor(sf::Color::White);
    
    // Hero/Army toggle buttons
    heroButtonText.setFont(font);
    heroButtonText.setString("Hero Info");
    heroButtonText.setCharacterSize(16);
    heroButtonText.setFillColor(sf::Color::White);
    
    armyButtonText.setFont(font);
    armyButtonText.setString("Army");
    armyButtonText.setCharacterSize(16);
    armyButtonText.setFillColor(sf::Color::White);
    
    // Modal texts
    modalTitle.setFont(font);
    modalTitle.setCharacterSize(18);
    modalTitle.setFillColor(sf::Color::White);
    
    modalContent.setFont(font);
    modalContent.setCharacterSize(14);
    modalContent.setFillColor(sf::Color::White);
    
    closeButton.setFont(font);
    closeButton.setString("Close");
    closeButton.setCharacterSize(14);
    closeButton.setFillColor(sf::Color::White);
    
    // Menu texts
    titleText.setFont(font);
    titleText.setString("Hexagon Strategy Game");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    
    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);
    
    // Initialize inventory slots
      const int maxInventorySlots = 12;
    inventorySlots.resize(maxInventorySlots);
    // Instead of using resize for sf::Text, clear and fill it with constructed objects.
    inventoryTexts.clear();
    for (int i = 0; i < maxInventorySlots; ++i) {
        inventoryTexts.push_back(sf::Text(font, "", 14));
    }
    
    for (int i = 0; i < maxInventorySlots; i++) {
        inventorySlots[i].setSize(sf::Vector2f(220.f, 30.f));
        inventorySlots[i].setFillColor(sf::Color(60, 60, 80));
        inventorySlots[i].setOutlineColor(sf::Color(120, 120, 150));
        inventorySlots[i].setOutlineThickness(1.f);
        
        // Now inventoryTexts[i] is already constructed with the font.
        inventoryTexts[i].setFont(font);
        inventoryTexts[i].setCharacterSize(14);
        inventoryTexts[i].setFillColor(sf::Color::White);
    }
    
    // Initialize skill slots
    const int maxSkillSlots = 6;
    skillSlots.resize(maxSkillSlots);
    skillTexts.clear();
    for (int i = 0; i < maxSkillSlots; ++i) {
        skillTexts.push_back(sf::Text(font, "", 14));
    }
    
    for (int i = 0; i < maxSkillSlots; i++) {
        skillSlots[i].setSize(sf::Vector2f(220.f, 40.f));
        skillSlots[i].setFillColor(sf::Color(60, 60, 80));
        skillSlots[i].setOutlineColor(sf::Color(120, 120, 150));
        skillSlots[i].setOutlineThickness(1.f);
        
        skillTexts[i].setFont(font);
        skillTexts[i].setCharacterSize(14);
        skillTexts[i].setFillColor(sf::Color::White);
    }
    
    // Initialize army unit slots
    const int maxUnitSlots = 8;
    unitSlots.resize(maxUnitSlots);
    unitTexts.clear();
    for (int i = 0; i < maxUnitSlots; ++i) {
        unitTexts.push_back(sf::Text(font, "", 14));
    }
    
    for (int i = 0; i < maxUnitSlots; i++) {
        unitSlots[i].setSize(sf::Vector2f(480.f, 40.f));
        unitSlots[i].setFillColor(sf::Color(60, 60, 80));
        unitSlots[i].setOutlineColor(sf::Color(120, 120, 150));
        unitSlots[i].setOutlineThickness(1.f);
        
        unitTexts[i].setFont(font);
        unitTexts[i].setCharacterSize(14);
        unitTexts[i].setFillColor(sf::Color::White);
    }
    
    // Initialize shop item slots
    const int maxShopItemSlots = 10;
    shopItemSlots.resize(maxShopItemSlots);
    shopItemTexts.clear();
    for (int i = 0; i < maxShopItemSlots; ++i) {
        shopItemTexts.push_back(sf::Text(font, "", 14));
    }
    
    for (int i = 0; i < maxShopItemSlots; i++) {
        shopItemSlots[i].setSize(sf::Vector2f(240.f, 34.f));
        shopItemSlots[i].setFillColor(sf::Color(60, 60, 80));
        shopItemSlots[i].setOutlineColor(sf::Color(120, 120, 150));
        shopItemSlots[i].setOutlineThickness(1.f);
        
        shopItemTexts[i].setFont(font);
        shopItemTexts[i].setCharacterSize(14);
        shopItemTexts[i].setFillColor(sf::Color::White);
    }
    
    // Initialize shop unit slots
    const int maxShopUnitSlots = 6;
    shopUnitSlots.resize(maxShopUnitSlots);
    shopUnitTexts.clear();
    for (int i = 0; i < maxShopUnitSlots; ++i) {
        shopUnitTexts.push_back(sf::Text(font, "", 14));
    }
    
    for (int i = 0; i < maxShopUnitSlots; i++) {
        shopUnitSlots[i].setSize(sf::Vector2f(240.f, 50.f));
        shopUnitSlots[i].setFillColor(sf::Color(60, 60, 80));
        shopUnitSlots[i].setOutlineColor(sf::Color(120, 120, 150));
        shopUnitSlots[i].setOutlineThickness(1.f);
        
        shopUnitTexts[i].setFont(font);
        shopUnitTexts[i].setCharacterSize(14);
        shopUnitTexts[i].setFillColor(sf::Color::White);
    }
    
    updateResourceDisplay();
    
    return true;
}

void UIManager::updateResources(const PlayerResources& resources) {
    playerResources = resources;
    updateResourceDisplay();
}

void UIManager::updateResourceDisplay() {
    foodText.setString("Food: " + std::to_string(playerResources.food));
    woodText.setString("Wood: " + std::to_string(playerResources.wood));
    stoneText.setString("Stone: " + std::to_string(playerResources.stone));
    goldText.setString("Gold: " + std::to_string(playerResources.gold));
}

void UIManager::updateUnitInfoDisplay(PlayerUnit* unit) {
    if (unit) {
        // Show panel with unit info
        UnitType type = unit->getType();
        
        // Update text based on unit type
        switch(type) {
            case UnitType::Settler:
                unitTypeText.setString("Type: Settler");
                unitHealthText.setString("Health: 10/10");
                unitMovementText.setString("Movement: 2");
                unitActionText.setString("[F] - Found City");
                break;
            case UnitType::Warrior:
                unitTypeText.setString("Type: Warrior");
                unitHealthText.setString("Health: 20/20");
                unitMovementText.setString("Movement: 3");
                unitActionText.setString("[A] - Attack");
                break;
            default:
                unitTypeText.setString("Type: Unknown");
                unitHealthText.setString("Health: --");
                unitMovementText.setString("Movement: --");
                unitActionText.setString("");
        }
    }
}

void UIManager::updateCityDisplay(game::GameCity* city) {
    if (city) {
        cityTitle.setString(city->getName());
        cityPopulation.setString("Population: " + std::to_string(city->getPopulation()));
        cityFood.setString("Food: " + std::to_string(city->getFood()) + " per turn");
        cityProduction.setString("Production: " + std::to_string(city->getProduction()) + " per turn");
        cityGold.setString("Gold: " + std::to_string(city->getGoldPerTurn()) + " per turn");
        
        // Update production information
        auto currentProduction = city->getCurrentProduction();
        int progress = city->getProductionProgress();
        int needed = city->getProductionNeeded();
        
        // Update production buttons based on what's currently being produced
        std::string itemName = game::GameCity::getItemName(currentProduction);
        settlerText.setString("Settler (" + std::to_string(progress) + "/" + std::to_string(needed) + ")");
    }
}

void UIManager::updateHeroDisplay(Hero* hero) {
    if (!hero) return;
    
    // Update hero panel information
    heroTitle.setString(hero->getName());
    heroLevel.setString("Level: " + std::to_string(hero->getLevel()));
    heroExp.setString("Experience: " + std::to_string(hero->getExperience()) + 
                     "/" + std::to_string(hero->getExperienceToNextLevel()));
    heroGold.setString("Gold: " + std::to_string(hero->getGold()));
    
    // Update attributes text
    std::string attrText = "Attributes:\n";
    attrText += "STR: " + std::to_string(hero->getAttribute(HeroAttribute::Strength)) + "\n";
    attrText += "INT: " + std::to_string(hero->getAttribute(HeroAttribute::Intelligence)) + "\n";
    attrText += "DEX: " + std::to_string(hero->getAttribute(HeroAttribute::Dexterity)) + "\n";
    attrText += "VIT: " + std::to_string(hero->getAttribute(HeroAttribute::Vitality));
    heroAttributes.setString(attrText);
    
    // Update inventory slots
    const auto& inventory = hero->getInventory();
    for (size_t i = 0; i < inventorySlots.size(); i++) {
        if (i < inventory.size()) {
            // Item exists at this slot
            inventoryTexts[i].setString(inventory[i].name + (inventory[i].isEquipped ? " [E]" : ""));
            inventorySlots[i].setFillColor(sf::Color(60, 60, 100));
        } else {
            // Empty slot
            inventoryTexts[i].setString("Empty");
            inventorySlots[i].setFillColor(sf::Color(60, 60, 80));
        }
    }
    
    // Update skill slots
    const auto& skills = hero->getSkills();
    for (size_t i = 0; i < skillSlots.size(); i++) {
        if (i < skills.size()) {
            // Skill exists at this slot
            skillTexts[i].setString(skills[i].name + " (Lvl " + std::to_string(skills[i].level) + ")");
            skillSlots[i].setFillColor(sf::Color(60, 100, 60));
        } else {
            // Empty slot
            skillTexts[i].setString("No Skill");
            skillSlots[i].setFillColor(sf::Color(60, 60, 80));
        }
    }
}

void UIManager::updateArmyDisplay(Army* army) {
    if (!army) return;
    
    // Update army panel title
    Hero* leader = army->getLeader();
    armyTitle.setString(leader ? leader->getName() + "'s Army" : "Army");
    
    // Update army stats
    armyCounts.setString("Units: " + std::to_string(army->getSize()) + "/" + 
                        std::to_string(army->getCapacity()) + "\n" +
                        "Total Attack: " + std::to_string(army->getTotalAttack()) + "\n" +
                        "Total Defense: " + std::to_string(army->getTotalDefense()));
    
    // Update unit slots
    const auto& units = army->getUnits();
    for (size_t i = 0; i < unitSlots.size(); i++) {
        if (i < units.size()) {
            // Unit exists at this slot
            std::string unitInfo = units[i].name + " (" + 
                                  std::to_string(units[i].health) + "/" + 
                                  std::to_string(units[i].maxHealth) + ")";
            unitTexts[i].setString(unitInfo);
            
            // Color based on unit type
            switch (units[i].type) {
                case ArmyUnitType::Infantry:
                    unitSlots[i].setFillColor(sf::Color(60, 60, 150));
                    break;
                case ArmyUnitType::Archer:
                    unitSlots[i].setFillColor(sf::Color(60, 150, 60));
                    break;
                case ArmyUnitType::Cavalry:
                    unitSlots[i].setFillColor(sf::Color(150, 60, 60));
                    break;
                case ArmyUnitType::Mage:
                    unitSlots[i].setFillColor(sf::Color(150, 60, 150));
                    break;
                default:
                    unitSlots[i].setFillColor(sf::Color(60, 60, 80));
            }
        } else {
            // Empty slot
            unitTexts[i].setString("Empty");
            unitSlots[i].setFillColor(sf::Color(60, 60, 80));
        }
    }
}

void UIManager::updateMerchantDisplay(NPCMerchant* merchant) {
    if (!merchant) return;
    
    // Update merchant info
    merchantTitle.setString(merchant->getName());
    merchantDescription.setString("Welcome to my shop! I have units and items for sale.");
    
    // Update item shop slots
    const auto& items = merchant->getAvailableItems();
    for (size_t i = 0; i < shopItemSlots.size(); i++) {
        if (i < items.size()) {
            // Item exists at this slot
            shopItemTexts[i].setString(items[i].name + " - " + 
                                     std::to_string(items[i].value) + " gold");
            shopItemSlots[i].setFillColor(sf::Color(60, 60, 100));
        } else {
            // Empty slot
            shopItemTexts[i].setString("No item");
            shopItemSlots[i].setFillColor(sf::Color(60, 60, 80));
        }
    }
    
    // Update unit shop slots
    const auto& units = merchant->getAvailableUnits();
    for (size_t i = 0; i < shopUnitSlots.size(); i++) {
        if (i < units.size()) {
            // Unit exists at this slot
            shopUnitTexts[i].setString(units[i].name + " - " + 
                                     std::to_string(units[i].cost) + " gold");
            
            // Color based on unit type
            switch (units[i].type) {
                case ArmyUnitType::Infantry:
                    shopUnitSlots[i].setFillColor(sf::Color(60, 60, 150));
                    break;
                case ArmyUnitType::Archer:
                    shopUnitSlots[i].setFillColor(sf::Color(60, 150, 60));
                    break;
                case ArmyUnitType::Cavalry:
                    shopUnitSlots[i].setFillColor(sf::Color(150, 60, 60));
                    break;
                case ArmyUnitType::Mage:
                    shopUnitSlots[i].setFillColor(sf::Color(150, 60, 150));
                    break;
                default:
                    shopUnitSlots[i].setFillColor(sf::Color(60, 60, 80));
            }
        } else {
            // Empty slot
            shopUnitTexts[i].setString("No unit");
            shopUnitSlots[i].setFillColor(sf::Color(60, 60, 80));
        }
    }
}

void UIManager::showTileInfo(const game::Tile& tile, int col, int row) {
    // Set modal to visible
    showModal = true;
    
    // Position modal in center of screen
    float windowWidth = uiView.getSize().x;
    float windowHeight = uiView.getSize().y;
    
    modalBackground.setPosition(sf::Vector2f(windowWidth / 2.f - 150.f, windowHeight / 2.f - 100.f));
    modalTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 140.f, windowHeight / 2.f - 90.f));
    modalContent.setPosition(sf::Vector2f(windowWidth / 2.f - 140.f, windowHeight / 2.f - 60.f));
    closeButton.setPosition(sf::Vector2f(windowWidth / 2.f + 100.f, windowHeight / 2.f - 90.f));
    
    // Update modal text with tile info
    std::string tileTypeName;
    switch (tile.type) {
        case game::TileType::Plains: tileTypeName = "Plains"; break;
        case game::TileType::Hills: tileTypeName = "Hills"; break;
        case game::TileType::Mountain: tileTypeName = "Mountain"; break;
        case game::TileType::Forest: tileTypeName = "Forest"; break;
        case game::TileType::Water: tileTypeName = "Water"; break;
    }
    modalTitle.setString("Tile Info: " + tileTypeName);
    
    std::string content = "Position: " + std::to_string(col) + ", " + std::to_string(row) + "\n";
    content += "Movement Cost: " + std::to_string(tile.stats.movementCost) + "\n";
    content += "Resource: ";
    if (tile.resource.hasResource) {
        std::string resourceName;
        switch(tile.resource.resourceType) {
            case game::ResourceType::Food: resourceName = "Food"; break;
            case game::ResourceType::Wood: resourceName = "Wood"; break;
            case game::ResourceType::Stone: resourceName = "Stone"; break;
            case game::ResourceType::Gold: resourceName = "Gold"; break;
        }
        content += resourceName + " (+" + std::to_string(tile.resource.baseProduction) + ")";
    } else {
        content += "None";
    }
    modalContent.setString(content);
}

void UIManager::showHeroInfo(Hero* hero) {
    if (!hero) return;
    
    showHeroPanel = true;
    updateHeroDisplay(hero);
    
    // Position hero panel in center of screen
    float windowWidth = uiView.getSize().x;
    float windowHeight = uiView.getSize().y;
    
    heroPanel.setPosition(sf::Vector2f(windowWidth / 2.f - 250.f, windowHeight / 2.f - 200.f));
    
    // Position title and stats
    heroTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f - 190.f));
    heroLevel.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f - 160.f));
    heroExp.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f - 140.f));
    heroGold.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f - 120.f));
    heroAttributes.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f - 90.f));
    
    // Position inventory panel
    inventoryPanel.setPosition(sf::Vector2f(windowWidth / 2.f - 240.f, windowHeight / 2.f - 10.f));
    inventoryTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f));
    
    // Position inventory slots
    for (size_t i = 0; i < inventorySlots.size(); i++) {
        float yPos = windowHeight / 2.f + 25.f + (i % 6) * 35.f;
        float xPos = windowWidth / 2.f - 230.f + (i / 6) * 225.f;
        
        inventorySlots[i].setPosition(sf::Vector2f(xPos, yPos));
        inventoryTexts[i].setPosition(sf::Vector2f(xPos + 5.f, yPos + 5.f));
    }
    
    // Position skill panel
    skillPanel.setPosition(sf::Vector2f(windowWidth / 2.f + 10.f, windowHeight / 2.f - 10.f));
    skillTitle.setPosition(sf::Vector2f(windowWidth / 2.f + 20.f, windowHeight / 2.f));
    
    // Position skill slots
    for (size_t i = 0; i < skillSlots.size(); i++) {
        skillSlots[i].setPosition(sf::Vector2f(windowWidth / 2.f + 20.f, windowHeight / 2.f + 25.f + i * 45.f));
        skillTexts[i].setPosition(sf::Vector2f(windowWidth / 2.f + 25.f, windowHeight / 2.f + 30.f + i * 45.f));
    }
    
    // Position back button
    backButton.setPosition(sf::Vector2f(windowWidth / 2.f + 150.f, windowHeight / 2.f - 190.f));
    backText.setPosition(sf::Vector2f(windowWidth / 2.f + 180.f, windowHeight / 2.f - 184.f));
}

void UIManager::showArmyInfo(Army* army) {
    if (!army) return;
    
    showArmyPanel = true;
    updateArmyDisplay(army);
    
    // Position army panel in center of screen
    float windowWidth = uiView.getSize().x;
    float windowHeight = uiView.getSize().y;
    
    armyPanel.setPosition(sf::Vector2f(windowWidth / 2.f - 250.f, windowHeight / 2.f - 200.f));
    
    // Position title and stats
    armyTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f - 190.f));
    armyCounts.setPosition(sf::Vector2f(windowWidth / 2.f - 230.f, windowHeight / 2.f - 160.f));
    
    // Position unit slots
    for (size_t i = 0; i < unitSlots.size(); i++) {
        unitSlots[i].setPosition(sf::Vector2f(windowWidth / 2.f - 240.f, windowHeight / 2.f - 80.f + i * 45.f));
        unitTexts[i].setPosition(sf::Vector2f(windowWidth / 2.f - 235.f, windowHeight / 2.f - 75.f + i * 45.f));
    }
    
    // Position back button
    backButton.setPosition(sf::Vector2f(windowWidth / 2.f + 150.f, windowHeight / 2.f - 190.f));
    backText.setPosition(sf::Vector2f(windowWidth / 2.f + 180.f, windowHeight / 2.f - 184.f));
}

void UIManager::showMerchantInfo(NPCMerchant* merchant) {
    if (!merchant) return;
    
    showMerchantPanel = true;
    updateMerchantDisplay(merchant);
    
    // Position merchant panel in center of screen
    float windowWidth = uiView.getSize().x;
    float windowHeight = uiView.getSize().y;
    
    merchantPanel.setPosition(sf::Vector2f(windowWidth / 2.f - 275.f, windowHeight / 2.f - 225.f));
    
    // Position title and description
    merchantTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 255.f, windowHeight / 2.f - 215.f));
    merchantDescription.setPosition(sf::Vector2f(windowWidth / 2.f - 255.f, windowHeight / 2.f - 185.f));
    
    // Position item shop panel
    shopItemsPanel.setPosition(sf::Vector2f(windowWidth / 2.f - 265.f, windowHeight / 2.f - 155.f));
    shopItemsTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 255.f, windowHeight / 2.f - 145.f));
    
    // Position item slots
    for (size_t i = 0; i < shopItemSlots.size(); i++) {
        shopItemSlots[i].setPosition(sf::Vector2f(windowWidth / 2.f - 255.f, windowHeight / 2.f - 120.f + i * 38.f));
        shopItemTexts[i].setPosition(sf::Vector2f(windowWidth / 2.f - 250.f, windowHeight / 2.f - 115.f + i * 38.f));
    }
    
    // Position unit shop panel
    shopUnitsPanel.setPosition(sf::Vector2f(windowWidth / 2.f + 5.f, windowHeight / 2.f - 155.f));
    shopUnitsTitle.setPosition(sf::Vector2f(windowWidth / 2.f + 15.f, windowHeight / 2.f - 145.f));
    
    // Position unit slots
    for (size_t i = 0; i < shopUnitSlots.size(); i++) {
        shopUnitSlots[i].setPosition(sf::Vector2f(windowWidth / 2.f + 15.f, windowHeight / 2.f - 120.f + i * 54.f));
        shopUnitTexts[i].setPosition(sf::Vector2f(windowWidth / 2.f + 20.f, windowHeight / 2.f - 115.f + i * 54.f));
    }
    
    // Position back button
    backButton.setPosition(sf::Vector2f(windowWidth / 2.f + 175.f, windowHeight / 2.f - 215.f));
    backText.setPosition(sf::Vector2f(windowWidth / 2.f + 205.f, windowHeight / 2.f - 209.f));
}

void UIManager::showCityInfo(game::GameCity* city) {
    if (!city) return;
    
    showCityPanel = true;
    updateCityDisplay(city);
    
    // Position city panel in center of screen
    float windowWidth = uiView.getSize().x;
    float windowHeight = uiView.getSize().y;
    
    cityPanel.setPosition(sf::Vector2f(windowWidth / 2.f - 200.f, windowHeight / 2.f - 150.f));
    
    // Position title and stats
    cityTitle.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f - 140.f));
    cityPopulation.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f - 100.f));
    cityFood.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f - 75.f));
    cityProduction.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f - 50.f));
    cityGold.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f - 25.f));
    
    // Position production buttons
    settlerButton.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f + 10.f));
    settlerText.setPosition(sf::Vector2f(windowWidth / 2.f - 170.f, windowHeight / 2.f + 20.f));
    
    warriorButton.setPosition(sf::Vector2f(windowWidth / 2.f - 180.f, windowHeight / 2.f + 60.f));
    warriorText.setPosition(sf::Vector2f(windowWidth / 2.f - 170.f, windowHeight / 2.f + 70.f));
    
    builderButton.setPosition(sf::Vector2f(windowWidth / 2.f + 20.f, windowHeight / 2.f + 10.f));
    builderText.setPosition(sf::Vector2f(windowWidth / 2.f + 30.f, windowHeight / 2.f + 20.f));
    
    buildingButton.setPosition(sf::Vector2f(windowWidth / 2.f + 20.f, windowHeight / 2.f + 60.f));
    buildingText.setPosition(sf::Vector2f(windowWidth / 2.f + 30.f, windowHeight / 2.f + 70.f));
}

bool UIManager::isCloseButtonClicked(const sf::Vector2f& position) const {
    return closeButton.getGlobalBounds().contains(position);
}

bool UIManager::isStartButtonClicked(const sf::Vector2f& position) const {
    return startButton.getGlobalBounds().contains(position);
}

bool UIManager::isSettlerButtonClicked(const sf::Vector2f& position) const {
    return settlerButton.getGlobalBounds().contains(position);
}

bool UIManager::isWarriorButtonClicked(const sf::Vector2f& position) const {
    return warriorButton.getGlobalBounds().contains(position);
}

bool UIManager::isBuilderButtonClicked(const sf::Vector2f& position) const {
    return builderButton.getGlobalBounds().contains(position);
}

bool UIManager::isBuildingButtonClicked(const sf::Vector2f& position) const {
    return buildingButton.getGlobalBounds().contains(position);
}

bool UIManager::isBackButtonClicked(const sf::Vector2f& position) const {
    return backButton.getGlobalBounds().contains(position);
}

bool UIManager::isHeroButtonClicked(const sf::Vector2f& position) const {
    return heroButton.getGlobalBounds().contains(position);
}

bool UIManager::isArmyButtonClicked(const sf::Vector2f& position) const {
    return armyButton.getGlobalBounds().contains(position);
}

bool UIManager::isInventorySlotClicked(const sf::Vector2f& position, int& slotIndex) const {
    for (size_t i = 0; i < inventorySlots.size(); i++) {
        if (inventorySlots[i].getGlobalBounds().contains(position)) {
            slotIndex = i;
            return true;
        }
    }
    return false;
}

bool UIManager::isSkillSlotClicked(const sf::Vector2f& position, int& slotIndex) const {
    for (size_t i = 0; i < skillSlots.size(); i++) {
        if (skillSlots[i].getGlobalBounds().contains(position)) {
            slotIndex = i;
            return true;
        }
    }
    return false;
}

bool UIManager::isUnitSlotClicked(const sf::Vector2f& position, int& slotIndex) const {
    for (size_t i = 0; i < unitSlots.size(); i++) {
        if (unitSlots[i].getGlobalBounds().contains(position)) {
            slotIndex = i;
            return true;
        }
    }
    return false;
}

bool UIManager::isShopItemClicked(const sf::Vector2f& position, int& itemIndex) const {
    for (size_t i = 0; i < shopItemSlots.size(); i++) {
        if (shopItemSlots[i].getGlobalBounds().contains(position)) {
            itemIndex = i;
            return true;
        }
    }
    return false;
}

bool UIManager::isShopUnitClicked(const sf::Vector2f& position, int& unitIndex) const {
    for (size_t i = 0; i < shopUnitSlots.size(); i++) {
        if (shopUnitSlots[i].getGlobalBounds().contains(position)) {
            unitIndex = i;
            return true;
        }
    }
    return false;
}

void UIManager::drawResourcePanel(sf::RenderWindow& window) {
    // Position resource panel in top-left
    resourcePanel.setPosition(sf::Vector2f(10.f, 10.f));
    resourceTitle.setPosition(sf::Vector2f(20.f, 15.f));
    foodText.setPosition(sf::Vector2f(20.f, 40.f));
    woodText.setPosition(sf::Vector2f(20.f, 60.f));
    stoneText.setPosition(sf::Vector2f(20.f, 80.f));
    goldText.setPosition(sf::Vector2f(20.f, 100.f));
    
    window.draw(resourcePanel);
    window.draw(resourceTitle);
    window.draw(foodText);
    window.draw(woodText);
    window.draw(stoneText);
    window.draw(goldText);
}

void UIManager::drawUnitInfo(sf::RenderWindow& window, PlayerUnit* selectedUnit) {
    if (selectedUnit) {
        float windowHeight = uiView.getSize().y;
        
        // Position unit info panel in bottom-left
        unitInfoPanel.setPosition(sf::Vector2f(10.f, windowHeight - 160.f));
        unitTitle.setPosition(sf::Vector2f(20.f, windowHeight - 155.f));
        unitTypeText.setPosition(sf::Vector2f(20.f, windowHeight - 130.f));
        unitHealthText.setPosition(sf::Vector2f(20.f, windowHeight - 110.f));
        unitMovementText.setPosition(sf::Vector2f(20.f, windowHeight - 90.f));
        unitActionText.setPosition(sf::Vector2f(20.f, windowHeight - 70.f));
        
        updateUnitInfoDisplay(selectedUnit);
        
        window.draw(unitInfoPanel);
        window.draw(unitTitle);
        window.draw(unitTypeText);
        window.draw(unitHealthText);
        window.draw(unitMovementText);
        window.draw(unitActionText);
    }
}

void UIManager::drawCityInfo(sf::RenderWindow& window, game::GameCity* selectedCity) {
    if (showCityPanel && selectedCity) {
        // Draw city panel
        window.draw(cityPanel);
        
        // Draw city info
        window.draw(cityTitle);
        window.draw(cityPopulation);
        window.draw(cityFood);
        window.draw(cityProduction);
        window.draw(cityGold);
        
        // Draw production buttons
        window.draw(settlerButton);
        window.draw(settlerText);
        window.draw(warriorButton);
        window.draw(warriorText);
        window.draw(builderButton);
        window.draw(builderText);
        window.draw(buildingButton);
        window.draw(buildingText);
    }
}

void UIManager::drawHeroInfo(sf::RenderWindow& window, Hero* hero) {
    if (showHeroPanel && hero) {
        // Draw hero panel
        window.draw(heroPanel);
        
        // Draw hero info
        window.draw(heroTitle);
        window.draw(heroLevel);
        window.draw(heroExp);
        window.draw(heroGold);
        window.draw(heroAttributes);
        
        // Draw inventory panel
        window.draw(inventoryPanel);
        window.draw(inventoryTitle);
        
        // Draw inventory slots
        for (size_t i = 0; i < inventorySlots.size(); i++) {
            window.draw(inventorySlots[i]);
            window.draw(inventoryTexts[i]);
        }
        
        // Draw skill panel
        window.draw(skillPanel);
        window.draw(skillTitle);
        
        // Draw skill slots
        for (size_t i = 0; i < skillSlots.size(); i++) {
            window.draw(skillSlots[i]);
            window.draw(skillTexts[i]);
        }
        
        // Draw back button
        window.draw(backButton);
        window.draw(backText);
    }
}

void UIManager::drawArmyInfo(sf::RenderWindow& window, Army* army) {
    if (showArmyPanel && army) {
        // Draw army panel
        window.draw(armyPanel);
        
        // Draw army info
        window.draw(armyTitle);
        window.draw(armyCounts);
        
        // Draw unit slots
        for (size_t i = 0; i < unitSlots.size(); i++) {
            window.draw(unitSlots[i]);
            window.draw(unitTexts[i]);
        }
        
        // Draw back button
        window.draw(backButton);
        window.draw(backText);
    }
}

void UIManager::drawMerchantInfo(sf::RenderWindow& window, NPCMerchant* merchant) {
    if (showMerchantPanel && merchant) {
        // Draw merchant panel
        window.draw(merchantPanel);
        
        // Draw merchant info
        window.draw(merchantTitle);
        window.draw(merchantDescription);
        
        // Draw item shop panel
        window.draw(shopItemsPanel);
        window.draw(shopItemsTitle);
        
        // Draw item slots
        for (size_t i = 0; i < shopItemSlots.size(); i++) {
            window.draw(shopItemSlots[i]);
            window.draw(shopItemTexts[i]);
        }
        
        // Draw unit shop panel
        window.draw(shopUnitsPanel);
        window.draw(shopUnitsTitle);
        
        // Draw unit slots
        for (size_t i = 0; i < shopUnitSlots.size(); i++) {
            window.draw(shopUnitSlots[i]);
            window.draw(shopUnitTexts[i]);
        }
        
        // Draw back button
        window.draw(backButton);
        window.draw(backText);
    }
}

void UIManager::drawToggleButtons(sf::RenderWindow& window) {
    float windowWidth = uiView.getSize().x;
    float windowHeight = uiView.getSize().y;
    
    // Position hero button in bottom-right
    heroButton.setPosition(sf::Vector2f(windowWidth - 130.f, windowHeight - 100.f));
    heroButtonText.setPosition(sf::Vector2f(windowWidth - 110.f, windowHeight - 94.f));
    
    // Position army button in bottom-right
    armyButton.setPosition(sf::Vector2f(windowWidth - 130.f, windowHeight - 50.f));
    armyButtonText.setPosition(sf::Vector2f(windowWidth - 110.f, windowHeight - 44.f));
    
    // Draw buttons
    window.draw(heroButton);
    window.draw(heroButtonText);
    window.draw(armyButton);
    window.draw(armyButtonText);
}

void UIManager::drawModal(sf::RenderWindow& window) {
    if (showModal) {
        window.draw(modalBackground);
        window.draw(modalTitle);
        window.draw(modalContent);
        window.draw(closeButton);
    }
}

void UIManager::drawMenu(sf::RenderWindow& window) {
    float windowWidth = uiView.getSize().x;
    float windowHeight = uiView.getSize().y;
    
    window.draw(menuBackground);
    
    // Position title and buttons
    titleText.setPosition(sf::Vector2f(windowWidth / 2.f - 200.f, windowHeight / 2.f - 150.f));
    startButton.setPosition(sf::Vector2f(windowWidth / 2.f - 100.f, windowHeight / 2.f - 25.f));
    startText.setPosition(sf::Vector2f(windowWidth / 2.f - 60.f, windowHeight / 2.f - 20.f));
    
    window.draw(titleText);
    window.draw(startButton);
    window.draw(startText);
}