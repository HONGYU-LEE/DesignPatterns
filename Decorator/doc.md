[TOC]

---------
# 案例：奶茶店
小明经营着一家奶茶店，由于疫情导致线下销量不佳，于是他准备拓展网上订餐业务，针对下面的菜单设计了一套订餐系统
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031164441797.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031170144777.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
小明初步的设计如下，使用一个抽象类饮料，并让所有类型的饮品继承于它，并且里面包含返回描述信息与价钱的方法，代码如下

```cpp
class Beverage
{
public:
    virtual ~Beverage() = default;
    virtual double cost() = 0;

    virtual std::string getDescription()
    {
        return _desc;
    }

    std::string _desc;
};
```
由于我们还可以自由的搭配配料，如为奶茶增加椰果和珍珠，这种混搭的组合饮料的价钱和描述信息都会发生改变。如果我们让混搭的饮品直接继承于饮品种类的话，就会出现下面这种场景
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031170919829.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
如果每种不同的搭配都由一个类来表示的话，就会出现<font color=red>**类爆炸**</font>的情况，因为我们可以无限制的增加配料的数量，不断地排列，类的数量就会无休止的扩张。

这就导致了我们的维护和拓展都会变成一场噩梦。由于不符合<font color=red>**开放-封闭原则**</font>，如果我们想修改珍珠的价格，就需要到它所有的搭配中进行修改，如果我们想新增配料布丁，又会产生出一系列的组合类。

所以我们可以尝试换个角度思考，试着用<font color=red>**组合**</font>来完成这个任务。我们可以将奶茶、红茶、咖啡等饮品当做饮品的<font color=red>**主体**</font>，而将珍珠、椰果等配料当坐为其点缀的<font color=red>**装饰品**。</font>

例如用户点了一杯奶茶，加了两份珍珠，一份椰果，此时的构造关系如下
我们先准备一份奶茶
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031194041106.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
然后为其加上一份椰果
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031194208526.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
再为其加上两份珍珠
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020103119443514.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
通过这样的对象组合，我们就能够将原来成百上千的饮品类，压缩为几个主体饮品类和配料类。这种方法其实就是<font color=red>**装饰器模式**</font>

-------
# 装饰器模式
<font color=red>**装饰器模式动态地将责任附加到对象上。就增加功能而已，比继承更加灵活。其本质就是用组合来代替继承，防止继承关系过于复杂**</font>

装饰器模式由以下四个部分组成
- **组件(Component)**：抽象类或者接口，保证装饰者能够自由的装饰被装饰者，它们必须具有相同的父类型
- **被装饰者(ConcreteComponent)**：需要动态添加添加新行为的对象(如例子中的饮料)，继承自组件
- **装饰者(Decorator)**：装饰器接口，虽然继承于组件，但是由于其同时内含了一个组件，所以实际上并不是is-a，而是has-a的关系，即组合。例如上面的调料
- **装饰器的具体实例(ConcreteDecorator)**：实现了装饰者接口的具体的装饰对象，例如例子中的珍珠、牛奶、椰果

类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031191435139.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

由于需要创建大量的装饰器对象来装饰饮品，因此可能会有内存泄漏的问题，需要引入智能指针来解决，但是考虑到不了解C++的人可能看不懂，所以这里就不考虑这个问题，修改后的代码我放在了末尾的github链接中

提供一个组件，也就是饮品抽象类，让装饰者和被装饰者都继承它，来达到自由搭配的目的

```cpp
class Beverage
{
public:
    virtual ~Beverage() = default;
    virtual double cost() = 0;	//获取当前价值

	//获取描述信息
    virtual std::string getDescription()
    {
        return _desc;
    }
protected:
    std::string _desc;	//描述信息
};
```

实现具体饮品的代码

```cpp
class RedTea : public Beverage
{
public:
    RedTea()
    {
        _desc = "RedTea";	//饮品的描述信息
    }

    double cost() override
    {
        return 10.5;		//饮品的价格
    }
};
```

下面实现装饰品类，需要注意的是我们需要保留一个指向被装饰者的指针，来为其添加装饰
```cpp
class Condiment : public Beverage
{
public:
    Condiment(Beverage* beverage)
        : _beverage(beverage)
    {}
    virtual ~Condiment() = default;

protected:
    Beverage* _beverage;	//被装饰者的指针
};
```
实现一个珍珠类，其中把调用委托给被装饰的对象，再加上装饰者本身的内容，完成装饰

```cpp
class Pearl : public Condiment
{
public:
    Pearl(Beverage* beverage)
        : Condiment(beverage)
    {}

	//将新职责附加到被装饰者，新增加上配料后的描述
    std::string getDescription() override
    {
        return _beverage->getDescription() + " + Pearl";
    }
	//添加加上配料后的价钱
    double cost()
    {
        return _beverage->cost() + 1.5;
    }
};
```
最后给出我们具体的类图，方便理解
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031211148495.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

下面写个程序测试一下，为红茶添加两份牛奶、一份珍珠、一份椰果作为装饰
```cpp
int main()
{
    Beverage* drink1 = new RedTea;	//红茶主题
    drink1 = new Milk(drink1);		//用牛奶进行装饰
    drink1 = new Pearl(drink1);		//用珍珠进行装饰
    drink1 = new Coconut(drink1);	//用椰果进行装饰
    drink1 = new Milk(drink1);		//用牛奶进行装饰
       
    cout << drink1->getDescription() << endl;
    cout << drink1->cost() << endl;

    return 0;
}
```
执行结果没有问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201031200209442.png#pic_center)
通过这样的设计，我们将装饰器和被装饰者<font color=red>**完全解耦**</font>，使得它们可以相互独立的拓展，完全符合开放-封闭原则。

当我们要增加新的饮品的时候，例如果汁，就只需要让其继承组件抽象类即可，而如果想增加如红豆等新配料，就只需要让其实现装饰器接口即可。由于完全遵守开放封闭原则，所以追加这些新内容的时候完全不需要修改原对象

但是他也有致命的缺点，就是<font color=red>**生成大量的装饰者会大大的增加代码的复杂程度以及带来内存泄漏的风险**</font>，所以通常会利用<font color=red>**RAII机制以及工厂模式、生成器模式**</font>来帮助解决这些问题。

---------
# 总结
**要点**

- 装饰器模式是继承的一个替代模式，可以动态拓展一个实现类的功能
- 装饰者和被装饰者之间不会互相耦合，可以各自独立发展
- 装饰者可以在被装饰者的行为前/后加上自己的行为，以达到特定的目的
- 装饰者和被装饰者具有相同的父类型，因此可以用无数个装饰者来装饰一个组件
- 装饰者对导致设计中出现大量的装饰者对象，如果过度使用会让程序变得复杂，特别是C++这种没有GC机制的语言，最好使用智能指针进行管理，防止内存泄漏。

**应用场景**

- 在不想增加很多子类的情况下拓展类
- 需要动态增加/撤销功能
- 不想让继承关系过于复杂，需要用组合来替代继承时
