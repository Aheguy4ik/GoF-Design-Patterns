#include <iostream>
#include <memory>
#include <string>

struct Color
{
    Color(std::uint8_t R, std::uint8_t G, std::uint8_t B)
        : R(R), G(G), B(B)
    {}

    std::uint8_t R, G, B;
};

class Theme
{
public:
    virtual ~Theme() = default;

    virtual std::string Name() const = 0;
    virtual Color WallColor() const = 0;
    virtual Color FloorColor() const = 0;
    virtual Color CeilingColor() const = 0;
};

class WhiteTheme : public Theme
{
public:
    std::string Name() const override { return "White Theme"; }
    Color WallColor() const override { return { 255, 255, 255 }; }
    Color FloorColor() const override { return { 255, 255, 255 }; }
    Color CeilingColor() const override { return { 255, 255, 255 }; }
};

class DarkTheme : public Theme
{
public:
    std::string Name() const override { return "Dark Theme"; }
    Color WallColor() const override { return { 0, 0, 0 }; }
    Color FloorColor() const override { return { 0, 0, 0 }; }
    Color CeilingColor() const override { return { 0, 0, 0 }; }
};

class CustomTheme : public Theme
{
public:
    CustomTheme(std::string name, Color wallColor, Color floorColor, Color ceilingColor)
        : name_(std::move(name)), wallColor_(wallColor), floorColor_(floorColor), ceilingColor_(ceilingColor)
    {}

    std::string Name() const override { return name_; }
    Color WallColor() const override { return wallColor_; }
    Color FloorColor() const override { return floorColor_; }
    Color CeilingColor() const override { return ceilingColor_; }

private:
    std::string name_;
    Color wallColor_, floorColor_, ceilingColor_;
};

class House
{
public:
    explicit House(std::shared_ptr<Theme> theme)
        : theme_(std::move(theme))
    {}
    virtual ~House() = default;

    virtual std::string Name() const = 0;

    void ChangeTheme(const std::shared_ptr<Theme>& theme) 
    {
        std::cout << Name() << " changes theme to '" << theme->Name() << "'." << std::endl;
        theme_ = theme; 
    }

    void ShowDescription() const
    {
        std::cout << Name() << " with theme('" << theme_->Name() << "')." << std::endl;
    }

private:
    std::shared_ptr<Theme> theme_;
};

class OneRoom : public House
{
public:
    explicit OneRoom(const std::shared_ptr<Theme>& theme)
        : House(theme)
    {}

    std::string Name() const override { return "One Room"; }
};

class Apartment : public House
{
public:
    explicit Apartment(const std::shared_ptr<Theme>& theme)
        : House(theme)
    {}

    std::string Name() const override { return "Apartment"; }
};

class Castle : public House
{
public:
    explicit Castle(const std::shared_ptr<Theme>& theme)
        : House(theme)
    {}

    std::string Name() const override { return "Castle"; }
};

/*
    Bridge ������ interface�� implementation�� �и��ϴ� �뵵�� ���˴ϴ�.
    ����ڿ��� ���� ���� ������ ������ �� �ִ� ������ �ֽ��ϴ�. 
    ����, interface�� implementation ������ ���� ���踦 ���� �� �ְ� �ǰ�, 
    ��Ÿ�ӿ� implementation�� �����ϴ� ���� ���������� ���� ������ �ֽ��ϴ�.

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
