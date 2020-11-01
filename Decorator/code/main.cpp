#include"ConcreteDecorator.hpp"
#include"ConcreteComponent.hpp"
#include<iostream>

using namespace std;

int main()
{
    unique_ptr<Beverage> drink1 = make_unique<RedTea>();
    drink1 = make_unique<Milk>(move(drink1));
    drink1 = make_unique<Pearl>(move(drink1));
    drink1 = make_unique<Coconut>(move(drink1));
    drink1 = make_unique<Milk>(move(drink1));
     
    cout << drink1->getDescription() << endl;
    cout << drink1->cost() << endl;

    return 0;
}