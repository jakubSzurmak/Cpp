cmake_minimum_required(VERSION 3.24)
project(JakDojade)

set(CMAKE_CXX_STANDARD 17)

add_executable(JakDojade main.cpp Source/String.cpp Headers/String.h Source/Sll.cpp Headers/Sll.h Source/Vector.cpp Headers/Vector.h)
