#ifndef CITY_MANAGER_HPP
#define CITY_MANAGER_HPP

#include "City.hpp"
#include <vector>
#include <string>

namespace game {

class CityManager {
private:
    std::vector<GameCity> cities;
    GameCity* selectedCity;
    
    // City name generator
    std::vector<std::string> cityNames;
    int nameIndex;
    
    void initializeCityNames();
    
public:
    CityManager();
    
    // City management
    void addCity(const sf::Vector2f& position);
    void removeCity(size_t index);
    
    // City access
    size_t getCityCount() const { return cities.size(); }
    GameCity* getCityAt(size_t index);
    
    // Selection
    bool selectCityAt(const sf::Vector2f& position);
    void deselectCity();
    GameCity* getSelectedCity() { return selectedCity; }
    
    // Update and render
    void update();
    void draw(sf::RenderWindow& window);
    
    // Utility
    std::string getNextCityName();
    bool isCityAt(const sf::Vector2f& position) const;
};

} // namespace game

#endif // CITY_MANAGER_HPP