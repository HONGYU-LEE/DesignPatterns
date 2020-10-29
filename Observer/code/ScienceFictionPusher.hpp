#include"Subject.hpp"
#include"Observer.hpp"

#include<iostream>
#include<string>
#include<unordered_set>

class ScienceFictionPusher : public Subject
{
public:
    void registerObserver(Observer* observer) override
    {
        _observers.insert(observer);
    }

    void removeObserver(Observer* observer) override
    {
        _observers.erase(observer);
    }

    void notifyObservers() override
    {
        for(const auto& ob : _observers)
        {
            ob->update(_url, _title, _desc);
        }
    }

    void newPush()
    {
        notifyObservers();
    }

    void setNewFiction(const std::string& url, const std::string& title, const std::string& desc)
    {
        _url = url;
        _title = title;
        _desc = desc;
        newPush();
    }

private:
    std::string _url;    //小说链接
    std::string _title;  //小说名
    std::string _desc;   //小说简介
    std::unordered_set<Observer*> _observers;   //订阅的粉丝
};