#pragma once
#include"mouse.hpp"
#include"keyboard.hpp"
#include"earphones.hpp"

class IPeripheralFactory
{
public:
virtual ~IPeripheralFactory() = default;
virtual Mouse* createMouse() = 0;
virtual Earphtones* createEarPhones () = 0;
virtual KeyBoard* createKeyBoard() = 0;
};

class LogitechFactory : public IPeripheralFactory
{
    Mouse* createMouse() override
    {
        return new Razer_DeathAdder;
    }

    Earphtones* createEarPhones () override
    {
        return new Razer_Mako;
    }

    KeyBoard* createKeyBoard() override
    {
        return new Razer_Huntsman;
    }
};

class RazerFactory : public IPeripheralFactory
{
    Mouse* createMouse() override
    {
        return new Logitech_G502;
    }
    
    Earphtones* createEarPhones () override 
    {
        return new Logitech_G443;
    }

    KeyBoard* createKeyBoard() override
    {
        return new Logitech_G913;
    }
};