#include <memory>
#include <string>
#include <iostream>
#include <type_traits>

/* ���ʿ� Monster���� �����ߴ�.. */
struct Monster 
{
	virtual std::string Name() const = 0;
	virtual int AttackAbility() const = 0;
	virtual int DefenseAbility() const = 0;
};

struct Slime : public Monster
{
	virtual std::string Name() const override { return "Slime"; }
	virtual int AttackAbility() const override { return 6; }
	virtual int DefenseAbility() const override { return 20; }
};

struct Goblin : public Monster
{
	virtual std::string Name() const override { return "Goblin"; }
	virtual int AttackAbility() const override { return 30; }
	virtual int DefenseAbility() const override { return 10; }
};

struct Dragon : public Monster
{
	virtual std::string Name() const override { return "Dragon"; }
	virtual int AttackAbility() const override { return 1000; }
	virtual int DefenseAbility() const override { return 500; }
};

/* �׸��� ���ʿ� Pet���� �����ߴ�.. */
struct Pet
{
	virtual std::string Name() const = 0;
	virtual int CutenessAbility() const = 0;
	virtual int BattleBonus() const = 0;
};

struct Puppy : public Pet
{
	virtual std::string Name() const override { return "Puppy"; }
	virtual int CutenessAbility() const override { return 50; }
	virtual int BattleBonus() const override { return 5; }
};

struct Cat : public Pet
{
	virtual std::string Name() const override { return "Cat"; }
	virtual int CutenessAbility() const override { return 40; }
	virtual int BattleBonus() const override { return 10; }
};

/*** �׷��� ������ ������Ʈ�Ǹ鼭 Monster�鵵 Pet�� �� �� �ְ� �Ǿ��ٸ�?! 
		==> �� ��� Adapter ������ �̿��ϸ� ������ Monster Ŭ���� ������ �������� �ʰ�, �� ������ �ذ� �� �� �ִ�!
***/

/* Monster�� ��������(compile-time) Pet�� �Ϻημ� ����� ���� ���, 
	template�� Ȱ���ϸ�, overhead�� �ּ�ȭ�� �� �ִ�. ��, �������� ��������.
*/
template <typename _MonsterType, 
			typename = std::enable_if_t<std::is_base_of<Monster, _MonsterType>::value>>
struct PetAdapterStatic : public Pet
{
	virtual std::string Name() const override { return m_monster.Name(); }
	virtual int CutenessAbility() const override { return m_monster.DefenseAbility() - 2 * m_monster.AttackAbility(); }
	virtual int BattleBonus() const override { return m_monster.AttackAbility() + m_monster.DefenseAbility() / 2; }

private:
	_MonsterType m_monster;
};

/* Monster�� ��������(run-time) Pet�� �Ϻημ� ����� ���� ���,
	Monster Ŭ���� ������ base class�μ� ����Ÿ������ �ϸ� ū �������� ���� �� �ִ�.
	pet�� �ش��ϴ� monster�� �ٲٰų� pet�� �ٽ� monster�� ���ͽ�Ű�� ���� ������ �۾��� ����������.
	��, static�� ����(template�� �̿��� ����)�� ���� overhead�� �� �����Ѵ�.
*/
struct PetAdapterDynamic : public Pet
{
	PetAdapterDynamic(std::unique_ptr<Monster>&& monster)
		: m_monster(std::move(monster))
	{}

	std::unique_ptr<Monster> ChangeMonster(std::unique_ptr<Monster>&& monster) 
	{
		std::unique_ptr<Monster> returnedMonster = std::move(m_monster);
		m_monster = std::move(monster); 
		return returnedMonster;
	}

	virtual std::string Name() const override { return m_monster->Name(); }
	virtual int CutenessAbility() const override { return m_monster->DefenseAbility() - 2 * m_monster->AttackAbility(); }
	virtual int BattleBonus() const override { return m_monster->AttackAbility() + m_monster->DefenseAbility() / 2; }

private:
	std::unique_ptr<Monster> m_monster;
};

void PrintMonster(const Monster& monster)
{
	std::cout << "---- Infomation ----" << std::endl;
	std::cout << "Name             : " << monster.Name() << std::endl;
	std::cout << "Attack Ability   : " << monster.AttackAbility() << std::endl;
	std::cout << "Defense Ability  : " << monster.DefenseAbility() << std::endl;
	std::cout << "--------------------" << std::endl;
}

void PrintPet(const Pet& pet)
{
	std::cout << "---- Infomation ----" << std::endl;
	std::cout << "Name             : " << pet.Name() << std::endl;
	std::cout << "Cuteness Ability : " << pet.CutenessAbility() << std::endl;
	std::cout << "Battle Bonus     : " << pet.BattleBonus() << std::endl;
	std::cout << "--------------------" << std::endl;
}

int main()
{
	Puppy puppy;
	Cat cat;

	std::cout << "====== Normal Pet ======" << std::endl << std::endl;

	PrintPet(puppy);
	PrintPet(cat);

	std::cout << std::endl << "====== Monster Pet ======" << std::endl << std::endl;

	PetAdapterStatic<Slime> petSlime;
	PetAdapterStatic<Goblin> petGoblin;
	PetAdapterStatic<Dragon> petDragon;

	PrintPet(petSlime);
	PrintPet(petGoblin);
	PrintPet(petDragon);

	std::cout << std::endl << "====== Monster ======" << std::endl << std::endl;

	auto slime = std::make_unique<Slime>();
	auto goblin = std::make_unique<Goblin>();
	auto dragon = std::make_unique<Dragon>();

	PrintMonster(*slime);
	PrintMonster(*goblin);
	PrintMonster(*dragon);

	std::cout << std::endl << "====== Pet From Monster ======" << std::endl << std::endl;

	PetAdapterDynamic petAdapter(std::move(slime));
	PrintPet(petAdapter);
	petAdapter.ChangeMonster(std::move(goblin));
	PrintPet(petAdapter);
	auto returnedMonster = petAdapter.ChangeMonster(std::move(dragon));
	PrintPet(petAdapter);

	std::cout << std::endl << "====== Monster Returned From Pet ======" << std::endl << std::endl;

	PrintMonster(*returnedMonster);
}