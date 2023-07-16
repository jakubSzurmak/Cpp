#pragma once
#include "String.h"

struct cityData{
  int x, y;
  char* cityName;
};

class Sll {
 private:
  bool written = false;
  cityData city;
  Sll* next;
 public:
  Sll();
  void appendCity(char* cityName, int x, int y);
  void printAll();
  char* getCityName();
  int getX();
  int getY();
  Sll* getNext();
};
