[TOC]

----------
~~命令模式的应用场景较少，且不易理解，因此我也不好举例，所以下面的描述可能会存在一些问题，请见谅~~ 

# 案例：智能遥控
小明所在的公司正在研发一个智能遥控APP，可以通过将家电的命令配对到APP上，通过APP我们就能够远程的启动家中的家电，并让其执行任务。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201105211518855.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

如果我们直接让遥控器来要求家电做出某些命令，由于家电的品牌、种类不同，其功能的接口以及实现也各不相同，为我们的设计带来了巨大的挑战。

由于不同的产品的命令不一样，接口也不一样，如果让控制器全权负责家电命令的请求、下达、执行，这就要求控制器必须要清楚家电的所有细节，并且需要针对对象编程，一旦我们需要进行拓展，就会需要让我们的遥控器来适应新的家电。

这种针对细节编程的设计存在大量的缺陷，例如下图，当存在大量的类时，就会导致控制器的逻辑十分繁杂，并且拓展性、维护性极低。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201105210802734.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
如果继续根据品牌、型号进行划分，又会产生一大堆类型，并且当有新型号产品出现时，我们的拓展也非常麻烦

所以我们不妨换个思路，<font color=red>**将命令的执行与调用进行分离**</font>，控制器不需要知道这些家电的执行方式，他只需要发出命令的请求，而后让专门的对象去处理这些命令。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201105211728714.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
<font color=red>**采用这样的设计，控制器就不再需要了解命令的执行细节，当发起请求命令时，控制器就会调用命令对象的执行方法，然后让命令对象操纵接收者执行动作。这样，就将动作的请求者从动作的执行者中进行解耦。**</font>

这就是<font color=red>**命令模式**</font>的核心。

------
# 命令模式
<font color=red>**命令模式将一个请求(行为)封装成一个对象，从而使你可用不同的请求对客户进行参数化；对请求排队或记录请求日志，以及支持可撤销的操作。**</font>

命令模式由以下部分组成
- **Invoker(调用者)**：命令的调用者，接收客户端的请求后通过调用命令对象中的执行方法来下达命令
- **Command(命令接口)**：用来声明执行命令的接口
- **ConcreteCommand(命令对象)**：绑定了一个接收者，调用接收者的对应操作来完成命令
- **Receiver(接收者)**：命令的接收者，即实际执行命令的人

类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201105212504888.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
了解完命令模式之后，我们继续实现我们的控制器

为了能让控制器能够适配多种命令，我们创造出一个命令接口，并让所有的具体命令都去实现它。并且为了防止我们可能会存在误操作，我还加入了一个撤回操作的undo方法
```cpp
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0; //执行任务
    virtual void undo() = 0;    //撤回任务
};
```
接着为了方便举例，我们还需要实现一个家电的实例

```cpp
class SweepingRobot
{
public:
    void action()
    {
        std::cout << "扫地机器人开始执行清扫计划！" << std::endl;
    }

    void undo()
    {
        std::cout << "撤销扫地机器人的清扫计划！" << std::endl;
    }
};
```

<font color=red>**命令对象会保留一份执行者的实例，通过调用执行者的对应操作来完成命令**</font>
```cpp
class SweepingRobotCommand : public Command
{
public:
    SweepingRobotCommand(SweepingRobot* recvive)
        : _recvive(recvive)
    {}

    void execute() override
    {
        _recvive->action();
    }

    void undo() override
    {
        _recvive->undo();
    }
private:
    SweepingRobot* _recvive;
};
```
下面就实现我们具体的控制器吧，为了方便下达命令，我利用<font color=red>**哈希表**</font>来将命令语句与具体命令建立映射，当输入执行的语句后，我们就会自动的去查找哈希表中存在的命令，然后执行它

同时，利用一个栈来保存所有的执行命令，来方便我们进行误操作的回滚
```cpp
class Controller
{
public:
    //保存命令，即我们通常说的“配对”
    void setCommand(Command* command, std::string type)
    {
        _commands.insert(make_pair(type, command));
    }
    
    //查找命令是否存在，如果存在则执行
    void executeCommand(const std::string& type)
    {
        auto res = _commands.find(type);

        if(res == _commands.end())
        {
            std::cout << "该命令不存在，请检查输入" << std::endl;
        }
        else
        {
            res->second->execute();     //执行命令
        }
    }
    //撤回上一条命令
    void undoCommand()
    {
        //从undo栈中取出上一条命令，并撤回
        if(!_undo.empty())
        {
            Command* command = _undo.top();
            _undo.pop();

            command->undo();
            _undo.push(res->second);    //将执行过的命令放入undo栈中
        }
    }
private:
	std::stack<Command*> _undo;   //用栈来保存执行过的命令，用于进行回退
    std::unordered_map<std::string, Command*> _commands;    //利用哈希来建立起具体命令的映射
};
```

测试代码
```cpp
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

```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201105203406573.png#pic_center)

----
# 应用场景
虽然命令模式在日常的应用、业务编写中都不是很常见，但这并不意味着它离我们很遥远，在一些较为底层的设计中还是会存在着它的身影。

## 队列请求
上面我提到过，命令模式将发出请求的对象和执行请求的对象进行解耦，这也就意味着任务的发布者不需要知道任务的执行流程以及细节，只需要下达命令，而执行者只需要接收任务并进行执行，不需要了解任务的发布者是谁，两者之间不存在耦合关系。

说到这里，我们马上就想到了生产者消费者模型、线程池、工作队列等应用。工作队列来说，客户将命令对象放入队列中，而另一端的线程从队列中取出命令对象，并调用命令对象中的execute函数来完成任务，它不在乎对象到底做些什么，它只知道取出命令并调用执行方法，两者完全解耦。

## 日志系统
在上面的实现中，我利用一个栈将所有的执行命令保存下来，并提供了undo命令来进行回退，这不就是我们的日志系统吗？这里就用数据库的日志系统进行举例，其会保存我们所有执行的sql语句，并将其写入日志中，我们可以通过日志来进行反向的undo操作，进行版本的回退。

而我们通常所说的事务，也是这样实现的。事务要么全都执行，要么全都不执行。当有某个事务执行失败时，就会查询日志，并执行其undo操作，来达到版本的回退效果

--------
# 总结
**要点**
- 命令模式将发出请求的对象和执行请求的对象解耦，做法是将命令抽象为对象
- 命令支持撤销，可以通过undo方法来进行回滚 
- 调用者通过调用命令对象的执行方法来发出请求，使得接收者执行动作
- 可能会导致存在大量的命令类

**应用场景**
- 日志系统、事务等需要对命令记录、撤回、重做等场景
- 工作队列等需要将命令的发布者和执行者解耦的场景

