#pragma once

#include"Component.hpp"
#include<memory>


class Condiment : public Beverage
{
public:
    Condiment(std::unique_ptr<Beverage> beverage)
        : _beverage(std::move(beverage))
    {}
    virtual ~Condiment() = default;

protected:
    std::unique_ptr<Beverage> _beverage;
};
