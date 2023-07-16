#pragma once
#include <iostream>
#include <cstring>

class String {
 private:
  char* stringArr = nullptr;
  short stringArrSize = 0;
  short stringTerminatorIndex = 0;
  friend std::ostream& operator<<(std::ostream& ostr, const String& stringForPrinting);

 public:
  String();
  String(char* givenString);
  short const stringLength();
  short stringLength(const char* givenString);
  char stringPop();
  char* getStrArr();
  void stringFillArray(const char* givenString);
  const char& operator[](std::size_t index) const;
  ~String();
};

