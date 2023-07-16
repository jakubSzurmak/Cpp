#include "../Headers/Sosnowsky.h"

Sosnowsky::Sosnowsky(Organism **boardBeginning, std::vector<Organism*>* deadOrganismBox)
    : Plant(10, 0, 1, SOSNOWSKY, boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
}

void Sosnowsky::action() {
  if(this->considerAction()){
    this->seekSurroundingAnimals();
    this->recreate(this);
  }
}

void Sosnowsky::seekSurroundingAnimals() {
  if ((this->boardField)->getYCord() == 1) {
    if ((this->boardField)->getXCord() == 1) {
      if (this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        this->boardBeginning[position + 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
      }
      if (this->boardBeginning[position + M] != nullptr && this->boardBeginning[position + M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + M]->getSpecies(), VICTORY);
        this->boardBeginning[position + M]->setKilledOrganism();
        this->boardBeginning[position + M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + M]);
      }
    } else if ((this->boardField)->getXCord() == N) {
      if (this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        this->boardBeginning[position - 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
      }
      if (this->boardBeginning[position + M] != nullptr && this->boardBeginning[position + M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + M]->getSpecies(), VICTORY);
        this->boardBeginning[position + M]->setKilledOrganism();
        this->boardBeginning[position + M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + M]);
      }
    } else {
      if (this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        this->boardBeginning[position + 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
      }
      if (this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        this->boardBeginning[position - 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
      }
      if (this->boardBeginning[position + M] != nullptr && this->boardBeginning[position + M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + M]->getSpecies(), VICTORY);
        this->boardBeginning[position + M]->setKilledOrganism();
        this->boardBeginning[position + M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + M]);
      }
    }
  } else if ((this->boardField)->getYCord() == M) {
    if ((this->boardField)->getXCord() == 1) {
      if (this->boardBeginning[position - M] != nullptr && this->boardBeginning[position - M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - M]->getSpecies(), VICTORY);
        this->boardBeginning[position - M]->setKilledOrganism();
        this->boardBeginning[position - M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - M]);
      }
      if (this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        this->boardBeginning[position + 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
      }

    } else if ((this->boardField)->getXCord() == N) {
      if (this->boardBeginning[position - M] != nullptr && this->boardBeginning[position - M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - M]->getSpecies(), VICTORY);
        this->boardBeginning[position - M]->setKilledOrganism();
        this->boardBeginning[position - M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - M]);
      }
      if (this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        this->boardBeginning[position - 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
      }
    } else {
      if (this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        this->boardBeginning[position + 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
      }
      if (this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        this->boardBeginning[position - 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
      }
      if (this->boardBeginning[position - M] != nullptr && this->boardBeginning[position - M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - M]->getSpecies(), VICTORY);
        this->boardBeginning[position - M]->setKilledOrganism();
        this->boardBeginning[position - M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - M]);
      }
    }
  } else {
    if ((this->boardField)->getXCord() == 1) {
      if (this->boardBeginning[position - M] != nullptr && this->boardBeginning[position - M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - M]->getSpecies(), VICTORY);
        this->boardBeginning[position - M]->setKilledOrganism();
        this->boardBeginning[position - M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - M]);
      }
      if (this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        this->boardBeginning[position + 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
      }
      if (this->boardBeginning[position + M] != nullptr && this->boardBeginning[position + M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + M]->getSpecies(), VICTORY);
        this->boardBeginning[position + M]->setKilledOrganism();
        this->boardBeginning[position + M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + M]);
      }
    } else if ((this->boardField)->getXCord() == N) {
      if (this->boardBeginning[position - M] != nullptr && this->boardBeginning[position - M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - M]->getSpecies(), VICTORY);
        this->boardBeginning[position - M]->setKilledOrganism();
        this->boardBeginning[position - M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - M]);
      }
      if (this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        this->boardBeginning[position - 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
      }
      if (this->boardBeginning[position + M] != nullptr && this->boardBeginning[position + M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + M]->getSpecies(), VICTORY);
        this->boardBeginning[position + M]->setKilledOrganism();
        this->boardBeginning[position + M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + M]);
      }
    } else {
      if (this->boardBeginning[position - M] != nullptr && this->boardBeginning[position - M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - M]->getSpecies(), VICTORY);
        this->boardBeginning[position - M]->setKilledOrganism();
        this->boardBeginning[position - M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - M]);
      }
      if (this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        this->boardBeginning[position - 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
      }
      if (this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        this->boardBeginning[position + 1] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
      }
      if (this->boardBeginning[position + M] != nullptr && this->boardBeginning[position + M]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + M]->getSpecies(), VICTORY);
        this->boardBeginning[position + M]->setKilledOrganism();
        this->boardBeginning[position + M] = nullptr;
        this->deadOrganismBox->push_back(this->boardBeginning[position + M]);
      }
    }
  }
}

void Sosnowsky::fightWith(Organism *enemy) {
  enemy->setKilledOrganism();
}

char Sosnowsky::defendAgainst(Organism *attacker) {
  if (attacker->getStrength() <= this->strength) {
    return POISONED;
  } else {
    return VICTORY;
  }
}

Organism *Sosnowsky::getBaby() {
  return new Sosnowsky(this->boardBeginning, this->deadOrganismBox);
}
