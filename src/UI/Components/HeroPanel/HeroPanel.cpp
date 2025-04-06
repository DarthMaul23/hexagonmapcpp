#include "HeroPanel.hpp"
#include "Hero.hpp"
#include <iostream>

namespace ui {

HeroPanel::HeroPanel(const sf::Font& font)
    : Panel(font),
      showHeroPanel(false),
      selectedHero(nullptr)
{
    // Initialize text elements with font
    heroTitle.setFont(font);
    heroLevel.setFont(font);
    heroExp.setFont(font);
    heroGold.setFont(font);
    heroAttributes.setFont(font);
    inventoryTitle.setFont(font);
    skillTitle.setFont(font);
    backText.setFont(font);

    // Initialize dynamic text vectors
    for (int i = 0; i < 6; ++i) {  // 6 inventory slots
        sf::Text slotText;
        slotText.setFont(font);
        inventoryTexts.push_back(slotText);
    }

    for (int i = 0; i < 4; ++i) {  // 4 skill slots
        sf::Text skillText;
        skillText.setFont(font);
        skillTexts.push_back(skillText);
    }
}

bool HeroPanel::initialize()
{
    // Set up hero panel background
    heroPanel.setSize(sf::Vector2f(600.f, 400.f));
    heroPanel.setFillColor(sf::Color(40, 40, 60, 230));
    heroPanel.setOutlineColor(sf::Color(100, 100, 150));
    heroPanel.setOutlineThickness(2.f);
    
    // Initialize hero info text properties
    heroTitle.setCharacterSize(24);
    heroTitle.setFillColor(sf::Color::White);
    heroTitle.setStyle(sf::Text::Bold);
    
    heroLevel.setCharacterSize(16);
    heroLevel.setFillColor(sf::Color::White);
    
    heroExp.setCharacterSize(16);
    heroExp.setFillColor(sf::Color(150, 200, 255));  // Light blue
    
    heroGold.setCharacterSize(16);
    heroGold.setFillColor(sf::Color(255, 215, 0));   // Gold
    
    heroAttributes.setCharacterSize(16);
    heroAttributes.setFillColor(sf::Color::White);
    
    // Set up inventory panel
    inventoryPanel.setSize(sf::Vector2f(280.f, 200.f));
    inventoryPanel.setFillColor(sf::Color(50, 50, 70, 230));
    inventoryPanel.setOutlineColor(sf::Color(100, 100, 150));
    inventoryPanel.setOutlineThickness(1.f);
    
    inventoryTitle.setString("Inventory");
    inventoryTitle.setCharacterSize(18);
    inventoryTitle.setFillColor(sf::Color::White);
    
    // Initialize inventory slots
    initializeInventorySlots();
    
    // Set up skill panel
    skillPanel.setSize(sf::Vector2f(280.f, 200.f));
    skillPanel.setFillColor(sf::Color(50, 50, 70, 230));
    skillPanel.setOutlineColor(sf::Color(100, 100, 150));
    skillPanel.setOutlineThickness(1.f);
    
    skillTitle.setString("Skills");
    skillTitle.setCharacterSize(18);
    skillTitle.setFillColor(sf::Color::White);
    
    // Initialize skill slots
    initializeSkillSlots();
    
    // Initialize back button
    backButton.setSize(sf::Vector2f(100.f, 40.f));
    backButton.setFillColor(sf::Color(100, 60, 60));
    backButton.setOutlineColor(sf::Color(150, 100, 100));
    backButton.setOutlineThickness(1.f);
    
    backText.setString("Back");
    backText.setCharacterSize(16);
    backText.setFillColor(sf::Color::White);
    
    return true;
}

void HeroPanel::initializeInventorySlots()
{
    float slotSize = 80.f;
    float spacing = 10.f;
    
    // Create 6 inventory slots (2 rows x 3 columns)
    for (int i = 0; i < 6; ++i) {
        sf::RectangleShape slot;
        slot.setSize(sf::Vector2f(slotSize, slotSize));
        slot.setFillColor(sf::Color(30, 30, 50, 230));
        slot.setOutlineColor(sf::Color(100, 100, 150));
        slot.setOutlineThickness(1.f);
        inventorySlots.push_back(slot);
        
        // Initialize corresponding text
        inventoryTexts[i].setCharacterSize(14);
        inventoryTexts[i].setFillColor(sf::Color::White);
    }
}

void HeroPanel::initializeSkillSlots()
{
    float slotSize = 80.f;
    float spacing = 10.f;
    
    // Create 4 skill slots (2 rows x 2 columns)
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape slot;
        slot.setSize(sf::Vector2f(slotSize, slotSize));
        slot.setFillColor(sf::Color(30, 30, 50, 230));
        slot.setOutlineColor(sf::Color(100, 100, 150));
        slot.setOutlineThickness(1.f);
        skillSlots.push_back(slot);
        
        // Initialize corresponding text
        skillTexts[i].setCharacterSize(14);
        skillTexts[i].setFillColor(sf::Color::White);
    }
}

void HeroPanel::showHeroInfo(Hero* hero)
{
    if (!hero) return;
    
    selectedHero = hero;
    showHeroPanel = true;
    updateHeroDisplay();
}

void HeroPanel::updateHeroDisplay()
{
    if (!selectedHero) return;
    
    heroTitle.setString(selectedHero->getName());
    heroLevel.setString("Level: " + std::to_string(selectedHero->getLevel()));
    heroExp.setString("Experience: " + std::to_string(selectedHero->getExperience()) + 
                     "/" + std::to_string(selectedHero->getExperienceForNextLevel()));
    heroGold.setString("Gold: " + std::to_string(selectedHero->getGold()));
    
    // Update attributes string with strength, agility, etc.
    std::string attributes = "Attributes:\n";
    attributes += "Strength: " + std::to_string(selectedHero->getStrength()) + "\n";
    attributes += "Agility: " + std::to_string(selectedHero->getAgility()) + "\n";
    attributes += "Intelligence: " + std::to_string(selectedHero->getIntelligence());
    heroAttributes.setString(attributes);
    
    // Update inventory slots
    for (size_t i = 0; i < inventoryTexts.size(); ++i) {
        if (i < selectedHero->getInventory().size()) {
            inventoryTexts[i].setString(selectedHero->getInventory()[i]);
        } else {
            inventoryTexts[i].setString("Empty");
        }
    }
    
    // Update skill slots
    for (size_t i = 0; i < skillTexts.size(); ++i) {
        if (i < selectedHero->getSkills().size()) {
            skillTexts[i].setString(selectedHero->getSkills()[i]);
        } else {
            skillTexts[i].setString("Empty");
        }
    }
}

void HeroPanel::positionElements(float windowWidth, float windowHeight)
{
    // Center the panel on the screen
    float panelX = (windowWidth - heroPanel.getSize().x) / 2.f;
    float panelY = (windowHeight - heroPanel.getSize().y) / 2.f;
    heroPanel.setPosition(panelX, panelY);
    
    // Position hero info text
    float textX = panelX + 20.f;
    float currentY = panelY + 20.f;
    float lineSpacing = 25.f;
    
    heroTitle.setPosition(textX, currentY);
    currentY += lineSpacing * 1.5f;
    
    heroLevel.setPosition(textX, currentY);
    currentY += lineSpacing;
    
    heroExp.setPosition(textX, currentY);
    currentY += lineSpacing;
    
    heroGold.setPosition(textX, currentY);
    currentY += lineSpacing;
    
    heroAttributes.setPosition(textX, currentY);
    
    // Position inventory panel and slots
    float inventoryX = panelX + 300.f;
    float inventoryY = panelY + 20.f;
    inventoryPanel.setPosition(inventoryX, inventoryY);
    inventoryTitle.setPosition(inventoryX + 10.f, inventoryY + 10.f);
    
    // Position inventory slots in a 2x3 grid
    float slotX = inventoryX + 10.f;
    float slotY = inventoryY + 40.f;
    float slotSize = 80.f;
    float slotSpacing = 10.f;
    
    for (size_t i = 0; i < inventorySlots.size(); ++i) {
        int row = i / 3;
        int col = i % 3;
        float x = slotX + col * (slotSize + slotSpacing);
        float y = slotY + row * (slotSize + slotSpacing);
        
        inventorySlots[i].setPosition(x, y);
        centerTextInSlot(inventoryTexts[i], inventorySlots[i]);
    }
    
    // Position skill panel and slots
    float skillX = panelX + 300.f;
    float skillY = panelY + 210.f;
    skillPanel.setPosition(skillX, skillY);
    skillTitle.setPosition(skillX + 10.f, skillY + 10.f);
    
    // Position skill slots in a 2x2 grid
    slotX = skillX + 10.f;
    slotY = skillY + 40.f;
    
    for (size_t i = 0; i < skillSlots.size(); ++i) {
        int row = i / 2;
        int col = i % 2;
        float x = slotX + col * (slotSize + slotSpacing);
        float y = slotY + row * (slotSize + slotSpacing);
        
        skillSlots[i].setPosition(x, y);
        centerTextInSlot(skillTexts[i], skillSlots[i]);
    }
    
    // Position back button
    backButton.setPosition(
        panelX + heroPanel.getSize().x - backButton.getSize().x - 20.f,
        panelY + heroPanel.getSize().y - backButton.getSize().y - 20.f
    );
    centerTextInButton(backText, backButton);
}

void HeroPanel::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        button.getPosition().x + (button.getSize().x - textBounds.width) / 2.f,
        button.getPosition().y + (button.getSize().y - textBounds.height) / 2.f - 5.f
    );
}

void HeroPanel::centerTextInSlot(sf::Text& text, const sf::RectangleShape& slot)
{
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        slot.getPosition().x + (slot.getSize().x - textBounds.width) / 2.f,
        slot.getPosition().y + (slot.getSize().y - textBounds.height) / 2.f - 5.f
    );
}

void HeroPanel::draw(sf::RenderWindow& window)
{
    if (!showHeroPanel || !selectedHero) return;
    
    // Position elements before drawing
    positionElements(window.getSize().x, window.getSize().y);
    
    // Draw main panel and hero info
    window.draw(heroPanel);
    window.draw(heroTitle);
    window.draw(heroLevel);
    window.draw(heroExp);
    window.draw(heroGold);
    window.draw(heroAttributes);
    
    // Draw inventory panel and slots
    window.draw(inventoryPanel);
    window.draw(inventoryTitle);
    for (size_t i = 0; i < inventorySlots.size(); ++i) {
        window.draw(inventorySlots[i]);
        window.draw(inventoryTexts[i]);
    }
    
    // Draw skill panel and slots
    window.draw(skillPanel);
    window.draw(skillTitle);
    for (size_t i = 0; i < skillSlots.size(); ++i) {
