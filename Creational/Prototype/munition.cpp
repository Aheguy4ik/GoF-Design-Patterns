#include <memory>
#include <vector>
#include <string>
#include <iostream>

struct Weapon 
{ 
	virtual std::string Name() const = 0; 
	virtual std::unique_ptr<Weapon> Clone() const = 0;
};

struct Knife : public Weapon 
{
	virtual std::string Name() const override { return "Knife"; }
	virtual std::unique_ptr<Weapon> Clone() const override { return std::make_unique<Knife>(*this); }
};
struct Gun : public Weapon 
{
	virtual std::string Name() const override { return "Gun"; }
	virtual std::unique_ptr<Weapon> Clone() const override { return std::make_unique<Gun>(*this); }
};
struct Missile : public Weapon
{
	virtual std::string Name() const override { return "Missile"; }
	virtual std::unique_ptr<Weapon> Clone() const override { return std::make_unique<Missile>(*this); }
};

struct Vehicle 
{ 
	virtual std::string Name() const = 0;
	virtual std::unique_ptr<Vehicle> Clone() const = 0;
};

struct Horse : public Vehicle 
{ 
	virtual std::string Name() const override { return "Horse"; }
	virtual std::unique_ptr<Vehicle> Clone() const { return std::make_unique<Horse>(*this); }
};
struct Tank : public Vehicle
{ 
	virtual std::string Name() const override { return "Tank"; }
	virtual std::unique_ptr<Vehicle> Clone() const { return std::make_unique<Tank>(*this); }
};
struct Spaceship : public Vehicle 
{ 
	virtual std::string Name() const override { return "Spaceship"; }
	virtual std::unique_ptr<Vehicle> Clone() const { return std::make_unique<Spaceship>(*this); }
};

class MunitionStore
{
public:
	MunitionStore(std::unique_ptr<Weapon>&& weapon, std::unique_ptr<Vehicle>&& vehicle)
		: m_weapon(std::move(weapon)), m_vehicle(std::move(vehicle))
	{}

	void RegisterWeapon(std::unique_ptr<Weapon>&& weapon) { m_weapon = std::move(weapon); }
	void RegisterVehicle(std::unique_ptr<Vehicle>&& vehicle) { m_vehicle = std::move(vehicle); }

	std::unique_ptr<Weapon> MakeWeapon() const { return m_weapon->Clone(); }
	std::unique_ptr<Vehicle> MakeVehicle() const { return m_vehicle->Clone(); }

private:
	std::unique_ptr<Weapon> m_weapon;
	std::unique_ptr<Vehicle> m_vehicle;
};

void PrintStore(const MunitionStore& store)
{
	std::cout << "---- Infomation ----" << std::endl;
	std::cout << "Weapon  : " << store.MakeWeapon()->Name() << std::endl;
	std::cout << "Vehicle : " << store.MakeVehicle()->Name() << std::endl;
	std::cout << "--------------------" << std::endl;
}

void ChangeWeapon(MunitionStore& store, std::unique_ptr<Weapon>&& weapon)
{
	std::cout << "Change Weapon to " << weapon->Name() << std::endl;
	store.RegisterWeapon(std::move(weapon));
}

void ChangeVehicle(MunitionStore& store, std::unique_ptr<Vehicle>&& vehicle)
{
	std::cout << "Change Vehicle to " << vehicle->Name() << std::endl;
	store.RegisterVehicle(std::move(vehicle));
}

/*
	Prototype Pattern�� ���ο� Ŭ���� ������ ���� �� �ʴ� ������ �ֽ��ϴ�.
	�׷���, ������ �����ϴ� ��ǰ Ŭ���� ������ Clone ������ �����ؾ��մϴ�. (���� �װ��� �Ұ����� ���, ���������� ����� �� �����ϴ�.)
	
	����, ��Ÿ�ӿ� ���ο� ��ǰ�� �߰��� �� �ְ�, ��ü�� ������ �پ�ȭ�����ν� ���ο� ��ǰ�� ���� �� �ֽ��ϴ�.

	Factory Method Pattern(Ȥ�� Abstract Factory Pattern) ���� ���� ����Ŭ���� ��������� Ŭ���� ������ ��������� ������ �ֽ��ϴ�.
	�ݸ鿡, Prototype Pattern�� ��ǰ Ŭ���� ������ �����ϴ� ���, ���ο� Ŭ���� ������ ��������� ������ �����ϴ�.
*/

int main()
{
	MunitionStore store(std::make_unique<Knife>(), std::make_unique<Horse>());

	std::cout << "==== Munition Store ====" << std::endl;
	PrintStore(store);

	ChangeWeapon(store, std::make_unique<Gun>());
	PrintStore(store);

	ChangeVehicle(store, std::make_unique<Tank>());
	PrintStore(store);

	ChangeWeapon(store, std::make_unique<Missile>());
	ChangeVehicle(store, std::make_unique<Spaceship>());
	PrintStore(store);
}