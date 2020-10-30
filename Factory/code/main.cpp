#include"mouse.hpp"
#include"PeripheralStore.hpp"
#include"FactoryMethod.hpp"
#include"SimpleFactory.hpp"
#include"AbstractFactory.hpp"

using namespace std;
/*
int main()
{
    IPeripheralFactory* logitech = new LogitechFactory;  //罗技工厂
    IPeripheralFactory* razer = new RazerFactory;        //雷蛇工厂

    Mouse* m1 = logitech->createMouse();
    m1->showMessage();

    KeyBoard* k1 = razer->createKeyBoard();
    k1->showMessage();

    delete k1;
    delete m1;
    delete logitech;
    delete razer;   
}

*/

int main()
{
    Logitech_G403_Factory* G403_factory = new Logitech_G403_Factory;
    Razer_DeathAdder_Factory* DeathAdder_factory = new Razer_DeathAdder_Factory;
    
    Mouse* m1 = G403_factory->createMouse();
    m1->showMessage();
    Mouse* m2 = DeathAdder_factory->createMouse();
    m2->showMessage();

    delete m2;
    delete m1;
    delete G403_factory;
    delete DeathAdder_factory;

    return 0;
}