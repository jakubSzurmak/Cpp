#include <cstdio>
#include <cstring>

#include "Headers/World.h"
#include "Headers/Organism.h"

#include "Headers/Human.h"
#include "Headers/Wolf.h"
#include "Headers/Sheep.h"
#include "Headers/Fox.h"
#include "Headers/Turtle.h"
#include "Headers/Antelope.h"

#include "Headers/Grass.h"
#include "Headers/SowThistle.h"
#include "Headers/Guarana.h"
#include "Headers/Belladonna.h"
#include "Headers/Sosnowsky.h"

#define ESC_KEY 27

std::string getFileName() {
  std::string name;
  std::cout << "Enter desired fileName: ";
  std::cin >> name;
  return name;
}

void saveGameState(World *mainWorld) {

  FILE *fSave;
  std::string name = getFileName();
  char *name2 = new char[name.size() + 1];
  strcpy(name2, name.c_str());
  fSave = fopen(name2, "wb");
  if (fSave == nullptr) {
    exit(-100);
  }

  int X = N;
  int Y = M;
  fwrite(&X, sizeof(int), 1, fSave);
  fwrite(&Y, sizeof(int), 1, fSave);
  std::vector<Organism *> orgsOnBoard = mainWorld->getOrganismsOnBoard();
  unsigned long long max = orgsOnBoard.size();
  fwrite(&max, sizeof(int), 1, fSave);

  char species;
  bool alive;
  int strength, initiative, position, age, xCord, yCord, movSpeed, cooldown, decreaseReps, ability;
  for (int i = 0; i < max; i++) {
    species = orgsOnBoard[i]->getSpecies();
    if (species == HUMAN) {
      alive = !orgsOnBoard[i]->getLifeStatus();
      ability = orgsOnBoard[i]->abilityActive();
      decreaseReps = orgsOnBoard[i]->getStrengthDecreaseReps();
      cooldown = orgsOnBoard[i]->getCooldownReps();
      strength = orgsOnBoard[i]->getStrength();
      initiative = orgsOnBoard[i]->getInitiative();
      position = orgsOnBoard[i]->getPosition();
      age = orgsOnBoard[i]->getAge();
      xCord = orgsOnBoard[i]->getXCord();
      yCord = orgsOnBoard[i]->getYCord();
      movSpeed = orgsOnBoard[i]->getMovementSpeed();

      fwrite(&species, sizeof(char), 1, fSave);
      fwrite(&alive, sizeof(bool), 1, fSave);
      fwrite(&ability, sizeof(bool), 1, fSave);
      fwrite(&decreaseReps, sizeof(int), 1, fSave);
      fwrite(&cooldown, sizeof(int), 1, fSave);
      fwrite(&strength, sizeof(int), 1, fSave);
      fwrite(&initiative, sizeof(int), 1, fSave);
      fwrite(&position, sizeof(int), 1, fSave);
      fwrite(&age, sizeof(int), 1, fSave);
      fwrite(&xCord, sizeof(int), 1, fSave);
      fwrite(&yCord, sizeof(int), 1, fSave);
      fwrite(&movSpeed, sizeof(int), 1, fSave);
      continue;
    }
    strength = orgsOnBoard[i]->getStrength();
    initiative = orgsOnBoard[i]->getInitiative();
    position = orgsOnBoard[i]->getPosition();
    age = orgsOnBoard[i]->getAge();
    xCord = orgsOnBoard[i]->getXCord();
    yCord = orgsOnBoard[i]->getYCord();
    movSpeed = orgsOnBoard[i]->getMovementSpeed();

    fwrite(&species, sizeof(char), 1, fSave);
    fwrite(&strength, sizeof(int), 1, fSave);
    fwrite(&initiative, sizeof(int), 1, fSave);
    fwrite(&position, sizeof(int), 1, fSave);
    fwrite(&age, sizeof(int), 1, fSave);
    fwrite(&xCord, sizeof(int), 1, fSave);
    fwrite(&yCord, sizeof(int), 1, fSave);
    fwrite(&movSpeed, sizeof(int), 1, fSave);
  }

  fclose(fSave);
  delete[] name2;
}

void nullArr(int x, int y, Organism **arr) {
  for (int i = 0; i < x * y; i++) {
    arr[i] = nullptr;
  }
}

void initiateLoadedInstance(char species, int strength, int initiative, int age, int xCord, int yCord,
                            int movSpeed, World *mainWorld, bool ability, int strengthDecrease,
                            int cooldown, Human *mainCharacter) {

  if (species == HUMAN) {
    *mainCharacter = *new Human(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
    mainCharacter->setStrength(strength);
    mainCharacter->setInitiative(initiative);
    mainCharacter->setPosition(xCord, yCord);
    mainCharacter->setAge(age);
    mainCharacter->setXYCords(xCord, yCord);
    mainCharacter->setMovementSpeed(movSpeed);
    mainCharacter->setAbility(ability);
    mainCharacter->setStrengthDecrease(strengthDecrease);
    mainCharacter->setAbilityCooldown(cooldown);
    return;
  }
  Wolf *x;
  Sheep *y;
  Fox *z;
  Turtle *a;
  Antelope *b;
  Grass *c;
  SowThistle *d;
  Belladonna *e;
  Guarana *f;
  Sosnowsky *g;
  switch (species) {
    case WOLF:x = new Wolf(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      x->setStrength(strength);
      x->setInitiative(initiative);
      x->setPosition(xCord, yCord);
      x->setAge(age);
      x->setXYCords(xCord, yCord);
      x->setMovementSpeed(movSpeed);
      break;
    case SHEEP:y = new Sheep(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      y->setStrength(strength);
      y->setInitiative(initiative);
      y->setPosition(xCord, yCord);
      y->setAge(age);
      y->setXYCords(xCord, yCord);
      y->setMovementSpeed(movSpeed);
      break;
    case FOX:z = new Fox(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      z->setStrength(strength);
      z->setInitiative(initiative);
      z->setPosition(xCord, yCord);
      z->setAge(age);
      z->setXYCords(xCord, yCord);
      z->setMovementSpeed(movSpeed);
      break;
    case TURTLE:a = new Turtle(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      a->setStrength(strength);
      a->setInitiative(initiative);
      a->setPosition(xCord, yCord);
      a->setAge(age);
      a->setXYCords(xCord, yCord);
      a->setMovementSpeed(movSpeed);
      break;
    case ANTELOPE:b = new Antelope(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      b->setStrength(strength);
      b->setInitiative(initiative);
      b->setPosition(xCord, yCord);
      b->setAge(age);
      b->setXYCords(xCord, yCord);
      b->setMovementSpeed(movSpeed);
      break;
    case GRASS:c = new Grass(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      c->setStrength(strength);
      c->setInitiative(initiative);
      c->setPosition(xCord, yCord);
      c->setAge(age);
      c->setXYCords(xCord, yCord);
      c->setMovementSpeed(movSpeed);
      break;
    case SOWTHISTLE:d = new SowThistle(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      d->setStrength(strength);
      d->setInitiative(initiative);
      d->setPosition(xCord, yCord);
      d->setAge(age);
      d->setXYCords(xCord, yCord);
      d->setMovementSpeed(movSpeed);
      break;
    case BELLADONNA:e = new Belladonna(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      e->setStrength(strength);
      e->setInitiative(initiative);
      e->setPosition(xCord, yCord);
      e->setAge(age);
      e->setXYCords(xCord, yCord);
      e->setMovementSpeed(movSpeed);
      break;
    case GUARANA:f = new Guarana(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      f->setStrength(strength);
      f->setInitiative(initiative);
      f->setPosition(xCord, yCord);
      f->setAge(age);
      f->setXYCords(xCord, yCord);
      f->setMovementSpeed(movSpeed);
      break;
    case SOSNOWSKY:g = new Sosnowsky(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      g->setStrength(strength);
      g->setInitiative(initiative);
      g->setPosition(xCord, yCord);
      g->setAge(age);
      g->setXYCords(xCord, yCord);
      g->setMovementSpeed(movSpeed);
      break;
    default:break;
  }
}

void loadGameState(World *mainWorld, Human *mainCharacter) {
  mainCharacter->setLifeStatus(false);
  FILE *fLoad;
  std::string name = getFileName();
  char *name2 = new char[name.size() + 1];
  strcpy(name2, name.c_str());
  fLoad = fopen(name2, "rb");
  int X, Y, max;
  fread(&X, sizeof(int), 1, fLoad);
  fread(&Y, sizeof(int), 1, fLoad);
  fread(&max, sizeof(int), 1, fLoad);
  if (X == N && Y == M) {
    nullArr(N, M, mainWorld->getBoardBeginning());
    char species;
    int strength, initiative, position, age, xCord, yCord, movSpeed, decreaseReps, cooldown;
    bool ability, alive;
    for (int i = 0; i < max; i++) {
      fread(&species, sizeof(char), 1, fLoad);
      if (species == HUMAN) {
        fread(&alive, sizeof(bool), 1, fLoad);
        fread(&ability, sizeof(bool), 1, fLoad);
        fread(&decreaseReps, sizeof(int), 1, fLoad);
        fread(&cooldown, sizeof(int), 1, fLoad);
      }
      fread(&strength, sizeof(int), 1, fLoad);
      fread(&initiative, sizeof(int), 1, fLoad);
      fread(&position, sizeof(int), 1, fLoad);
      fread(&age, sizeof(int), 1, fLoad);
      fread(&xCord, sizeof(int), 1, fLoad);
      fread(&yCord, sizeof(int), 1, fLoad);
      fread(&movSpeed, sizeof(int), 1, fLoad);
      initiateLoadedInstance(species, strength, initiative, age,
                             xCord, yCord, movSpeed, mainWorld, ability,
                             decreaseReps, cooldown, mainCharacter);
    }
  } else {
    std::cout << "Incompatible configuration, try a different file. " << std::endl;
  }
  fclose(fLoad);
  delete[] name2;
}

void deleteEntities(World *mainWorld) {
  std::vector<Organism *> orgsOnBoard = mainWorld->getOrganismsOnBoard();
  for (auto &i : orgsOnBoard) {
    delete i;
  }
}

void gameControl(World *mainWorld, Human *mainCharacter) {
  char flags = ' ';

  while (mainCharacter != nullptr &&  !mainCharacter->getLifeStatus() && flags != ESC_KEY) {
    mainWorld->drawWorld();
    std::cout << "Jakub Szurmak 193095 Interface: s-Save, l-Load, a-Ability, ESC-End, Arrows-Move: " << std::endl;
    flags = (char) getch();
    switch (flags) {
      case '\000':
        mainCharacter->getMoveDirection();
        system("cls");
        mainWorld->makeTurn();
        mainCharacter->setArrowKey(0);
        break;
      case '\340':
        mainCharacter->getMoveDirection();
        system("cls");
        mainWorld->makeTurn();
        mainCharacter->setArrowKey(0);
        break;
      case 's':
        saveGameState(mainWorld);
        mainWorld->makeTurn();
        break;
      case 'l':
        loadGameState(mainWorld, mainCharacter);
        mainWorld->makeTurn();
        break;
      case 'a':
        mainCharacter->activateAbility();
        mainCharacter->setArrowKey(0);
        flags = ' ';
        system("cls");
        mainWorld->makeTurn();
        break;
      default:
        break;
    }
  }
}

int main() {

  srand((unsigned) time(nullptr));

  World mainWorld = World();

  auto mainCharacter = new Human(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  mainCharacter->setPosition(7, 7);

  Organism *wolf1 = new Wolf(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  wolf1->setPosition(1, 1);

  Organism *wolf2 = new Wolf(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  wolf2->setPosition(2, 1);

  Organism *wolf3 = new Wolf(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  wolf3->setPosition(1, 2);

  Organism *wolf4 = new Wolf(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  wolf4->setPosition(2, 2);

  Organism *sheep1 = new Sheep(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sheep1->setPosition(4, 1);

  Organism *sheep2 = new Sheep(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sheep2->setPosition(6, 1);

  Organism *sheep3 = new Sheep(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sheep3->setPosition(15, 2);

  Organism *sheep4 = new Sheep(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sheep4->setPosition(14, 2);

  Organism *fox1 = new Fox(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  fox1->setPosition(7, 1);

  Organism *fox2 = new Fox(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  fox2->setPosition(7, 15);

  Organism *turtle1 = new Turtle(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  turtle1->setPosition(15, 15);

  Organism *turtle2 = new Turtle(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  turtle2->setPosition(14, 15);

  Organism *antelope1 = new Antelope(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  antelope1->setPosition(1, 7);

  Organism *antelope2 = new Antelope(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  antelope2->setPosition(15, 7);

  Organism *grass1 = new Grass(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  grass1->setPosition(9, 1);

  Organism *grass2 = new Grass(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  grass2->setPosition(9, 15);

  Organism *sowthistle1 = new SowThistle(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sowthistle1->setPosition(10, 15);

  Organism *sowthistle2 = new SowThistle(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sowthistle2->setPosition(10, 1);

  Organism *guarana1 = new Guarana(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  guarana1->setPosition(8, 7);

  Organism *guarana2 = new Guarana(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  guarana2->setPosition(9, 7);

  Organism *belladonna2 = new Belladonna(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  belladonna2->setPosition(1, 15);

  Organism *sosnowsky2 = new Sosnowsky(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sosnowsky2->setPosition(9, 1);

  gameControl(&mainWorld, mainCharacter);

  mainWorld.drawWorld();
  deleteEntities(&mainWorld);
  delete mainCharacter;
  return 0;
}
