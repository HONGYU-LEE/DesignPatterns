#pragma once

#include<iostream>

class EngineSystem
{
public:
    void systemOn()
    {
        std::cout << "启动能源系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭能源系统" << std::endl;
    }
};

class DynamicSystem
{
public:
    void systemOn()
    {
        std::cout << "启动动力系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭动力系统" << std::endl;
    }   
};

class CoolingSystem
{
public:
    void systemOn()
    {
        std::cout << "启动冷却系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭冷却系统" << std::endl;
    }
};

class NavigationSystem
{
public:
    void systemOn()
    {
        std::cout << "启动导航系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭导航系统" << std::endl;
    }
};