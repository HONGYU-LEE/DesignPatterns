#pragma once
#include"Subject.hpp"
#include<iostream>
/*
class Proxy : public Subject
{
public:
    Proxy(Subject* subject)
        : _subject(subject)
    {}

    void rentingHouse() override
    {
        _subject->rentingHouse();                      //代理行为
        std::cout << "中介代替客户去租房" << std::endl; //新增的代理逻辑
    }

private:
    Subject* _subject;  //代理的客户
};
*/

class Proxy : public Tenant
{
public:
    Proxy(Tenant* client)
        : _client(client)
    {}

    void rentingHouse() override
    {
        _client->rentingHouse();      //代理行为
        std::cout << "中介代替客户去租房，并收取佣金" << std::endl; //新增的代理逻辑
    }

private:
    Tenant* _client;  //代理的客户，需要让目标知道租房的人是谁
};