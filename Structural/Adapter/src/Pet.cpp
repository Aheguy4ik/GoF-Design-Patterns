#include "Pet.h"

std::string Puppy::Name() const { return "Puppy"; }
int Puppy::CutenessAbility() const { return 50; }
int Puppy::BattleBonus() const { return 5; }

std::string Cat::Name() const { return "Cat"; }
int Cat::CutenessAbility() const { return 40; }
int Cat::BattleBonus() const { return 10; }
