#include "../Headers/World.h"

World::World() = default;

Organism **World::getBoardBeginning() {
  return this->boardOfOrganisms;
}

std::vector<Organism*>* World::getDeadOrganismsBox() {
  return &this->deadOrganismsBox;
}

void World::drawWorld() {
  int j = 1;
  for (int i = 0; i < N * M; i++) {
    if(this->boardOfOrganisms[i] == nullptr){
      std::cout << ' ' << ',' << ' ';
    }else{
      std::cout << ' ' << this->boardOfOrganisms[i]->getSpecies() << ' ';
    }
    if(j%N == 0){
      std::cout << std::endl;
    }
    j+=1;
  }
  std::cout << std::endl;
}

bool World::compareOrganismsImportancy(Organism* obj1, Organism* obj2){
  if(obj1->getInitiative() != obj2->getInitiative()){
   return obj1->getInitiative() > obj2->getInitiative();
  }else{
    return obj1->getAge() > obj2->getAge();
  }
}

std::vector<Organism*> World::getOrganismsOnBoard(){
  std::vector<Organism*> orgsOnBoard = {};
  for(int i = 0; i < N*M; i++){
    if(this->getBoardBeginning()[i] != nullptr){
      orgsOnBoard.push_back(this->getBoardBeginning()[i]);
    }
  }
  return orgsOnBoard;
}

void World::makeTurn() {
  std::vector<Organism*> orgsOnBoard = this->getOrganismsOnBoard();
  std::sort((&orgsOnBoard)->begin(), (&orgsOnBoard)->end() , &World::compareOrganismsImportancy);
  for(auto & i : orgsOnBoard){
    i->action();
    i->incrementAge();
  }
  deadOrganismsBox = {};
}

