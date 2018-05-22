#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../../AccessKey.h"

class Observable;

// ������
class Observer
{
public:
    virtual ~Observer() = default;

    virtual void Update(Observable& observable, const void* dataKey) = 0;

protected:
    design::AccessKey<Observer> GetAccessKey() { return {}; }
};

// ���� ���
class Observable
{
public:
    virtual ~Observable() = 0;

    void Attach(Observer& observer)
    {
        observerSet_.insert(&observer);
    }

    void Detach(Observer& observer)
    {
        observerSet_.erase(&observer);
    }

    void Notify(const void* dataKey)
    {
        for (auto& observer : observerSet_)
        {
            observer->Update(*this, dataKey);
        }
    }

private:
    std::set<Observer*> observerSet_;
};

inline Observable::~Observable() = default;

class ChatRoom : public Observable
{
public:
    explicit ChatRoom(std::string name)
        : name_(std::move(name))
    {}

    void SendMessage(std::string const& message)
    {
        Notify(&message);
    }

    std::string GetName() const { return name_; }

    std::string const& GetDataFromKey(design::AccessKey<Observer>,
                                      const void* dataKey)
    {
        assert(dataKey);
        return *reinterpret_cast<std::string const*>(dataKey);
    }

private:
    const std::string name_;
};

class User : public Observer
{
public:
    explicit User(std::string name)
        : name_(std::move(name))
    {}

    void Update(Observable& observable, const void* dataKey) override
    {
        auto& chatRoom = static_cast<ChatRoom&>(observable);
        assert(chatRoomSet_.find(&chatRoom) != std::end(chatRoomSet_));

        std::cout << "[" << name_ << "][" << chatRoom.GetName() << "] " <<
            chatRoom.GetDataFromKey(GetAccessKey(), dataKey) << std::endl;
    }

    void JoinChatRoom(ChatRoom& chatRoom)
    {
        chatRoomSet_.insert(&chatRoom);
        chatRoom.Attach(*this);
    }

private:
    std::string name_;
    std::set<ChatRoom*> chatRoomSet_;
};

/*
    Observer Pattern�� � ��ü�� ���°� ���� ��, �� ��ü�� �������� ���� �ٸ�
    ��ü���� �� ��ȭ�� �����ް� �ڵ����� ���ŵ� �� �ֵ��� ���ݴϴ�.
*/
int main()
{
    ChatRoom chatRoom_1("ChatRoom_1"), chatRoom_2("ChatRoom_2");
    User user_1("User_1"), user_2("User_2"), user_3("User_3");

    user_1.JoinChatRoom(chatRoom_1);
    user_2.JoinChatRoom(chatRoom_2);
    user_3.JoinChatRoom(chatRoom_1);
    user_3.JoinChatRoom(chatRoom_2);

    chatRoom_1.SendMessage("Hi, nice to meet you!");
    chatRoom_2.SendMessage("I'm Taeguk Kwon!");
}
