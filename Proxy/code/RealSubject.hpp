#pragma once
#include"Subject.hpp"

/*
class RealSubject : public Subject
{
public:
    void rentingHouse() override
    {
        std::cout << "客户需要租房！" << std::endl;
    }
};
*/
class XiaoMing: public Tenant
{
public:
    void rentingHouse() override
    {
        std::cout << "小明需要租房！" << std::endl;
    }
};