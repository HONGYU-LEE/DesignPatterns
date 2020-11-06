#include"Facade.hpp"

using namespace std;

int main()
{
    AutoAircraft airCraft;
    airCraft.systemOn();
    cout << endl;
    airCraft.systemOff();

    return 0;
}