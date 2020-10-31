#include<iostream>
#include<string>
using namespace std;

class Commander
{
    void doAction(const std::string& situation) 
    {
        if(situation == "wall")
        {
            std::cout << "计策：用破城槌来破坏城墙" << std::endl;
        }
        else if(situation == "infantry")
        {
            std::cout << "计策：用弓箭手来对付步兵" << std::endl;
        }
        else if(situation == "cavalry")
        {
            std::cout << "计策：长枪兵来对付骑兵" << std::endl;
        }
        //....................其他策略
    }
};