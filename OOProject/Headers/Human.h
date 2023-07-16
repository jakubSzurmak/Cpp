#pragma once

#import "Animal.h"
#include "../../../../../Program Files/JetBrains/CLion 2022.2.4/bin/mingw/x86_64-w64-mingw32/include/conio.h"

class Human : public Animal {
  bool ability;
  int cooldownReps;
  int strengthDecreaseReps;
  int arrowPressed;
 public:
  Human(Organism** boardBeginning, std::vector<Organism*>* deadOrganismBox);
  Organism* getBaby() override;
  virtual void action() override;
  virtual int generateNextPosition() const override;
  void setAbility(bool x) override;
  void setStrengthDecrease(int x) override;
  void setAbilityCooldown(int x) override;
  void setArrowKey(int x);
  void setLifeStatus(bool x);
  int getArrowPressed() const;
  void makeMove() override;
  bool abilityActive() override;
  int getCooldownReps() override;
  int getStrengthDecreaseReps() override;
  bool detectArrow(int key);
  bool considerAction() override;
  void shortenAbility();
  void getMoveDirection();
  void activateAbility();
};

