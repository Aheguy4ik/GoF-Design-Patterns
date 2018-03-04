#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

class Singleton final
{
public:
    static Singleton& Instance()
    {
        // Thread safety since C++11 (VS2015) - Magic Statics
        static Singleton instance;
        return instance;
    }

    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

private:
    Singleton() { std::cout << "Lazy creation!" << std::endl; }
};

void Test()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    auto& a = Singleton::Instance();
    std::cout << &a << std::endl;
}

/*
    Singleton�� ���� ���� ���ڰ� (Ȥ�� �����ϰ� ������ڰ�) �������� �ֽ��ϴ�.
    ���� : https://softwareengineering.stackexchange.com/questions/40373/so-singletons-are-bad-then-what
*/

int main()
{
    std::cout << "Start!" << std::endl;
    std::vector<std::thread> vec;
    for (int i = 0; i < 800; ++i)
        vec.emplace_back(Test);
    for (auto &elem : vec)
        elem.join();
}
