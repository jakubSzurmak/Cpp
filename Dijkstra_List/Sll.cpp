#include "Sll.h"

Sll::Sll() {
  this->next = nullptr;
  written = false;
}

void Sll::appendCity(char* cityName, int x, int y, int id) {

  if(this->written){
    Sll* newNode = new Sll();
    Sll* lastNode = this;

    newNode->city.cityName = cityName;
    newNode->city.x = x;
    newNode->city.y = y;
    newNode->city.id = id;
    while(lastNode->next != nullptr){
      lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    lastNode->next->written = true;

  }else{
    this->city.y = y;
    this->city.x = x;
    this->city.cityName = cityName;
    this->city.id = id;
    this->written = true;
  }

}

char* Sll::getCityName() const {
  return this->city.cityName;
}

int Sll::getId() const{
  return this->city.id;
}


Sll* Sll::getNext() {
  return this->next;
}