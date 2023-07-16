#include "../Headers/Belladonna.h"

Belladonna::Belladonna(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox)
:Plant(99,0,1,BELLADONNA,boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

bool Belladonna::considerAction() {
  return true;
}

void Belladonna::fightWith(Organism *enemy) {}

char Belladonna::defendAgainst(Organism *attacker) {
  if(attacker->getStrength() < this->strength){
    return POISONED;
  }else{
    return VICTORY;
  }
}

Organism* Belladonna::getBaby(){
  return new Belladonna(this->boardBeginning, this->deadOrganismBox);
}
