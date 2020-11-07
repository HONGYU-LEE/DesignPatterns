#pragma once
#include<iostream>

class Type_C
{
public:
    virtual ~Type_C() = default;
    void useTypeC()
    {
        std::cout << "使用Type-C数据线" << std::endl;
    }
};