#include "../Headers/Animal.h"

Animal::Animal(int strength,
               int initiative,
               int movementSpeed,
               char species,
               Organism **rootBoardBeginning,
               std::vector<Organism *> *deadOrganismBox)
    : Organism(strength, initiative, movementSpeed, species, rootBoardBeginning, deadOrganismBox) {
  this->boardBeginning = rootBoardBeginning;
  this->deadOrganismBox = deadOrganismBox;
}

Organism **Animal::getBoardBeginning() {
  return this->boardBeginning;
}

void Animal::action() {
  if (!killed && this->considerAction()) {
    this->makeMove();
  }
}

void Animal::fightWith(Organism *enemy) {
  char status = ' ';
  if (enemy != nullptr) {
    status = enemy->defendAgainst(this);
  } else {
    status = ESCAPED;
  }

  if (status == VICTORY) {
    this->displayComment(this->getSpecies(), enemy->getSpecies(), VICTORY);
    enemy->setKilledOrganism();
    this->getBoardBeginning()[this->nextPosition] = nullptr;
    this->setXYCords(enemy->getXCord(), enemy->getYCord());
    this->deadOrganismBox->push_back(enemy);
    this->setField(this->nextPosition);
    this->boardBeginning[this->position] = nullptr;
    this->position = this->nextPosition;

  } else if (status == DEFEATED) {
    this->displayComment(this->getSpecies(), enemy->getSpecies(), DEFEATED);
    this->setKilledOrganism();
    if(this->species != HUMAN){
      this->deadOrganismBox->push_back(this);
    }
    this->getBoardBeginning()[this->position] = nullptr;

  } else if (status == POISONED) {
    this->displayComment(this->getSpecies(), enemy->getSpecies(), POISONED);
    enemy->setKilledOrganism();
    this->deadOrganismBox->push_back(enemy);
    enemy->getBoardBeginning()[enemy->getPosition()] = nullptr;
    this->setKilledOrganism();
    this->deadOrganismBox->push_back(this);
    this->boardBeginning[this->position] = nullptr;

  } else if (status == REFLECTED) {
    this->displayComment(this->getSpecies(), enemy->getSpecies(), REFLECTED);
    this->nextPosition = this->position;

  } else if (status == ESCAPED) {
    this->displayComment(this->getSpecies(), enemy->getSpecies(), ESCAPED);
    this->boardBeginning[nextPosition] = this->boardField;
    this->boardField = this->boardBeginning[nextPosition];
    this->boardBeginning[position] = nullptr;
    this->position = this->nextPosition;
  }
}

char Animal::defendAgainst(Organism *attacker) {
  if (attacker->getStrength() < this->strength) {
    return DEFEATED;
  } else {
    return VICTORY;
  }
}

void Animal::recreate(Organism *partner) {
  int newBornField = this->findFreeRecreationSpot();
  if (newBornField != -1) {
    this->boardBeginning[newBornField] = this->getBaby();

    if (newBornField == this->position + N) {
      this->boardBeginning[newBornField]->setXYCords(this->getXCord(), this->getYCord() + 1);
      this->boardBeginning[newBornField]->setPosition(this->getXCord(), this->getYCord() + 1);
    } else if (newBornField == this->position - N) {
      this->boardBeginning[newBornField]->setXYCords(this->getXCord(), this->getYCord() - 1);
      this->boardBeginning[newBornField]->setPosition(this->getXCord(), this->getYCord() - 1);
    } else if (newBornField == this->position - 1) {
      this->boardBeginning[newBornField]->setXYCords(this->getXCord() - 1, this->getYCord());
      this->boardBeginning[newBornField]->setPosition(this->getXCord() - 1, this->getYCord());
    } else if (newBornField == this->position + 1) {
      this->boardBeginning[newBornField]->setXYCords(this->getXCord() + 1, this->getYCord());
      this->boardBeginning[newBornField]->setPosition(this->getXCord() + 1, this->getYCord());
    }
    this->displayComment(this->getSpecies(), partner->getSpecies(), RECREATION);
  }
}

void Animal::cordChangeOnMove(int nextPos) {
  switch (nextPos) {
    case NORTH:this->yCord -= this->movementSpeed;
      break;
    case EAST:this->xCord += this->movementSpeed;
      break;
    case SOUTH:this->yCord += this->movementSpeed;
      break;
    case WEST:this->xCord -= this->movementSpeed;
      break;
    default:break;
  }
}

int Animal::determineMoveDirection(int positionChange) {

  if(positionChange == this->movementSpeed){
    return EAST;
  }else if(positionChange == -(this->movementSpeed)){
    return WEST;
  }else if(positionChange == N*this->movementSpeed){
    return SOUTH;
  }else if(positionChange == -N*this->movementSpeed){
    return NORTH;
  }
  return -1;
}

void Animal::makeMove() {
  this->nextPosition = this->generateNextPosition();
  if(this->nextPosition >= 0) {
    if (this->getBoardBeginning()[nextPosition] == nullptr) {
      this->cordChangeOnMove(this->determineMoveDirection(this->nextPosition - this->position));
      this->boardBeginning[this->nextPosition] = this;
      this->boardField = this->boardBeginning[this->nextPosition];
      this->boardBeginning[this->position] = nullptr;
      this->position = this->nextPosition;
      return;
    } else {
      this->collision();
    }
  }
}

int Animal::generateMoveDirection() const {
  int moveDirection;
  if(M == 1){
    moveDirection = rand() % 2;
    if (moveDirection % 2 == 0) {
      return WEST;
    } else {
      return SOUTH;
    }
  }else{
    if ((this->boardField)->getYCord() <= this->movementSpeed) {
      if ((this->boardField)->getXCord() <= this->movementSpeed) {
        moveDirection = rand() % 2;
        if (moveDirection % 2 == 0) {
          return EAST;
        } else {
          return SOUTH;
        }
      } else if ((this->boardField)->getXCord() > N - this->movementSpeed) {
        moveDirection = rand() % 2;
        if (moveDirection % 2 == 0) {
          return WEST;
        } else {
          return SOUTH;
        }
      } else {
        moveDirection = rand() % 3;
        if (moveDirection == 0) {
          return EAST;
        } else if (moveDirection == 1) {
          return SOUTH;
        } else {
          return WEST;
        }
      }
    } else if ((this->boardField)->getYCord() > M - this->movementSpeed) {
      if ((this->boardField)->getXCord() <= this->movementSpeed) {
        moveDirection = rand() % 2;
        if (moveDirection % 2 == 0) {
          return EAST;
        } else {
          return NORTH;
        }
      } else if ((this->boardField)->getXCord() > N - this->movementSpeed ) {
        moveDirection = rand() % 2;
        if (moveDirection % 2 == 0) {
          return WEST;
        } else {
          return NORTH;
        }
      } else {
        moveDirection = rand() % 3;
        if (moveDirection == 0) {
          return NORTH;
        } else if (moveDirection == 1) {
          return EAST;
        } else {
          return WEST;
        }
      }
    } else {
      if ((this->boardField)->getXCord() < this->movementSpeed) {
        moveDirection = rand() % 3;
        if (moveDirection == 0) {
          return NORTH;
        } else if (moveDirection == 1) {
          return EAST;
        } else {
          return SOUTH;
        }
      } else if ((this->boardField)->getXCord() > N - this->movementSpeed) {
        moveDirection = rand() % 3;
        if (moveDirection == 0) {
          return NORTH;
        } else if (moveDirection == 1) {
          return WEST;
        } else {
          return SOUTH;
        }
      } else {
        moveDirection = rand() % 4;
        if (moveDirection == 0) {
          return NORTH;
        } else if (moveDirection == 1) {
          return EAST;
        } else if (moveDirection == 2) {
          return SOUTH;
        } else {
          return WEST;
        }
      }
    }
  }
}

int Animal::generateNextPosition() const {
  switch (this->generateMoveDirection()) {
    case NORTH:return this->position - (this->movementSpeed * N);
    case EAST:return this->position + this->movementSpeed;
    case SOUTH:return this->position + (this->movementSpeed * N);
    case WEST:return this->position - this->movementSpeed;
    default:break;
  }
  return -1;
}
