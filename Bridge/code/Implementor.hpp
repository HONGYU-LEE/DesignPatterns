#pragma once

class Implementor
{
public:
    virtual ~Implementor() = default;
    virtual void run() = 0;
};