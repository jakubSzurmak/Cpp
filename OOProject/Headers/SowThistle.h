#pragma once

#include "Plant.h"

class SowThistle: public Plant {
 public:
  SowThistle(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  void action() override;
  bool considerAction() override;
  Organism* getBaby() override;
};

