#include "../Headers/String.h"

std::ostream& operator<<(std::ostream& ostr, const String& stringForPrinting) {
  for (unsigned short i = 0; i < stringForPrinting.stringArrSize; i++) {
    ostr << stringForPrinting[i];
  }
  return ostr;
}

const char& String::operator[](std::size_t index) const {
  return stringArr[index];
}


short const String::stringLength() {
  return this->stringArrSize;
}

short String::stringLength(const char* givenString) { //GivenstrLen and objStrLen
  short i = 0;
  char x = ' ';
  while ((x != '\0') && (x != '\r')) {
    x = givenString[i];
    i++;
  }
  return i;
}

char String::stringPop() {
  char tmp = stringArr[stringTerminatorIndex - 1];
  stringArr[stringTerminatorIndex - 1] = '\0';
  return tmp;
}

char* String::getStrArr() {
  return this->stringArr;
}

void String::stringFillArray(const char* givenString) {
  if (stringArr == NULL) {
    short len = stringLength(givenString);
    stringArr = (char*)malloc(sizeof(*stringArr) * len);
    stringArrSize = len;
    stringTerminatorIndex = len - 1;
  }
  for (short i = 0; i < stringArrSize; i++) {
    stringArr[i] = givenString[i];
  }
}

String::String() {
  return;
}

String::String(char* givenString) {
  if (givenString != nullptr) {
    short len = stringLength(givenString);
    stringArr = new char[len];
    stringArrSize = len;
    stringTerminatorIndex = stringArrSize - 1;
    stringFillArray(givenString);
  }
}

String::~String() {
}