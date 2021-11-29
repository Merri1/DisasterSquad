// NAME: Disaster Squad.
// FUNC: Create Engine class.
// DATE: 29/11/2021.

// Include header file.
#include "Engine.h"

// Handles sfml functionality
// Resolutions, memory loading etc.
// Get the screen resolution and create an SFML window and view.
Engine::Engine()
{
    // Set resolution to device width / height values, and set to fullscreen.
    sf::Vector2<float> resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;

    m_Window.create(sf::VideoMode(resolution.x, resolution.y), "Disaster Squad", sf::Style::Fullscreen);

    // Create blank background image.
    sf::Image background;
    background.create(1074, 576, sf::Color::Black);

    // Load grasslands image from file.
    sf::Image grasslandsMap;
}

// Calculating delta time
void Engine::run()
{
    sf::Clock clock;

    while (m_Window.isOpen()) {
        sf::Time dt = clock.restart();

        // Update the total game time.
        m_GameTimeTotal += dt;

        // Make a decimal fraction from the delta time.
        float dtAsSeconds = dt.asSeconds();

        // Input();
        // Update(dtAsSeconds);
        // Draw();
    }
}

// Render function.
void render() {
    // Does something.
}

// Update function.
void update() {}

// Check character and item collisions.
void checkCollisions() {}

// Clean game screen.
void clean() {}

// Testing purposes:
int main() {
}