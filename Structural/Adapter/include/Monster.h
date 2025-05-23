#pragma once
#include <string>

class Monster {
public:
    virtual ~Monster() = default;
    virtual std::string Name() const = 0;
    virtual int AttackAbility() const = 0;
    virtual int DefenseAbility() const = 0;
};

class Slime : public Monster {
public:
    std::string Name() const override;
    int AttackAbility() const override;
    int DefenseAbility() const override;
};

class Goblin : public Monster {
public:
    std::string Name() const override;
    int AttackAbility() const override;
    int DefenseAbility() const override;
};

class Dragon : public Monster {
public:
    std::string Name() const override;
    int AttackAbility() const override;
    int DefenseAbility() const override;
};
