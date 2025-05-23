#include "PetAdapterDynamic.h"

PetAdapterDynamic::PetAdapterDynamic(std::unique_ptr<Monster>&& monster)
    : monster_(std::move(monster)) {}

std::unique_ptr<Monster> PetAdapterDynamic::ChangeMonster(std::unique_ptr<Monster>&& monster) {
    std::unique_ptr<Monster> returnedMonster = std::move(monster_);
    monster_ = std::move(monster);
    return returnedMonster;
}

std::string PetAdapterDynamic::Name() const {
    return monster_->Name();
}

int PetAdapterDynamic::CutenessAbility() const {
    return monster_->DefenseAbility() - 2 * monster_->AttackAbility();
}

int PetAdapterDynamic::BattleBonus() const {
    return monster_->AttackAbility() + monster_->DefenseAbility() / 2;
}
