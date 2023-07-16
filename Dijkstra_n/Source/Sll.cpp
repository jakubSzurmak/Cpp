#include "../Headers/Sll.h"


Sll::Sll() {
  this->next = nullptr;
}

void Sll::printAll() {
  Sll* node = this;
  while(node){
    std::cout << node->city.cityName << node->getX() << " " << node->getY() << std::endl;
    node = node->next;
  }
}


void Sll::appendCity(char* cityName, int x, int y) {

  if(this->written){
    Sll* newNode = new Sll();
    Sll* lastNode = this;

    newNode->city.cityName = cityName;
    newNode->city.x = x;
    newNode->city.y = y;
    while(lastNode->next != nullptr){
      lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    lastNode->next->written = true;

  }else{
    this->city.y = y;
    this->city.x = x;
    this->city.cityName = cityName;
    this->written = true;
  }

}

char* Sll::getCityName() {
  return this->city.cityName;
}

int Sll::getX() {
  return this->city.x;
}

int Sll::getY() {
  return this->city.y;
}

Sll* Sll::getNext() {
  return this->next;
}