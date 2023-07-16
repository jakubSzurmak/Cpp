#pragma once
#include "Animal.h"

class Antelope:public Animal{
 public:
  Antelope(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  char defendAgainst(Organism* attacker) override;
  Organism* getBaby() override;
};
