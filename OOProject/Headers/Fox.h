#pragma once

#include "Animal.h"

class Fox : public Animal{
 public:
  Fox(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  int generateNextPosition() const override;
  Organism* getBaby() override;
};
