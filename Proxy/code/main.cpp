#include"Proxy.hpp"
#include"RealSubject.hpp"

using namespace std;
/*
int main()
{
    Subject* subject = new RealSubject();   //客户对象
    Proxy* proxy = new Proxy(subject);      //中介代理客户

    proxy->rentingHouse();  //中介代理客户执行任务

    delete proxy, subject;
    return 0;
}
*/

int main()
{
    Tenant* xiaoming = new XiaoMing();      //小明
    Proxy* proxy = new Proxy(xiaoming);     //中介代理小明的租房行为

    proxy->rentingHouse();  //中介代替客户租房

    delete proxy, xiaoming;
    return 0;
}