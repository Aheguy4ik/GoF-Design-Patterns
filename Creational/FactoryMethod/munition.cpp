#include <memory>
#include <vector>
#include <string>
#include <iostream>

struct Weapon { virtual std::string Name() const = 0; };
struct Vehicle { virtual std::string Name() const = 0; };

struct Knife : public Weapon { virtual std::string Name() const override { return "Knife"; } };
struct Gun : public Weapon { virtual std::string Name() const override { return "Gun"; } };
struct Missile : public Weapon { virtual std::string Name() const override { return "Missile"; } };

struct Horse : public Vehicle { virtual std::string Name() const override { return "Horse"; } };
struct Tank : public Vehicle { virtual std::string Name() const override { return "Tank"; } };
struct Spaceship : public Vehicle { virtual std::string Name() const override { return "Spaceship"; } };


struct WeaponCreator { virtual std::unique_ptr<Weapon> MakeWeapon() const = 0; };
struct VehicleCreator { virtual std::unique_ptr<Vehicle> MakeVehicle() const = 0; };

struct KnifeCreator : public WeaponCreator
	{ virtual std::unique_ptr<Weapon> MakeWeapon() const override { return std::make_unique<Knife>(); } };
struct GunCreator : public WeaponCreator
	{ virtual std::unique_ptr<Weapon> MakeWeapon() const override { return std::make_unique<Gun>(); } };
struct MissileCreator : public WeaponCreator
	{ virtual std::unique_ptr<Weapon> MakeWeapon() const override { return std::make_unique<Missile>(); } };

struct HorseCreator : public VehicleCreator
	{ virtual std::unique_ptr<Vehicle> MakeVehicle() const override { return std::make_unique<Horse>(); } };
struct TankCreator : public VehicleCreator
	{ virtual std::unique_ptr<Vehicle> MakeVehicle() const override { return std::make_unique<Tank>(); } };
struct SpaceshipCreator : public VehicleCreator
	{ virtual std::unique_ptr<Vehicle> MakeVehicle() const override { return std::make_unique<Spaceship>(); } };


class MunitionStore
{
public:
	MunitionStore(std::unique_ptr<WeaponCreator>&& weaponCreator, std::unique_ptr<VehicleCreator>&& vehicleCreator)
		: m_weaponCreator(std::move(weaponCreator)), m_vehicleCreator(std::move(vehicleCreator))
	{}

	void ChangeWeaponCreator(std::unique_ptr<WeaponCreator>&& creator) { m_weaponCreator = std::move(creator); }
	void ChangeVehicleCreator(std::unique_ptr<VehicleCreator>&& creator) { m_vehicleCreator = std::move(creator); }

	void Print() const
	{
		std::cout << "---- Infomation ----" << std::endl;
		std::cout << "Weapon  : " << m_weaponCreator->MakeWeapon()->Name() << std::endl;
		std::cout << "Vehicle : " << m_vehicleCreator->MakeVehicle()->Name() << std::endl; 
		std::cout << "--------------------" << std::endl;
		std::cout << std::endl;
	}

private:
	std::unique_ptr<WeaponCreator> m_weaponCreator;
	std::unique_ptr<VehicleCreator> m_vehicleCreator;
};

/*
	Factory Method Pattern�� ��ǰ Ŭ���� ������ �������� �ʰ�, �ս��� ������ �� �ִ� ������ �ֽ��ϴ�. 
	(�������� Ŭ���� ������ �����ϴ� ������ ����մϴ�.)
	�׷���, ��ǰ Ŭ���� ����� �����Ǵ� ���丮 Ŭ���� ������ ��������鼭, 
	��ǰ�� �߰��� ������ ���丮 Ŭ������ �߰��Ǿ�� �ϸ�, ���� Ŭ�������� �������� �Ǵ� ������ �ֽ��ϴ�.
*/

int main()
{
	MunitionStore store(std::make_unique<KnifeCreator>(), std::make_unique<HorseCreator>());

	std::cout << "==== Munition Store ====" << std::endl;
	store.Print();

	store.ChangeWeaponCreator(std::make_unique<GunCreator>());
	store.Print();

	store.ChangeVehicleCreator(std::make_unique<TankCreator>());
	store.Print();

	store.ChangeWeaponCreator(std::make_unique<MissileCreator>());
	store.ChangeVehicleCreator(std::make_unique<SpaceshipCreator>());
	store.Print();
}