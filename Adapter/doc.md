[TOC]

-------
# 案例：数据线转换器
相信对于安卓用户，曾经或多或少都有着因为接口不适配而带来的苦恼。当你在更换手机时，可能会因为新手机中不配数据线，而自己的旧手机的数据线接口不同而带来烦恼。又或者是当我们购买耳机、充电宝、手机U盘时由于接口不同而导致产品无法使用的情况。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106164949238.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
由于当年type-c是为了解决快充而实现的新接口，使用者大部分都是些新生代、追求效率的公司，而市面上大部分公司都仍然使用传统的Micro USB接口，所以为大家的使用带来了困难。

想要解决这个问题的方法有好几种，第一种就是让市面统一接口，但是这很明显不现实，因为技术的变革总是会伴随着争议，保守方和革新方的斗争往往都是长期的，不可能一下子改变。

而第二种方法则有些特别，既然市面上大多数都是使用Micro USB，那我们为何不推出一种适配器，让我们的新接口能够使用这些传统的产品呢？
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106165716263.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
这也就是我们今天所要提到的适配器模式的原理，让现存的设备能够应用于新的环境。

-------
# 适配器模式
<font color=red>**将一个类的接口转换成客户希望的另一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。**</font>

适配器模式由以下三部分组成
- **Target(目标)**：客户期望使用的接口
- **Adaptee(适配者)**：我们当前具备的，即需要被适配的类
- **Adapter(适配器)**：用于适配目标和适配者，在内部将目标接口转换为适配者的接口

适配器模式有两种实现方式：<font color=red>**类适配器**</font>和<font color=red>**对象适配器**</font>。其中，<font color=red>**类适配器使用继承关系来实现，对象适配器使用组合关系来实现。**</font>(由于类适配器需要用到多继承，所以在除了C++外的大多数面向对象语言中都不适用)

两种实现方法的类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106163132381.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106163138440.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
下面分别用这两种方法来实现我们的数据线适配器

首先为了方便举例，先给出适配者Type-C和目标MicroUSB的代码

```cpp
class Type_C
{
public:
    virtual ~Type_C() = default;
    void useTypeC()
    {
        std::cout << "使用Type-C数据线" << std::endl;
    }
};

class MicroUSB
{
public:
    virtual ~MicroUSB() = default;
    virtual void useMicroUSB()
    {
        std::cout << "使用Micro USB数据线" << std::endl;
    }
};

```

类适配器，通过<font color=red>**继承**</font>来调用适配者的方法
```cpp
//类适配器，通过继承来实现
class ClassAdapter : public MicroUSB, Type_C
{
public:
    void useMicroUSB() override
    {
        std::cout << "使用类适配器将Type-C转换为Micro USB" << std::endl;
        useTypeC();
    }
};
```
对象适配器，通过<font color=red>**组合**</font>适配者来实现方法的复用
```cpp
//对象适配器
class ObjectAdapter : public MicroUSB
{
public:
    ObjectAdapter(Type_C* typeC)
        : _typeC(typeC)
    {}

    void useMicroUSB() override
    {
        std::cout << "使用对象适配器将Type-C转换为Micro USB" << std::endl;
        _typeC->useTypeC();
    }
private:
    Type_C* _typeC;
};
```

下面测试两种适配器是否成功运作

```cpp
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
```
这样，我们的TYPE-C就可以适配于Micro USB的设备了
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201106163004728.png#pic_center)

-------
# “补偿”模式
在上面我们也提到了，适配器模式的主要应用场景就是<font color=red>**接口不兼容**</font>的情况，而在设计阶段时，我们完全可以通过<font color=red>**统一调用同一接口**</font>来更加简单、直接的解决这个问题。

因此适配器模式并不适合在设计的阶段实现，因为我们有更好的选择，所以我更偏向将适配器模式称为<font color=red>**补偿模式**</font>，当系统的开发已经完毕，在代码难以重构或者不容易修改的情况下，就可以使用适配器模式来<font color=red>**补救设计上的缺陷**</font>。最常见的场景就是遗留代码复用、类库迁移等

当然上面的说法也不是绝对的，如果我们在一开始设计的时候就考虑搭配多种第三方组件，而又不想去迎合它们而改动自己的接口，这时也可以考虑通过适配器来解决接口不同的问题。

------
# 总结
**要点**
- 适配器的主要工作就是转换接口以符合客户的期望
- 当需要使用一个现有的类，而接口不符合我们的需求时，就可以通过适配器来转换其接口
- 适配器有两种实现方法，基于多继承的类适配器和基于组合的对象适配器
- 通过适配器可以让两个无关联的类一起允许，提高了类的复用。但是与之相应的也会让系统更加凌乱，因为我们明明需要的时类A，结果实际调用的是适配器中的类B，使得代码不容易理解。


**应用场景**
- 封装有缺陷的接口设计时
- 需要兼容老版本时
- 需要统一多个类的接口设计时
- 需要适配多种情况时
