#pragma once

#include<string>

class Beverage
{
public:
    virtual ~Beverage() = default;
    virtual double cost() = 0;

    virtual std::string getDescription()
    {
        return _desc;
    }
protected:
    std::string _desc;
};