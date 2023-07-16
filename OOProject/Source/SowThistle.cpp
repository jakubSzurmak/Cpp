#include "../Headers/SowThistle.h"

SowThistle::SowThistle(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox)
:Plant(0,0,1,SOWTHISTLE, boardBeginning, deadOrganismBox){}

void SowThistle::action() {
  if(!this->killed){
    for (short i = 0; i < 3; i++){
      this->recreate(this);
    }
  }
}

bool SowThistle::considerAction() {
  return true;
}

Organism *SowThistle::getBaby() {
  return new SowThistle(this->boardBeginning, this->deadOrganismBox);
}
