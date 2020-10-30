#pragma once
#include"mouse.hpp"

class MouseFactory
{
public:
    Mouse* createMouse(const std::string& type)
    {
        Mouse* mouse;
        if(type == "Logitech_G403")
        {
            mouse = new Logitech_G403;
        }
        else if(type == "Logitech_G502")
        {
            mouse = new Logitech_G502;
        }
        else if(type == "Razer_DeathAdder")
        {
            mouse = new Razer_DeathAdder;
        }
        else if(type == "Razer_Mamba")
        {
            mouse = new Razer_Mamba;
        }

        return mouse;
    }
};