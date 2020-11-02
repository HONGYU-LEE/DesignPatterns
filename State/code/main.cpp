//#include"BranchLogic.hpp"
//#include"QueryTable.hpp"
#include<iostream>
#include"StateMachine.hpp"
//#include"State.hpp"

int main()
{
    MarioStateMachine Mario;
    
    Mario.getMushroom();    //马里奥获取蘑菇
    Mario.getSunFlower();   //马里奥获取太阳花
    Mario.getSunFlower();   //马里奥获取太阳花
    std::cout << Mario.getScore() << std::endl; //查看得分情况

    Mario.getRevive();  //尝试复活

    Mario.getHurt();
    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //检查受伤后是否扣分

    Mario.getHurt();
    std::cout << Mario.getScore() << std::endl; //死亡分数清空
}



