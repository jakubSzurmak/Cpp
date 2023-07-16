#include "../Headers/Antelope.h"

Antelope::Antelope(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox): Animal(4,4, 2, ANTELOPE, boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

bool Antelope::considerAction() {
  return true;
}

char Antelope::defendAgainst(Organism *attacker) {
  if( rand()%2 == 0){
    int nextInd = this->findFreeEscapeSpot();
    this->cordChangeOnMove(this->determineMoveDirection(nextInd-this->position));
    this->boardBeginning[nextInd] = this->boardField;
    this->boardBeginning[position] = nullptr;
    this->nextPosition = nextInd;
    this->position = nextInd;
    return ESCAPED;
  }else{
    if(attacker->getStrength() < this->strength){
      return DEFEATED;
    }else{
      return VICTORY;
    }
  }
}

Organism *Antelope::getBaby() {
  return new Antelope(this->boardBeginning, this->deadOrganismBox);
}

bool Antelope::abilityActive() {
  return true;
}

int Antelope::getCooldownReps() {
  return 0;
}

int Antelope::getStrengthDecreaseReps() {
  return 0;
}