#pragma once
#include<iostream>
#include<string>

class MarioStateMachine;

class MarioState
{
public:
    virtual ~MarioState() = default;
    virtual std::string getStateName() = 0;  //获取状态名
    virtual void getRevive() = 0;       //复活
    virtual void getMushroom() = 0;     //获得蘑菇
    virtual void getSunFlower() = 0;    //获得太阳花
    virtual void getHurt() = 0;         //受到伤害
};