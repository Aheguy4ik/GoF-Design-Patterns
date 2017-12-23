#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct HamburgerIngredient { virtual ~HamburgerIngredient() = default; virtual std::string Name() const = 0; };

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

class Hamburger final
{
public:
    explicit Hamburger(std::vector<std::unique_ptr<HamburgerIngredient>>&& ingredientList)
        : ingredientList_(std::move(ingredientList))
    {}

    void Print() const
    {
        std::cout << "----------" << std::endl;
        for (const auto& ingredient : ingredientList_)
            std::cout << ingredient->Name() << std::endl;
        std::cout << "----------" << std::endl;
    }

private:
    std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList_;
};

class HamburgerBuilder
{
public:
    virtual ~HamburgerBuilder() = default;

    virtual void Initialize() = 0;

    virtual void BuildBread() = 0;
    virtual void BuildPatty() = 0;
    virtual void BuildCheese() = 0;
    virtual void BuildTomato() = 0;
    virtual void BuildLettuce() = 0;
    virtual void BuildSauce() = 0;

    virtual Hamburger GetHamburger() = 0;
};

class BeefHamburgerBuilder : public HamburgerBuilder
{
public:
    virtual void Initialize() override { ingredientList_.clear(); }

    virtual void BuildBread() override { ingredientList_.push_back(std::make_unique<LightBread>()); }
    virtual void BuildPatty() override { ingredientList_.push_back(std::make_unique<BeefPatty>()); }
    virtual void BuildCheese() override { ingredientList_.push_back(std::make_unique<MozzarellaCheese>()); }
    virtual void BuildTomato() override { ingredientList_.push_back(std::make_unique<Tomato>()); }
    virtual void BuildLettuce() override { ingredientList_.push_back(std::make_unique<Lettuce>()); }
    virtual void BuildSauce() override { ingredientList_.push_back(std::make_unique<GarlicSauce>()); }

    virtual Hamburger GetHamburger() override 
    { 
        Hamburger hamburger(std::move(ingredientList_));
        return hamburger;
    };

private:
    std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList_;
};

class PorkHamburgerBuilder : public HamburgerBuilder
{
public:
    virtual void Initialize() override { ingredientList_.clear(); }

    virtual void BuildBread() override { ingredientList_.push_back(std::make_unique<SaltyBread>()); }
    virtual void BuildPatty() override { ingredientList_.push_back(std::make_unique<PorkPatty>()); }
    virtual void BuildCheese() override { ingredientList_.push_back(std::make_unique<CheddarCheese>()); }
    virtual void BuildTomato() override { ingredientList_.push_back(std::make_unique<Tomato>()); }
    virtual void BuildLettuce() override { ingredientList_.push_back(std::make_unique<Lettuce>()); }
    virtual void BuildSauce() override { ingredientList_.push_back(std::make_unique<MustardSauce>()); }

    virtual Hamburger GetHamburger() override
    {
        Hamburger hamburger(std::move(ingredientList_));
        return hamburger;
    };

private:
    std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList_;
};

class HamburgerHouse final
{
public:
    explicit HamburgerHouse(std::unique_ptr<HamburgerBuilder>&& builder)
        : builder_(std::move(builder))
    {}

    void ChangeBuilder(std::unique_ptr<HamburgerBuilder>&& builder) { builder_ = std::move(builder); }

    Hamburger MakeCheeseBurger()
    {
        builder_->Initialize();

        builder_->BuildBread();
        builder_->BuildLettuce();
        builder_->BuildSauce();
        builder_->BuildPatty();
        builder_->BuildCheese();
        builder_->BuildBread();

        return builder_->GetHamburger();
    }

    Hamburger MakeJumboBurger()
    {
        builder_->Initialize();

        builder_->BuildBread();
        builder_->BuildLettuce();
        builder_->BuildSauce();
        builder_->BuildPatty();
        builder_->BuildCheese();
        builder_->BuildBread();
        builder_->BuildLettuce();
        builder_->BuildSauce();
        builder_->BuildPatty();
        builder_->BuildCheese();
        builder_->BuildBread();

        return builder_->GetHamburger();
    }

private:
    std::unique_ptr<HamburgerBuilder> builder_;
};

/*
    ���� ��ü�� ���� �˰���� �ռ��Ǵ� ��� ��ü���� ���� ����� �������̰�,
        �ռ������� ����� �Ͱ�, ������ ��ü�� �ܰ������� �����ϰ� ���� ��쿡,
        Builder Pattern�� ��︳�ϴ�.

    ������ ��ü�� �����ؾ� �� ��, Builder ���ϰ� Abstract Factory ������ ������� ������ ���� �ֽ��ϴ�.
    ����, ��������(��� ��ü���� �ռ�����)���� ����� �Ͱ�, ������ ��ü�� �ϼ��� �� ��ȯ�Ǿ�� �ϴ� �����,
        Builder Pattern �� �� ��︳�ϴ�.
*/

int main()
{
    HamburgerHouse macdoria(std::make_unique<BeefHamburgerBuilder>());

    std::cout << "======== Beef Based Hamburger House ========" << std::endl;
    std::cout << "* Let's make a cheese burger" << std::endl;
    macdoria.MakeCheeseBurger().Print();
    std::cout << "* Let's make a jumbo burger" << std::endl;
    macdoria.MakeJumboBurger().Print();

    macdoria.ChangeBuilder(std::make_unique<PorkHamburgerBuilder>());
    std::cout << std::endl;
    std::cout << "======== Pork Based Hamburger House ========" << std::endl;
    std::cout << "* Let's make a cheese burger" << std::endl;
    macdoria.MakeCheeseBurger().Print();
    std::cout << "* Let's make a jumbo burger" << std::endl;
    macdoria.MakeJumboBurger().Print();

    return 0;
}
