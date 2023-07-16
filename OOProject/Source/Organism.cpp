#include "../Headers/Organism.h"

Organism::Organism(int strength, int initiative, int movementSpeed, char species, Organism **boardBeginning,
                   std::vector<Organism *> *deadOrganismBox) {
  this->strength = strength;
  this->initiative = initiative;
  this->species = species;
  this->movementSpeed = movementSpeed;
  this->killed = false;
  this->age = 0;
  this->position = -1;
  this->nextPosition = -1;
  this->xCord = -1;
  this->yCord = -1;
  this->boardField = nullptr;
  this->boardBeginning = boardBeginning;
  this->deadOrganismBox = deadOrganismBox;
}

Organism::~Organism() = default;

void Organism::displayOrganismName(char currentOrganism) {
  switch (currentOrganism) {
    case WOLF:std::cout << "Wolf ";
      break;
    case TURTLE:std::cout << "Turtle ";
      break;
    case FOX:std::cout << "Fox ";
      break;
    case ANTELOPE:std::cout << "Antelope ";
      break;
    case SHEEP:std::cout << "Sheep ";
      break;
    case HUMAN:std::cout << "Human ";
      break;
    case GRASS:std::cout << "Grass ";
      break;
    case SOWTHISTLE:std::cout << "Sow Thistle ";
      break;
    case GUARANA:std::cout << "Guarana ";
      break;
    case BELLADONNA:std::cout << "Belladonna ";
      break;
    case SOSNOWSKY:std::cout << "Sosnowsky's Hedgehog ";
      break;
    default:break;
  }
}

void Organism::displayComment(char attacker, char defender, char statusFlag) const {
  switch (statusFlag) {
    case VICTORY:
      this->displayOrganismName(attacker);
      std::cout << "has killed ";
      break;
    case DEFEATED:
      this->displayOrganismName(attacker);
      std::cout << "failed to kill ";
      break;
    case REFLECTED:
      this->displayOrganismName(attacker);
      std::cout << "attack was reflected by ";
      break;
    case POISONED:
      this->displayOrganismName(attacker);
      if (defender == BELLADONNA || defender == SOSNOWSKY) {
        std::cout << "was poisoned because it ate ";
      } else {
        std::cout << "ate ";
      }
      break;
    case ESCAPED:
      this->displayOrganismName(defender);
      std::cout << " ESCAPED the attack of: ";
      this->displayOrganismName(attacker);
      std::cout << std::endl;
      break;
    case RECREATION:
      this->displayOrganismName(attacker);
      if(isCharAnimal(attacker)){
        std::cout << "has given birth to a new ";
      }else{
        std::cout << "has sowed a new ";
      }
      break;
    default:
      return;
  }
  this->displayOrganismName(defender);
  std::cout << std::endl;
}

void Organism::setXYCords(int x, int y) {
  this->xCord = x;
  this->yCord = y;
}

void Organism::setStrength(int newStrength) {
  this->strength = newStrength;
}

void Organism::incrementAge() {
  this->age = this->age + 1;
}

void Organism::setPosition(int x, int y) {
  this->xCord = x;
  this->yCord = y;
  this->position = (N * (y - 1)) + (x - 1);
  this->boardBeginning[position] = this;
  this->boardField = boardBeginning[position];
}

void Organism::setField(int newIndex) {
  //this->boardBeginning[newIndex] = this->boardField;
  this->boardBeginning[newIndex] = this;
}

void Organism::setInitiative(int x){
  this->initiative = x;
}

void Organism::setAge(int x){
  this->age = x;
}

void Organism::setAbility(bool x) {
  return;
}

void Organism::setStrengthDecrease(int x) {
  return;
}

void Organism::setAbilityCooldown(int x) {
  return;
}

void Organism::setMovementSpeed(int x) {
  this->movementSpeed = x;
}


int Organism::getXCord() const {
  return this->xCord;
}

int Organism::getYCord() const {
  return this->yCord;
}

int Organism::getStrength() const {
  return this->strength;
}

int Organism::getInitiative() const {
  return this->initiative;
}

int Organism::getPosition() const {
  return this->position;
}

int Organism::getAge() const {
  return this->age;
}

char Organism::getSpecies() const {
  return this->species;
}

int Organism::getMovementSpeed() const{
  return this->movementSpeed;
}

void Organism::setKilledOrganism() {
  this->killed = true;
}

bool Organism::getLifeStatus() const {
  return this->killed;
}

bool Organism::isAnimal() const {
  switch (this->species) {
    case WOLF:return true;
    case SHEEP:return true;
    case FOX:return true;
    case TURTLE:return true;
    case ANTELOPE:return true;
    case HUMAN:return true;
    default:return false;
  }
}

bool Organism::isCharAnimal(char speciesChar) {
  switch (speciesChar) {
    case WOLF:return true;
    case SHEEP:return true;
    case FOX:return true;
    case TURTLE:return true;
    case ANTELOPE:return true;
    case HUMAN:return true;
    default:return false;
  }
}



int Organism::findFreeRecreationSpot() const {
  static int counter = 0;
  if ((this->boardField)->getYCord() == 1) {
    if ((this->boardField)->getXCord() == 1) {
      if (this->boardBeginning[this->position + N] == nullptr) {
        return this->position + N;

      } else if (this->boardBeginning[this->position + 1] == nullptr) {
        return this->position + 1;

      } else {
          return -1;
      }
    } else if ((this->boardField)->getXCord() == N) {
      if (this->boardBeginning[this->position + N] == nullptr) {
        return this->position + N;

      } else if (this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;

      } else {
        return -1;
      }
    } else {
      if (this->boardBeginning[this->position + N] == nullptr) {
        return this->position + N;

      } else if (this->boardBeginning[this->position + 1] == nullptr) {
        return this->position + 1;

      } else if (this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;

      } else {
        return -1;
      }
    }
  } else if ((this->boardField)->getYCord() == N) {
    if ((this->boardField)->getXCord() == 1) {
      if (this->boardBeginning[this->position - N] == nullptr) {
        return this->position - N;
      } else if (this->boardBeginning[this->position + 1] == nullptr) {
        return this->position + 1;

      } else {
          return -1;
      }

    } else if ((this->boardField)->getXCord() == N) {
      if (this->boardBeginning[this->position - N] == nullptr) {
        return this->position - N;
      } else if (this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;
      } else {
        return -1;
      }

    } else {
      if (this->boardBeginning[this->position - N] == nullptr) {
        return this->position - N;

      } else if (this->boardBeginning[this->position + 1] == nullptr) {
        return this->position + 1;

      } else if (this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;

      } else {
        return -1;
      }
    }
  } else {
    if ((this->boardField)->getXCord() == 1) {
      if (this->boardBeginning[this->position - N] == nullptr) {
        return this->position - N;

      } else if (this->boardBeginning[this->position + N] == nullptr) {
        return this->position + N;

      } else if (this->boardBeginning[this->position + 1] == nullptr) {
        return this->position + 1;

      } else {
        return -1;
      }

    } else if ((this->boardField)->getXCord() == N) {
      if (this->boardBeginning[this->position - N] == nullptr) {
        return this->position - N;

      } else if (this->boardBeginning[this->position + N] == nullptr) {
        return this->position + N;

      } else if (this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;

      } else {
          return -1;
      }

    } else {
      if (this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;

      } else if (this->boardBeginning[this->position + 1] == nullptr) {
        return this->position + 1;

      } else if (this->boardBeginning[this->position + 1] == nullptr) {
        return this->position + 1;

      } else if (this->boardBeginning[this->position - 1] == nullptr) {
        return this->position - 1;

      } else {
        return -1;
      }
    }
  }
}

int Organism::findFreeEscapeSpot() const {
  int moveDirection;
  static int counter = 0;
  if ((this->boardField)->getYCord() <= this->movementSpeed) {
    if ((this->boardField)->getXCord() <= this->movementSpeed) {
      if (this->boardBeginning[this->position + this->movementSpeed] == nullptr) {
        return EAST;
      } else if (this->boardBeginning[this->position + (this->movementSpeed * M)] == nullptr) {
        return SOUTH;
      }
    } else if ((this->boardField)->getXCord() == N) {

      if (this->boardBeginning[this->position - this->movementSpeed] == nullptr) {
        return WEST;
      } else if (this->boardBeginning[this->position + (this->movementSpeed * M)] == nullptr) {
        return SOUTH;
      }

    } else {

      if (this->boardBeginning[this->position + this->movementSpeed] == nullptr) {
        return EAST;
      } else if (this->boardBeginning[this->position + (this->movementSpeed * M)] == nullptr) {
        return SOUTH;
      } else if (this->boardBeginning[this->position - this->movementSpeed] == nullptr) {
        return WEST;
      }

    }
  } else if ((this->boardField)->getYCord() <= M - this->movementSpeed) {
    if ((this->boardField)->getXCord() <= this->movementSpeed) {
      if (this->boardBeginning[this->position - (this->movementSpeed * M)] == nullptr) {
        return NORTH;
      } else if (this->boardBeginning[this->position + this->movementSpeed] == nullptr) {
        return EAST;
      }
    } else if ((this->boardField)->getXCord() >= N - this->movementSpeed) {
      if (this->boardBeginning[this->position - (this->movementSpeed * M)] == nullptr) {
        return NORTH;
      } else if (this->boardBeginning[this->position - this->movementSpeed] == nullptr) {
        return WEST;
      }

    } else {
      if (this->boardBeginning[this->position - (this->movementSpeed * M)] == nullptr) {
        return NORTH;
      } else if (this->boardBeginning[this->position + this->movementSpeed] == nullptr) {
        return EAST;
      } else if (this->boardBeginning[this->position - this->movementSpeed] == nullptr) {
        return WEST;
      }

    }
  } else {
    if ((this->boardField)->getXCord() <= this->movementSpeed) {
      if (this->boardBeginning[this->position - (this->movementSpeed * M)] == nullptr) {
        return NORTH;
      } else if (this->boardBeginning[this->position + this->movementSpeed] == nullptr) {
        return EAST;
      } else if (this->boardBeginning[this->position + (this->movementSpeed * M)] == nullptr) {
        return SOUTH;
      }

    } else if ((this->boardField)->getXCord() >= N - this->movementSpeed) {
      if (this->boardBeginning[this->position - (this->movementSpeed * M)] == nullptr) {
        return NORTH;
      } else if (this->boardBeginning[this->position - this->movementSpeed] == nullptr) {
        return WEST;
      } else if (this->boardBeginning[this->position + (this->movementSpeed * M)] == nullptr) {
        return SOUTH;
      }

    } else {
      if (this->boardBeginning[this->position - (this->movementSpeed * M)] == nullptr) {
        return NORTH;
      } else if (this->boardBeginning[this->position + this->movementSpeed] == nullptr) {
        return EAST;
      } else if (this->boardBeginning[this->position + (this->movementSpeed * M)] == nullptr) {
        return SOUTH;
      } else if (this->boardBeginning[this->position - this->movementSpeed] == nullptr) {
        return WEST;
      }
    }
  }
  return -1;
}

void Organism::collision() {
  if(this->boardBeginning[this->nextPosition] != nullptr && this->nextPosition >= 0) {
    if (this->species == this->boardBeginning[this->nextPosition]->getSpecies()) {
      this->recreate(this->boardBeginning[this->nextPosition]);
    } else {
      this->fightWith(this->boardBeginning[this->nextPosition]);
    }
  }
}

void Organism::setLifeStatus(bool x) {
  this->killed = !x;
}
