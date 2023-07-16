#pragma once
#include "Animal.h"

class Antelope:public Animal{
 public:
  Antelope(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  char defendAgainst(Organism* attacker) override;
  bool considerAction() override;
  bool abilityActive() override;
  int getCooldownReps() override;
  int getStrengthDecreaseReps() override;
  Organism* getBaby() override;
};
