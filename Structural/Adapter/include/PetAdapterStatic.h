#pragma once
#include "Monster.h"
#include "Pet.h"
#include <type_traits>
#include <algorithm> // for std::max

template <typename MonsterType, typename = std::enable_if_t<std::is_base_of<Monster, MonsterType>::value>>
class PetAdapterStatic : public Pet {
public:
    std::string Name() const override { return monster_.Name(); }
    int CutenessAbility() const override {
        return std::max(0, monster_.DefenseAbility() - 2 * monster_.AttackAbility());
    }
    int BattleBonus() const override {
        return monster_.AttackAbility() + monster_.DefenseAbility() / 2;
    }

private:
    MonsterType monster_;
};
