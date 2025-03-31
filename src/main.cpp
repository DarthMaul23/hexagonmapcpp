#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

// Define the different tile types.
enum class TileType { Water, Sand, Land, Mountain };

// Structure for tile statistics.
struct TileStats {
    int defense;
    int movementCost;
};

// Each tile holds its type, stats, and computed center position.
struct Tile {
    TileType type;
    TileStats stats;
    sf::Vector2f center; // Pixel coordinates for the center of the hexagon.
};

// ------------------ GLOBAL CONSTANTS ------------------
const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 50;
const float HEX_SIZE = 30.f; // "Radius" of the pointy-topped hexagon.

// Returns a color associated with each tile type.
sf::Color getTileColor(TileType type) {
    switch (type) {
        case TileType::Water:    return sf::Color(77, 166, 255);
        case TileType::Sand:     return sf::Color(255, 230, 128);
        case TileType::Land:     return sf::Color(102, 204, 102);
        case TileType::Mountain: return sf::Color(153, 153, 153);
        default:                 return sf::Color::White;
    }
}

/*
   Create a pointy-topped hexagon shape centered at 'center'.
   Corners at angles: 0°, 60°, 120°, 180°, 240°, 300°.
*/
sf::ConvexShape createPointyHex(const sf::Vector2f& center) {
    sf::ConvexShape hex;
    hex.setPointCount(6);

    // Each side is HEX_SIZE, corners at multiples of 60 degrees.
    for (int i = 0; i < 6; i++) {
        float angle_deg = 60.f * i;
        float angle_rad = angle_deg * 3.14159265f / 180.f;
        sf::Vector2f point(HEX_SIZE * std::cos(angle_rad),
                           HEX_SIZE * std::sin(angle_rad));
        hex.setPoint(i, center + point);
    }
    return hex;
}

/*
   "Odd-q" layout for pointy-topped hexes:
   - Each column is 0.75 * hexWidth apart (hexWidth = sqrt(3)*HEX_SIZE).
   - Each row is hexHeight (2*HEX_SIZE) apart.
   - For an odd column, shift the center down by half a hexHeight.
*/
sf::Vector2f getHexCenter(int col, int row) {
    float hexWidth  = std::sqrt(3.f) * HEX_SIZE;  // tip-to-tip horizontally
    float hexHeight = HEX_SIZE;             // tip-to-tip vertically

    // Horizontal spacing: 0.75 * hexWidth for each column.
    float x = col * (0.90f * hexWidth);

    // Base vertical position: row * hexHeight.
    float y = row * hexHeight;

    // For an odd column, shift down by half a hex height.
    if (col % 2 == 1) {
        y += hexHeight * 0.5f;
    }

    return sf::Vector2f(x, y);
}

// Helper function to see if the mouse is over a rectangle (in screen coords).
bool isMouseOverShape(const sf::RectangleShape& shape, const sf::RenderWindow& window) {
    auto bounds = shape.getGlobalBounds();
    auto mousePos = sf::Mouse::getPosition(window); // screen coords
    return bounds.contains(sf::Vector2f(static_cast<float>(mousePos.x), 
                                      static_cast<float>(mousePos.y)));
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create the SFML window.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hexagon Tile Map");
    window.setFramerateLimit(60);

    // Create a view (camera) and velocity for smooth movement.
    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    window.setView(view);
    sf::Vector2f viewVelocity(0.f, 0.f);
    const float moveSpeed = 300.f; // pixels per second

    // Build the tile map (odd-q layout).
    std::vector<std::vector<Tile>> tileMap(MAP_WIDTH, std::vector<Tile>(MAP_HEIGHT));
    for (int col = 0; col < MAP_WIDTH; col++) {
        for (int row = 0; row < MAP_HEIGHT; row++) {
            // Randomly choose a tile type.
            int randVal = std::rand() % 4;
            TileType type;
            switch(randVal) {
                case 0: type = TileType::Water; break;
                case 1: type = TileType::Sand; break;
                case 2: type = TileType::Land; break;
                case 3: type = TileType::Mountain; break;
            }
            TileStats stats = { std::rand() % 10, std::rand() % 5 + 1 };

            // Compute the center for a pointy hex in an odd-q layout.
            sf::Vector2f center = getHexCenter(col, row);

            tileMap[col][row] = { type, stats, center };
        }
    }

    // Load a font for rendering text.
    sf::Font font;
    if (!font.openFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load font from assets/arial.ttf\n";
        return -1;
    }

    // Modal variables for showing tile info.
    bool showModal = false;
    int selectedCol = -1;
    int selectedRow = -1;

    // Modal background
    sf::RectangleShape modalBackground(sf::Vector2f(350.f, 220.f));
    modalBackground.setFillColor(sf::Color(50, 50, 50, 200));
    modalBackground.setPosition({225.f, 180.f});  // fixed screen position for modal

    // Text to display tile info
    sf::Text modalText(font, "", 18);
    modalText.setFillColor(sf::Color::White);
    modalText.setPosition({modalBackground.getPosition().x + 10.f,
                           modalBackground.getPosition().y + 10.f});

    // Close button (a small red square in the top-right of the modal)
    sf::RectangleShape closeButton(sf::Vector2f(20.f, 20.f));
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setPosition({
        modalBackground.getPosition().x + modalBackground.getSize().x - 30.f,
        modalBackground.getPosition().y + 10.f
    });
    sf::Text closeButtonText(font, "X", 14);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setPosition({
        closeButton.getPosition().x + 4.f,
        closeButton.getPosition().y - 2.f
    });

    // Buttons to change the tile type.
    // We'll make 4 small rectangles + labels for each tile type.
    const float btnWidth = 70.f;
    const float btnHeight = 30.f;
    const float btnTop = modalBackground.getPosition().y + 130.f;
    const float btnLeft = modalBackground.getPosition().x + 10.f;

    sf::RectangleShape btnWater(sf::Vector2f(btnWidth, btnHeight));
    btnWater.setFillColor(sf::Color(90, 90, 90));
    btnWater.setPosition({btnLeft, btnTop});

    sf::Text btnWaterText(font, "Water", 14);
    btnWaterText.setFillColor(sf::Color::White);
    btnWaterText.setPosition({btnLeft + 5.f, btnTop + 5.f});

    sf::RectangleShape btnSand(sf::Vector2f(btnWidth, btnHeight));
    btnSand.setFillColor(sf::Color(90, 90, 90));
    btnSand.setPosition({btnLeft + 80.f, btnTop});

    sf::Text btnSandText(font, "Sand", 14);
    btnSandText.setFillColor(sf::Color::White);
    btnSandText.setPosition({btnSand.getPosition().x + 10.f, btnTop + 5.f});

    sf::RectangleShape btnLand(sf::Vector2f(btnWidth, btnHeight));
    btnLand.setFillColor(sf::Color(90, 90, 90));
    btnLand.setPosition({btnLeft + 160.f, btnTop});

    sf::Text btnLandText(font, "Land", 14);
    btnLandText.setFillColor(sf::Color::White);
    btnLandText.setPosition({btnLand.getPosition().x + 10.f, btnTop + 5.f});

    sf::RectangleShape btnMountain(sf::Vector2f(btnWidth, btnHeight));
    btnMountain.setFillColor(sf::Color(90, 90, 90));
    btnMountain.setPosition({btnLeft + 240.f, btnTop});

    sf::Text btnMountainText(font, "Mountain", 14);
    btnMountainText.setFillColor(sf::Color::White);
    btnMountainText.setPosition({btnMountain.getPosition().x + 2.f, btnTop + 5.f});

    // Helper to refresh the text displayed in the modal.
    auto updateModalText = [&](int c, int r) {
        const Tile& t = tileMap[c][r];
        std::stringstream ss;
        ss << "Tile Type: ";
        switch(t.type) {
            case TileType::Water:    ss << "Water";    break;
            case TileType::Sand:     ss << "Sand";     break;
            case TileType::Land:     ss << "Land";     break;
            case TileType::Mountain: ss << "Mountain"; break;
        }
        ss << "\nDefense: " << t.stats.defense;
        ss << "\nMovement Cost: " << t.stats.movementCost;
        modalText.setString(ss.str());
    };

    sf::Clock clock;
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            // Close window.
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Keyboard input for camera movement (only if modal not active, or you can allow camera movement anyway).
            if (!showModal) {
                if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyEvent->code == sf::Keyboard::Key::Left || keyEvent->code == sf::Keyboard::Key::A)
                        viewVelocity.x = -moveSpeed;
                    if (keyEvent->code == sf::Keyboard::Key::Right || keyEvent->code == sf::Keyboard::Key::D) 
                        viewVelocity.x = moveSpeed;
                    if (keyEvent->code == sf::Keyboard::Key::Up || keyEvent->code == sf::Keyboard::Key::W)
                        viewVelocity.y = -moveSpeed;
                    if (keyEvent->code == sf::Keyboard::Key::Down || keyEvent->code == sf::Keyboard::Key::S)
                        viewVelocity.y = moveSpeed;
                }
                if (const auto* keyEvent = event->getIf<sf::Event::KeyReleased>()) {
                    if (keyEvent->code == sf::Keyboard::Key::Left || keyEvent->code == sf::Keyboard::Key::Right)
                        viewVelocity.x = 0;
                    if (keyEvent->code == sf::Keyboard::Key::Up || keyEvent->code == sf::Keyboard::Key::Down)
                        viewVelocity.y = 0;
                }
            }
            else {
                // If modal is open, ignore arrow keys for tile selection, etc.
                // (You can still allow camera movement if desired.)
            }

            // Mouse input
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {

                    // If the modal is open, first check if user clicked the close button or type buttons.
                    if (showModal) {
                        if (isMouseOverShape(closeButton, window)) {
                            showModal = false;
                            continue;
                        }
                        // Check tile-type buttons:
                        if (isMouseOverShape(btnWater, window)) {
                            tileMap[selectedCol][selectedRow].type = TileType::Water;
                            updateModalText(selectedCol, selectedRow);
                        }
                        else if (isMouseOverShape(btnSand, window)) {
                            tileMap[selectedCol][selectedRow].type = TileType::Sand;
                            updateModalText(selectedCol, selectedRow);
                        }
                        else if (isMouseOverShape(btnLand, window)) {
                            tileMap[selectedCol][selectedRow].type = TileType::Land;
                            updateModalText(selectedCol, selectedRow);
                        }
                        else if (isMouseOverShape(btnMountain, window)) {
                            tileMap[selectedCol][selectedRow].type = TileType::Mountain;
                            updateModalText(selectedCol, selectedRow);
                        }
                        // If modal is open, do NOT allow selecting another tile.
                        // So skip the tile-selection logic below.
                    }
                    else {
                        // Modal not open, so we can select a tile.
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                        bool found = false;
                        for (int col = 0; col < MAP_WIDTH && !found; col++) {
                            for (int row = 0; row < MAP_HEIGHT && !found; row++) {
                                sf::Vector2f center = tileMap[col][row].center;
                                float dx = worldPos.x - center.x;
                                float dy = worldPos.y - center.y;
                                // If within HEX_SIZE, consider it clicked (quick approximation).
                                if (std::sqrt(dx * dx + dy * dy) < HEX_SIZE) {
                                    selectedCol = col;
                                    selectedRow = row;
                                    showModal = true;
                                    updateModalText(col, row);
                                    found = true;
                                }
                            }
                        }
                    }
                }
            }

            // Right-click to close the modal (alternative to the close button).
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Right) {
                    if (showModal) {
                        showModal = false;
                    }
                }
            }
        }

        // Smooth camera movement.
        float dt = clock.restart().asSeconds();
        view.move(viewVelocity * dt);
        window.setView(view);

        window.clear(sf::Color::Black);

        // Draw the hex tiles.
        for (int col = 0; col < MAP_WIDTH; col++) {
            for (int row = 0; row < MAP_HEIGHT; row++) {
                sf::ConvexShape hex = createPointyHex(tileMap[col][row].center);
                hex.setFillColor(getTileColor(tileMap[col][row].type));
                hex.setOutlineThickness(1.f);
                hex.setOutlineColor(sf::Color::Black);
                window.draw(hex);
            }
        }

        // If modal is active, draw it using the default (screen) view.
        if (showModal) {
            window.setView(window.getDefaultView());
            window.draw(modalBackground);
            window.draw(modalText);

            // Close button
            window.draw(closeButton);
            window.draw(closeButtonText);

            // Tile-type buttons
            window.draw(btnWater);
            window.draw(btnWaterText);
            window.draw(btnSand);
            window.draw(btnSandText);
            window.draw(btnLand);
            window.draw(btnLandText);
            window.draw(btnMountain);
            window.draw(btnMountainText);

            window.setView(view); // Restore the game view afterward
        }

        window.display();
    }

    return 0;
}