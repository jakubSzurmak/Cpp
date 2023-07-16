#include "../Headers/Human.h"

Human::Human(Organism **boardBeginning, std::vector<Organism *> *deadOrganismBox) :
    Animal(5, 4, 1, HUMAN, boardBeginning, deadOrganismBox) {
  this->boardBeginning = boardBeginning;
  this->ability = false;
  this->cooldownReps = 0;
  this->strengthDecreaseReps = 0;
}

Organism *Human::getBaby() {
  return nullptr;
}

bool Human::abilityActive() {
  return this->ability;
}

void Human::action() {
  this->makeMove();
}

void Human::cordChangeOnMove(int nextPos) {
  if(arrowPressed == KEY_UP){
    yCord -= 1;
  }else if(arrowPressed == KEY_DOWN){
    yCord += 1;
  }else if(arrowPressed == KEY_RIGHT){
    xCord += 1;
  }else if(arrowPressed == KEY_LEFT){
    xCord -= 1;
  }
}

void Human::activateAbility() {
  if (!ability && cooldownReps == 0) {
    this->ability = true;
    this->strength = 10;
    this->cooldownReps = 5;
    this->strengthDecreaseReps = 5;

  } else {
    std::cout << "The ability is on cooldown for next: " << this->cooldownReps << " Rounds." << std::endl;
  }
}

void Human::setStrengthDecrease(int x) {
  this->strengthDecreaseReps = x;
}

void Human::setAbilityCooldown(int x) {
  this->cooldownReps = x;
}

void Human::setAbility(bool x) {
  this->ability = x;
}

void Human::shortenAbility() {
  if (this->strengthDecreaseReps != 0) {
    this->strength -= 1;
    this->strengthDecreaseReps -= 1;
  } else if (this->cooldownReps != 0) {
    this->cooldownReps -= 1;
  }
}

bool Human::detectArrow(int key) {
  switch (key) {
    case KEY_DOWN:return true;
    case KEY_RIGHT:return true;
    case KEY_UP:return true;
    case KEY_LEFT:return true;
    default:break;
  }
  return false;
}

int Human::getCooldownReps() {
  return this->cooldownReps;
}

int Human::getStrengthDecreaseReps() {
  return this->strengthDecreaseReps;
}

void Human::setArrowKey(int x) {
  this->arrowPressed = x;
}

void Human::getMoveDirection() {
  char ch = ' ';
  while (true) {
    ch = (char) getch();
    if(ch == '\340' || ch == '\000'){
      ch = (char) getch();
    }
    switch (ch) {
      case KEY_UP:this->arrowPressed = KEY_UP;
        break;
      case KEY_DOWN:this->arrowPressed = KEY_DOWN;
        break;
      case KEY_LEFT:this->arrowPressed = KEY_LEFT;
        break;
      case KEY_RIGHT:this->arrowPressed = KEY_RIGHT;
        break;
      default:break;

    }
    if (this->detectArrow(this->arrowPressed)) {
      if (!this->considerAction()) {
        std::cout << "Invalid Human direction \n";
        continue;
      }
      this->nextPosition = this->generateNextPosition();
      std::cout << std::endl;
      break;
    }
  }
}

int Human::generateNextPosition() const {
  switch (this->arrowPressed) {
    case KEY_UP:return this->position - N;
    case KEY_RIGHT:return this->position + 1;
    case KEY_DOWN:return this->position + N;
    case KEY_LEFT:return this->position - 1;
    default:break;
  }
  return -1;
}

void Human::makeMove() {
  if(!killed){
    this->nextPosition = this->generateNextPosition();
    if (this->nextPosition >= 0) {
      if (this->getBoardBeginning()[nextPosition] == nullptr) {
        this->cordChangeOnMove(0);
        this->shortenAbility();
        this->boardBeginning[this->nextPosition] = this;
        this->boardField = this->boardBeginning[this->nextPosition];
        this->boardBeginning[this->position] = nullptr;
        this->position = this->nextPosition;
        return;
      } else {
        this->collision();
        this->shortenAbility();
      }
    }
  }
}

bool Human::considerAction() {
  if (this->boardField->getYCord() == 1) {
    if (this->arrowPressed == KEY_UP) {
      return false;
    } else if (this->boardField->getXCord() == 1 && this->arrowPressed == KEY_LEFT) {
      return false;
    } else if (this->boardField->getXCord() == N && this->arrowPressed == KEY_RIGHT) {
      return false;
    }
  } else if (this->boardField->getYCord() == M) {
    if (this->arrowPressed == KEY_DOWN) {
      return false;
    } else if (this->boardField->getXCord() == 1 && this->arrowPressed == KEY_LEFT) {
      return false;
    } else if (this->boardField->getXCord() == N && this->arrowPressed == KEY_RIGHT) {
      return false;
    }
  } else {
    if (this->boardField->getXCord() == 1 && this->arrowPressed == KEY_LEFT) {
      return false;
    } else if (this->boardField->getXCord() == N && this->arrowPressed == KEY_RIGHT) {
      return false;
    }
  }
  return true;

}
