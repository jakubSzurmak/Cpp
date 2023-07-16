#pragma once

#include "Plant.h"

class Sosnowsky: public Plant {
 public:
  Sosnowsky(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  bool considerAction() override;
  void action() override;
  void fightWith(Organism *enemy) override;
  char defendAgainst(Organism* attacker) override;
  void seekSurroundingAnimals();
  Organism* getBaby() override;
};

