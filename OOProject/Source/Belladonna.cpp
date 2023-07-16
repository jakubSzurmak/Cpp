#include "../Headers/Belladonna.h"

Belladonna::Belladonna(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox)
:Plant(99,0,1,BELLADONNA,boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

void Belladonna::fightWith(Organism *enemy) {
  return;
}

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

Belladonna::~Belladonna() =default;
