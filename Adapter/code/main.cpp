#include"Adapter.hpp"

using namespace std;

int main()
{
    MicroUSB* micro = new MicroUSB;
    Type_C* typeC = new Type_C;

    MicroUSB* objectAdapter = new ObjectAdapter(typeC);
    MicroUSB* classAdapter = new ClassAdapter;

    micro->useMicroUSB();
    cout << endl;

    objectAdapter->useMicroUSB();   //使用对象适配器
    cout << endl;   
    classAdapter->useMicroUSB();    //使用类适配器

    delete micro, typeC, objectAdapter, classAdapter;
    return 0;
}