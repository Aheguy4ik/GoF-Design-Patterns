#include <iostream>
#include <memory>
#include <string>

class NoRestrictionStrategy
{
public:
    bool Check(std::string const& text) const
    {
        return true;
    }
};

class CurseRestrictionStrategy
{
public:
    bool Check(std::string const& text) const
    {
        auto npos = std::string::npos;

        if (text.find("fuck") != npos || text.find("shit") != npos)
        {
            return false;
        }
        
        return true;
    }
};

class LengthRestrictionStrategy
{
public:
    LengthRestrictionStrategy(std::size_t minLength, std::size_t maxLength)
        : minLength_(minLength), maxLength_(maxLength)
    {}

    bool Check(std::string const& text) const
    {
        auto length = text.length();

        if (length < minLength_ || length > maxLength_)
        {
            return false;
        }

        return true;
    }

private:
    std::size_t minLength_, maxLength_;
};

/*
    ��Ÿ�ӿ� ������ ������ �ʿ䰡 ���� ���, ���ø��� Ȱ���Ͽ� �������� ������
    binding �ǵ��� �� �� �ֽ��ϴ�.
    �� ���, ��� �������� ����������, ���� �Լ� ȣ�⿡ ���� overhead��
    �߻����� �ʴ� ������ �ֽ��ϴ�.
*/
template <typename TextRestrictionStrategy>
class TextRestricter
{
public:
    explicit TextRestricter(TextRestrictionStrategy&& strategy)
        : strategy_(std::move(strategy))
    {}

    void PrintText(std::string const& text) const
    {
        if (strategy_.Check(text))
        {
            std::cout << text << std::endl;
        }
        else
        {
            std::cout << "** Given text was restricted. **" << std::endl;
        }
    }

    bool ConcatText(std::string const& text_1,
                    std::string const& text_2,
                    std::string& concatedText) const
    {
        concatedText = text_1 + text_2;

        if (strategy_.Check(concatedText))
        {
            return true;
        }
        else
        {
            concatedText.clear();
            return false;
        }
    }

private:
    TextRestrictionStrategy strategy_;
};

template <typename TextRestrictionStrategy>
auto MakeTextRestrictor(TextRestrictionStrategy&& strategy)
    -> TextRestricter<TextRestrictionStrategy>
{
    return TextRestricter<TextRestrictionStrategy>(std::move(strategy));
}

template <typename TextRestricter>
void ConcatAndPrintText(TextRestricter const& textRestricter,
                        std::string const& text_1,
                        std::string const& text_2)
{
    std::string concatedText;
    
    if (textRestricter.ConcatText(text_1, text_2, concatedText))
    {
        std::cout << concatedText << std::endl;
    }
    else
    {
        std::cout << "** Concated text was restricted. **" << std::endl;
    }
}

template <typename TextRestricter>
void Test(TextRestricter const& textRestricter)
{
    textRestricter.PrintText("fuck");
    textRestricter.PrintText("looooooooooooooooooooooooooong text");
    ConcatAndPrintText(textRestricter, "hi sh", "it bye");
}

int main()
{
    std::cout << "[*] Test with 'NoRestrictionStrategy'." << std::endl;
    Test(MakeTextRestrictor(NoRestrictionStrategy()));

    std::cout << "\n[*] Test with 'CurseRestrictionStrategy'." << std::endl;
    Test(MakeTextRestrictor(CurseRestrictionStrategy()));

    std::cout << "\n[*] Test with 'LengthRestrictionStrategy'." << std::endl;
    Test(MakeTextRestrictor(LengthRestrictionStrategy(0, 8)));
}
