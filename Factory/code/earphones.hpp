#pragma once

#include<string>
#include<iostream>

class Earphtones
{
public:
    virtual ~Earphtones() = default;

    void showMessage() const
    {
        std::cout << "耳机名：" << _name << "\n" << std::endl;
    }

    virtual void test()
    {
        std::cout << "正在对耳机进行测试...." << std::endl;
    }

    virtual void packing()
    {
        std::cout << "正在对耳机处理...." << std::endl;
    }

    virtual void registerItem()
    {
        std::cout << "正在注册耳机的商品信息...." << std::endl;
    }
protected:
    std::string _name;
};

class Logitech_G443 : public Earphtones
{
public:
    Logitech_G443()
    {
        _name = "Logitech_G443";
    }
};


class Razer_Mako : public Earphtones
{
public:
    Razer_Mako()
    {
        _name = "Razer_Mako";
    }
};
