#include <memory>
#include <vector>
#include <string>
#include <iostream>

struct HamburgerIngredient { virtual std::string Name() const = 0; };

struct Bread : public HamburgerIngredient { virtual std::string Name() const override { return "Bread"; } };
struct Patty : public HamburgerIngredient { virtual std::string Name() const override { return "Patty"; } };
struct Cheese : public HamburgerIngredient { virtual std::string Name() const override { return "Cheese"; } };
struct Tomato : public HamburgerIngredient { virtual std::string Name() const override { return "Tomato"; } };
struct Lettuce : public HamburgerIngredient { virtual std::string Name() const override { return "Lettuce"; } };
struct Sauce : public HamburgerIngredient { virtual std::string Name() const override { return "Sauce"; } };

struct LightBread : public Bread { virtual std::string Name() const override { return "LightBread"; } };
struct SaltyBread : public Bread { virtual std::string Name() const override { return "SaltyBread"; } };

struct BeefPatty : public Patty { virtual std::string Name() const override { return "BeefPatty"; } };
struct PorkPatty : public Patty { virtual std::string Name() const override { return "PorkPatty"; } };

struct MozzarellaCheese : public Cheese { virtual std::string Name() const override { return "MozzarellaCheese"; } };
struct CheddarCheese : public Cheese { virtual std::string Name() const override { return "CheddarCheese"; } };

struct GarlicSauce : public Sauce { virtual std::string Name() const override { return "GarlicSauce"; } };
struct MustardSauce : public Sauce { virtual std::string Name() const override { return "MustardSauce"; } };


class Hamburger
{
public:
	Hamburger(std::vector<std::unique_ptr<HamburgerIngredient>>&& ingredientList)
		: m_ingredientList(std::move(ingredientList))
	{}

	void Print() const
	{
		std::cout << "----------" << std::endl;
		for (const auto & ingredient : m_ingredientList)
			std::cout << ingredient->Name() << std::endl;
		std::cout << "----------" << std::endl;
	}

private:
	std::vector<std::unique_ptr<HamburgerIngredient>> m_ingredientList;
};

class HamburgerFactory
{
public:
	virtual std::unique_ptr<Bread> MakeBread() const = 0;
	virtual std::unique_ptr<Patty> MakePatty() const = 0;
	virtual std::unique_ptr<Cheese> MakeCheese() const = 0;
	virtual std::unique_ptr<Tomato> MakeTomato() const = 0;
	virtual std::unique_ptr<Lettuce> MakeLettuce() const = 0;
	virtual std::unique_ptr<Sauce> MakeSauce() const = 0;
};

class BeefHamburgerFactory : public HamburgerFactory
{
public:
	virtual std::unique_ptr<Bread> MakeBread() const override { return std::make_unique<LightBread>(); }
	virtual std::unique_ptr<Patty> MakePatty() const override { return std::make_unique<BeefPatty>(); };
	virtual std::unique_ptr<Cheese> MakeCheese() const override { return std::make_unique<MozzarellaCheese>(); }
	virtual std::unique_ptr<Tomato> MakeTomato() const override { return std::make_unique<Tomato>(); }
	virtual std::unique_ptr<Lettuce> MakeLettuce() const override { return std::make_unique<Lettuce>(); }
	virtual std::unique_ptr<Sauce> MakeSauce() const override { return std::make_unique<GarlicSauce>(); }
};

class PorkHamburgerFactory : public HamburgerFactory
{
public:
	virtual std::unique_ptr<Bread> MakeBread() const override { return std::make_unique<SaltyBread>(); }
	virtual std::unique_ptr<Patty> MakePatty() const override { return std::make_unique<PorkPatty>(); };
	virtual std::unique_ptr<Cheese> MakeCheese() const override { return std::make_unique<CheddarCheese>(); }
	virtual std::unique_ptr<Tomato> MakeTomato() const override { return std::make_unique<Tomato>(); }
	virtual std::unique_ptr<Lettuce> MakeLettuce() const override { return std::make_unique<Lettuce>(); }
	virtual std::unique_ptr<Sauce> MakeSauce() const override { return std::make_unique<MustardSauce>(); }
};

class HamburgerHouse
{
public:
	HamburgerHouse(std::unique_ptr<HamburgerFactory>&& factory)
		: m_factory(std::move(factory))
	{}

	void ChangeFactory(std::unique_ptr<HamburgerFactory>&& factory) { m_factory = std::move(factory); }

	Hamburger MakeCheeseBurger() const
	{
		std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList;

		ingredientList.push_back(m_factory->MakeBread());
		ingredientList.push_back(m_factory->MakeLettuce());
		ingredientList.push_back(m_factory->MakeSauce());
		ingredientList.push_back(m_factory->MakePatty());
		ingredientList.push_back(m_factory->MakeCheese());
		ingredientList.push_back(m_factory->MakeBread());

		return Hamburger(std::move(ingredientList));
	}

	Hamburger MakeJumboBurger() const
	{
		std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList;

		ingredientList.push_back(m_factory->MakeBread());
		ingredientList.push_back(m_factory->MakeLettuce());
		ingredientList.push_back(m_factory->MakeSauce());
		ingredientList.push_back(m_factory->MakePatty());
		ingredientList.push_back(m_factory->MakeCheese());
		ingredientList.push_back(m_factory->MakeBread());
		ingredientList.push_back(m_factory->MakeLettuce());
		ingredientList.push_back(m_factory->MakeSauce());
		ingredientList.push_back(m_factory->MakePatty());
		ingredientList.push_back(m_factory->MakeCheese());
		ingredientList.push_back(m_factory->MakeBread());

		return Hamburger(std::move(ingredientList));
	}

private:
	std::unique_ptr<HamburgerFactory> m_factory;
};

/*
	Ư�� ��ǰ���� ��Ƽ� ��ǰ �� ���·� �����ϰ�, ��ǰ �� ������ ������ �����Ͽ� �ϰ����� ��Ű�� ���� ���,
		Abstract Factory ������ ��︳�ϴ�.

	������ ��ü�� �����ؾ� �� ��, Builder ���ϰ� Abstract Factory ������ ������� ������ ���� �ֽ��ϴ�.
	����, ��ǰ ������ ��ǰ�� ������ ���������� ������ �ʿ伺�� �ְ�, �� �� ���谡 ������ �ʿ伺�� �ִٸ�,
		Abstract Factory Pattern �� �� ��︳�ϴ�.
*/

int main()
{
	HamburgerHouse macdoria(std::make_unique<BeefHamburgerFactory>());

	std::cout << "======== Beef Based Hamburger House ========" << std::endl;
	std::cout << "* Let's make a cheese burger" << std::endl;
	macdoria.MakeCheeseBurger().Print();
	std::cout << "* Let's make a jumbo burger" << std::endl;
	macdoria.MakeJumboBurger().Print();

	macdoria.ChangeFactory(std::make_unique<PorkHamburgerFactory>());
	std::cout << std::endl;
	std::cout << "======== Pork Based Hamburger House ========" << std::endl;
	std::cout << "* Let's make a cheese burger" << std::endl;
	macdoria.MakeCheeseBurger().Print();
	std::cout << "* Let's make a jumbo burger" << std::endl;
	macdoria.MakeJumboBurger().Print();

	return 0;
}