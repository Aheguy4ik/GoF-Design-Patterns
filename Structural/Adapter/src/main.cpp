#include <iostream>
#include <memory>

#include "Monster.h"
#include "Pet.h"
#include "PetAdapterStatic.h"
#include "PetAdapterDynamic.h"

void PrintMonster(const Monster& monster) {
    std::cout << "---- Information ----\n";
    std::cout << "Name             : " << monster.Name() << '\n';
    std::cout << "Attack Ability   : " << monster.AttackAbility() << '\n';
    std::cout << "Defense Ability  : " << monster.DefenseAbility() << '\n';
    std::cout << "--------------------\n";
}

void PrintPet(const Pet& pet) {
    std::cout << "---- Information ----\n";
    std::cout << "Name             : " << pet.Name() << '\n';
    std::cout << "Cuteness Ability : " << pet.CutenessAbility() << '\n';
    std::cout << "Battle Bonus     : " << pet.BattleBonus() << '\n';
    std::cout << "--------------------\n";
}

int main() {
    Puppy puppy;
    Cat cat;

    std::cout << "====== Normal Pet ======\n\n";
    PrintPet(puppy);
    PrintPet(cat);

    std::cout << "\n====== Monster Pet ======\n\n";

    PetAdapterStatic<Slime> petSlime;
    PetAdapterStatic<Goblin> petGoblin;
    PetAdapterStatic<Dragon> petDragon;

    PrintPet(petSlime);
    PrintPet(petGoblin);
    PrintPet(petDragon);

    std::cout << "\n====== Monster ======\n\n";

    auto slime = std::make_unique<Slime>();
    auto goblin = std::make_unique<Goblin>();
    auto dragon = std::make_unique<Dragon>();

    PrintMonster(*slime);
    PrintMonster(*goblin);
    PrintMonster(*dragon);

    std::cout << "\n====== Pet From Monster ======\n\n";

    PetAdapterDynamic petAdapter(std::move(slime));
    PrintPet(petAdapter);
    petAdapter.ChangeMonster(std::move(goblin));
    PrintPet(petAdapter);
    auto returnedMonster = petAdapter.ChangeMonster(std::move(dragon));
    PrintPet(petAdapter);

    std::cout << "\n====== Monster Returned From Pet ======\n\n";

    PrintMonster(*returnedMonster);

    return 0;
}
