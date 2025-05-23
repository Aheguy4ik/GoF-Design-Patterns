#pragma once
#include <string>

class Pet {
public:
    virtual ~Pet() = default;
    virtual std::string Name() const = 0;
    virtual int CutenessAbility() const = 0;
    virtual int BattleBonus() const = 0;
};

class Puppy : public Pet {
public:
    std::string Name() const override;
    int CutenessAbility() const override;
    int BattleBonus() const override;
};

class Cat : public Pet {
public:
    std::string Name() const override;
    int CutenessAbility() const override;
    int BattleBonus() const override;
};
