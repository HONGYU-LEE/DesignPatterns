#pragma once
#include<iostream>

enum State
{
    NORMAL, //普通状态
    SUPER,  //超级状态
    FIRE,   //火焰状态
    DEAD    //死亡状态
};

class MarioStateMachine
{
public:
    MarioStateMachine()
        : _score(0)
        , _state(NORMAL)
    {}

    void getRevive();       //复活
    void getMushroom();     //获得蘑菇
    void getSunFlower();    //获得太阳花
    void getHurt();         //受到伤害
    int getScore() const;   //获取当前分数
    State getState() const; //获取当前状态

private:
    int _score;     //当前分数
    State _state;   //当前状态
};

int MarioStateMachine::getScore() const
{
    return _score;
}

State MarioStateMachine::getState() const
{
    return _state;
}

void MarioStateMachine::getRevive()
{
    if(_state == FIRE)
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;        
    }
    else if(_state == SUPER)
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;   
    }
    else if(_state == NORMAL)
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;   
    }
    else if(_state == DEAD)
    {
        _state = NORMAL;
        _score = 0;
        std::cout << "复活马里奥，回到普通状态，分数重新计算" << std::endl;
    }
}
    
void MarioStateMachine::getMushroom()
{
    if(_state == FIRE)
    {
        _score += 100;
        std::cout << "获得蘑菇，增加一百分" << std::endl;        
    }
    else if(_state == SUPER)
    {
        _score += 100;
        std::cout << "获得蘑菇，增加一百分" << std::endl;
    }
    else if(_state == NORMAL)
    {
        _state = SUPER;
        _score += 100;
        std::cout << "获得蘑菇，由普通马里奥变为超级马里奥，增加一百分" << std::endl;
    }
    else if(_state == DEAD)
    {
        std::cout << "死亡后不能获取道具，不存在该逻辑" << std::endl;
    }
};     

void MarioStateMachine::getSunFlower()
{
    if(_state == FIRE)
    {
        _score += 200;
        std::cout << "获得太阳花，增加两百分" << std::endl;        
    }
    else if(_state == SUPER)
    {
        _state = FIRE;
        _score += 200;
        std::cout << "获得太阳花，由超级马里奥变为火焰马里奥，增加两百分" << std::endl;
    }
    else if(_state == NORMAL)
    {
        _state = FIRE;
        _score += 200;

        std::cout << "获得太阳花，由普通马里奥变为火焰马里奥，增加两百分" << std::endl;
    }
    else if(_state == DEAD)
    {
        std::cout << "死亡后不能获取道具，不存在该逻辑" << std::endl;
    }
};  

void MarioStateMachine::getHurt()
{
    if(_state == FIRE)
    {
        _state = SUPER;
        _score -= 100;
        std::cout << "受到伤害，由火焰马里奥变为超级马里奥，扣一百分" << std::endl;        
    }
    else if(_state == SUPER)
    {
        _state = NORMAL;
        _score -= 100;
        std::cout << "受到伤害，由超级马里奥变为普通马里奥，扣一百分" << std::endl;
    }
    else if(_state == NORMAL)
    {
        _state = DEAD;
        _score = 0;

        std::cout << "受到伤害，马里奥死亡，分数清空" << std::endl;
    }
    else if(_state == DEAD)
    {
        std::cout << "死亡后不能受到伤害，不存在该逻辑" << std::endl;
    }
};        
    

