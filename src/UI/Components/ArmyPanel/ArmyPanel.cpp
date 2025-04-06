#include "ArmyPanel.hpp"
#include "Army.hpp"
#include <iostream>

ArmyPanel::ArmyPanel(const sf::Font& font)
    : Panel(font),
      showArmyPanel(false),
      selectedArmy(nullptr)
{
    // Initialize text elements with the font
    armyTitle.setFont(font);
    armyCounts.setFont(font);
    backText.setFont(font);
}

bool ArmyPanel::initialize()
{
    // Set up army panel
    armyPanel.setSize(sf::Vector2f(500.f, 400.f));
    armyPanel.setFillColor(sf::Color(40, 40, 60, 230));
    armyPanel.setOutlineColor(sf::Color(100, 100, 150));
    armyPanel.setOutlineThickness(2.f);
    
    // Initialize text properties
    armyTitle.setCharacterSize(24);
    armyTitle.setFillColor(sf::Color::White);
    
    armyCounts.setCharacterSize(16);
    armyCounts.setFillColor(sf::Color::White);
    
    // Initialize back button
    backButton.setSize(sf::Vector2f(100.f, 40.f));
    backButton.setFillColor(sf::Color(80, 80, 120));
    backButton.setOutlineColor(sf::Color(120, 120, 180));
    backButton.setOutlineThickness(1.f);
    
    backText.setString("Back");
    backText.setCharacterSize(16);
    backText.setFillColor(sf::Color::White);
    
    // Initialize unit slots
    initializeUnitSlots();
    
    return true;
}

void ArmyPanel::initializeUnitSlots()
{
    const int maxUnitSlots = 8;
    unitSlots.resize(maxUnitSlots);
    unitTexts.clear();
    
    for (int i = 0; i < maxUnitSlots; ++i) {
        // Create text with proper font initialization
        sf::Text slotText;
        slotText.setFont(font);
        slotText.setCharacterSize(14);
        slotText.setFillColor(sf::Color::White);
        unitTexts.push_back(slotText);
        
        // Initialize rectangle shape for slot
        unitSlots[i].setSize(sf::Vector2f(480.f, 40.f));
        unitSlots[i].setFillColor(sf::Color(60, 60, 80));
        unitSlots[i].setOutlineColor(sf::Color(120, 120, 150));
        unitSlots[i].setOutlineThickness(1.f);
    }
}

void ArmyPanel::showArmyInfo(Army* army)
{
    if (!army) return;
    
    selectedArmy = army;
    showArmyPanel = true;
    updateArmyDisplay();
}

void ArmyPanel::updateArmyDisplay()
{
    if (!selectedArmy) return;
    
    // Update army panel title
    Hero* leader = selectedArmy->getLeader();
    armyTitle.setString(leader ? leader->getName() + "'s Army" : "Army");
    
    // Update army stats
    armyCounts.setString("Units: " + std::to_string(selectedArmy->getSize()) + "/" + 
                        std::to_string(selectedArmy->getCapacity()) + "\n" +
                        "Total Attack: " + std::to_string(selectedArmy->getTotalAttack()) + "\n" +
                        "Total Defense: " + std::to_string(selectedArmy->getTotalDefense()));
    
    // Update unit slots
    const auto& units = selectedArmy->getUnits();
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

void ArmyPanel::positionElements(float windowWidth, float windowHeight)
{
    // Position army panel in center of screen
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

void ArmyPanel::draw(sf::RenderWindow& window)
{
    if (!showArmyPanel || !selectedArmy) return;
    
    // Get window dimensions for proper positioning
    float windowWidth = window.getView().getSize().x;
    float windowHeight = window.getView().getSize().y;
    
    // Position elements before drawing
    positionElements(windowWidth, windowHeight);
    
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

void ArmyPanel::update(float deltaTime)
{
    // Currently no animation or time-based updates needed
    // This method is here to fulfill the UIComponent interface
}

bool ArmyPanel::isBackButtonClicked(const sf::Vector2f& position) const
{
    return backButton.getGlobalBounds().contains(position);
}

bool ArmyPanel::isUnitSlotClicked(const sf::Vector2f& position, int& slotIndex) const
{
    for (size_t i = 0; i < unitSlots.size(); i++) {
        if (unitSlots[i].getGlobalBounds().contains(position)) {
            slotIndex = i;
            return true;
        }
    }
    return false;
}

