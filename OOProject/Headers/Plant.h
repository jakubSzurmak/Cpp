#pragma once

#include "Organism.h"

class Plant:public Organism {
 protected:
  Plant(int strength, int initiative, int movementSpeed, char species, Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  virtual void action();
  Organism** getBoardBeginning() override;
  void recreate(Organism* partner) override;
  void fightWith(Organism* enemy) override;
  char defendAgainst(Organism* attacker) override;
  bool abilityActive() override;
  int getCooldownReps() override;
  int getStrengthDecreaseReps() override;
};

