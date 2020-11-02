#pragma once
#include<iostream>
#include<vector>

enum State
{
    NORMAL, //普通状态
    SUPER,  //超级状态
    FIRE,   //火焰状态
    DEAD    //死亡状态
};

enum Event
{
    GET_MUSHROOM,   //获得蘑菇
    GET_SUNFLOWER,  //获得太阳花
    GET_HURT,       //遭受伤害
    GET_REVIVE,     //复活
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
    void executeEvent(Event event); //执行事件
    int _score;     //当前分数
    State _state;   //当前状态
    static std::vector<std::vector<int>> _actionTable;    //行为表
    static std::vector<std::vector<State>> _stateTable;   //状态表
};

//用INT_MIN表示清空，用0表示不符合逻辑的忽略情况
std::vector<std::vector<int>> MarioStateMachine::_actionTable = 
{
    {100, 200, INT_MIN, 0},
    {100, 200, -100, 0},
    {200, 200, -100, 0},
    {0, 0, 0, INT_MIN},
};

std::vector<std::vector<State>> MarioStateMachine::_stateTable = 
{
    {SUPER, FIRE, DEAD, NORMAL},
    {SUPER, FIRE, NORMAL, SUPER},
    {FIRE, FIRE, SUPER, FIRE},
    {DEAD, DEAD, DEAD, NORMAL},
};

void MarioStateMachine::executeEvent(Event event)
{
    int score = _actionTable[_state][event];    //查询表中对应的动作
    
    _score = (score == INT_MIN) ? _score = 0 : _score + score;   //如果为INT_MIN,则说明需要清空 
    _state = _stateTable[_state][event];        //查询表中对应的状态
}

void MarioStateMachine::getRevive()
{
    executeEvent(GET_REVIVE);
}
    
void MarioStateMachine::getMushroom()
{
    executeEvent(GET_MUSHROOM);
};     

void MarioStateMachine::getSunFlower()
{
    executeEvent(GET_SUNFLOWER);
};  

void MarioStateMachine::getHurt()
{
    executeEvent(GET_HURT);
};        

int MarioStateMachine::getScore() const
{
    return _score;
}

State MarioStateMachine::getState() const
{
    return _state;
}


