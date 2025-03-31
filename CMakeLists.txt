cmake_minimum_required(VERSION 3.10)
project(HexagonTileMap)

set(CMAKE_CXX_STANDARD 11)

# Let CMake find the installed SFML (which is version 3) without forcing 2.5.
find_package(SFML COMPONENTS Graphics Window System REQUIRED)


file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Note: You may need to update how you link or use SFML’s graphics functions if the API has changed.
target_link_libraries(${PROJECT_NAME} SFML::Graphics SFML::Window SFML::System)
