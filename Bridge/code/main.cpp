#include"RefinedAbstraction.hpp"
#include"ConcreteImplementor.hpp"

using namespace std;

int main()
{
    Abstraction* linux = new Linux;
    Abstraction* windows = new Windows;
    Abstraction* mac = new Mac;

    linux->setImplementor(new Vedio);
    windows->setImplementor(new Vedio);
    linux->run();
    windows->run();
    

    linux->setImplementor(new Music);
    linux->run();

    mac->setImplementor(new Text);
    mac->run();

    return 0;
}