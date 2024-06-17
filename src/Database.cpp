#include "Database.hpp"
#include <iostream>

sf::Color intToColor(int color) {
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    return sf::Color(r, g, b);
}

// Constructor to initialize(represent) the database connection and provide functionality to load planets from the database.
Database::Database(const std::string& connectionString){ // This constructor takes a single parameter, const std::string& connectionString, which is a string containing the connection details for the PostgreSQL database.
    try{
        // Try to create a new database connection using the provided connection string
        db = new pqxx::connection(connectionString); // pqxx is like jdbc in Java, both are APIs that allow to interact with database, but pqxx is only for PostgreSQL
            if(!db->is_open()){
               std::cerr << "Can't open database" << std::endl;
            }
        } catch (const std::exception &e){ // for example, if the connection string is invalid or the database server is not running.
            std::cerr << e.what() << std::endl; // output the error message to the standard error stream.
        }
}


// Destructor to close the database connection
Database::~Database(){
    db->disconnect(); // Disconnect from the database
    delete db; // Delete the database connection object
}

// Function to load planets from the database
std::vector<Planet> Database::loadPlanets(){
    std::vector<Planet> planets; // Create a vector to store the loaded planets: std::vector is a dynamic array that can grow or shrink in size.
    try {
        pqxx::work W(*db); // Start a database transaction using the connection object
        std::string query = "SELECT name, radius, distance, orbit_speed, rotation_speed, color, position_x, position_y FROM planets"; // SQL query to select all planets from the database
        pqxx::result R = W.exec(query); // Execute the query and store the result in R

        // Iterate over the result set and create a Planet object for each row
        for(auto row : R){
            // Extract the values from the row
            std::string name = row["name"].c_str();
            float radius = row["radius"].as<float>();
            float distance = row["distance"].as<float>();
            float orbitSpeed = row["orbit_speed"].as<float>();
            float rotationSpeed = row["rotation_speed"].as<float>();
            int colorInt = row["color"].as<int>();
            sf::Color color = intToColor(colorInt);

            float position_X = row["position_x"].as<float>();
            float position_Y = row["position_y"].as<float>();

            sf::Vector2f position(position_X, position_Y); // Create a 2D vector representing the position of the planet

            planets.emplace_back(radius, distance, orbitSpeed, rotationSpeed, color, sf::Vector2f(position_X, position_Y)); // Create a new Planet object and add it to the vector of planets
        }
        W.commit(); // Commit the transaction
    } catch (const std::exception &e) { // Catch any exceptions that occur during the database operation
        std::cerr << e.what() << std::endl; // Output the error message to the standard error stream
    }

    return planets; // Return the vector of loaded planets
}