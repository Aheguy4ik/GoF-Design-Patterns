#include <memory>
#include <string>
#include <iostream>

struct Color
{
	Color(std::uint8_t R, std::uint8_t G, std::uint8_t B)
		: R(R), G(G), B(B)
	{}
	std::uint8_t R, G, B;
};

struct Theme
{
	virtual std::string Name() const = 0;
	virtual Color WallColor() const = 0;
	virtual Color FloorColor() const = 0;
	virtual Color CeilingColor() const = 0;
};

struct WhiteTheme : public Theme
{
	virtual std::string Name() const override { return "White Theme"; }
	virtual Color WallColor() const override { return Color(255, 255, 255); }
	virtual Color FloorColor() const override { return Color(255, 255, 255); }
	virtual Color CeilingColor() const override { return Color(255, 255, 255); }
};

struct DarkTheme : public Theme
{
	virtual std::string Name() const override { return "Dark Theme"; }
	virtual Color WallColor() const override { return Color(0, 0, 0); }
	virtual Color FloorColor() const override { return Color(0, 0, 0); }
	virtual Color CeilingColor() const override { return Color(0, 0, 0); }
};

struct CustomTheme : public Theme
{
	CustomTheme(std::string name, Color wallColor, Color floorColor, Color ceilingColor)
		: m_name(name), m_wallColor(wallColor), m_floorColor(floorColor), m_ceilingColor(ceilingColor)
	{}

	virtual std::string Name() const override { return m_name; }
	virtual Color WallColor() const override { return m_wallColor; }
	virtual Color FloorColor() const override { return m_floorColor; }
	virtual Color CeilingColor() const override { return m_ceilingColor; }

private:
	std::string m_name;
	Color m_wallColor, m_floorColor, m_ceilingColor;
};

class House
{
public:
	House(const std::shared_ptr<Theme>& theme)
		: m_theme(theme)
	{}

	virtual std::string Name() const = 0;
	virtual void ShowDescription() const = 0;
	void ChangeTheme(const std::shared_ptr<Theme>& theme) 
	{
		std::cout << Name() << " changes theme to '" << theme->Name() << "'." << std::endl;
		m_theme = theme; 
	}

protected:
	const std::shared_ptr<Theme>& GetTheme() const { return m_theme; }

private:
	std::shared_ptr<Theme> m_theme;
};

class OneRoom : public House
{
public:
	OneRoom(const std::shared_ptr<Theme>& theme)
		: House(theme)
	{}

	virtual std::string Name() const override { return "One Room"; }
	virtual void ShowDescription() const override
	{
		auto theme = GetTheme();
		std::cout << Name() << " with theme('" << theme->Name() << "')." << std::endl;
	};
};

class Apartment : public House
{
public:
	Apartment(const std::shared_ptr<Theme>& theme)
		: House(theme)
	{}

	virtual std::string Name() const override { return "Apartment"; }
	virtual void ShowDescription() const override
	{
		auto theme = GetTheme();
		std::cout << Name() << " with theme('" << theme->Name() << "')." << std::endl;
	};
};

class Castle : public House
{
public:
	Castle(const std::shared_ptr<Theme>& theme)
		: House(theme)
	{}

	virtual std::string Name() const override { return "Castle"; }
	virtual void ShowDescription() const override
	{
		auto theme = GetTheme();
		std::cout << Name() << " with theme('" << theme->Name() << "')." << std::endl;
	};
};

/*
	Bridge Pattern�� �� ���� Ŭ���� ������ �и���ų �� �ִ� ������ �ֽ��ϴ�.
	����, �� �������� bridge ������ ������� �ʾҴٸ�,

           House
             |
   --------------------
   |         |        |
OneRoom  Apartment  Castle
   |         |        |
  ...       ...   ---------------------------
                  |            |            |
             WhiteCastle  DarkCastle  CustomCastle

	�� ���� House Ŭ���� ������ ��û���� Ŀ���� ���Դϴ�.
	���� bridge ������ �̿������μ�, House Ŭ���� ����� Theme Ŭ���� ������ �и��ǰ� �ǰ�,
	�̿� ���� House ����� Theme ������ ���������� Ȯ���� �� �ֽ��ϴ�.
	����, ��Ÿ�ӿ� theme�� �����ϴ� ���� ����������, 
	������ theme�� ���� ���� house���� �����ϴ� ���� ���������ϴ�.

	Bridge ������ interface�� implementation�� �и��ϴ� �뵵�ε� ��밡���մϴ�.
	�� ���, ����ڿ��� ���� ���� ������ ������ �� �ִ� ������ �ֽ��ϴ�. 
	����, interface�� implementation ������ ���� ���踦 ���� �� �ְ� �ǰ�, 
	��Ÿ�ӿ� implementation�� �����ϴ� ���� ���������� ���� ������ �ֽ��ϴ�.
*/

int main()
{
	OneRoom oneRoom(std::make_shared<DarkTheme>());
	oneRoom.ShowDescription();
	oneRoom.ChangeTheme(std::make_shared<WhiteTheme>());
	oneRoom.ShowDescription();

	Apartment apartment(std::make_shared<WhiteTheme>());
	apartment.ShowDescription();

	auto customTheme = std::make_shared<CustomTheme>("My Custom Theme", 
		Color(12, 34, 56), Color(78, 90, 12), Color(34, 56, 78));

	Castle castle(customTheme);
	castle.ShowDescription();
	
	apartment.ChangeTheme(customTheme);
	apartment.ShowDescription();
}