#pragma once
#include<iostream>
#include"Abstraction.hpp"

class Linux : public Abstraction
{
public:
    void run() override
    {
        std::cout << "Linux系统：";
        _implementor->run();
    }
};

class Windows : public Abstraction
{
public:
    void run() override
    {
        std::cout << "Windows系统：";
        _implementor->run();
    }
};

class Mac : public Abstraction
{
public:
    void run() override
    {
        std::cout << "Mac系统：";
        _implementor->run();
    }
};