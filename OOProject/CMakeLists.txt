cmake_minimum_required(VERSION 3.24)
project(OOProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOProject main.cpp Source/World.cpp Headers/World.h Headers/Organism.h Source/Animal.cpp Headers/Animal.h Source/Human.cpp Headers/Human.h Source/Wolf.cpp Headers/Wolf.h Source/Organism.cpp Source/Sheep.cpp Headers/Sheep.h Source/Fox.cpp Headers/Fox.h Source/Turtle.cpp Headers/Turtle.h Source/Antelope.cpp Headers/Antelope.h Source/Plant.cpp Headers/Plant.h Source/Grass.cpp Headers/Grass.h Source/SowThistle.cpp Headers/SowThistle.h Source/Guarana.cpp Headers/Guarana.h Source/Belladonna.cpp Headers/Belladonna.h Source/Sosnowsky.cpp Headers/Sosnowsky.h)
