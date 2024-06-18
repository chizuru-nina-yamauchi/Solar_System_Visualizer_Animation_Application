/**
 * Purpose: Implement the methods of the Planet class that are declared in the Planet.hpp header file.
 *  It defines how the planet's position is updated based on its orbit and rotation, and how it is drawn on the screen using SFML.
 *  The setter methods allow customization of the planet's properties.
 *
 *
 * */


#include <cmath>
#include <iostream>
#include "Planet.hpp" // Include the header file for the Planet class


// Constructor for the Planet class that initializes the planet with specified parameters
Planet::Planet(const std::string name, float radius, float distance, float orbitSpeed, float rotationSpeed, sf::Color color,
               sf::Vector2f position)
    : name(name), radius(radius), distance(distance/10), orbitSpeed(orbitSpeed), rotationSpeed(rotationSpeed),
      color(color), position(position), currentAngle(0), currentRotation(0), orbitingPlanet(nullptr) {
    // Initialize the circle shape with the specified radius
    shape.setRadius(radius);

    // Set the position of the circle shape to the specified position
    shape.setPosition(position);

    // Set the fill color of the circle shape to the specified color
    shape.setFillColor(color);

    // Set the origin of the circle shape to the center of the shape
    shape.setOrigin(radius, radius); // Origin is set to the center of the circle

}

/**
 * This function updates the state of a Planet object based on the elapsed time.
 * If the planet is orbiting another planet (i.e., orbitingPlanet is not nullptr), it calculates the new position of the planet in its orbit around the orbitingPlanet.
 * This is done by incrementing the current angle of the planet's orbit (currentAngle) based on the planet's orbit speed (orbitSpeed) and the elapsed time (deltaTime),
 * and then calculating the new x and y coordinates of the planet's position.
 *
 * */

void Planet::update(float deltaTime) {
    if(orbitingPlanet){
        // orbitSpeed * deltaTime calculates how much the current angle should change based on the speed of the orbit and the elapsed time.
        // The new x and y coordinates are then calculated using the updated angle and the distance from the planet it's orbiting.
        // The position of the planet is then updated with these new coordinates.
        float angleIncrement = orbitSpeed * deltaTime;
        std::cout << "orbitSpeed: " << orbitSpeed << ", deltaTime: " << deltaTime << ", angleIncrement: " << angleIncrement << std::endl;
        currentAngle += angleIncrement;
            float x = orbitingPlanet->position.x + distance * cos(currentAngle);
            float y = orbitingPlanet->position.y + distance * sin(currentAngle);
            position = sf::Vector2f(x, y); // Update the position of the planet based on the new x and y coordinates.
            shape.setPosition(position); // Update the position of the circle shape to match the new position of the planet.
        } else {
            float screenCenterX = 800.0f; // X coordinate of the screen center
            float screenCenterY = 600.0f; // Y coordinate of the screen center
            position = sf::Vector2f(screenCenterX + distance*cos(currentAngle), screenCenterY + distance*sin(currentAngle)); // Update the position member variable of the Planet object based on the current angle and distance from the center.
            shape.setPosition(position);  // sets the position of the shape object to the current position of the Planet object. The setPosition function takes a sf::Vector2f object that represents the new position of the shape.
        }


    /**
     * this code ensures that the planet rotates and moves correctly based on the elapsed time, which makes the movement smooth and consistent,
     * regardless of the frame rate.
     *
     *
     * */
    float rotationIncrement = rotationSpeed * deltaTime;  // Calculates the amount by which the planet's rotation should change in the current frame. rotationSpeed is the speed at which the planet rotates, and deltaTime is the time elapsed since the last frame.
    currentRotation += rotationIncrement; // Updates the current rotation angle of the planet by adding the rotation increment. This means the planet's rotation is increased by an amount that ensures it rotates at the correct speed, regardless of the frame rate.
    shape.setRotation(currentRotation); // applies the updated rotation to the shape object, which is a sf::CircleShape that visually represents the planet. The setRotation function sets the rotation of the shape in degrees.


    // Debug print statements
    std::cout << name << " position: (" << position.x << ", " << position.y << ")" << std::endl;
    std::cout << name << " rotation: " << shape.getRotation() << std::endl;

}

/**
 * The purpose of this function is to draw the Planet object on a specified window.
 * It uses the sf::RenderWindow object passed as a parameter to draw the circle shape that represents the planet.
 * This function is typically called once per frame to render the planet on the screen.
 *
 * */

void Planet::draw(sf::RenderWindow& window) {
    // Debug print statement
    std::cout << "Drawing planet...\n"; // Outputs "Drawing planet..." to the console to indicate that the planet is being drawn.
    std::cout << "Drawing "<< name << " at position: (" << shape.getPosition().x << ", " << shape.getPosition().y << ")" << std::endl;

    window.draw(shape); // Draws the circle shape on the specified window. The draw function is used to render the shape on the window.
}



// Setters for various properties of the Planet class

/**
 * The purpose of this function is to set the planet as orbiting around another planet.
 * It takes a pointer to a Planet object as a parameter and sets the orbitingPlanet member variable to point to the specified planet.
 * This establishes a relationship between the two planets, where the current planet orbits around the specified planet.
 *
 * */
void Planet::setOrbiting(Planet* planet) {
    orbitingPlanet = planet; // Sets the orbitingPlanet member variable to point to the specified planet. This establishes the relationship where the current planet orbits around the specified planet.
}

void Planet::setRotationSpeed(float speed) {
    rotationSpeed = speed; // Sets the rotation speed of the planet to the specified speed. This determines how fast the planet rotates around its own axis.
}

void Planet::setOrbitSpeed(float speed) {
    orbitSpeed = speed; // Sets the orbit speed of the planet to the specified speed. This determines how fast the planet orbits around another planet or point.
}

void Planet::setDistance(float distance) {
    this->distance = distance; // Sets the distance of the planet from the planet it's orbiting around to the specified distance. This determines how far the planet is from the center of the orbit.
}

void Planet::setRadius(float radius) {
    this->radius = radius; // Sets the radius of the planet to the specified radius. This determines the size of the planet.
    shape.setRadius(radius); // Updates the radius of the circle shape to match the new radius of the planet: update for visual representation with sfml
    shape.setOrigin(radius, radius); // Updates the origin of the circle shape to the center of the shape based on the new radius: update for visual representation with sfml
}

void Planet::setColor(sf::Color color) {
    this->color = color; // Sets the color of the planet to the specified color. This determines the visual appearance of the planet.
    shape.setFillColor(color); // Updates the fill color of the circle shape to match the new color of the planet: update for visual representation with sfml
}

void Planet::setPosition(sf::Vector2f position) {
    this->position = position; // Sets the position of the planet to the specified position. This determines the location of the planet on the screen.
    shape.setPosition(position); // Updates the position of the circle shape to match the new position of the planet: update for visual representation with sfml
}

void Planet::setTexture(const std::string& texturePath) { // const: In this context, const means the function promises not to modify the texturePath argument that it receives.
    // const and &: it means that the function promises not to modify the original data. This allows the function to be called with both modifiable and non-modifiable strings.
    if (texture.loadFromFile(texturePath)) { // Loads the texture from the specified file path. If the texture is loaded successfully, the function returns true.
        shape.setTexture(&texture); // Sets the texture of the circle shape to the loaded texture. This applies the texture to the visual representation of the planet.
    }

}

void Planet::setOrigin(sf::Vector2f origin) {
    shape.setOrigin(origin); // Sets the origin of the circle shape to the specified origin. This determines the point around which the shape rotates and scales.
}

void Planet::setRotation(float angle) {
    shape.setRotation(angle); // Sets the rotation of the circle shape to match the specified angle. This visually rotates the planet to the specified angle.
}


