#include "../Headers/Sheep.h"

Sheep::Sheep(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox):Animal(4, 4, 1, SHEEP, boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

bool Sheep::considerAction() {
  return true;
}

Organism* Sheep::getBaby() {
  return new Sheep(this->boardBeginning, this->deadOrganismBox);
}

bool Sheep::abilityActive() {
  return true;
}

int Sheep::getCooldownReps() {
  return 0;
}

int Sheep::getStrengthDecreaseReps() {
  return 0;
}
