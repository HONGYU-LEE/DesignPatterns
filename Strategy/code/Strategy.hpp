#pragma once
#include<iostream>

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual void getStrategy() = 0;
};

class infantryStrategy : public Strategy
{
public:
    void getStrategy() override
    {
        std::cout << "计策：用弓箭手来对付步兵" << std::endl;
    }
};

class wallStrategy : public Strategy
{
public:
    void getStrategy() override
    {
        std::cout << "计策：用破城槌来破坏城墙" << std::endl;
    }
};

class cavalryStrategy : public Strategy
{
public:
    void getStrategy() override
    {
        std::cout << "计策：长枪兵来对付骑兵" << std::endl;
    }
};