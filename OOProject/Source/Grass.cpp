#include "../Headers/Grass.h"

Grass::Grass(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox):
Plant(0,0,1,GRASS, boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

void Grass::fightWith(Organism *enemy) {
  return;
}

Organism* Grass::getBaby(){
  return new Grass(this->boardBeginning, this->deadOrganismBox);
}
