/*
 *  This class represents a database connection and provides functionality to load planets from the database.
 *  It uses the pqxx library, which is a C++ interface for working with PostgreSQL databases.
 *
 */

//Include guard
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <vector>
#include <pqxx/pqxx> // Include the PostgreSQL library
#include "Planet.hpp" // Include the Planet class header file: It is like an interface class in Java

class Database {
public:
    Database(const std::string& connectionString); // Constructor to initialize the database connection
    ~Database(); // Destructor to close the database connection

    std::vector<Planet> loadPlanets(); // Function to load planets from the database

private:
    pqxx::connection* db; // Pointer to the database connection object
};





#endif