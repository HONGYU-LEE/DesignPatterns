#pragma once
#include<string>

//请求结构体，包含请求类型和正文
struct Request
{
    std::string _type;
    std::string _text;
};

class Handler
{
public:
    Handler()
        : _sussessor(nullptr)
    {}

    virtual ~Handler() = default;

    void setSussessor(Handler* sussessor)
    {
        _sussessor = sussessor;
    }

    virtual void HandlerRequest(const Request& req) = 0;
    
protected:
    Handler* _sussessor;
};