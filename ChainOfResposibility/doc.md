[TOC]

--------------
# 案例：企业信息处理
对于一个企业来说，每天难免的要收到大量的信息，有求职者发送过来的简历、其他公司的商务合作信息、又或者是和一些企业或客户的法律纠纷信息、又或者是一些广告、推销信息。面对这大量的信息，处理起来十分的麻烦。


于是企业准备开发一套信息管理系统，初步的设计如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201208160417519.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)
我们设计了一个信息的管理员，他会判断信息的种类，并将信息转发到对应的部门中，让这些部门来处理它们对应的任务。

但是，这样的设计存在着严重的问题。

随着我们公司的规模不断扩张，各个部门的职责也更加细化，对于这些信息，我们又新增了几个新部门进行处理，同时我们可能又会对业务细化，将一个部门拆分成多个部门。甚至我们又会对信息进行分级，例如普通信息管理者，机密信息管理者等等

在这种情况下，管理者存在着大量的职责，违反了<font color=red>**单一职责原则**</font>。同时，我们每一次增加、修改部门时，都需要去修改管理者的内部实现，这同时又违反了<font color=red>**开放-封闭原则**</font>，这样的代码不仅维护性差，类与类之间也存在着强耦合的关系，是个不好的设计方案。

为了解决这个问题，就引入了<font color=red>**职责链模式**</font>

--------
# 职责链模式
<font color=red>**职责链模式使得多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递该请求，知道有一个对象处理它为止**</font>

职责链模式由两部分组成
- **Handler(处理者接口)**：提供了处理请求的接口，所有的具体处理者都会实现它
- **ConcreteHandle(具体处理者)**：具体处理者，处理它所负责的请求，可访问它的后继者，如果可以处理则处理，处理不了则将任务转发给它的后继者

类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201208150020544.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)

根据职责链模式，此时我们的关系是这样的，我们让部门之间以<font color=red>**链表**</font>的形式连接起来。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201208153202891.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)
当客户向我们发送信息后，每个部门都会处理自己分内的信息，如果处理不了，则将其转发给职责链中的下一个部门，让其继续处理。

例如客户发送来一个XXX的求职简历，此时的处理流程是这样的
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201208162618125.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)



下面就以代码的形式实现一下这个功能

首先实现一个请求的结构，以及处理者的抽象类，其中为了实现链式结构，处理者中保留了一个指向职责链下一个处理者的指针
```cpp
//请求结构体，包含请求类型和正文
struct Request
{
    std::string _type;
    std::string _text;
};

//处理者抽象类，所有的具体处理者都会继承并实现该类
class Handler
{
public:
    Handler()
        : _sussessor(nullptr)
    {}

    virtual ~Handler() = default;

    void setSussessor(Handler* sussessor)
    {
        _sussessor = sussessor;
    }

    virtual void HandlerRequest(const Request& req) = 0;
    
protected:
    Handler* _sussessor;	//继任者
};
```

接着实现具体的处理者
```cpp
#include"Handler.hpp"
#include<iostream>

//法务部门
class LegalHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        if(req._type == "法务信息")
        {
            std::cout << "法务部门处理法务信息: " << req._text << std::endl;
        }
        else
        {
            if(_sussessor != nullptr)
            {
                _sussessor->HandlerRequest(req);
            }   
        }
    }
};

//商务部门
class BusinessHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        if(req._type == "商务信息")
        {
            std::cout << "商务部门处理商务信息: " << req._text << std::endl;
        }
        else
        {
            if(_sussessor != nullptr)
            {
                _sussessor->HandlerRequest(req);
            }    
        }
    }
};

//人事部门
class PersonnelHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        if(req._type == "人事信息")
        {
            std::cout << "人事部门处理人事信息: " << req._text << std::endl;
        }
        else
        {
            if(_sussessor != nullptr)
            {
                _sussessor->HandlerRequest(req);
            }   
        }
    }
};

//杂务部门，也相当于是收尾人，负责处理剩余的请求
class MiscellaneousHandler : public Handler
{
public:
    void HandlerRequest(const Request& req) override
    {
        std::cout << "杂务部门处理剩余信息: " << req._text << std::endl;
    }
};
```

测试代码
```cpp
int main()
{
    Handler* legal = new LegalHandler;
    Handler* business = new BusinessHandler;
    Handler* personnel = new PersonnelHandler;
    Handler* miscellaneous = new MiscellaneousHandler;
    legal->setSussessor(business);
    business->setSussessor(personnel);
    personnel->setSussessor(miscellaneous);

    legal->HandlerRequest({"法务信息", "XXX法院传票"});
    legal->HandlerRequest({"商务信息", "XXX商业合作"});
    legal->HandlerRequest({"人事信息", "XXX投递简历"});
    legal->HandlerRequest({"杂务信息", "XXX无关信息"});

    delete legal, business, personnel, miscellaneous;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201208144347767.png)

在当前的设计中，客户只需要将所有的信息发送给职责链的首部即可，如果他能够处理则直接完成请求，如果无法完成就会将请求转发给职责链的下一个处理者继续执行

---------
# 总结
**要点**
- 职责链模式将请求的发送者和接收者解耦
- 可以简化对象的相互连接，因为它不需要知道链的结构
- 通过改变链内的成员或者调动他们的次序，允许我们动态地增加或者修改处理一个请求的结构，增强了给对象指派职责的灵活性
- 并不保证请求一定会被执行，如果没有任何对象处理它，可能回落到链尾端之外，因此最好需要设立一个收尾者，来解决所有未被处理的请求
- 由于处理是链式传递的，因此不容易观察运行时的特征，有碍于除错


**应用场景**
- 有多个对象可以处理同一个请求，具体哪个对象处理该请求由运行时刻自动确定
- 在不明确指定接收者的情况下，向多个对象中的一个提交一个请求
- 可动态指定一组对象处理请求
- 通常用于实现拦截器、过滤器、窗口事件处理等

