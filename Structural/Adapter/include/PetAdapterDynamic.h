#pragma once
#include "Pet.h"
#include "Monster.h"
#include <memory>

class PetAdapterDynamic : public Pet {
public:
    explicit PetAdapterDynamic(std::unique_ptr<Monster>&& monster);

    std::unique_ptr<Monster> ChangeMonster(std::unique_ptr<Monster>&& monster);

    std::string Name() const override;
    int CutenessAbility() const override;
    int BattleBonus() const override;

private:
    std::unique_ptr<Monster> monster_;
};
