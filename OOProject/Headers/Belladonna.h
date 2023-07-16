#pragma once

#include "Plant.h"

class Belladonna:public Plant {
 public:
  Belladonna(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  bool considerAction() override;
  void fightWith(Organism *enemy) override;
  char defendAgainst(Organism* attacker) override;
  Organism* getBaby() override;

};
