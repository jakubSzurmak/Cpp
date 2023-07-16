#pragma once

#include "Organism.h"

class Animal : public Organism {
 protected:
  Animal(int strength, int initiative, int movementSpeed, char species,
         Organism **boardBeginning,std::vector<Organism *> *deadOrganismBox);
  virtual void action() override;
  virtual int generateNextPosition() const;
  virtual int generateMoveDirection() const;
  virtual void makeMove();
  void recreate(Organism *partner) override;
  void fightWith(Organism *enemy) override;
  virtual void cordChangeOnMove(int nextPos);
  char defendAgainst(Organism *attacker) override;
  int determineMoveDirection(int positionChange) ;
  Organism **getBoardBeginning() override;
};

