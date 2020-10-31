#pragma once
#include"Strategy.hpp"
#include<unordered_map>
#include<mutex>

class StrategyFactory
{
public:
    //加载所有的策略
    StrategyFactory()
    {
        _strategys.insert(std::make_pair("wall", new wallStrategy));
        _strategys.insert(std::make_pair("infantry", new infantryStrategy));
        _strategys.insert(std::make_pair("cavalry", new cavalryStrategy));
    }

    //获取对应场景的策略
    Strategy* getStrategyObject(const std::string& situation)
    {
        return _strategys[situation];
    }
private:
    std::unordered_map<std::string, Strategy*> _strategys;   //利用哈希表来建立起场景和策略的映射
};