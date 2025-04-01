#include "CityManager.hpp"
#include <iostream>

namespace game {

CityManager::CityManager() : selectedCity(nullptr), nameIndex(0) {
    initializeCityNames();
}

void CityManager::initializeCityNames() {
    // Add some common city names
    cityNames = {
        "Athens", "Rome", "Alexandria", "Babylon", "Cairo",
        "Paris", "London", "Tokyo", "Beijing", "Delhi",
        "Moscow", "Berlin", "Madrid", "Vienna", "Prague",
        "Warsaw", "Stockholm", "Oslo", "Helsinki", "Amsterdam",
        "Brussels", "Lisbon", "Dublin", "Edinburgh", "Copenhagen",
        "Zurich", "Geneva", "Milan", "Naples", "Barcelona",
        "Valencia", "Seville", "Porto", "Lyon", "Marseille",
        "Munich", "Frankfurt", "Hamburg", "Cologne", "Dresden"
    };
}

void CityManager::addCity(const sf::Vector2f& position) {
    std::string name = getNextCityName();
    cities.emplace_back(name, position);
    std::cout << "New city founded: " << name << std::endl;
}

void CityManager::removeCity(size_t index) {
    if (index < cities.size()) {
        if (&cities[index] == selectedCity) {
            selectedCity = nullptr;
        }
        cities.erase(cities.begin() + index);
    }
}

GameCity* CityManager::getCityAt(size_t index) {
    if (index < cities.size()) {
        return &cities[index];
    }
    return nullptr;
}

bool CityManager::selectCityAt(const sf::Vector2f& position) {
    for (auto& city : cities) {
        if (city.contains(position)) {
            selectedCity = &city;
            return true;
        }
    }
    return false;
}

void CityManager::deselectCity() {
    selectedCity = nullptr;
}

void CityManager::update() {
    for (auto& city : cities) {
        city.processTurn();
    }
}

void CityManager::draw(sf::RenderWindow& window) {
    for (auto& city : cities) {
        city.draw(window);
    }
}

std::string CityManager::getNextCityName() {
    if (cityNames.empty()) {
        return "City " + std::to_string(nameIndex++);
    }
    
    if (nameIndex >= cityNames.size()) {
        nameIndex = 0;
    }
    
    return cityNames[nameIndex++];
}

bool CityManager::isCityAt(const sf::Vector2f& position) const {
    for (const auto& city : cities) {
        if (city.contains(position)) {
            return true;
        }
    }
    return false;
}

} // namespace game