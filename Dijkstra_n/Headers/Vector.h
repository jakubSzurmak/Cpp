#pragma once
#include "String.h"
#include <cstdlib>
#include <iostream>

struct graphNode{
  int x, y, id;
  char terrainType;
  char* cityName;
};

class Vector {
 private:
    graphNode* data;
    int size;
    int capacity;
 public:
  Vector(int givenCapacity);
  void pushBack(int j, int i, int nodeCounter, char terrainType);
  void printAll();
  graphNode* getAt(int index);
};