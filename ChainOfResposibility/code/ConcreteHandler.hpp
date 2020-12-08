#include"Handler.hpp"
#include<iostream>
class LegalHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        if(req._type == "法务信息")
        {
            std::cout << "法务部门处理法务信息: " << req._text << std::endl;
        }
        else
        {
            if(_sussessor != nullptr)
            {
                _sussessor->HandlerRequest(req);
            }   
        }
    }
};

class BusinessHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        if(req._type == "商务信息")
        {
            std::cout << "商务部门处理商务信息: " << req._text << std::endl;
        }
        else
        {
            if(_sussessor != nullptr)
            {
                _sussessor->HandlerRequest(req);
            }    
        }
    }
};

class PersonnelHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        if(req._type == "人事信息")
        {
            std::cout << "人事部门处理人事信息: " << req._text << std::endl;
        }
        else
        {
            if(_sussessor != nullptr)
            {
                _sussessor->HandlerRequest(req);
            }   
        }
    }
};

class MiscellaneousHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        std::cout << "杂务部门处理剩余信息: " << req._text << std::endl;
    }
};
