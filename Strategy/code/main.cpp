#include"Context.hpp"
#include"Strategy.hpp"
#include"StrategyFactory.hpp"

using namespace std;


int main()
{
    Context* commander = new Commander();    //指挥官对象
    StrategyFactory factoty;                 //策略工厂
    
    
    commander->setstrategy(factoty.getStrategyObject("cavalry"));       //当玩家的骑兵到来的时候
    commander->doAction();

    commander->setstrategy(factoty.getStrategyObject("wall"));          //当玩家退回城堡中防守时   
    commander->doAction();

    delete commander;
    return 0;
}