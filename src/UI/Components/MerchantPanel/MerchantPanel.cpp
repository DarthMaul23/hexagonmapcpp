#include "MerchantPanel.hpp"
#include "Merchant.hpp"
#include "Hero.hpp"
#include <iostream>

MerchantPanel::MerchantPanel(const sf::Font& font)
    : Panel(font),
      showMerchantPanel(false),
      selectedMerchant(nullptr),
      playerHero(nullptr),
      selectedItemIndex(-1),
      selectedUnitIndex(-1)
{
    // Initialize text elements with the font
    merchantTitle.setFont(font);
    merchantDescription.setFont(font);
    playerGold.setFont(font);
    
    itemsTitle.setFont(font);
    unitsTitle.setFont(font);
    
    purchaseText.setFont(font);
    sellText.setFont(font);
    backText.setFont(font);
}

bool MerchantPanel::initialize()
{
    // Set up merchant panel
    merchantPanel.setSize(sf::Vector2f(600.f, 500.f));
    merchantPanel.setFillColor(sf::Color(40, 40, 60, 230));
    merchantPanel.setOutlineColor(sf::Color(100, 100, 150));
    merchantPanel.setOutlineThickness(2.f);
    
    // Initialize text properties
    merchantTitle.setCharacterSize(24);
    merchantTitle.setFillColor(sf::Color::White);
    
    merchantDescription.setCharacterSize(16);
    merchantDescription.setFillColor(sf::Color::White);
    
    playerGold.setCharacterSize(18);
    playerGold.setFillColor(sf::Color(255, 215, 0));
    
    // Item shop panel
    shopItemsPanel.setSize(sf::Vector2f(280.f, 380.f));
    shopItemsPanel.setFillColor(sf::Color(50, 50, 70, 200));
    shopItemsPanel.setOutlineColor(sf::Color(100, 100, 150));
    shopItemsPanel.setOutlineThickness(1.f);
    
    itemsTitle.setString("Items for Sale");
    itemsTitle.setCharacterSize(18);
    itemsTitle.setFillColor(sf::Color::White);
    
    // Unit shop panel
    shopUnitsPanel.setSize(sf::Vector2f(280.f, 380.f));
    shopUnitsPanel.setFillColor(sf::Color(50, 50, 70, 200));
    shopUnitsPanel.setOutlineColor(sf::Color(100, 100, 150));
    shopUnitsPanel.setOutlineThickness(1.f);
    
    unitsTitle.setString("Units for Sale");
    unitsTitle.setCharacterSize(18);
    unitsTitle.setFillColor(sf::Color::White);
    
    // Purchase buttons
    purchaseButton.setSize(sf::Vector2f(120.f, 40.f));
    purchaseButton.setFillColor(sf::Color(60, 100, 60));
    purchaseButton.setOutlineColor(sf::Color(100, 150, 100));
    purchaseButton.setOutlineThickness(1.f);
    
    purchaseText.setString("Purchase");
    purchaseText.setCharacterSize(16);
    purchaseText.setFillColor(sf::Color::White);
    
    sellButton.setSize(sf::Vector2f(120.f, 40.f));
    sellButton.setFillColor(sf::Color(100, 60, 60));
    sellButton.setOutlineColor(sf::Color(150, 100, 100));
    sellButton.setOutlineThickness(1.f);
    
    sellText.setString("Sell");
    sellText.setCharacterSize(16);
    sellText.setFillColor(sf::Color::White);
    
    // Back button
    backButton.setSize(sf::Vector2f(100.f, 40.f));
    backButton.setFillColor(sf::Color(80, 80, 120));
    backButton.setOutlineColor(sf::Color(120, 120, 180));
    backButton.setOutlineThickness(1.f);
    
    backText.setString("Back");
    backText.setCharacterSize(16);
    backText.setFillColor(sf::Color::White);
    
    // Initialize shop slots
    initializeShopSlots();
    
    return true;
}

void MerchantPanel::initializeShopSlots()
{
    const int maxItemSlots = 8;
    itemSlots.resize(maxItemSlots);
    itemTexts.clear();
    itemPrices.clear();
    
    const int maxUnitSlots = 6;
    unitSlots.resize(maxUnitSlots);
    unitTexts.clear();
    unitPrices.clear();
    
    // Initialize item slots
    for (int i = 0; i < maxItemSlots; ++i) {
        // Create item text with proper font initialization
        sf::Text itemText;
        itemText.setFont(font);
        itemText.setCharacterSize(14);
        itemText.setFillColor(sf::Color::White);
        itemTexts.push_back(itemText);
        
        // Create price text
        sf::Text priceText;
        priceText.setFont(font);
        priceText.setCharacterSize(14);
        priceText.setFillColor(sf::Color(255, 215, 0));
        itemPrices.push_back(priceText);
        
        // Initialize rectangle shape for slot
        itemSlots[i].setSize(sf::Vector2f(260.f, 40.f));
        itemSlots[i].setFillColor(sf::Color(60, 60, 80));
        itemSlots[i].setOutlineColor(sf::Color(120, 120, 150));
        itemSlots[i].setOutlineThickness(1.f);
    }
    
    // Initialize unit slots
    for (int i = 0; i < maxUnitSlots; ++i) {
        // Create unit text with proper font initialization
        sf::Text unitText;
        unitText.setFont(font);
        unitText.setCharacterSize(14);
        unitText.setFillColor(sf::Color::White);
        unitTexts.push_back(unitText);
        
        // Create price text
        sf::Text priceText;
        priceText.setFont(font);
        priceText.setCharacterSize(14);
        priceText.setFillColor(sf::Color(255, 215, 0));
        unitPrices.push_back(priceText);
        
        // Initialize rectangle shape for slot
        unitSlots[i].setSize(sf::Vector2f(260.f, 50.f));
        unitSlots[i].setFillColor(sf::Color(60, 60, 80));
        unitSlots[i].setOutlineColor(sf::Color(120, 120, 150));
        unitSlots[i].setOutlineThickness(1.f);
    }
}

void MerchantPanel::showMerchantShop(Merchant* merchant, Hero* hero)
{
    if (!merchant || !hero) return;
    
    selectedMerchant = merchant;
    playerHero = hero;
    showMerchantPanel = true;
    clearSelection();
    updateMerchantDisplay();
}

void MerchantPanel::updateMerchantDisplay()
{
    if (!selectedMerchant || !playerHero) return;
    
    // Update merchant information
    merchantTitle.setString(selectedMerchant->getName() + "'s Shop");
    merchantDescription.setString(selectedMerchant->getDescription());
    playerGold.setString("Your Gold: " + std::to_string(playerHero->getGold()));
    
    // Update item shop slots
    const auto& items = selectedMerchant->getItemsForSale();
    for (size_t i = 0; i < itemSlots.size(); i++) {
        if (i < items.size()) {
            // Item exists at this slot
            itemTexts[i].setString(items[i].name);
            itemPrices[i].setString(std::to_string(items[i].price) + " gold");
            
            // Highlight if selected
            if (static_cast<int>(i) == selectedItemIndex) {
                itemSlots[i].setFillColor(sf::Color(80, 80, 120));
                itemSlots[i].setOutlineColor(sf::Color(150, 150, 200));
                itemSlots[i].setOutlineThickness(2.f);
            } else {
                itemSlots[i].setFillColor(sf::Color(60, 60, 100));
                itemSlots[i].setOutlineColor(sf::Color(120, 120, 150));
                itemSlots[i].setOutlineThickness(1.f);
            }
        } else {
            // Empty slot
            itemTexts[i].setString("");
            itemPrices[i].setString("");
            itemSlots[i].setFillColor(sf::Color(60, 60, 80));
            itemSlots[i].setOutlineColor(sf::Color(120, 120, 150));
            itemSlots[i].setOutlineThickness(1.f);
        }
    }
    
    // Update unit shop slots
    const auto& units = selectedMerchant->getUnitsForSale();
    for (size_t i = 0; i < unitSlots.size(); i++) {
        if (i < units.size()) {
            // Unit exists at this slot
            unitTexts[i].setString(units[i].name);
            unitPrices[i].setString(std::to_string(units[i].price) + " gold");
            
            // Highlight if selected
            if (static_cast<int>(i) == selectedUnitIndex) {
                unitSlots[i].setFillColor(sf::Color(80, 80, 120));
                unitSlots[i].setOutlineColor(sf::Color(150, 150, 200));
                unitSlots[i].setOutlineThickness(2.f);
            } else {
                // Color based on unit type
                unitSlots[i].setFillColor(sf::Color(60, 60, 100));
                unitSlots[i].setOutlineColor(sf::Color(120, 120, 150));
                unitSlots[i].setOutlineThickness(1.f);
            }
        } else {
            // Empty slot
            unitTexts[i].setString("");
            unitPrices[i].setString("");
            unitSlots[i].setFillColor(sf::Color(60, 60, 80));
            unitSlots[i].setOutlineColor(sf::Color(120, 120, 150));
            unitSlots[i].setOutlineThickness(1.f);
        }
    }
    
    // Update purchase button state based on selection
    bool canPurchase = (selectedItemIndex >= 0 || selectedUnitIndex >= 0);
    purchaseButton.setFillColor(canPurchase ? sf::Color(60, 100, 60) : sf::Color(60, 80, 60));
}

void MerchantPanel::selectItemSlot(int index)
{
    if (index == selectedItemIndex) {
        // Clicking the already selected item deselects it
        selectedItemIndex = -1;
    } else

