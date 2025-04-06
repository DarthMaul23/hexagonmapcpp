#ifndef MERCHANT_PANEL_HPP
#define MERCHANT_PANEL_HPP

#include "../../Common/Panel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

// Forward declarations
class Merchant;
class Hero;

/**
 * MerchantPanel component that displays merchant shop with items and units for trade.
 * Extracted from UIManager to follow component-based architecture.
 */
class MerchantPanel : public Panel {
private:
    // Merchant panel
    bool showMerchantPanel;
    sf::RectangleShape merchantPanel;
    sf::Text merchantTitle;
    sf::Text merchantDescription;
    sf::Text playerGold;
    
    // Item shop section
    sf::RectangleShape shopItemsPanel;
    sf::Text itemsTitle;
    std::vector<sf::RectangleShape> itemSlots;
    std::vector<sf::Text> itemTexts;
    std::vector<sf::Text> itemPrices;
    
    // Unit shop section
    sf::RectangleShape shopUnitsPanel;
    sf::Text unitsTitle;
    std::vector<sf::RectangleShape> unitSlots;
    std::vector<sf::Text> unitTexts;
    std::vector<sf::Text> unitPrices;
    
    // Purchase buttons
    sf::RectangleShape purchaseButton;
    sf::Text purchaseText;
    sf::RectangleShape sellButton;
    sf::Text sellText;
    
    // Back button
    sf::RectangleShape backButton;
    sf::Text backText;
    
    // References to currently selected merchant and hero
    Merchant* selectedMerchant;
    Hero* playerHero;
    
    // Currently selected item/unit index
    int selectedItemIndex;
    int selectedUnitIndex;

public:
    MerchantPanel(const sf::Font& font);
    ~MerchantPanel() override = default;
    
    // UIComponent interface implementation
    bool initialize() override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    
    // MerchantPanel specific methods
    void showMerchantShop(Merchant* merchant, Hero* hero);
    void hidePanel() { showMerchantPanel = false; }
    bool isPanelVisible() const { return showMerchantPanel; }
    
    // Interaction handlers
    bool isBackButtonClicked(const sf::Vector2f& position) const;
    bool isPurchaseButtonClicked(const sf::Vector2f& position) const;
    bool isSellButtonClicked(const sf::Vector2f& position) const;
    bool isItemSlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    bool isUnitSlotClicked(const sf::Vector2f& position, int& slotIndex) const;
    
private:
    // Helper methods
    void updateMerchantDisplay();
    void positionElements(float windowWidth, float windowHeight);
    void initializeShopSlots();
    void selectItemSlot(int index);
    void selectUnitSlot(int index);
    void clearSelection();
};

#endif // MERCHANT_PANEL_HPP

