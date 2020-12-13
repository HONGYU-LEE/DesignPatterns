[TOC]

----------
# 案例：跨平台应用开发
A公司最近准备开发一组应用合集，目前包括了视频播放器、音乐播放器、文本播放器三种应用，但是在发售前，他们遇到了困难。

由于目前计算机系统繁多，且彼此之间大多不相互兼容，所以还需要针对不同平台，为应用进行处理。

在初步的设计中，A公司将平台抽象为接口，然后针对不同平台来实现应用，设计图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201213152220608.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)
这一设计乍一看没有什么问题，但是复用性却极差。

例如当A公司新开发了一个PDF阅读器时，就需要分别在这三个平台下都实现一个PDF阅读器，可由于这些PDF阅读器之间相差不大，代码的复用程度低。

而如果A公司此时想要兼容更多的平台，例如新加入了Android平台，就需要新增一个Android类，并且在其下实现所有之前的应用，这样的设计不仅代码复用性差，灵活性也不足。

于是A公司想到了第二种方案，按照具体应用的实现来进行分类，设计图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201213152719574.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)
但是由于这一设计的本质还是依赖于继承，所以它无论是平台，还是具体的应用发生了拓展，它都仍然存在着上面的问题。

引用GOF的观点

> **对象的继承关系是在编译时就定义好了的，所以无法在运行时改变从父类继承的实现。子类的实现与它的父类有非常紧密的依赖关系，以至于父类实现中的任何变化都必然会导致子类发生变化。当你需要复用子类时，如果继承下来的实现不适合解决性的问题，则父类必须重写或被其他更适合的类替换。这种依赖关系限制了灵活性并最终限制了复用性。**

那如何解决这个问题呢？我们可以考虑<font color=red>**用聚合代替继承**</font>

在上面的设计中，最大的问题就是平台以及应用之间存在着强耦合的关系，无论我们新增的是平台还是应用，都会对彼此造成影响。

既然如此，我们为何不将他们分离呢？
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201213165603181.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)
此时，平台和应用之间相互独立，当我们要新增平台，只需要去实现平台接口，应用也同理。

那么接下来如何处理平台与应用之间的关系呢？首先我们要知道，虽然平台中包含了各种应用，但是应用本身并不是平台的一部分，那么它们其实是<font color=red>**has-a**</font>的关系，所以我们可以使用<font color=red>**聚合(即A包含B，但B不是A的一部分**)**</font>来实现

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201213170005801.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)
通过聚合，既保证了平台与应用两者的独立变化，同时又保证了两者之间的包含关系。

聚合像桥梁一样将两者连接到一块，所以这种设计模式又叫做<font color=red>**桥接模式**</font>



------
# 桥接模式
<font color=red>**桥接模式将抽象部分与它的实现部分分离，使他们都可以独立地变化**</font>

> **什么叫将抽象和实现分离呢?
> 这里的抽象指的并不是抽象类或者接口，而是被抽象出来的一套“类库”，它只包含骨架代码，真正的业务逻辑需要委托给定义中的“实现”来完成。我们这里所说的实现也绝非接口的实现类，而是一套独立的“类库”。“抽象”和“实现”独立开发，通过对象之间的组合关系，组装在一起。**

桥接模式由以下部分组成
- **Abstraction(抽象)**：使用实现提供的接口来定义基本功能接口
- **Implementor(实现)**：提供了用于抽象的接口，它是一个抽象类或者接口。
- **RefinedAbstraction(提炼后的抽象)**：作为抽象的子类，增加新的功能，也就是增加新的接口（方法）
- **ConcreteImplementor(具体的实现)**：作为实现的子类，通过实现具体方法来实现接口

类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201212212502494.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)
根据桥接模式来改造我们的设计，如下图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201213152832490.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70)



首先分别实现“抽象”：平台，以及“实现”：软件

```cpp
#pragma once

class Implementor
{
public:
    virtual ~Implementor() = default;
    virtual void run() = 0;
};
```

```cpp
#pragma once
#include"Implementor.hpp"

class Abstraction
{
public:
    virtual ~Abstraction() = default;

    void setImplementor(Implementor* implementor)
    {
        _implementor = implementor;
    }

    virtual void run()
    {
        if(_implementor != nullptr)
        {
            _implementor->run();
        }
    }

protected:
    Implementor* _implementor = nullptr;
};
```

接着实现我们具体的实现，以及提炼后的抽象

```cpp
#pragma once
#include<iostream>
#include"Implementor.hpp"

class Music : public Implementor
{
public:
    void run() override
    {
        std::cout << "启动音乐播放器" << std::endl;
    }
};

class Vedio : public Implementor
{
public:
    void run() override
    {
        std::cout << "启动视频播放器" << std::endl;
    }
};

class Text : public Implementor
{
public:
    void run() override
    {
        std::cout << "启动文本阅读器" << std::endl;
    }
};
```

```cpp
#pragma once
#include<iostream>
#include"Abstraction.hpp"

class Linux : public Abstraction
{
public:
    void run() override
    {
        std::cout << "Linux系统：";
        _implementor->run();
    }
};

class Windows : public Abstraction
{
public:
    void run() override
    {
        std::cout << "Windows系统：";
        _implementor->run();
    }
};

class Mac : public Abstraction
{
public:
    void run() override
    {
        std::cout << "Mac系统：";
        _implementor->run();
    }
};
```

测试代码
```cpp
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
```
运行结果如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201213141748801.png)
在这种设计下，当我们需要拓展平台或者应用的时候，就只需要去实现对应的抽象类即可

--------
# 总结
**要点**
- 将抽象与实现分离，起到了解耦合的作用
- 抽象和实现可以独立拓展，不会影响到对方
- 实现细节对客户透明
- 增加了设计的复杂度，由于聚合关系建立在抽象层，要求开发者针对抽象进行设计与编程。

**应用场景**
- 适合使用在需要跨越多平台、型号的设计
- 需要用不同的方法改变接口与实现时
- 一个类存在两个独立变化的维度时

