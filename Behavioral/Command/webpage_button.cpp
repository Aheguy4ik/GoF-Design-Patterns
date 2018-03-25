#include <iostream>
#include <string>

/* Receiver (���� ��û�� ó���� å���� ���� ��ü) */
class WebPageManager
{
public:
    void ChangeWebPage(std::string const& webPage)
    {
        std::cout << "Change web page to " << webPage << "." << std::endl;
    }
};

class Command
{
public:
    virtual ~Command() = default;

    virtual void Execute() = 0;
};

class ChangeWebPageCommand : public Command
{
public:
    ChangeWebPageCommand(WebPageManager& pageManager, std::string webPage)
        : pageManager_(pageManager), webPage_(std::move(webPage))
    {}

    void Execute() override
    {
        pageManager_.ChangeWebPage(webPage_);
    }

private:
    WebPageManager& pageManager_;
    std::string webPage_;
};

/* ���ø��� Ȱ���ؼ�, ������ Receiver���� ����� ������ �� �ֵ��� �Ѵ�. */
template <typename Receiver>
class GenericCommand : public Command
{
public:
    explicit GenericCommand(Receiver&& receiver)
        : receiver_(std::move(receiver))
    {}

    void Execute() override
    {
        receiver_();
    }

private:
    Receiver receiver_;
};

template <typename Receiver>
auto MakeGenericCommand(Receiver&& receiver)
    -> GenericCommand<Receiver>
{
    return GenericCommand<Receiver>(std::move(receiver));
}

class Button
{
public:
    explicit Button(Command* command)
        : command_(command)
    {}

    void Click()
    {
        if (command_)
        {
            command_->Execute();
        }
    }

    Command* ChangeCommand(Command* command)
    {
        Command* old = command_;
        command_ = command;
        return old;
    }

private:
    Command* command_;
};

/*
    Command Pattern�� ��û ��ü�� ĸ��ȭ�ϱ� ���� ����մϴ�.
    Invoker (����� ��û�ϴ� ��) �� Receiver (���� ����� �����ϴ� ��) �� ���� ���
    ��ü���� ������ �˰� ���� �ʾƵ� �˴ϴ�. ��, Invoker�� Receiver�� ������ ���ִ�
    ȿ���� �ֽ��ϴ�.
    Receiver�� ���� ��ü���� ������ �������� Concrete Command Ŭ������ ���� �ǰ�,
    �߻�ȭ�� ���̽� Ŭ������ Command Ŭ������ Receiver�� ���� �������� ������ �ʽ��ϴ�.
    ����, Invoker ���� Receiver�� ���� �������� ������ ���� ����� ��û�� �� �ְ� �˴ϴ�.
*/

int main()
{
    WebPageManager webPageManager;
    ChangeWebPageCommand changeWebPageCommand(webPageManager, "http://taeguk.me");

    Button button(&changeWebPageCommand);
    button.Click();

    auto genericCommand = MakeGenericCommand(
        []() -> void
        {
            std::cout << "This is generic command." << std::endl;
        });

    button.ChangeCommand(&genericCommand);
    button.Click();
}
