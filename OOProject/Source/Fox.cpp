#include "../Headers/Fox.h"

Fox::Fox(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox):Animal(3, 7, 1, FOX, boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

bool Fox::considerAction() {
  return true;
}

bool Fox::abilityActive() {
  return true;
}

int Fox::getCooldownReps() {
  return 0;
}

int Fox::getStrengthDecreaseReps() {
  return 0;
}

int Fox::generateNextPosition() const {
  if ((this->boardField)->getYCord() == 1) {
    if ((this->boardField)->getXCord() == 1) {
      if(this->boardBeginning[this->position + M] == nullptr){
        return this->position + M;
      }else if (this->boardBeginning[this->position + M]->getStrength() <= this->strength) {
        return this->position + M;
      }
      if(this->boardBeginning[this->position + 1] == nullptr){
        return this->position + 1;
      }else if (this->boardBeginning[this->position + 1]->getStrength() <= this->strength) {
        return this->position + 1;
      }
      else{
        return -1;
      }
    } else if ((this->boardField)->getXCord() == N) {
      if(this->boardBeginning[this->position + M] == nullptr){
        return this->position + M;
      }else if (this->boardBeginning[this->position + M]->getStrength() <= this->strength) {
        return this->position + M;
      }
      if(this->boardBeginning[this->position - 1] == nullptr){
        return this->position + M;
      }else if (this->boardBeginning[this->position - 1]->getStrength() <= this->strength) {
        return this->position - 1;
      }
      else{
        return -1;
      }
    } else {
      if(this->boardBeginning[this->position + M] == nullptr){
        return this->position + M;
      }else if (this->boardBeginning[this->position + M]->getStrength() <= this->strength) {
        return this->position + M;
      }
      if(this->boardBeginning[this->position + 1] == nullptr){
        return this->position + 1;
      }else if (this->boardBeginning[this->position + 1]->getStrength() <= this->strength) {
        return this->position + 1;
      }
      if(this->boardBeginning[this->position - 1] == nullptr){
        return this->position - 1;
      }else if (this->boardBeginning[this->position - 1]->getStrength() <= this->strength) {
        return this->position - 1;
      }
      else{
        return -1;
      }
    }
  } else if ((this->boardField)->getYCord() == M) {
    if ((this->boardField)->getXCord() == 1) {
      if(this->boardBeginning[this->position - M] == nullptr){
        return this->position - M;
      }else if (this->boardBeginning[this->position - M]->getStrength() <= this->strength) {
        return this->position - M;
      }
      if(this->boardBeginning[this->position + 1] == nullptr){
        return this->position + 1;
      }else if (this->boardBeginning[this->position + 1]->getStrength() <= this->strength) {
        return this->position + 1;
      }
      else{
        return -1;
      }
    } else if ((this->boardField)->getXCord() == N) {
      if(this->boardBeginning[this->position - M] == nullptr){
        return this->position - M;
      }else if (this->boardBeginning[this->position - M]->getStrength() <= this->strength) {
        return this->position - M;
      }
      if(this->boardBeginning[this->position - 1] == nullptr){
        return this->position - 1;
      }else if (this->boardBeginning[this->position - 1]->getStrength() <= this->strength) {
        return this->position - 1;
      }
      else{
        return -1;
      }

    } else {
      if(this->boardBeginning[this->position - M] == nullptr){
        return this->position - M;
      }else if (this->boardBeginning[this->position - M]->getStrength() <= this->strength) {
        return this->position - M;
      }
      if(this->boardBeginning[this->position +1] == nullptr){
        return this->position + 1;
      }else if (this->boardBeginning[this->position + 1]->getStrength() <= this->strength) {
        return this->position + 1;
      }
      if(this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;
      }else if (this->boardBeginning[this->position - 1]->getStrength() <= this->strength) {
        return this->position - 1;
      }
      else{
        return -1;
      }
    }
  } else {
    if ((this->boardField)->getXCord() == 1) {
      if(this->boardBeginning[this->position - M] == nullptr){
        return this->position - M;
      }else if (this->boardBeginning[this->position - M]->getStrength() <= this->strength) {
        return this->position - M;
      }if(this->boardBeginning[this->position + M] == nullptr){
        return this->position + M;
      }else if (this->boardBeginning[this->position + M]->getStrength() <= this->strength) {
        return this->position + M;
      } if(this->boardBeginning[this->position + 1] == nullptr){
        return this->position + 1;
      }else if (this->boardBeginning[this->position + 1]->getStrength() <= this->strength) {
        return this->position + 1;
      }
      else{
        return -1;
      }

    } else if ((this->boardField)->getXCord() == N) {
      if(this->boardBeginning[this->position - M] == nullptr){
        return this->position - M;
      }else if (this->boardBeginning[this->position - M]->getStrength() <= this->strength) {
        return this->position - M;
      }if(this->boardBeginning[this->position + M] == nullptr){
        return this->position + M;
      }else if (this->boardBeginning[this->position + M]->getStrength() <= this->strength) {
        return this->position + M;
      }
      if(this->boardBeginning[this->position - 1] == nullptr){
        return this->position - 1;
      }else if (this->boardBeginning[this->position - 1]->getStrength() <= this->strength) {
        return this->position - 1;
      }
      else{
        return -1;
      }

    } else {
      if(this->boardBeginning[this->position - M] == nullptr){
        return this->position - M;
      }else if (this->boardBeginning[this->position - M]->getStrength() <= this->strength) {
        return this->position - M;
      }
      if(this->boardBeginning[this->position + M] == nullptr){
        return this->position + M;
      }else if (this->boardBeginning[this->position + (this->movementSpeed * M)]->getStrength() <= this->strength) {
        return this->position + M;
      }
      if(this->boardBeginning[this->position + 1] == nullptr){
        return this->position + 1;
      }else if (this->boardBeginning[this->position + this->movementSpeed]->getStrength() <= this->strength) {
        return this->position + 1;
      }
      if(this->boardBeginning[this->position - 1] == nullptr){
        return this->position - 1;
      }else if (this->boardBeginning[this->position - this->movementSpeed]->getStrength() <= this->strength) {
        return this->position - 1;
      }
      else{
        return -1;
      }
    }
  }
}

Organism* Fox::getBaby() {
  return new Fox(this->boardBeginning, this->deadOrganismBox);
}
