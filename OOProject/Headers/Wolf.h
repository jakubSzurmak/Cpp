#pragma once

#include "Animal.h"

class Wolf:public Animal{
 public:
  Wolf(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  bool considerAction() override;
  Organism* getBaby() override;
  bool abilityActive() override;
  int getCooldownReps() override;
  int getStrengthDecreaseReps() override;
};
