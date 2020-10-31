[TOC]

-------
# 案例：指挥官AI
~~案例可能不符合实际逻辑，仅用于表述设计模式的思想，勿介意~~ 
假设我们开发了一款类似全面战争的即时战略游戏，为了能够增加玩家的对抗体验，我们决定设计一个指挥官AI，与以往的无脑人机不同，指挥官会根据战况以及玩家的操作，来指定克制玩家的计策。
例如当玩家派出骑兵时，指挥官就会派出枪兵，当玩家退回城中防守时，指挥官就会派出破城槌来攻城。

于是我们初步的设计如下，我们使用If-else这样的条件判断，根据玩家的不同行为来做出不同的操作。
```cpp
class Commander
{
    void doAction(const std::string& situation) 
    {
        if(situation == "wall")
        {
            //对付城墙的战术
        }
        else if(situation == "infantry")
        {
            //对付步兵的战术
        }
        else if(situation == "cavalry")
        {
            //对付骑兵的战术
        }
        ......
    }
}
```
如果对于简单的功能来说，这样的代码并没有什么问题，因为代码量不多，后续也不需要拓展和修改。但是对于一款战略游戏来说，战场上的形式千变万化，兵种、阵法、战术等策略可能达到庞大的数量。如果一个项目中写上成百上千个条件判断，那无论是拓展性、维护性、代码的可读性都十分的低下，所以我们需要考虑一下别的设计。

这时，就到了<font color=red>**策略模式**</font>大显身手的时候了

--------
# 策略模式 
<font color=red>**策略模式就是定义了一套算法族，将它们分别封装起来，让它们之间可以互相替换，这样就能够轻松的切换不同的算法来解决同一个问题的不同情况，这种模式让算法的变化独立于使用算法的客户端**</font>

策略模式由以下三者组成
- **Strategy(策略)**：策略的接口，所有的具体策略都需要实现它
- **ConcreteStrategy(具体的策略)**：具体的策略(如上面的骑兵、步兵、城墙策略)
- **Context(上下文)**：策略的使用者(如上面的指挥官)

类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201030171350128.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
下面就使用策略模式，来对代码进行优化

首先定义出Strategy接口，它提供一个getStrategy函数来帮助指挥官获取策略的内容
```cpp
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual void getStrategy() = 0;	//获取策略的内容
};
```
接着实现具体策略ConcreteStrategy

```cpp
class infantryStrategy : public Strategy
{
public:
    void getStrategy() override
    {
        std::cout << "计策：用弓箭手来对付步兵" << std::endl;
    }
};

class wallStrategy : public Strategy
{
public:
    void getStrategy() override
    {
        std::cout << "计策：用破城槌来破坏城墙" << std::endl;
    }
};

class cavalryStrategy : public Strategy
{
public:
    void getStrategy() override
    {
        std::cout << "计策：长枪兵来对付骑兵" << std::endl;
    }
};
```
因为考虑到程序的拓展，有可能我们后期还会推出各种指挥官的特化版本，因此我们实现一个通用的Context接口，并且下面这种设计能够动态的修改策略
```cpp
class Context
{
public:
    Context(Strategy* strategy = nullptr)
        : _strategy(strategy)
    {}

    virtual ~Context() = default;
    virtual void doAction() = 0;						//指挥官做出行动
    virtual void setstrategy(Strategy* strategy) = 0;	//变更策略

protected:
    Strategy* _strategy;	//策略指针，利用多态来转变不同的策略
};
```
接着实现我们具体的指挥官

```cpp
class Commander : public Context
{
    void doAction() override
    {
        if(_strategy)
        {
            _strategy->getStrategy();
        }
    }

    void setstrategy(Strategy* strategy) override
    {
        _strategy = strategy;
    }
};
```
写个程序测试一下，分别让指挥官执行两种策略
```cpp
int main()
{
    Context* commander = new Commander();    //指挥官对象
    Strategy* s1 = new cavalryStrategy;      //策略对象
    Strategy* s2 = new wallStrategy; 
           
    commander->setstrategy(s1);              //当玩家的骑兵到来的时候
    commander->doAction();

    commander->setstrategy(s2);              //当玩家退回城堡中防守时   
    commander->doAction();

    delete s2, s1, commander;
    return 0;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020103017361462.png#pic_center)
通过上面这种方法，我们很简单的就从If-else中脱身而出，并且如果当我们想要增加新策略的时候，也仅仅只需要让新类实现Strategy接口即可，而如果我们想增加新的Strategy类，如(指挥官自身的行动)，我们也只需要在Context中再组合上一个新的Strategy。

这样的代码不仅符合开放-封闭原则，而且通过对象组合建立的系统还具有很大的弹性。并且这种将算法族封装成类的方式还支持动态修改行为。

--------
# 配合工厂模式
上面代码还遗留一些小问题，我们在上面是直接指定了具体的某些策略，而通常在使用中我们的程序并不会这样的指定，而是会通过具体的场景来判断应该创建哪个策略来使用。

所以为了封装创建逻辑，并且对客户端代码屏蔽创建细节，我们可以运用上一篇所提到的<font color=red>**工厂模式**</font>，将根据场景创建策略的逻辑放到工厂类中

如果对于工厂模式不了解的可以看看我的往期博客
[趣谈设计模式 | 工厂模式(Factory)：利用工厂来创建对象](https://blog.csdn.net/qq_35423154/article/details/109359802)

```cpp
//策略工厂
class StrategyFactory
{
public:
    //加载所有的策略，即将策略对象缓存到工厂中
    StrategyFactory()
    {
        _strategys.insert(std::make_pair("wall", new wallStrategy));
        _strategys.insert(std::make_pair("infantry", new infantryStrategy));
        _strategys.insert(std::make_pair("cavalry", new cavalryStrategy));
    }

    //获取对应场景的策略
    Strategy* getStrategyObject(const std::string& situation)
    {
        return _strategys[situation];
    }
private:
    std::unordered_map<std::string, Strategy*> _strategys;   //利用哈希表来建立起场景和策略的映射
};
```
这时候我们只需要输入需求，就可以通过策略工厂来生成我们需要的策略对象了

```cpp
int main()
{
    Context* commander = new Commander();    //指挥官对象
    StrategyFactory factoty;                 //策略工厂
    
    
    commander->setstrategy(factoty.getStrategyObject("cavalry"));   //当玩家的骑兵到来的时候
    commander->doAction();

    commander->setstrategy(factoty.getStrategyObject("wall"));      //当玩家退回城堡中防守时   
    commander->doAction();

    delete commander;
    return 0;
}
```
需要注意的是上面生成的策略对象都是我们提前<font color=red>**缓存**</font>到策略工厂里的，因此都是<font color=red>**无状态**</font>的对象，里面不能有成员变量。

如果需要保存状态的策略对象，我们可以通过<font color=red>**查表法和元组**</font>来实现，由于那种场景并不常见，所以这里就不介绍了。

--------
# 总结
**要点**

- 策略模式由策略、策略接口、上下文三部分组成，主要作用就是用来解耦策略的定义、创建、使用
- 策略模式的核心就是策略的自由切换
- 为了避免策略类对外暴露，通常与工厂模式搭配使用
- 策略模式定义一族算法类，将每个算法分别封装起来，让它们可以互相替换。策略模式可以使算法的变化独立于使用它们的客户端(代指使用算法的代码)

**应用场景**

- 如果在一个系统里面有许多类，它们之间的区别仅在于它们的行为，希望动态地让一个对象在许多行为中选择一种行为时
-  一个决策者需要动态的在多种策略(算法)中选择一种时
- 一个对象有很多行为，不想使用冗长的条件判断语句来决定对象的行为时(即标题说的取代if-else)


