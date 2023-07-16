#include "Vector.h"

Vector::Vector(int givenCapacity) {
  this->capacity = givenCapacity;
  this->size = 0;
  this->data = new graphNode[capacity];
}

int Vector::getSize() const {
  return size;
}

void Vector::pushBack(int j, int i, int nodeCounter, char terrainType) {
  if(this->size == this->capacity){
    this->capacity = (int)(1.5*this->capacity);
    this->data = (graphNode*)realloc(this->data, capacity*sizeof(graphNode));
  }
  this->data[size] = graphNode{j,i,nodeCounter, terrainType, nullptr};
  size += 1;
}

graphNode* Vector::getAt(int index) {
  if (index < 0 || index >= this->size) {
    return nullptr;
  }
  return &(this->data[index]);
}