#include <SFML/Graphics.hpp> // Include the SFML graphics library for graphics rendering
#include "Planet.hpp"
#include "Database.hpp"
#include <vector>
#include <cstdlib> // For std::getenv
#include <iostream> // For std::cerr

int main() {
    // Create a window with a resolution of 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(800, 600), "Solar System Simulation");

    // Retrieve the connection string from an environment variable
    const char* db_conn = std::getenv("DB_CONNECTION_STRING");
    if (!db_conn) {
        std::cerr << "DB_CONNECTION_STRING environment variable not set" << std::endl;
        return 1;
    }
    std::string connectionString = db_conn;
    // Create a database connection
    Database db(connectionString);

    // Create a vector to store the planets
    std::vector<Planet> planets;

    // Load planets from the database
    planets = db.loadPlanets();

    sf::Clock clock; // Create a clock to measure time

    // Main game loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds(); // Restart the clock and get the elapsed time since the last frame in seconds
        // Clear the window
        window.clear();

        // Update and draw each planet
        for (auto& planet : planets) {
            planet.update(deltaTime); // Update the planet's position with the actual delta time
            planet.draw(window); // Draw the planet on the window
        }

        // Display the window contents
        window.display();
    }

    return 0;
}
