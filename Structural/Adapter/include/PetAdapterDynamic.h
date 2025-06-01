#pragma once
#include "Pet.h"
#include "Monster.h"
#include <memory>
#include <algorithm>

class PetAdapterDynamic : public Pet {
public:
    explicit PetAdapterDynamic(std::unique_ptr<Monster>&& monster)
        : monster_(std::move(monster)) {}

    std::unique_ptr<Monster> ChangeMonster(std::unique_ptr<Monster>&& monster) {
        auto old = std::move(monster_);
        monster_ = std::move(monster);
        return old;
    }

    std::string Name() const override { return monster_->Name(); }

    int CutenessAbility() const override {
        return std::max(0, monster_->DefenseAbility() - 2 * monster_->AttackAbility());
    }

    int BattleBonus() const override {
        return monster_->AttackAbility() + monster_->DefenseAbility() / 2;
    }

private:
    std::unique_ptr<Monster> monster_;
};
