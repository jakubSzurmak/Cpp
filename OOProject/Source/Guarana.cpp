#include "../Headers/Guarana.h"

Guarana::Guarana(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox): Plant(0,0,1,GUARANA,boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

void Guarana::fightWith(Organism *enemy){}

bool Guarana::considerAction() {
  return true;
}

char Guarana::defendAgainst(Organism *attacker) {
  attacker->setStrength(attacker->getStrength()+3);
  return VICTORY;
}

Organism *Guarana::getBaby() {
  return new Guarana(this->boardBeginning, this->deadOrganismBox);
}
