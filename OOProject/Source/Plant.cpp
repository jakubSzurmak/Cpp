#include "../Headers/Plant.h"

Plant::Plant(int strength, int initiative, int movementSpeed, char species, Organism** rootBoardBeginning, std::vector<Organism*>* deadOrganismBox): Organism(strength, initiative, movementSpeed, species, rootBoardBeginning, deadOrganismBox) {
  this->boardBeginning = rootBoardBeginning;
  this->deadOrganismBox = deadOrganismBox;
}

Organism** Plant::getBoardBeginning() {
  return this->boardBeginning;
}

void Plant::action() {
  if(!this->killed){
    if(this->considerAction()){
      this->recreate(this);
    }
  }
}

void Plant::fightWith(Organism *enemy) {}

char Plant::defendAgainst(Organism *attacker) {
  if(this->getSpecies() == BELLADONNA || this->getSpecies() == SOSNOWSKY){
    return POISONED;
  }else {
    return VICTORY;
  }
}

void Plant::recreate(Organism* partner) {
  int newBornField = this->findFreeRecreationSpot();
  if( newBornField != -1){
    this->displayComment(this->getSpecies(), this->getSpecies(), RECREATION);
    this->boardBeginning[newBornField] = this->getBaby();
    if(newBornField == this->position + N){
      this->boardBeginning[newBornField]->setXYCords(this->getXCord(), this->getYCord()+1);
    }else if(newBornField == this->position - N){
      this->boardBeginning[newBornField]->setXYCords(this->getXCord(), this->getYCord()-1);
    }else if(newBornField == this->position - 1){
      this->boardBeginning[newBornField]->setXYCords(this->getXCord()-1, this->getYCord());
    }else if(newBornField == this->position + 1){
      this->boardBeginning[newBornField]->setXYCords(this->getXCord()+1, this->getYCord());
    }
    this->boardBeginning[newBornField]->
    setPosition(this->boardBeginning[newBornField]->getXCord(),this->boardBeginning[newBornField]->getYCord());
  }
}

bool Plant::abilityActive() {
  return true;
}

int Plant::getCooldownReps() {
  return 0;
}

int Plant::getStrengthDecreaseReps() {
  return 0;
}
