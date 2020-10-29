#pragma once

class DisplayElement
{
public:
    virtual ~DisplayElement() = default;
    virtual void display() = 0;     //显示数据
};

