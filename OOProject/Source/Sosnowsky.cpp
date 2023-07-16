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

bool Sosnowsky::considerAction() {
  return true;
}

void Sosnowsky::seekSurroundingAnimals() {
  if ((this->boardField)->getYCord() == 1) {
    if ((this->boardField)->getXCord() == 1) {
      if (this->getXCord()+1 < N && this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        if(this->boardBeginning[position + 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
        }
        this->boardBeginning[position + 1] = nullptr;
      }
      if (this->getYCord()+1 < M && this->boardBeginning[position + N] != nullptr && this->boardBeginning[position + N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + N]->getSpecies(), VICTORY);
        this->boardBeginning[position + N]->setKilledOrganism();
        if(this->boardBeginning[position + N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + N]);
        }
        this->boardBeginning[position + N] = nullptr;
      }
    } else if ((this->boardField)->getXCord() == N) {
      if (this->getXCord()+1 >= 0 && this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        if(this->boardBeginning[position - 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
        }
        this->boardBeginning[position - 1] = nullptr;
      }
      if (this->getYCord()+1 < M && this->boardBeginning[position + N] != nullptr && this->boardBeginning[position + N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + N]->getSpecies(), VICTORY);
        this->boardBeginning[position + N]->setKilledOrganism();
        if(this->boardBeginning[position + N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + N]);
        }
        this->boardBeginning[position + N] = nullptr;
      }
    } else {
      if (this->getXCord()+1 < N && this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        if(this->boardBeginning[position + 1]->getSpecies() != HUMAN) {
          this->boardBeginning[position + 1] = nullptr;
        }
        this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
      }
      if (this->getXCord()+1 >= 0 && this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        if(this->boardBeginning[position - 1]->getSpecies() != HUMAN){
          this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
        }
        this->boardBeginning[position - 1] = nullptr;
      }
      if (this->getYCord()+1 < M && this->boardBeginning[position + N] != nullptr && this->boardBeginning[position + N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + N]->getSpecies(), VICTORY);
        this->boardBeginning[position + N]->setKilledOrganism();
        if(this->boardBeginning[position + N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + N]);
        }
        this->boardBeginning[position + N] = nullptr;
      }
    }
  } else if ((this->boardField)->getYCord() == N) {
    if ((this->boardField)->getXCord() == 1) {
      if (this->getYCord()-1 >= 0 && this->boardBeginning[position - N] != nullptr && this->boardBeginning[position - N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - N]->getSpecies(), VICTORY);
        this->boardBeginning[position - N]->setKilledOrganism();
        if(this->boardBeginning[position - N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - N]);
        }
        this->boardBeginning[position - N] = nullptr;
      }
      if (this->getXCord()+1 < N && this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        if(this->boardBeginning[position + 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
        }
        this->boardBeginning[position + 1] = nullptr;
      }

    } else if ((this->boardField)->getXCord() == N) {
      if (this->getYCord()-1 >= 0 && this->boardBeginning[position - N] != nullptr && this->boardBeginning[position - N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - N]->getSpecies(), VICTORY);
        this->boardBeginning[position - N]->setKilledOrganism();
        if(this->boardBeginning[position - N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - N]);
        }
        this->boardBeginning[position - N] = nullptr;
      }
      if (this->getXCord()+1 >= 0 && this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        if(this->boardBeginning[position - 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
        }
        this->boardBeginning[position - 1] = nullptr;
      }
    } else {
      if (this->getXCord()+1 < N && this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        if(this->boardBeginning[position + 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
        }
        this->boardBeginning[position + 1] = nullptr;
      }
      if (this->getXCord()+1 >= 0 && this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        if(this->boardBeginning[position - 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
        }
        this->boardBeginning[position - 1] = nullptr;
      }
      if (this->getYCord()-1 >= 0 && this->boardBeginning[position - N] != nullptr && this->boardBeginning[position - N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - N]->getSpecies(), VICTORY);
        this->boardBeginning[position - N]->setKilledOrganism();
        if(this->boardBeginning[position - N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - N]);
        }
        this->boardBeginning[position - N] = nullptr;
      }
    }
  } else {
    if ((this->boardField)->getXCord() == 1) {
      if (this->getYCord()-1 >= 0 && this->boardBeginning[position - N] != nullptr && this->boardBeginning[position - N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - N]->getSpecies(), VICTORY);
        this->boardBeginning[position - N]->setKilledOrganism();
        if(this->boardBeginning[position - N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - N]);
        }
        this->boardBeginning[position - N] = nullptr;
      }
      if (this->getXCord()+1 < N && this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        if(this->boardBeginning[position+ 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
        }
        this->boardBeginning[position + 1] = nullptr;
      }
      if (this->getYCord()+1 < M && this->boardBeginning[position + N] != nullptr && this->boardBeginning[position + N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + N]->getSpecies(), VICTORY);
        this->boardBeginning[position + N]->setKilledOrganism();
        if(this->boardBeginning[position + N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + N]);
        }
        this->boardBeginning[position + N] = nullptr;
      }
    } else if ((this->boardField)->getXCord() == N) {
      if (this->getYCord()-1 >= 0 && this->boardBeginning[position - N] != nullptr && this->boardBeginning[position - N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - N]->getSpecies(), VICTORY);
        this->boardBeginning[position - N]->setKilledOrganism();
        if(this->boardBeginning[position - N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - N]);
        }
        this->boardBeginning[position - N] = nullptr;
      }
      if (this->getXCord()+1 >= 0 && this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        if(this->boardBeginning[position - 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
        }
        this->boardBeginning[position - 1] = nullptr;
      }
      if (this->getYCord()+1 < M && this->boardBeginning[position + N] != nullptr && this->boardBeginning[position + N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + N]->getSpecies(), VICTORY);
        this->boardBeginning[position + N]->setKilledOrganism();
        if(this->boardBeginning[position + N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + M]);
        }
        this->boardBeginning[position + N] = nullptr;
      }
    } else {
      if (this->getYCord()-1 >= 0 && this->boardBeginning[position - N] != nullptr && this->boardBeginning[position - N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - N]->getSpecies(), VICTORY);
        this->boardBeginning[position - N]->setKilledOrganism();
        if(this->boardBeginning[position - N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - N]);
        }
        this->boardBeginning[position - N] = nullptr;
      }
      if (this->getXCord()+1 >= 0 && this->boardBeginning[position - 1] != nullptr && this->boardBeginning[position - 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position - 1]->getSpecies(), VICTORY);
        this->boardBeginning[position - 1]->setKilledOrganism();
        if(this->boardBeginning[position - 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position - 1]);
        }
        this->boardBeginning[position - 1] = nullptr;
      }
      if (this->getXCord()+1 < N && this->boardBeginning[position + 1] != nullptr && this->boardBeginning[position + 1]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + 1]->getSpecies(), VICTORY);
        this->boardBeginning[position + 1]->setKilledOrganism();
        if(this->boardBeginning[position + 1]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + 1]);
        }
        this->boardBeginning[position + 1] = nullptr;
      }
      if (this->getYCord()+1 < M && this->boardBeginning[position + N] != nullptr && this->boardBeginning[position + N]->isAnimal()) {
        this->displayComment(this->getSpecies(), this->boardBeginning[position + N]->getSpecies(), VICTORY);
        this->boardBeginning[position + N]->setKilledOrganism();
        if(this->boardBeginning[position + N]->getSpecies() != HUMAN) {
          this->deadOrganismBox->push_back(this->boardBeginning[position + N]);
        }
        this->boardBeginning[position + N] = nullptr;
      }
    }
  }
}

void Sosnowsky::fightWith(Organism *enemy) {
  enemy->setKilledOrganism();
}

char Sosnowsky::defendAgainst(Organism *attacker) {
    return POISONED;
}

Organism *Sosnowsky::getBaby() {
  return new Sosnowsky(this->boardBeginning, this->deadOrganismBox);
}
