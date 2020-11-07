#pragma once
#include<iostream>

class MicroUSB
{
public:
    virtual ~MicroUSB() = default;
    virtual void useMicroUSB()
    {
        std::cout << "使用Micro USB数据线" << std::endl;
    }
};
