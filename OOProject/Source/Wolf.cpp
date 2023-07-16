#include "../Headers/Wolf.h"

Wolf::Wolf(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox):Animal(9, 5, 1, WOLF, boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

Organism* Wolf::getBaby() {
  return new Wolf(this->boardBeginning, this->deadOrganismBox);
}

bool Wolf::considerAction() {
  return true;
}

bool Wolf::abilityActive() {
  return true;
}

int Wolf::getCooldownReps() {
  return 0;
}

int Wolf::getStrengthDecreaseReps() {
  return 0;
}