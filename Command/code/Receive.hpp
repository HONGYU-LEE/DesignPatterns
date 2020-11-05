#pragma once
#include<string>
#include<iostream>

class SweepingRobot
{
public:
    void action()
    {
        std::cout << "扫地机器人开始执行清扫计划！" << std::endl;
    }

    void undo()
    {
        std::cout << "撤销扫地机器人的清扫计划！" << std::endl;
    }
};

class AirConditioner
{
public:
    void action()
    {
        std::cout << "空调开始启动！" << std::endl;
    }

    void undo()
    {
        std::cout << "撤回空调的启动命令！" << std::endl;
    }
};