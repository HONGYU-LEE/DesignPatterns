#pragma once
#include<stack>
#include<unordered_map>
#include"ConcreteCommand.hpp"

class Controller
{
public:
    //保存命令，即我们通常说的“配对”
    void setCommand(Command* command, std::string type)
    {
        _commands.insert(make_pair(type, command));
    }
    
    //查找命令是否存在，如果存在则执行
    void executeCommand(const std::string& type)
    {
        auto res = _commands.find(type);

        if(res == _commands.end())
        {
            std::cout << "该命令不存在，请检查输入" << std::endl;
        }
        else
        {
            res->second->execute();     //执行命令
            _undo.push(res->second);    //将执行过的命令放入undo栈中
        }
    }

    //撤回上一条命令
    void undoCommand()
    {
        //从undo栈中取出上一条命令，并撤回
        if(!_undo.empty())
        {
            Command* command = _undo.top();
            _undo.pop();

            command->undo();
        }
    }
private:
    std::stack<Command*> _undo;   //用栈来保存执行过的命令，用于进行回退
    std::unordered_map<std::string, Command*> _commands;    //利用哈希来建立起具体命令的映射
};