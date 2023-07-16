#include "../Headers/Vector.h"

Vector::Vector(int givenCapacity) {
  this->capacity = givenCapacity;
  this->size = 0;
  this->data = new graphNode[capacity];
}

void Vector::printAll() {

  for(int i = 0; i < this->size; i++){
    if(this->getAt(i)->cityName != nullptr){
      std::cout << this->getAt(i)->cityName << std::endl;
    }
  }
}

void Vector::pushBack(int j, int i, int nodeCounter, char terrainType) {
  if(this->size == this->capacity){
    this->capacity = (int)(1.5*this->capacity);
    this->data = (graphNode*)realloc(this->data, 32*this->capacity);
  }
  this->data[size] = graphNode{j,i,nodeCounter, terrainType, nullptr};
  size += 1;
}

graphNode* Vector::getAt(int index) {
  if (index < 0 || index >= this->size) {
    std::cout << "Invalid Index";
    exit(1);
  }
  return &(this->data[index]);
}