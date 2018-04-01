#include <iostream>
#include <stack>
#include <vector>

// Mementor Ŭ����
class Snapshot
{
private:
    friend class VirtualMachine;

    // ���ø� ���� �����ϰ� ������, �����δ� �ܺο� ����Ǹ� �ȵǴ� ���� ���� ��������
    // ������� ���Դϴ�.
    struct State
    {
        std::uint16_t cpuCount{ 1 };
        std::uint64_t ramSize{ 500 };
        // ...
    };

    explicit Snapshot(State const& state)
        : state_(state)
    {}

    State state_;
};

// Originator Ŭ����
class VirtualMachine
{
public:
    std::uint16_t GetCpuCount() const { return state_.cpuCount; }
    std::uint64_t GetRamSize() const { return state_.ramSize; }

    std::uint16_t ChangeCpuCount(std::uint16_t cpuCount)
    {
        auto old = state_.cpuCount;
        state_.cpuCount = cpuCount;
        return old;
    }

    std::uint64_t ChangeRamSize(std::uint64_t ramSize)
    {
        auto old = state_.ramSize;
        state_.ramSize = ramSize;
        return old;
    }

    void ResetToSnapshot(Snapshot const& snapshot)
    {
        state_ = snapshot.state_;
    }

    Snapshot TakeSnapshot() const
    {
        return Snapshot(state_);
    }

private:
    Snapshot::State state_;
};

void PrintVmInfo(VirtualMachine const& vm)
{
    std::cout << "----------------" << std::endl;
    std::cout << "Cpu Count : " << vm.GetCpuCount() << std::endl;
    std::cout << "Ram Size  : " << vm.GetRamSize() << std::endl << std::endl;
}

/*
    Memento Pattern�� ĸ��ȭ�� �������� ���� ä, � ��ü�� ���� ���¸� �����ص����μ�,
    ���߿� �� ��ü�� �ٽ� ���� ���·� �ǵ��� �� �� �ֵ��� ���ݴϴ�.
    �ٽ�����Ʈ��, Originator ��ü�� ���� ���¸� ��� �ִ� Memento ��ü�� �ܺο���
    �����Ѵٴ� ���Դϴ�.
    ����, Originator �� ��� ���� �������� �����Ѵٸ�, Originator �� �ʹ� ���������� �˴ϴ�.
    Memento Pattern�� ���� ������ ��� �ִ� ��ü���� �ܺο��� �����ϰ� �����μ�,
    Originator�� �ܼ��ϰ� ����ϴ�.
    �׷�����, �������� ���� ������ ���ؼ��� �ܺο��� ������ �� ����, ���� Originator������
    ������ �� �ֵ��� �մϴ�. (C++������ �̸� ����, friend keyword �� Ȱ���մϴ�.)
*/

int main()
{
    VirtualMachine vm;

    PrintVmInfo(vm);
    auto snapshot_1 = vm.TakeSnapshot();

    vm.ChangeCpuCount(16);
    vm.ChangeRamSize(1500);
    PrintVmInfo(vm);
    auto snapshot_2 = vm.TakeSnapshot();

    vm.ResetToSnapshot(snapshot_1);
    PrintVmInfo(vm);

    vm.ChangeCpuCount(4);
    vm.ChangeRamSize(6000);
    PrintVmInfo(vm);

    vm.ResetToSnapshot(snapshot_2);
    PrintVmInfo(vm);
}
