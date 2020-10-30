[TOC]

---------

工厂模式模式是创建型模式中较为常用的一个，它并不是一个模式，而是三种功能相近的设计模式的统称，它们分别是<font color=red>**简单工厂模式、工厂方法模式、抽象工厂模式**</font>，下面我将结合案例来一一讲解它们的特点
# 案例：外设店铺
假设我们经营着一家外设店铺，我们主要售卖雷蛇和罗技这两个型号的鼠标，为了方便用户购买，我们设计了一个网上购物的平台，用户在网上下单后我们会去根据需求来生成鼠标，再经过测试、包装、注册信息后，就将合格的产品发送给客户。于是我们设计的代码如下

我们设计了一个鼠标类，当有新型号的鼠标发布时，只需要继承这个类即可9
```cpp
class Mouse
{
public:
    virtual ~Mouse() = default;

    void showMessage() const
    {
        std::cout << "鼠标名：" << _name << "\n" << std::endl;
    }

    virtual void test()
    {
        std::cout << "正在对鼠标进行测试...." << std::endl;
    }

    virtual void packing()
    {
        std::cout << "正在对鼠标处理...." << std::endl;
    }

    virtual void registerItem()
    {
        std::cout << "正在注册鼠标的商品信息...." << std::endl;
    }
protected:
    std::string _name;
};
```
我们还实现了一个店铺类，用来处理订单以及销售
```cpp
class PeripheralStore
{
public:
    Mouse* orderMouse(const std::string& type) //订购鼠标
    {
        Mouse* mouse;	
        //确定生产的型号
        if(type == "Logitech_G403")
        {
            mouse = new Logitech_G403;
        }
        else if(type == "Logitech_G502")
        {
            mouse = new Logitech_G502;
        }
        else if(type == "Razer_DeathAdder")
        {
            mouse = new Razer_DeathAdder;
        }
        else if(type == "Razer_Mamba")
        {
            mouse = new Razer_Mamba;
        }

        mouse->test();          //测试鼠标
        mouse->packing();       //包装鼠标
        mouse->registerItem();  //注册商品信息

        return mouse;           //发货
    }   
};
```
但是随着产品的不断迭代以及我们的销量，我们售卖的产品时刻都会发生变化，因此我们就会经常来到这里对代码进行修改。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029145443721.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
我们发现，在这段代码中我们需要改变的只有上面生产鼠标的部分，而下面对鼠标的测试、包装、注册都是固定的步骤，是不需要改变的，而我们将这两者放在一起，违反了我们封闭原则，可能会因为我们生产的操作不当，影响这些固定功能的发挥。那我们要如何做呢？接下来就到<font color=red>**工厂模式**</font>发挥作用的时候了

-----
# 简单工厂
为了将生产与产品处理分割开，我们可以构建出一个鼠标工厂类，将生产鼠标的任务委托给它，它生产完后把鼠标给我们，我们进行处理后即可销售

鼠标工厂类实现起来很简单，我们只需要将原来创建鼠标的代码迁移过去即可

```cpp
class MouseFactory
{
public:
    Mouse* createMouse(const std::string& type)
    {
        Mouse* mouse;
        if(type == "Logitech_G403")
        {
            mouse = new Logitech_G403;
        }
        else if(type == "Logitech_G502")
        {
            mouse = new Logitech_G502;
        }
        else if(type == "Razer_DeathAdder")
        {
            mouse = new Razer_DeathAdder;
        }
        else if(type == "Razer_Mamba")
        {
            mouse = new Razer_Mamba;
        }

        return mouse;
    }
};
```
当有了工厂之后，为了将生产任务转交给工厂，店铺代码修改如下

```cpp
class PeripheralStore
{
public:
    Mouse* orderMouse(const std::string& type) //订购鼠标
    {
        Mouse* mouse;
        mouse = _factory.createMouse(type);	//让工厂生产鼠标
        
        mouse->test();          //测试鼠标
        mouse->packing();       //包装鼠标
        mouse->registerItem();  //注册商品信息

        return mouse;           //发货
    }   
private:
    MouseFactory _factory;	//工厂对象，让其来负责鼠标的生产
};
```
此时店铺的类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029153535663.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
<font color=red>**像这样通过工厂类创建对象，并且根据传入的参数决定具体子类对象的做法，就是简单工厂模式**</font>

有时候为了<font color=red>**避免实例化工厂对象**</font>，我们会将创建对象的方法声明为<font color=red>**静态**</font>的，所以简单工厂模式又被叫做<font color=red>**静态工厂方法模式**</font>，但是这种方法也存在缺点，它不能通过继承来改变创建方法的行为

-----
# 工厂方法
虽然我们实现了简单工厂模式，但是我们发现，如果我们新增或者减少鼠标的类型，我们就要去修改口罩工厂中的if-else判断，这不符合面向对象中的<font color=red>**开放-封闭原则**</font>，这样对旧代码的修改不仅容易出错，可读性也不好，我们拓展起来也十分麻烦，如何来优化它呢？

在上面的代码中，一个工厂类需要负责对所有具体鼠标类的实例化，我们可以进行一个转变，<font color=red>**让每个工厂只针对一种鼠标类的生产**</font>

我们可以将工厂抽象为一个接口，而为每一个鼠标型号都创建一个工厂子类，这些子类分别去实现工厂接口，如下

```cpp
class IMouseFactory
{
public:
    virtual Mouse* createMouse() = 0;
};

class Logitech_G403_Factory : public IMouseFactory
{
    Mouse* createMouse() override
    {
        return new Logitech_G403;
    }
};

class Razer_DeathAdder_Factory : public IMouseFactory
{
public:
    Mouse* createMouse() override
    {
        return new Razer_DeathAdder;
    }
};
```
当我们需要新增一个种类的鼠标的时候，只需要继承并实现工厂接口即可


这样一来，我们就依靠面向对象中的<font color=red>**多态**</font>，将每个工厂进行特化，当我们需要某一种类的鼠标时，只需要创建一个该类型的工厂并调用统一的接口，就可以得到这个类型的鼠标对象

```cpp
int main()
{
    Logitech_G403_Factory* G403_factory = new Logitech_G403_Factory;
    Razer_DeathAdder_Factory* DeathAdder_factory = new Razer_DeathAdder_Factory;
    
    Mouse* m1 = G403_factory->createMouse();
    m1->showMessage();
    Mouse* m2 = DeathAdder_factory->createMouse();
    m2->showMessage();

    delete m2;
    delete m1;
    delete G403_factory;
    delete DeathAdder_factory;

    return 0;
}
```
测试结果如下
![g.cn/20201029162602848.png#pic_center)](https://img-blog.csdnimg.cn/20201029195735758.png#pic_center)

上面这种做法也就是<font color=red>**工厂方法模式**</font>，其核心就是<font color=red>**每一个产品都对应一个工厂之类，并利用多态特性动态创建对象**</font>

<font color=red>**工厂方法模式定义了一个创建对象的接口，但由子类来决定要实例化的类是哪一个。工厂方法让类把实例化推迟到子类**</font>

此时的类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029163621141.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
从类图中可以看出，与简单工厂方法相比，工厂方法起到了<font color=red>**解耦合**</font>的作用，此时的无论是增加还是删除产品，都不会对工厂接口造成影响，这样我们程序就更具有弹性，未来想拓展产品时只需要实现接口即可。

但是在实际中，考虑到工厂方法过于复杂的问题，如果在业务逻辑十分简单的情况下，我们没必要使用工厂方法模式，这时使用简单工厂模式更加简单、方便

---
# 抽象工厂


随着商店越做越大，我们已经不满足于鼠标这个种类，我们想在商店中引入耳机、手柄、键盘等商品。但是如果我们还是使用工厂方法，那就意味着我们还需要创建耳机工厂、手柄工厂、键盘工厂.....并且根据它们的各种型号再次派生出大量的工厂类。

为了方便举例，这里假设每个种类的外设我们只卖一种型号 ~~(太多了图放不下,而且不好举例)~~ 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029194346348.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

如果每一个子类都对应一个工厂，那样不仅代码会越发繁琐，代码的维护也愈发艰难，所以此时就到了<font color=red>**抽象工厂模式**</font>大展身手的时候了

我们不需要再为每一个产品分配上一个工厂，<font color=red>**而是寻找它们之间的关联，将它们进行分组**。</font>对于上面的产品，我们可以发现主要就是雷蛇和罗技两个品牌，所以我们可以将它们按照品牌进行分组，建立罗技工厂和雷蛇工厂
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029194323395.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
所以我们根据品牌不同，抽象出一个品牌工厂接口，它提供了生产鼠标、键盘、耳机的接口

```cpp
class IPeripheralFactory
{
public:
virtual ~IPeripheralFactory() = default;
virtual Mouse* createMouse() = 0;
virtual Earphtones* createEarPhones () = 0;
virtual KeyBoard* createKeyBoard() = 0;
};
```
接着让雷蛇和罗技分别去实现这个接口

```cpp
class LogitechFactory : public IPeripheralFactory
{
    Mouse* createMouse() override
    {
        return new Razer_DeathAdder;
    }

    Earphtones* createEarPhones () override
    {
        return new Razer_Mako;
    }

    KeyBoard* createKeyBoard() override
    {
        return new Razer_Huntsman;
    }
};

class RazerFactory : public IPeripheralFactory
{
    Mouse* createMouse() override
    {
        return new Logitech_G502;
    }
    
    Earphtones* createEarPhones () override 
    {
        return new Logitech_G443;
    }

    KeyBoard* createKeyBoard() override
    {
        return new Logitech_G913;
    }
};
```
下面写一个测试程序，分别生产一个罗技鼠标和一个雷蛇键盘

```cpp
int main()
{
    IPeripheralFactory* logitech = new LogitechFactory;  //罗技工厂
    IPeripheralFactory* razer = new RazerFactory;        //雷蛇工厂

    Mouse* m1 = logitech->createMouse();
    m1->showMessage();

    KeyBoard* k1 = razer->createKeyBoard();
    k1->showMessage();

    delete k1;
    delete m1;
    delete logitech;
    delete razer;   
}
```
通过抽象工厂，我们就可以将产品划分为几个大家族
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029195629806.png#pic_center)
当我们想要增加新种类时(例如加入手柄)，就需要到抽象工厂接口以及每一个工厂类中添加一个新的方法。

说到这有人就会疑问，那么这不是不符合开放-封闭规则吗？确实，抽象工厂模式为了能够实现这样的分组，在这方面就做出了牺牲。

如果我们想对鼠标再进行一层细分，即想上面一样分为具体的型号，那就只需要对鼠标再实现一层的简单工厂或者工厂方法
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029215138399.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
并且我们还能发现，其实工厂方法早就以及潜伏在抽象工厂中

从上面的例子中我们可以得出，<font color=red>**抽象工厂模式其实就是依据某个特点来将相关(依赖)的产品分组，组内不同的产品就对应同一个工厂类中的不同方法。通过这种分组就能大大减少类的数量**</font>

抽象工厂允许客户使用抽象的接口来创建一组相关的产品，而不需要知道实际产出的产品是什么，这样一来就使得客户从具体的产品中被解耦

---------
# 总结
## 要点
- 所有的工厂模式都是用来封装对象的创建
- 所有工厂都通过减少应用程序和具体类之间的依赖来促进松耦合，更加具有弹性
- 所有的工厂都是针对抽象编程而非针对具体类编程
## 三类工厂模式的特点
**简单工厂模式**
- 简单工厂模式具有唯一的工厂类，通过对传入的参数做if-else判断来决定生产的对象

**工厂方法模式**
- 工厂方法模式提供了一个工厂接口，由多个派生工厂类实现接口，利用**继承**以及**多态**来创建不同的产品对象，避免了大量的条件判断
- 工厂方法将类的实例化推迟到了子类进行
- 工厂方法中一个工厂对应着一种产品，导致类的数量过多

**抽象工厂模式**
- 抽象工厂将具有关联(依赖)的产品进行分组，并且同组中的产品由同一个工厂子类的不同方法创建，大大减少了工厂类的数量
-    抽象工厂通过对象组合的方式维护了一个产品家族

## 三种工厂模式的适用场景
1. 当我们的对象创建的逻辑十分简单，并且可以将多个对象的创建逻辑放到一个工厂类时，就没必要大费周章，使用<font color=red>**简单工厂模式**</font>即可
2. 当对象创建逻辑复杂时，又或者是想将客户代码从具体类中解耦，又或者是我们并不知道未来还有哪些拓展的产品时，为了避免设计出一个庞大的简单工厂，我们会将创建逻辑细分，让每个类绑定一个工厂，这时就使用<font color=red>**工厂方法模式**</font>
3. 当需要创建产品家族，或者想让制造的相关产品集合起来时，就使用<font color=red>**抽象工厂模式**</font>

