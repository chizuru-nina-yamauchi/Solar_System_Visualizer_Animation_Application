/**
 *
 * hpp files are header files that contain declarations of classes, functions, and variables.
 * hpp file serve a similar role to interfaces in other languages. hpp files typically contain function prototypes, class definitions, constants, and other references which provide a "contract" that the corresponding implementation file (.cpp) must follow
 *
 *
 * */

#ifndef PLANET_HPP // Processor directive to avoid multiple inclusion(if not defined). Used with #endif
#define PLANET_HPP // Processor directive to define a macro which is a name that represents a piece of code or value. Once macro is defined, the compiler will replace all instances of the macro in the code wih its defined value or code before the actual compilation process begins.

#include <SFML/Graphics.hpp> // Include the SFML graphics library(Simple and Fast Multimedia Library) for graphics rendering
#include <string>

/**
 * In SFML library, a sf::Vector2f object represents a 2D vector,
 * which can be used to represent various things such as a position,
 * a size, or a velocity, depending on the context.
 * It contains two floating-point numbers, representing
 * the x and y coordinates (or components) of the vector.
 */

class Planet {
public:
    Planet(float radius, float distance, float orbitSpeed, float rotationSpeed, sf::Color color, sf::Vector2f position); // sf:: is a namespace that contains all the classes and functions provided by SFML library

    // deltaTime represents the time elapsed between two frames. In other words, it's the time it took to complete the last frame. This is used to make movement and other time-based actions smooth and consistent, regardless of the frame rate.
    void update(float deltaTime); // Function to update the planet's position based on time
    void draw(sf::RenderWindow& window); // Function to draw the planet on the window(sf::RenderWindow is a class that represents the window where graphics are rendered by SFML)

    //Setters
    void setOrbiting(Planet* planet); // Function to set the planet as orbiting around another planet : Planet* is a pointer to a Planet object#
    void setRotationSpeed(float speed); // Renamed setRotation to setRotationSpeed to avoid confusion with the setRotation function that sets the rotation angle
    void setOrbitSpeed(float speed);
    void setDistance(float distance);
    void setRadius(float radius);
    void setColor(sf::Color color);
    void setPosition(sf::Vector2f position);
    /*
     * The const keyword in const std::string& texturePath is used to indicate that the function setTexture will not modify the texturePath argument.
     * This is a promise to the compiler that the function will not change the value of texturePath
     * */
    void setTexture(const std::string& texturePath);  // Use const std::string& texturePath to pass the texture path as a constant reference to avoid copying the string
    void setOrigin(sf::Vector2f origin);
    void setRotation(float angle);

    private:
        std::string name;
        float radius;
        float distance;
        float orbitSpeed; // Speed of orbiting around another planet or point
        float rotationSpeed; // Speed of rotation around its own axis
        sf::Color color;
        sf::Vector2f position;
        sf::CircleShape shape; // Circle shape to represent the planet visually
        float currentAngle; // Current angle for the orbit
        float currentRotation; // Current rotation angle for the orbit
        Planet* orbitingPlanet; // Pointer to another planet that this planet is orbiting around
        sf::Texture texture; // Texture for the planet's appearance


};
#endif // End a conditional directive block started by #if, #ifdef, or #ifndef. It tells the preprocessor that the conditional code block has ended.