#pragma once

#include "Plant.h"

class Grass:public Plant {
 public:
  Grass(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  void fightWith(Organism* enemy) override;
  Organism* getBaby() override;
};
