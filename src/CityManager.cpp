#include "CityManager.hpp"
#include <iostream>
#include <algorithm>
#include <random>

namespace game {

CityManager::CityManager() 
    : selectedCity(nullptr), 
      nameIndex(0),
      maxCities(10),  // Limit total number of cities
      citySpawnCooldown(0.0f),
      citySpawnInterval(300.0f)  // 5 minutes between city spawns
{
    initializeCityNames();
}

void CityManager::initializeCityNames() {
    // Expanded city name list with more diverse names
    cityNames = {
        // Ancient cities
        "Athens", "Rome", "Alexandria", "Babylon", "Persepolis", 
        "Thebes", "Carthage", "Constantinople", "Jerusalem", "Damascus",
        
        // Medieval cities
        "Venice", "Florence", "Granada", "Samarkand", "Angkor",
        "Tenochtitlan", "Cusco", "Kyoto", "Beijing", "Delhi",
        
        // Modern cities
        "New York", "London", "Paris", "Tokyo", "Sydney",
        "Mumbai", "Shanghai", "Cairo", "Moscow", "Berlin"
    };
}

void CityManager::addCity(const sf::Vector2f& position) {
    // Check if we've reached maximum city limit
    if (cities.size() >= maxCities) {
        std::cout << "Maximum number of cities reached!" << std::endl;
        return;
    }
    
    // Check for minimum distance between cities
    const float minCityDistance = 300.0f;
    for (const auto& existingCity : cities) {
        float dx = position.x - existingCity.getPosition().x;
        float dy = position.y - existingCity.getPosition().y;
        float distanceSquared = dx*dx + dy*dy;
        
        if (distanceSquared < minCityDistance * minCityDistance) {
            std::cout << "Too close to an existing city!" << std::endl;
            return;
        }
    }
    
    // Get next city name
    std::string name = getNextCityName();
    
    // Create and add the city
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

void CityManager::update(float deltaTime) {
    // Update all cities
    for (auto& city : cities) {
        city.processTurn();
    }
    
    // City spawning mechanics (optional)
    citySpawnCooldown += deltaTime;
    if (citySpawnCooldown >= citySpawnInterval) {
        // Periodically attempt to spawn a new city
        trySpawnRandomCity();
        citySpawnCooldown = 0.0f;
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

void CityManager::trySpawnRandomCity() {
    // Only spawn if below max cities
    if (cities.size() >= maxCities) return;
    
    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Assume a reasonable map size (adjust based on your game's map)
    std::uniform_real_distribution<> xDist(100.0f, 3000.0f);
    std::uniform_real_distribution<> yDist(100.0f, 2000.0f);
    
    // Try to spawn a city at a random location
    sf::Vector2f potentialPosition(xDist(gen), yDist(gen));
    
    // This will check for minimum distance and max cities
    addCity(potentialPosition);
}

std::vector<GameCity>& CityManager::getCities() {
    return cities;
}

const std::vector<GameCity>& CityManager::getCities() const {
    return cities;
}

} // namespace game