[TOC]

--------------
# 案例：自动驾驶飞机
随着自动驾驶汽车的大卖，特X拉开始把目标转向飞行领域，打算开发出一款能够完全自动行驶的飞机，系统初步的设计如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106110945158.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
我们将所有系统的控制封装为方法提供给客户
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106111125839.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106111910997.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
客户只需要按照上面的步骤启动即可

但是，这样的设计存在着严重的问题
- 存在着大量的方法，用户存在学习成本
- 各个系统之间存在强耦合关系，例如我们不可能在没有能源的情况下启动导航和发动引擎
- 当需要关闭系统时，又要按照另一种关闭顺序进行关闭
- 当系统更新换代时，用户又需要学习另一套操作过程

上面的设计谈得上智能吗？自动驾驶飞机的本意就是要降低使用门槛，<font color=red>**因此我们不应该把这些底层的方法开放给客户，而是我们自己将其封装为一套合理的、方便使用的上层方法，用户只需要一键，就能够完成这些任务，这就是外观模式**</font>

--------
# 外观模式
<font color=red>**外观模式为子系统中的一组接口提供一个一致(稳定)的界面，Façade模式定义了一个高层接口，这个接口使得这一子系统更加容易使用(复用)。**</font>

外观模式由两部分组成
- **Facade(外观)**：负责将子系统中的接口整合为一个高层接口，供客户使用。外观中组合了子系统，并将任务委托给子系统处理
- **SubSystem(子系统)**：即系统的各个组件

类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106105804798.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
了解了外观模式后，设计师重新规划了设计图，新的设计如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106113121561.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
设计师将所有系统的启动、关闭方法封装成为一个上层的方法，这样用户就不再需要关系其中的细节以及依赖关系，只需要调用这一个方法即可。<font color=red>**不仅简化了接口，还将客户从组件的子系统中解耦**</font>

下面开始代码的实现，首先给出几个子系统的代码，为了方便演示子系统内容基本一样

```cpp
class EngineSystem
{
public:
    void systemOn()
    {
        std::cout << "启动能源系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭能源系统" << std::endl;
    }
};

class DynamicSystem
{
public:
    void systemOn()
    {
        std::cout << "启动动力系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭动力系统" << std::endl;
    }   
};
class CoolingSystem
{
public:
    void systemOn()
    {
        std::cout << "启动冷却系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭冷却系统" << std::endl;
    }
};

class NavigationSystem
{
public:
    void systemOn()
    {
        st-d::cout << "启动导航系统" << std::endl;
    }

    void systemOff()
    {
        std::cout << "关闭导航系统" << std::endl;
    }
};
```
接着我们将所有子系统的启动和关闭，按照他们之间的依赖关系封装为一个统一的启动、关闭方法，开放给上层
```cpp
class AutoAircraft
{
public:
    AutoAircraft()
        : _cooling(new CoolingSystem)
        , _dynamic(new DynamicSystem)
        , _engine(new EngineSystem)
        , _navigaton(new NavigationSystem)
    {}

    ~AutoAircraft()
    {
        delete _cooling, _dynamic, _engine, _navigaton;
    }

	//统一启动接口
    void systemOn()
    {
        _engine->systemOn();
        _cooling->systemOn();
        _dynamic->systemOn();
        _navigaton->systemOn();
    }

	//统一关闭接口
    void systemOff()
    {
        _navigaton->systemOff();
        _dynamic->systemOff();
        _cooling->systemOff();
        _engine->systemOff();
    }

private:
    CoolingSystem* _cooling;
    DynamicSystem* _dynamic;
    EngineSystem* _engine;
    NavigationSystem* _navigaton;
};
```

测试代码
```cpp
int main()
{
    AutoAircraft airCraft;
    airCraft.systemOn();
    cout << endl;
    airCraft.systemOff();

    return 0;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106105658952.png#pic_center)
在新的设计中，用户只需要执行开启和关闭，就能完成整个系统的开关，大大降低了操作的门槛，也避免了因为子系统互相依赖而发生的错误

---------
# 总结
**要点**
- 外观模式将客户从一个复杂的子系统中解耦，简化了用户操作
- 通常用于简化或者统一一群复杂的接口，减少系统相互依赖
- 需要将子系统组合进外观中，并且外观将工作委托给子系统，这就导致了不符合开放封闭原则，修改和拓展都有点麻烦


**应用场景**
- 当客户端不需要知道系统内部的复杂联系时，为复杂的模块或子系统封装一个供外界访问的入口
- 将多个低粒度接口整合为高粒度接口，减少通信成本，通常用于网络通信

