[TOC]

-------
~~这个设计模式过于简单，所以不是很好举例......~~ 

# 案例：房屋建造
假设我们是建筑公司中的规划者，负责设定建筑方案，在初期我们主要承接两种装修方案，分别是下图的中式装修与西式装修
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201110210750885.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
代码表示如下
```cpp
class WesternStyle
{
public:
    void Foundation() 
    {
        std::cout << "打地基" << std::endl;
    }

    void Build() 
    {
        std::cout << "建筑房屋" << std::endl;
    }

    void Design() 
    {
        std::cout << "设计出西式风格的装修计划" << std::endl;
    }

    void Renovation() 
    {
        std::cout << "将房屋装修为西式风格" << std::endl;                                                                                                                                                
    }
};

class ChineseStyle
{
public:
    void Foundation() 
    {
        std::cout << "打地基" << std::endl;
    }

    void Build() 
    {
        std::cout << "建筑房屋" << std::endl;
    }

    void Design() 
    {
        std::cout << "设计出中式风格的装修计划" << std::endl;
    }

    void Renovation() 
    {
        std::cout << "将房屋装修为中式风格" << std::endl;                                                                                                                                                
    }
};
```
随着公司不断发展，承接的项目也越来越多，我们开始往新的设计方案发展，如日式、欧式、复古式、奢华式等风格，但是在项目的拓展中，我们遇到了问题。

上面的代码中存在着严重的设计问题，我们将同样的代码重复写了多次，不仅仅降低了效率，还可能会因为疏忽导致错误，缺少代码复用。

虽然建筑方案不同，但是其中的地基、建筑房屋等步骤是永恒不变的，变化的只有设计与装修，我们可以将其抽象出来，设定为一个装修的抽象模板类，而那些具体风格的实现，则放到派生类中进行

设计方案如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201110213557546.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)




由于房屋建造的顺序是固定的，并且地基和房屋建造都是完全相同的步骤，只有后期的设计与装修才是不同的，因此我们将那部分相同的内容定义为final，然后将不同的部分抽象为接口，让具体派生类实现。
```cpp
class BuildTemplate
{
public:
    virtual ~BuildTemplate() = default;
    virtual void TemplateMethod() final	
    {
        Foundation();
        Build();
        Design();
        Renovation();
    }

protected:
    virtual void Design() = 0;
    virtual void Renovation() = 0;

    virtual void Foundation() final
    {
        std::cout << "打地基" << std::endl;
    }

    virtual void Build() final
    {
        std::cout << "建筑房屋" << std::endl;
    }
};
```
接着在派生类中完成具体设计与装修的实现
```cpp
class WesternStyle : public BuildTemplate
{
protected:
    void Design() override
    {
        std::cout << "设计出西式风格的装修计划" << std::endl;
    }

    
    void Renovation() override
    {
        std::cout << "将房屋装修为西式风格" << std::endl;                                                                                                                                                
    }
};

class ChineseStyle : public BuildTemplate
{
protected:
    void Design() override
    {
        std::cout << "设计出中式风格的装修计划" << std::endl;
    }

    
    void Renovation() override
    {
        std::cout << "将房屋装修为中式风格" << std::endl;                                                                                                                                                
    }
};
```
下面进行一下测试
```cpp
int main()
{
    BuildTemplate* chinese = new ChineseStyle;
    BuildTemplate* western = new WesternStyle;
    
    chinese->TemplateMethod();
    cout << endl;
    western->TemplateMethod();

    delete chinese, western;
    return 0;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020111020552963.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
上面的这种设计方法，就是<font color=red>**模板方法模式**</font>

------
# 模板方法模式
<font color=red>**模板方法模式定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。**</font>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201110203721696.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
模板方法模式由以下两部分组成
- **AbstractClass(抽象基类)**：实现了一个模板方法，定义算法的骨架，将一些会变化的操作封装为接口让子类实现
- **ConcreteClass(派生类)**：子类实现接口来完成那些与自己相关的操作

从上面的例子中可以看出，当不变的行为和可变的行为混合在一起时，就会导致不变的行为重复的出现，存在大量的代码冗余现象。

因此我们可以通过模板方法模式将这两部分分离，<font color=red>**将不变的部分移动到父类中，而变化的部分就由子类来实现**</font>，这样就能够使得我们的设计具有良好的代码复用能力。

-----------
# 模板方法模式与策略模式
在之前的博客博客中我还提到过另一个封装算法的模式，也就是策略模式
[趣谈设计模式 | 策略模式(Strategy)：你还在使用冗长的if-else吗？](https://blog.csdn.net/qq_35423154/article/details/109388643)

虽然它们两个同样是封装算法，但是它们的意图完全不同。

对于模板方法模式来说，父类定义出一个算法的骨架，将算法中不变的部分放入骨架中，而变化的部分则通过<font color=red>**继承**</font>交由子类实现，因此算法的控制权主要掌握在父类手中。主要目的就是用于<font color=red>**代码复用**</font>

对于策略模式来说，由于其使用<font color=red>**对象组合**</font>的方式，将具体算法委托给策略类，因此其放弃了对算法的控制，但也因此客户能够随意的根据情况来切换不同的算法，更加具有弹性。它的主要目的就是用于<font color=red>**根据问题的不同情况来切换不同的算法解决问题**</font>

----------

# 总结
**要点**
- 将算法中公共的、不变的部分封装为父类的模板，而变化的部分则交给子类实现
- 为了防止模板被修改，需要将其声明为final
- 策略模式和模板方法模式都封装算法，一个使用组合，一个使用继承，一个封装完整的算法，一个封装算法的细节

**应用场景**
- 有多个子类共有的方法，且逻辑相同
- 重要的、复杂的方法，可以考虑作为模板方法

