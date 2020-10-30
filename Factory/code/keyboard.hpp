#pragma once

#include<string>
#include<iostream>

class KeyBoard
{
public:
    virtual ~KeyBoard() = default;

    void showMessage() const
    {
        std::cout << "键盘名：" << _name << "\n" << std::endl;
    }

    virtual void test()
    {
        std::cout << "正在对键盘进行测试...." << std::endl;
    }

    virtual void packing()
    {
        std::cout << "正在对键盘处理...." << std::endl;
    }

    virtual void registerItem()
    {
        std::cout << "正在注册键盘的商品信息...." << std::endl;
    }
protected:
    std::string _name;
};

class Logitech_G913 : public KeyBoard
{
public:
    Logitech_G913()
    {
        _name = "Logitech_G913";
    }
};


class Razer_Huntsman : public KeyBoard
{
public:
    Razer_Huntsman()
    {
        _name = "Razer_Huntsman";
    }
};
