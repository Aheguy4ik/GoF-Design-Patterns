#include "Monster.h"

std::string Slime::Name() const { return "Slime"; }
int Slime::AttackAbility() const { return 6; }
int Slime::DefenseAbility() const { return 20; }

std::string Goblin::Name() const { return "Goblin"; }
int Goblin::AttackAbility() const { return 30; }
int Goblin::DefenseAbility() const { return 10; }

std::string Dragon::Name() const { return "Dragon"; }
int Dragon::AttackAbility() const { return 1000; }
int Dragon::DefenseAbility() const { return 500; }
