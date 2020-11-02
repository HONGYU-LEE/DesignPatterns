#include"State.hpp"
#include"StateMachine.hpp"

class NormalMario : public MarioState
{
public:
    NormalMario(MarioStateMachine* stateMachine)
        : _stateMachine(stateMachine)
    {}

    void getRevive() override
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;  
    }    

    void getMushroom() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 100);
        _stateMachine->setState(_stateMachine->getSuperMario());
        std::cout << "获得蘑菇，由普通马里奥变为超级马里奥，增加一百分" << std::endl;
    }

    void getSunFlower() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 200);
        _stateMachine->setState(_stateMachine->getFireMario());
        std::cout << "获得太阳花，由普通马里奥变为火焰马里奥，增加两百分" << std::endl;
    }

    void getHurt() override
    {
        _stateMachine->setScore(0);
        _stateMachine->setState(_stateMachine->getDeadMario());
        std::cout << "受到伤害，马里奥死亡，分数清空" << std::endl;
    }    

    std::string getStateName() override
    {
        return "普通马里奥";
    }

private:
    MarioStateMachine* _stateMachine;   //状态机
};

class SuperMario : public MarioState
{
public:
    SuperMario(MarioStateMachine* stateMachine)
        : _stateMachine(stateMachine)
    {}

    void getRevive() override
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;  
    }    

    void getMushroom() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 100);
        std::cout << "获得蘑菇，增加一百分" << std::endl;
    }

    void getSunFlower() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 200);
            _stateMachine->setState(_stateMachine->getFireMario());
        std::cout << "获得太阳花，由超级马里奥变为火焰马里奥，增加两百分" << std::endl;
    }

    void getHurt() override
    {
        _stateMachine->setScore(_stateMachine->getScore() - 100);
        _stateMachine->setState(_stateMachine->getNormalMario());
        std::cout << "受到伤害，由超级马里奥变为普通马里奥，扣一百分" << std::endl;
    }    

    std::string getStateName() override
    {
        return "超级马里奥";
    }

private:
    MarioStateMachine* _stateMachine;   //状态机
};

class FireMario : public MarioState
{
public:
    FireMario(MarioStateMachine* stateMachine)
        : _stateMachine(stateMachine)
    {}

    void getRevive() override
    {
        std::cout << "当前未死亡，不能复活。不存在该逻辑" << std::endl;  
    }    

    void getMushroom() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 100);
        std::cout << "获得蘑菇，增加一百分" << std::endl;
    }

    void getSunFlower() override
    {
        _stateMachine->setScore(_stateMachine->getScore() + 200);
        std::cout << "获得太阳花，增加两百分" << std::endl;
    }

    void getHurt() override
    {
        _stateMachine->setScore(_stateMachine->getScore() - 100);
        _stateMachine->setState(_stateMachine->getSuperMario());
        std::cout << "受到伤害，由火焰马里奥变为超级马里奥，扣一百分" << std::endl;
    }    

    std::string getStateName() override
    {
        return "火焰马里奥";
    }

private:
    MarioStateMachine* _stateMachine;   //状态机
};

class DeadMario : public MarioState
{
public:
    DeadMario(MarioStateMachine* stateMachine)
        : _stateMachine(stateMachine)
    {}

    void getRevive() override
    {
        _stateMachine->setScore(0);
        _stateMachine->setState(_stateMachine->getNormalMario());
        std::cout << "复活马里奥，会到普通状态，分数重新计算" << std::endl;  
    }    

    void getMushroom() override
    {
        std::cout << "死亡后不能获取道具，不存在该逻辑" << std::endl;
    }

    void getSunFlower() override
    {
        std::cout << "死亡后不能获取道具，不存在该逻辑" << std::endl;
    }

    void getHurt() override
    {
        std::cout << "死亡后不能受到伤害，不存在该逻辑" << std::endl;
    }    

    std::string getStateName() override
    {
        return "死亡";
    }

private:
    MarioStateMachine* _stateMachine;   //状态机
};