#pragma once

#include "Plant.h"

class Belladonna:public Plant {
 public:
  Belladonna(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  void fightWith(Organism *enemy) override;
  char defendAgainst(Organism* attacker) override;
  Organism* getBaby() override;
  ~Belladonna();

};
