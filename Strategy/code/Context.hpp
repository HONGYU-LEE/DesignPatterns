#pragma once
#include"Strategy.hpp"

class Context
{
public:
    Context(Strategy* strategy = nullptr)
        : _strategy(strategy)
    {}

    virtual ~Context() = default;
    virtual void doAction() = 0;
    virtual void setstrategy(Strategy* strategy) = 0;

protected:
    Strategy* _strategy;
};

class Commander : public Context
{
    void doAction() override
    {
        if(_strategy)
        {
            _strategy->getStrategy();
        }
    }

    void setstrategy(Strategy* strategy) override
    {
        _strategy = strategy;
    }
};