#include <iostream>

class PizzaStore
{
public:
    virtual ~PizzaStore() = default;

    void MakePizza()
    {
        MakeDough_();
        PutTopping_();
        BakePizza_();
    }

private:
    virtual void MakeDough_() = 0;
    virtual void PutTopping_() = 0;
    virtual void BakePizza_() = 0;
};

class DeliciousPizzaStore : public PizzaStore
{
private:
    void MakeDough_() override
    {
        std::cout << "Make delicious dough!" << std::endl;
    }

    void PutTopping_() override
    {
        std::cout << "Put delicious topping!" << std::endl;
    }

    void BakePizza_() override
    {
        std::cout << "Bake pizza in an expensive oven!" << std::endl;
    }
};

class PoorPizzaStore : public PizzaStore
{
private:
    void MakeDough_() override
    {
        std::cout << "Make poor dough!" << std::endl;
    }

    void PutTopping_() override
    {
        std::cout << "Put poor topping!" << std::endl;
    }

    void BakePizza_() override
    {
        std::cout << "Bake pizza in a cheap oven!" << std::endl;
    }
};

/*
    Template Method Pattern�� ��ü�� ���꿡�� �˰����� ���븸�� �����ϰ�,
    �� �ܰ迡�� ������ ��ü�� ó���� ����Ŭ���� ������ �̷�� �����Դϴ�.
    ��, "������ �ʴ� ��" ���� ���� "���ϴ� ��" �� �����Լ� ������� �и��ϴ� ���Դϴ�.

    �� ���ϰ��� �ٸ���, Strategy Pattern�� "������ �ʴ� ��" ���� ���� "���ϴ� ��" ��
    �ٸ� Ŭ������ �и��մϴ�. Strategy Pattern�� ��Ÿ�ӿ� ��ü���� ó�� �����
    ������ �� �ִ� �ݸ鿡 Template Method Pattern�� ��Ÿ�ӿ� ��ü�� ó�� �����
    ������ �� �����ϴ�.

    Template Method Pattern�� C++���� �����ϴ� ������� NVI idiom �� CRTP idiom ��
    �ֽ��ϴ�. �� �ҽ��ڵ忡���� NVI idiom �� �̿��Ͽ����ϴ�.
*/
int main()
{
    DeliciousPizzaStore deliciousPizzaStore;
    PoorPizzaStore poorPizzaStore;

    deliciousPizzaStore.MakePizza();
    std::cout << "----------------------------" << std::endl;
    poorPizzaStore.MakePizza();
}
