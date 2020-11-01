#pragma once

#include"Decorator.hpp"

class Pearl : public Condiment
{
public:
    Pearl(std::unique_ptr<Beverage> beverage)
        : Condiment(std::move(beverage))
    {}

    std::string getDescription() override
    {
        return _beverage->getDescription() + " + Pearl";
    }

    double cost() override
    {
        return _beverage->cost() + 1.5;
    }
};

class Coconut : public Condiment
{
public:
    Coconut(std::unique_ptr<Beverage> beverage)
        : Condiment(std::move(beverage))
    {}

    std::string getDescription() override
    {
        return _beverage->getDescription() + " + Coconut";
    }

    double cost() override
    {
        return _beverage->cost() + 0.8;
    }
};

class Milk  : public Condiment
{
public:
    Milk(std::unique_ptr<Beverage> beverage)
        : Condiment(std::move(beverage))
    {}

    std::string getDescription() override
    {
        return _beverage->getDescription() + " + Milk";
    }

    double cost() override
    {
        return _beverage->cost() + 0.5;
    }
};
