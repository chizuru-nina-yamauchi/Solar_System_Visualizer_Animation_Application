// Actual implementation of the Planet class

#include "Planet.hpp" // Include the header file for the Planet class


// Constructor for the Planet class that initializes the planet with specified parameters
Planet::Planet(float radius, float distance, float orbitSpeed, float rotationSpeed, sf::Color color,
               sf::Vector2f position)
    : radius(radius), distance(distance), orbitSpeed(orbitSpeed), rotationSpeed(rotationSpeed),
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
 * The purpose of this function is to update the state of a Planet object based on the elapsed time.
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
        currentAngle += angleIncrement;

        float x = orbitingPlanet->position.x + distance * cos(currentAngle);
        float y = orbitingPlanet->position.y + distance * sin(currentAngle);

        position = sf::Vector2f(x, y);
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
    shape.setPosition(position);  // sets the position of the shape object to the current position of the Planet object. The setPosition function takes a sf::Vector2f object that represents the new position of the shape.
}

/**
 * The purpose of this function is to draw the Planet object on a specified window.
 * It uses the sf::RenderWindow object passed as a parameter to draw the circle shape that represents the planet.
 * This function is typically called once per frame to render the planet on the screen.
 *
 * */

void Planet::draw(sf::RenderWindow& window) {
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


