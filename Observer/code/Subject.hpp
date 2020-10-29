#pragma once
#include"Observer.hpp"

class Subject
{
public:
    virtual ~Subject() = default;
    virtual void registerObserver(Observer*) = 0;   //注册观察者
    virtual void removeObserver(Observer*) = 0;     //移除观察者
    virtual void notifyObservers() = 0;             //通知所有观察者
};