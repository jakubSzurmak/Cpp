#pragma once

#include "Animal.h"

class Fox : public Animal{
 public:
  Fox(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  int generateNextPosition() const override;
  bool considerAction() override;
  Organism* getBaby() override;
  bool abilityActive() override;
  int getCooldownReps() override;
  int getStrengthDecreaseReps() override;
};
