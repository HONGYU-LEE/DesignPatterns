#pragma once
#include"Implementor.hpp"

class Abstraction
{
public:
    virtual ~Abstraction() = default;

    void setImplementor(Implementor* implementor)
    {
        _implementor = implementor;
    }

    virtual void run()
    {
        if(_implementor != nullptr)
        {
            _implementor->run();
        }
    }

protected:
    Implementor* _implementor = nullptr;
};