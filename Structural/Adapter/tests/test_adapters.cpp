#include "PetAdapterStatic.h"
#include <gtest/gtest.h>
#include "PetAdapterDynamic.h"
#include "Monster.h"
#include "Pet.h"
#include <memory>

TEST(MonsterTest, SlimeProperties) {
    Slime slime;
    EXPECT_EQ(slime.Name(), "Slime");
    EXPECT_EQ(slime.AttackAbility(), 6);
    EXPECT_EQ(slime.DefenseAbility(), 20);
}

TEST(PetTest, PuppyProperties) {
    Puppy puppy;
    EXPECT_EQ(puppy.Name(), "Puppy");
    EXPECT_EQ(puppy.CutenessAbility(), 50);
    EXPECT_EQ(puppy.BattleBonus(), 5);
}

TEST(PetAdapterDynamicTest, BasicFunctionality) {
    auto slime = std::make_unique<Slime>();
    PetAdapterDynamic adapter(std::move(slime));
    EXPECT_EQ(adapter.Name(), "Slime");
    EXPECT_GT(adapter.CutenessAbility(), 0);
    EXPECT_GT(adapter.BattleBonus(), 0);

    auto goblin = std::make_unique<Goblin>();
    auto oldMonster = adapter.ChangeMonster(std::move(goblin));
    EXPECT_EQ(adapter.Name(), "Goblin");
    EXPECT_EQ(oldMonster->Name(), "Slime");
}

TEST(PetAdapterStaticTest, BasicFunctionality) {
    PetAdapterStatic<Dragon> adapter;
    EXPECT_EQ(adapter.Name(), "Dragon");
    EXPECT_GT(adapter.CutenessAbility(), 0);  // теперь точно > 0
    EXPECT_GT(adapter.BattleBonus(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
