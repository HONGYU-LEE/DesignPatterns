#pragma once
#include"mouse.hpp"

class IMouseFactory
{
public:
    virtual Mouse* createMouse() = 0;
};

class Logitech_G403_Factory : public IMouseFactory
{
public:
    Mouse* createMouse() override
    {
        return new Logitech_G403;
    }
};

class Logitech_G502_Factory : public IMouseFactory
{
public:
    Mouse* createMouse() override
    {
        return new Logitech_G502;
    }
};

class Razer_DeathAdder_Factory : public IMouseFactory
{
public:
    Mouse* createMouse() override
    {
        return new Razer_DeathAdder;
    }
};

class Razer_Mamba_Factory : public IMouseFactory
{
public:
    Mouse* createMouse() override
    {
        return new Razer_Mamba;
    }
};