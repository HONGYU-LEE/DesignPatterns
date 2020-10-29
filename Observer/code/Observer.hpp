#pragma once
#include<string>

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& url, const std::string& title, const std::string& desc) = 0;      //更新数据
};

