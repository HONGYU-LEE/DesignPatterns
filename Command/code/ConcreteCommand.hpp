#pragma once

#include"Command.hpp"
#include"Receive.hpp"

class SweepingRobotCommand : public Command
{
public:
    SweepingRobotCommand(SweepingRobot* recvive)
        : _recvive(recvive)
    {}

    void execute() override
    {
        _recvive->action();
    }

    void undo() override
    {
        _recvive->undo();
    }
private:
    SweepingRobot* _recvive;
};

class AirConditionerCommand : public Command
{
public:
    AirConditionerCommand(AirConditioner* recvive)
        : _recvive(recvive)
    {}

    void execute() override
    {
        _recvive->action();
    }

    void undo() override
    {
        _recvive->undo();
    }
private:
    AirConditioner* _recvive;
};