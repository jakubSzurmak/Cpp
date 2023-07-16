#pragma once

#include "Animal.h"

class Turtle:public Animal{
 public:
  Turtle(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  bool considerAction() override;
  char defendAgainst(Organism* attacker) override;
  Organism* getBaby() override;
  bool abilityActive() override;
  int getCooldownReps() override;
  int getStrengthDecreaseReps() override;
};
