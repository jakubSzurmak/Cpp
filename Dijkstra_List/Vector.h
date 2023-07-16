#pragma once
#include <cstdlib>
#include <cstring>
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
  int getSize() const;
  void pushBack(int j, int i, int nodeCounter, char terrainType);
  graphNode* getAt(int index);
};