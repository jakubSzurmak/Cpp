#include "../Headers/Turtle.h"

Turtle::Turtle(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox): Animal(2,1, 1,TURTLE, boardBeginning, deadOrganismBox) {}

bool Turtle::considerAction(){
  if((rand()%100+1) <= 75){
    return false;
  }
  return true;
}

char Turtle::defendAgainst(Organism *attacker) {
  if(attacker->getStrength() < 5){
    return REFLECTED;
  }else{
    return VICTORY;
  }
}

Organism* Turtle::getBaby() {
  return new Turtle(this->boardBeginning, this->deadOrganismBox);
}

bool Turtle::abilityActive() {
  return true;
}

int Turtle::getCooldownReps() {
  return 0;
}

int Turtle::getStrengthDecreaseReps() {
  return 0;
}