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

std::string getFileName(){
  std::string name;
  std::cout << "Enter desired fileName: ";
  std::cin >> name;
  return name;
}

void saveGameState(World* mainWorld){

  FILE *fSave;
  std::string name = getFileName();
  char* name2 = new char[name.size() + 1];
  strcpy(name2, name.c_str());
  fSave = fopen(name2, "wb");
  if(fSave == nullptr){
    exit(-100);
  }

  int X = N;
  int Y = M;
  fwrite(&X, sizeof(int), 1, fSave);
  fwrite(&Y, sizeof(int), 1, fSave);
  std::vector<Organism*> orgsOnBoard = mainWorld->getOrganismsOnBoard();
  int max = orgsOnBoard.size();
  fwrite(&max, sizeof(int), 1, fSave);

  char species;
  bool alive;
  int strength, initiative, position, age, xCord, yCord, movSpeed, cooldown, decreaseReps, ability;
  for(int i = 0; i < max; i++){
    species = orgsOnBoard[i]->getSpecies();
    if(species == HUMAN){
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

void nullArr(int x, int y, Organism** arr){
  for(int i = 0; i < x*y; i++){
    arr[i] = nullptr;
  }
}

void initiateLoadedInstance(char species, int strength, int initiative, int position, int age, int xCord, int yCord,
                            int movSpeed, World* mainWorld, bool ability,int strengthDecrease,
                            int cooldown, bool alive, Human* mainCharacter ){

  if(species == HUMAN){
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
  Wolf* x;Sheep* y;Fox* z;Turtle* a;Antelope* b;Grass* c;SowThistle* d;Belladonna* e;Guarana* f;Sosnowsky* g;
  switch (species) {
    case WOLF:
      x = new Wolf(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      x->setStrength(strength);
      x->setInitiative(initiative);
      x->setPosition(xCord, yCord);
      x->setAge(age);
      x->setXYCords(xCord, yCord);
      x->setMovementSpeed(movSpeed);
      break;
    case SHEEP:
      y = new Sheep(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      y->setStrength(strength);
      y->setInitiative(initiative);
      y->setPosition(xCord, yCord);
      y->setAge(age);
      y->setXYCords(xCord, yCord);
      y->setMovementSpeed(movSpeed);
      break;
    case FOX:
      z = new Fox(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      z->setStrength(strength);
      z->setInitiative(initiative);
      z->setPosition(xCord, yCord);
      z->setAge(age);
      z->setXYCords(xCord, yCord);
      z->setMovementSpeed(movSpeed);
      break;
    case TURTLE:
      a = new Turtle(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      a->setStrength(strength);
      a->setInitiative(initiative);
      a->setPosition(xCord, yCord);
      a->setAge(age);
      a->setXYCords(xCord, yCord);
      a->setMovementSpeed(movSpeed);
      break;
    case ANTELOPE:
      b = new Antelope(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      b->setStrength(strength);
      b->setInitiative(initiative);
      b->setPosition(xCord, yCord);
      b->setAge(age);
      b->setXYCords(xCord, yCord);
      b->setMovementSpeed(movSpeed);
      break;
    case GRASS:
      c = new Grass(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      c->setStrength(strength);
      c->setInitiative(initiative);
      c->setPosition(xCord, yCord);
      c->setAge(age);
      c->setXYCords(xCord, yCord);
      c->setMovementSpeed(movSpeed);
      break;
    case SOWTHISTLE:
      d = new SowThistle(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      d->setStrength(strength);
      d->setInitiative(initiative);
      d->setPosition(xCord, yCord);
      d->setAge(age);
      d->setXYCords(xCord, yCord);
      d->setMovementSpeed(movSpeed);
      break;
    case BELLADONNA:
      e = new Belladonna(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      e->setStrength(strength);
      e->setInitiative(initiative);
      e->setPosition(xCord, yCord);
      e->setAge(age);
      e->setXYCords(xCord, yCord);
      e->setMovementSpeed(movSpeed);
      break;
    case GUARANA:
      f = new Guarana(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      f->setStrength(strength);
      f->setInitiative(initiative);
      f->setPosition(xCord, yCord);
      f->setAge(age);
      f->setXYCords(xCord, yCord);
      f->setMovementSpeed(movSpeed);
      break;
    case SOSNOWSKY:
      g = new Sosnowsky(mainWorld->getBoardBeginning(), mainWorld->getDeadOrganismsBox());
      g->setStrength(strength);
      g->setInitiative(initiative);
      g->setPosition(xCord, yCord);
      g->setAge(age);
      g->setXYCords(xCord, yCord);
      g->setMovementSpeed(movSpeed);
      break;
    default:
      break;
  }
}

void loadGameState(World* mainWorld, Human* mainCharacter){
  mainCharacter->setLifeStatus(false);
  FILE *fLoad;
  std::string name = getFileName();
  char* name2 = new char[name.size() + 1];
  strcpy(name2, name.c_str());
  fLoad = fopen(name2, "rb");
  int X, Y, max;
  fread(&X, sizeof(int), 1, fLoad);
  fread(&Y, sizeof(int), 1, fLoad);
  fread(&max, sizeof(int), 1, fLoad);
  if(X == N && Y == M){
    nullArr(N, M, mainWorld->getBoardBeginning());
    char species;
    int strength, initiative, position, age, xCord, yCord, movSpeed,decreaseReps, cooldown;
    bool ability, alive;
    for(int i = 0; i < max; i++){
      fread(&species, sizeof(char), 1, fLoad);
      if(species == HUMAN){
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
      fread(&yCord,sizeof(int), 1, fLoad);
      fread(&movSpeed, sizeof(int), 1, fLoad);
      initiateLoadedInstance(species, strength, initiative, position, age,
                             xCord, yCord, movSpeed, mainWorld, ability,
                             decreaseReps, cooldown, alive, mainCharacter);
    }
  }else{
    std::cout << "Incompatible configuration, try a different file. " << std::endl;
  }
  fclose(fLoad);
  delete[] name2;
}

void gameControl(World* mainWorld, Human* mainCharacter) {
  char flags = ' ';
  while(flags != ESC_KEY) {
    mainWorld->drawWorld();
    std::cout << "Do you want to save/load game State? (s,l,N): ";
    std::cin >> flags;
    if (flags == 's') {
      saveGameState(mainWorld);
    } else if (flags == 'l') {
      loadGameState(mainWorld, mainCharacter);
      system("CLS");
      flags = ' ';
      continue;
    } else {
      flags = ' ';
    }
    if (!mainCharacter->abilityActive() && !mainCharacter->getLifeStatus()) {
      std::cout << "Do you want to activate Human's ability (y,n)?: ";
      std::cin >> flags;
      if (flags == 'y') {
        mainCharacter->activateAbility();
      }
      flags = ' ';
    }
    if (mainCharacter != nullptr && !mainCharacter->getLifeStatus()) {
      mainCharacter->getMoveDirection();
    }
    mainWorld->makeTurn();
    mainCharacter->setArrowKey(0);
  }
}

int main() {

  srand((unsigned) time(nullptr));

  World mainWorld = World();

  Human mainCharacter(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  mainCharacter.setPosition(1,1);

  Guarana guarana2 = Guarana(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  guarana2.setPosition(1,2);

  Wolf wolf1 = Wolf(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  wolf1.setPosition(3,1);

  Sheep sheep1 = Sheep(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sheep1.setPosition(5,1);

  Fox fox1 = Fox(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  fox1.setPosition(7,1);

  Turtle turtle1 = Turtle(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  turtle1.setPosition(9,1);

  Antelope antelope1 = Antelope(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  antelope1.setPosition(11,1);

  Grass grass1 = Grass(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  grass1.setPosition(2,2);

  SowThistle sowthistle1 = SowThistle(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sowthistle1.setPosition(3,2);

  Guarana guarana1 = Guarana(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  guarana1.setPosition(5,2);

  Belladonna belladonna1 = Belladonna(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  belladonna1.setPosition(7,2);

  Sosnowsky sosnowsky1 = Sosnowsky(mainWorld.getBoardBeginning(), mainWorld.getDeadOrganismsBox());
  sosnowsky1.setPosition(9,2);

  gameControl( &mainWorld, &mainCharacter);

  return 0;
}
