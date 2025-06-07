
cmake_minimum_required(VERSION 3.10)
project(HexagonMap VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Homebrew prefix for macOS
if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

# Find SFML components
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/City.cpp
    src/CityManager.cpp
    src/PathFinder.cpp
    src/PlayerUnit.cpp
    src/Tile.cpp
    src/UIManager.cpp
    src/UnitManager.cpp
    src/GameManager.cpp    # Add this
    src/Hero.cpp           # Add this
    src/Army.cpp           # Add this
    src/NPCMerchant.cpp    # Add this if it exists
    src/HeroesGraphics.cpp # Add Heroes of Might and Magic 3 style graphics
    src/RomanUI.cpp        # Add Roman Empire UI system
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Link SFML
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

