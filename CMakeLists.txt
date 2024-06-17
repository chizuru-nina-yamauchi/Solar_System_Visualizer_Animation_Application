# Defines project structure, dependencies and build options

# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set project name
project(SolarSystemSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Use pkg-config to find libpqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Add executable
add_executable(SolarSystemSimulation src/main.cpp src/Planet.cpp src/Database.cpp)

# Link SFML and libpqxx libraries
target_link_libraries(SolarSystemSimulation sfml-graphics sfml-window sfml-system ${PQXX_LIBRARIES})
