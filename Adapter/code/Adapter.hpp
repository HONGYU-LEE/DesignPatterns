#pragma once
#include"Target.hpp"
#include"Adaptee.hpp"

//对象适配器
class ObjectAdapter : public MicroUSB
{
public:
    ObjectAdapter(Type_C* typeC)
        : _typeC(typeC)
    {}

    void useMicroUSB() override
    {
        std::cout << "使用对象适配器将Type-C转换为Micro USB" << std::endl;
        _typeC->useTypeC();
    }
private:
    Type_C* _typeC;
};

//类适配器
class ClassAdapter : public MicroUSB, Type_C
{
public:
    void useMicroUSB() override
    {
        std::cout << "使用类适配器将Type-C转换为Micro USB" << std::endl;
        useTypeC();
    }
};