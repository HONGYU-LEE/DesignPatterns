#pragma once

#include<string>
#include<iostream>

class Mouse
{
public:
    virtual ~Mouse() = default;

    void showMessage() const
    {
        std::cout << "鼠标名：" << _name << "\n" << std::endl;
    }

    virtual void test()
    {
        std::cout << "正在对鼠标进行测试...." << std::endl;
    }

    virtual void packing()
    {
        std::cout << "正在对鼠标处理...." << std::endl;
    }

    virtual void registerItem()
    {
        std::cout << "正在注册鼠标的商品信息...." << std::endl;
    }
protected:
    std::string _name;
};

class Logitech_G403 : public Mouse
{
public:
    Logitech_G403()
    {
        _name = "Logitech_G403";
    }
};

class Logitech_G502 : public Mouse
{
public:
    Logitech_G502()
    {
        _name = "Logitech_G502";
    }
};

class Razer_DeathAdder : public Mouse
{
public:
    Razer_DeathAdder()
    {
        _name = "Razer_DeathAdder";
    }
};

class Razer_Mamba : public Mouse
{
public:
    Razer_Mamba()
    {
        _name = "Razer_Mamba";
    }
};