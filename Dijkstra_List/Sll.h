#pragma once
#include <iostream>

struct cityData{
  int x, y, id, distToHead;
  char* cityName;
};

class Sll {
 private:
  bool written;
  cityData city{};
  Sll* next;
 public:
  Sll();
  void appendCity(char* cityName, int x, int y, int id);
  char* getCityName() const;
  int getId() const;
  Sll* getNext();
};
