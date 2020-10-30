#pragma once

#include<string>
#include"SimpleFactory.hpp"

class PeripheralStore
{
public:
    Mouse* orderMouse(const std::string& type) //订购鼠标
    {
        Mouse* mouse;
        mouse = _factory.createMouse(type);
        
        mouse->test();          //测试鼠标
        mouse->packing();       //包装鼠标
        mouse->registerItem();  //注册商品信息

        return mouse;           //发货
    }   
private:
    MouseFactory _factory;
};
