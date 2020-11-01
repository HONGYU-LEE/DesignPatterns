#pragma once

#include"Component.hpp"

class RedTea : public Beverage
{
public:
    RedTea()
    {
        _desc = "RedTea";
    }

    double cost() override
    {
        return 10.5;
    }
};

class MilkTea : public Beverage
{
public:
    MilkTea()
    {
        _desc = "MilkTea";
    }

    double cost() override
    {
        return 13;
    }
};

class Coffee : public Beverage
{
public:
    Coffee()
    {
        _desc = "Coffee";
    }

    double cost() override
    {
        return 19.9;
    }
};