#include"Invoker.hpp"

using namespace std;

int main()
{
    Controller controller;
    AirConditioner equipment1;
    SweepingRobot equipment2;

    Command* command1 = new AirConditionerCommand(&equipment1); 
    Command* command2 = new SweepingRobotCommand(&equipment2);

    controller.setCommand(command1, "AirConditioner");  //配对
    controller.setCommand(command2, "SweepingRobot");

    controller.executeCommand("AirConditioner");    //启动空调
    controller.executeCommand("SweepingRobot");     //启动扫地机器人
    controller.undoCommand();                       //撤回上一条命令
    controller.undoCommand();                       //撤回上一条命令

    delete command1, command2;
    return 0;
}
