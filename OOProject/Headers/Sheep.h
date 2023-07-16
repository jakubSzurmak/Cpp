#pragma once

#include "Animal.h"

class Sheep:public Animal{
 public:
  Sheep(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  bool considerAction() override;
  Organism* getBaby() override;
  bool abilityActive() override;
  int getCooldownReps() override;
  int getStrengthDecreaseReps() override;
};

