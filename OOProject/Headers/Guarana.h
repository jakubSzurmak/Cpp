#pragma once

#include "Plant.h"

class Guarana: public Plant {
 public:
  Guarana(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  void fightWith(Organism* enemy) override;
  char defendAgainst(Organism* attacker) override;
  bool considerAction() override;
  Organism* getBaby() override;
};

