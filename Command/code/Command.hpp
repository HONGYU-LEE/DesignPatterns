#pragma once

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0; //执行任务
    virtual void undo() = 0;    //撤回任务
};