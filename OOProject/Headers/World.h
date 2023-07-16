#pragma once
#include "Organism.h"

class World {
 private:
  Organism* boardOfOrganisms[N*M] = {nullptr};
  std::vector<Organism*> deadOrganismsBox = {};
 public:
  World();
  Organism** getBoardBeginning();
  std::vector<Organism*>* getDeadOrganismsBox();
  std::vector<Organism*> getOrganismsOnBoard();
  static bool compareOrganismsImportancy(Organism* obj1, Organism* obj2);
  void makeTurn();
  void drawWorld();
};
