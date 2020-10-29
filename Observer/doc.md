[TOC]

-------
# 案例：文章推送
假设我是一个科幻小说爱好者，我维护着一个叫做ScienceFictionPusher的公众号，定期向豆瓣、知乎等平台推送那些我觉得有趣的科幻小说，于是为了方便管理，我的推送程序是这样的逻辑
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020102821324384.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

```cpp
class ScienceFictionPusher 
{
public:
	//推送内容
    void newPush()
    {
    	//分别向各大平台推送内容
        _zhihu->update(_url, _title, _desc);
        _douban->update(_url, _title, _desc);
    }
	
	//设置新的内容
    void setNewFiction(const std::string& url, const std::string& title, const std::string& desc)
    {
        _url = url;
        _title = title;-
        _desc = desc;
        newPush();
    }

private:
    std::string _url;    //小说链接
    std::string _title;  //小说名
    std::string _desc;   //小说简介
    Douban* _douban;
    Zhihu* _zhihu;
};
```
上面这种实现方式咋一看没什么问题，甚至在某些地方处理的还不错，因为我们将内容的更新从平台主动的拉取变为了公众号的主动推送，大大减少了空转时间。因此，我们将代码投入使用

随着粉丝越来越多，公众号的名气也越来越大，于是乎越来越多的平台开始邀请我的专栏入驻，但是此时就出现了问题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028213549218.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
如果采用上面这种模式的话，当有大量的平台时，代码会是这样的，存在大量的冗余，可读性也极差

```cpp
void newPush()
{
 	//分别向各大平台推送内容
     _zhihu->update(_url, _title, _desc);
     _douban->update(_url, _title, _desc);
     _wechat->update(_url, _title, _desc);
     _uc->update(_url, _title, _desc);
     _tiktok->update(_url, _title, _desc);
     _bilibili->update(_url, _title, _desc);
     _baidu->update(_url, _title, _desc);
     _csdn->update(_url, _title, _desc);
     ...........................
 }
```
由于公众号的经营也存在波动，当流量大的时候我们会有新增的平台，当某个平台流量小的时候我们也不会再去维护，所以平台的数量是时刻变化的，那这样的代码就意味着我们需要时刻去程序中修改，无法动态的增加、删除，效率极低。

那有什么好的解决方法吗？这就到了<font color=red>**观察者模式**</font> 出场的时候

------
# 观察者模式
<font color=red>**观察者模式也叫做发布订阅模式，它定义了对象之间的一对多依赖，当一个对象改变状态的时候，它的所有依赖着都会收到通知并自动更新。**</font>

为了方便举例，这里我们将<font color=red>**发布内容的对象称为主题**，**接收内容的对象称为观察者**</font>

## 观察者模式的运作流程
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028224336162.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

此时对象C也想要获取内容，所以它告诉主题他想要注册成为观察者
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028224416564.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028224519299.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
由于主题发布的内容质量逐渐降低，对象A不再需要订阅，此时它请求注销主题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028224618832.png#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028224648108.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
从上面我们可以看到，主题主要做了三件事，注册、删除、通知观察者。而观察者所做的只是被动的接受主题提供的数据

## 观察者模式解决的问题

讲了这么多，其实观察者模式最主要的作用就是<font color=red>**让主题和观察者松耦合：即这两个对象虽然互相可以交互，但是它们都不清楚彼此的细节**</font>

主题只知道观察者实现了Observer接口，它并不需要知道观察者的具体类是谁，也不需要了解它究竟实现了什么，它只需要调用观察者的update将数据更新过去即可。

同样的，因为主题依赖的只是实现了Observer接口的对象列表，所以无论我们是对观察者增加还是删除，都不会对主题造成影响，主题也不需要为了兼容这些观察者而去修改代码。

甚至我们还可以在其他地方独立的复用主题和观察者，例如我们新增一个新的主题，又或者是新增一个观察者，由于二者并非紧耦合，所以不会有任何的影响。

<font color=red>**总结一下就是，这种设计将对象之间的互相依赖降到了最低，因此我们的程序具有弹性，能够应对各种变化。**</font>

-------
# 观察者模式大显身手
回到上面的问题，当我们的公众号发布新内容的时候，我们会将这些内容推送到所有的入驻平台中，这正好就符合上面所说的观察者模式的场景。此时公众号充当主题对象，而平台充当观察者。

此时完整的关系图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028222113760.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
根据上面所提到的内容，我们抽象出具体的主题接口和观察者接口。为了方便使用不同语言的读者阅读，我会尽量少用C++的特性，如果还是有不理解的可以私信或者评论区留言。

主题接口只需要提供必须的注册、删除、发布即可
```cpp
class Subject
{
public:
    virtual ~Subject() = default;
    virtual void registerObserver(Observer*) = 0;   //注册观察者
    virtual void removeObserver(Observer*) = 0;     //移除观察者
    virtual void notifyObservers() = 0;             //通知所有观察者
};
```
观察者被动等待主题的数据，所以我们也只提供一个更新接口供主题更新数据
```cpp
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& url, const std::string& title, const std::string& desc) = 0;      //更新数据
};
```
考虑到每个平台获取到新内容都必定要将其展示出来，而每个平台展示的方式又有所不同，所以我们将其再抽象为一个接口类，观察者需要继承这个类并实现自己的展示方法

```cpp
class DisplayElement
{
public:
    virtual ~DisplayElement() = default;
    virtual void display() = 0;     //显示数据
};
```
下面就开始具体实例的实现吧

为了保证不会对同一平台重复发送，以及后续可能会对某些平台单独推送内容，我们使用一个<font color=red>**哈希表**</font>来存储所有入驻的平台
```cpp
//主题派生子类
class ScienceFictionPusher : public Subject
{
public:
	//增加观察者
    void registerObserver(Observer* observer)
    {
        _observers.insert(observer);
    }
	
	//删除观察者
    void removeObserver(Observer* observer)
    {
        _observers.erase(observer);
    }
	
	//向所有平台推送内容
    void notifyObservers()
    {
        for(const auto& ob : _observers)
        {
            ob->update(_url, _title, _desc);
        }
    }
	
	//推送新内容
    void newPush()
    {
        notifyObservers();
    }
	
	//设置新内容，当有新内容发布的时候，就会自动推送给所有的平台
    void setNewFiction(const std::string& url, const std::string& title, const std::string& desc)
    {
        _url = url;
        _title = title;
        _desc = desc;
        newPush();
    }

private:
    std::string _url;    //小说链接
    std::string _title;  //小说名
    std::string _desc;   //小说简介
    std::unordered_set<Observer*> _observers;   //入驻的平台
};
```
当有新的平台想要入驻的时候，它只需要继承观察者类并实现update接口即可，同时由于我们接收新内容后还需要在自身平台中显示，所以还需要继承发布内容类，并实现display接口

为了方便注册和删除观察者，我们需要保存一个指向主题的指针

```cpp
//观察者派生子类
class Zhihu : public Observer, public DisplayElement
{
public:
    Zhihu(Subject* ScienceFictionPusher)
        : _ScienceFictionPusher(ScienceFictionPusher)
    {
        _ScienceFictionPusher->registerObserver(this);
    }

    ~Zhihu()
    {
        _ScienceFictionPusher->removeObserver(this);
    }

	//实现更新接口，让主题主动推送数据
    void update(const std::string& url, const std::string& title, const std::string& desc)
    {
        _url = url;
        _title = title;
        _desc = desc;

        display();
    }
	
	//在平台中显示推送的内容
    void display()
    {
        std::cout << "知乎每日书籍推荐：" << std::endl;
        std::cout << "链接：" << _url << std::endl;
        std::cout << "标题：" << _title << std::endl;
        std::cout << "简介：" << _desc << "\n" <<std::endl; 
    }
    
private:
    std::string _url;    //小说链接
    std::string _title;  //小说名
    std::string _desc;   //小说简介
    Subject* _ScienceFictionPusher; //主题对象，方便注册和删除
};
```
其他的观察者也类似，为了节省篇幅这里就不多写了，下面写个简单的程序测试一下

```cpp
int main()
{
    ScienceFictionPusher* _subject = new ScienceFictionPusher;
    Douban* douban = new Douban(_subject);
    Zhihu* zhihu = new Zhihu(_subject);

    _subject->setNewFiction("www.aaaaaaa.com", "三体", "作品讲述了地球人类文明和三体文明的信息交流、生死搏杀及两个文明在宇宙中的兴衰历程。");
    _subject->setNewFiction("www.bbbbbbb.com", "球形闪电", "描述了一个历经球状闪电的男主角对其历尽艰辛的研究历程，向我们展现了一个独特、神秘而离奇的世界");

    delete zhihu;
    delete douban;
    delete _subject;
    
    return 0;
}
```
我们添加了知乎和豆瓣两个观察者，并且连续推送了三体和球形闪电这两条内容
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028220410318.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
可以看到，测试结果没有问题

-------

# 总结
## 要点
- 观察者模式定义了对象之间一对多的关系
- 观察者模式使得我们可以独立地改变主题与观察者，从而使二者之间的依赖关系达致松耦合。主题不知道观察者接口
- 主题发送通知时，需要遍历观察者，因此其知道观察者的存在
- 观察者自己决定是否需要订阅通知，主题对象对此一无所知。

-------
## 应用场景
观察者模式应该可以说是应用最多、影响最广的模式之一，它通常应用于游戏引擎、GUI、邮件订阅等场景

**场景1 ：游戏中的事件监控**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028232238491.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

例如我们设计了一个RPG游戏，当我们的角色移动到敌人的视野范围时，周围的敌人就会向角色移动并且发起攻击。当我们移动到陷阱的触发位置时，陷阱就会对我们造成伤害。当我们移动到泉水时，泉水又会为角色提供治疗或者BUFF。

在上面的例子中，我们的角色就是一个主题，而泉水、陷阱、敌人这些就是观察者，当我们做出了某种举动的时候，就会通知它们这些事件的发生，它们就会做出一个具体的响应。这样就能够保证事件实时的同步，以及方便我们进行拓展，后续向增加新事件例如减速的泥潭等内容只需要将其注册为观察者并实现逻辑即可。

**场景2：GUI界面的事件侦听**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201028232505867.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
在GUI界面中，通常有着许多的选项， 而在这些选项背后，通常又有多个负责不同功能的侦听者等待我们的结果，当我们按下这个按钮的时候，就会通知负责这一功能的一系列侦听者响应号召，执行它们各自的工作，这也是一种观察者模式

-----
## 生产者-消费者模型 VS 观察者模式
说到数据的生产和发布、解耦合这两方面，那就难免要提到<font color=red>**生产者消费者模型**</font>，下面给出它们两个的对比图。

如果不了解生产者消费者模型的可以参考我的往期博客
[操作系统：生产者消费者模型的两种实现（C++）](https://blog.csdn.net/qq_35423154/article/details/106149185)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029104204422.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201029104741999.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
**相同点**
- 主要作用都是解耦合
- 两者都是行为模式，本质上都是发布-消费两个行为

**不同点**
- 观察者模式是一对多，一条消息可以被多个观察者使用
- 生产者-消费者模型是多对多的，并且一条消息只能被一个消费者使用
- 观察者模式可以同步实现，也可以异步实现
- 生产者消费者模式依赖于交易场所，只能异步实现
- 观察者模式中主题知道观察者的存在，因为它需要遍历订阅列表发送通知，因此两者之间还是存在微弱的耦合关系
- 生产者和消费者借助交易场所(中间队列)，它们只需要往队列中生成/消费数据，因此不需要知道对方的存在，属于完全解耦

