#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#define N 15
#define M 15

#define WOLF 'W'
#define SHEEP 'S'
#define FOX 'F'
#define TURTLE 'T'
#define ANTELOPE 'A'
#define HUMAN 1

#define REFLECTED 'R'
#define POISONED 'P'
#define DEFEATED 'D'
#define VICTORY 'K'
#define ESCAPED 'E'
#define RECREATION 'X'

#define GRASS 'G'
#define SOWTHISTLE 'O'
#define GUARANA 'U'
#define BELLADONNA 'B'
#define SOSNOWSKY 'H'

#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

#define ACTIVATE_ABILITY 97
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_LEFT 75

class Organism {
 protected:
  int strength, initiative, position, age, xCord, yCord, movementSpeed, nextPosition;
  char species;
  bool killed;
  Organism** boardBeginning;
  Organism* boardField;
  std::vector<Organism*>* deadOrganismBox;
 public:
  Organism(int strength, int initiative, int movementSpeed, char species, Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  virtual bool abilityActive() = 0;
  virtual void action() = 0;
  virtual void recreate(Organism* partner) = 0;
  virtual void fightWith(Organism* enemy) = 0;
  virtual char defendAgainst(Organism* attacker) = 0;
  virtual int getStrengthDecreaseReps() = 0;
  virtual Organism** getBoardBeginning() = 0;
  virtual int getCooldownReps() = 0;
  virtual bool considerAction() = 0;
  virtual Organism* getBaby() = 0;
  virtual void setAbility(bool x);
  virtual void setStrengthDecrease(int x);
  virtual void setAbilityCooldown(int x);
  bool getLifeStatus() const;
  static bool isCharAnimal(char speciesChar) ;
  bool isAnimal() const;
  char getSpecies() const;
  static void displayOrganismName(char currentOrganism) ;
  void displayComment(char attacker, char defender, char statusFlag) const;
  void collision();
  void setInitiative(int x);
  void setAge(int x);
  void setMovementSpeed(int x);
  void setXYCords(int x, int y);
  void setKilledOrganism();
  void setStrength(int newStrength);
  void setField(int newIndex);
  void incrementAge();
  void setPosition(int x, int y);
  void setLifeStatus(bool x);
  int findFreeRecreationSpot() const;
  int findFreeEscapeSpot() const;
  int getStrength() const;
  int getInitiative() const;
  int getPosition() const;
  int getAge() const;
  int getXCord() const;
  int getYCord() const;
  int getMovementSpeed() const;
  virtual ~Organism();
};
