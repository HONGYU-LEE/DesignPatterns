[TOC]

------
由于代理模式相较于前面的其他设计模式来说更加简单，容易理解，所以为了保证内容不会太少，我除了介绍代理模式外还会重点介绍远程代理和虚拟代理，以及简单提及其他的一些代理模式的应用

# 案例：房屋中介
假设小明准备去外地实习，于是他需要租一间房来居住。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103135322799.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
但是由于身在外地，人生地不熟的他根本没办法和正在出租房屋的房东联系，于是他想到了一个好办法，找到具有人脉的房产中介来代替他租房
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103135632460.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
有了房产中介的加入，小明就可以通过中介来帮助他联系房东，进行租房。

但是此时又面临了一个问题，此时租房的行为是由中介来代为进行的，因此在房东眼里，这间房屋是中介在租，他根本不知道小明的存在。这就导致了一个问题，如果中介翻脸不认账独占房屋，又或者房东有急事要通知小明，那该怎么办呢？

小明让中介代替他去租房，实际租房的人并不是中介，而是小明。因此我们在中介租房的时候，应该清楚的告知房东租房的对象，于是逻辑图变化如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103140711238.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
以行为的角度来说，小明和中介要做的事情都是租房，所以在旁观人眼里，他们两个人都是寻求租房的人，因此我们可以将他们两人都归类为租房者
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103141410431.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
以代码的角度来实现的话，我们可以将租房者定义为一个接口

```cpp
class Tenant
{
public:
    virtual ~Tenant() = default;
    virtual void rentingHouse() = 0;	//租房
};
```
小明也是租房者，因此他会去实现这个接口

```cpp
class XiaoMing: public Tenant
{
public:
    void rentingHouse() override
    {
        std::cout << "小明需要租房！" << std::endl;
    }
};
```
而中介为了让房东知道租房的真实对象，他会保留小明的个人信息(小明对象的引用)，并且他除了执行小明的租房任务以外，还会附加新的逻辑(收取佣金)，代码如下
```cpp
class Proxy : public Tenant
{
public:
    Proxy(Tenant* client)
        : _client(client)
    {}

    void rentingHouse() override
    {
        _client->rentingHouse();      //代理行为
        std::cout << "中介代替客户去租房，并收取佣金" << std::endl; //新增的代理逻辑
    }

private:
    Tenant* _client;  //代理的客户，需要让目标知道租房的人是谁
};
```
下面测试一下逻辑是否正确
```cpp
int main()
{
    Tenant* xiaoming = new XiaoMing();      //小明
    Proxy* proxy = new Proxy(xiaoming);     //中介代理小明的租房行为

    proxy->rentingHouse();  //中介代替客户租房

    delete proxy, xiaoming;
    return 0;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103142457625.png#pic_center)
小明虽然不认识房东，但是他通过中介帮助他租房，上面所描述的这一系列行为，其实就是<font color=red>**代理模式**</font>

----
# 代理模式
<font color=red>**代理模式为其他对象提供一种代理以控制(隔离，使用接口)对这个对象的访问**</font>

代理模式由以下三部分组成
- **Subject**：RealSubject和Proxy的共同接口，利用多态的性质来保证RealSubject能够随时使用Proxy
- **RealSubject**：实体，业务逻辑的真实执行者，同时也是Proxy代表的对象。
- **Proxy**：代理，保存了实体的引用使其可以访问实体，并且实现了Subject接口，保证其能够随时利用代理来替代实体，并添加新的附加功能

类图如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103145600873.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
从之前所举的例子中，我们不难看出，<font color=red>**代理模式的意图就是通过代理实体，来为其附加新的功能。来达到业务逻辑与附加功能的解耦**</font>

在上面的例子中，中介为小明代理后，分析需求、寻找房源、联系房东、代替租房，这些行为全都由中介来实现，小明只需要关心租房这件事情，这样我们就达到了解耦合的目的。

如果以工程实践的角度来讲的话，就好比程序员(实体)只需要负责必须的业务功能实现，而对于如：监控、统计、日志等附加的功能就交由运维、数据分析人员(代理)来实现。

但是如果这样理解的话，那么代理模式岂不是和装饰器模式一样，都在为实体对象增加新功能吗？
## 代理模式与装饰器模式
不了解装饰器模式的可以看看我的往期博客
[趣谈设计模式 | 装饰器模式(Decorator)：用装饰来动态扩展功能](https://blog.csdn.net/qq_35423154/article/details/109393606)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103161439469.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
搬出装饰器模式的类图，我们发现它的结构其实与代理模式非常相似。

装饰器模式使用装饰器来包装实体，而代理模式使用代理来代理实体，他们都是用一个对象将另一个对象包起来，并且把调用委托给实体。并且在这个基础上，他们都为实体附加了新的行为。

但是在前面的博客中我也说过，虽然大体的结构相同，但是这并不意味这这两个设计模式一样，<font color=red>**真正决定设计模式的其实是它具体的设计意图**</font>

代理模式的核心意图是<font color=red>**控制对象的访问**</font>，<font color=red>**代理通过增加与实体类无关的附加行为来达到访问控制的目的**</font>。

装饰器模式的核心意图是<font color=red>**增强对象的功能，通过附加与实体相关的新行为的方式，来增加实体类原本的功能**</font>

----------
## 代理模式的应用
下面讲讲远程代理和虚拟代理，并简单提一下安全代理、智能引用代理、写时拷贝代理
### 远程代理
<font color=red>**远程代理也就是为一个对象在不同的地址空间提供局部代表，这样可以隐藏一个对象存在于不同地址空间的事实**</font>

例如我们借助代理服务器来访问外网的时候，就是使用的远程代理。我们将请求直接发送给代理服务器，而后代理服务器将请求转发到真实服务器并接收服务器的响应，最后代理服务器再将响应的结果归还给我们。这样就仿佛我们直接与真实服务器通信一样。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103160613815.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)

-------
### 虚拟代理
<font color=red>**虚拟代理，是根据需要创建开销很大的对象，通过它来存放实例化需要很长时间的真实对象，来达到性能的最优化。** </font>

例如我们在网上购物的时候，通常界面上会显示很多商品图片，但是由于图片过多或者图片过大导致加载速度慢，导致图片可能立即无法显示出来。在这段加载的使用中 ，我们就是使用虚拟代理来替代了真实的图片，而虚拟代理中则存储了真实图片的路径
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103155227115.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
上图中的白框即为虚拟代理，我们会先用它来暂时替代真实图片，并且虚拟代理还会在内部中继续加载真实图片，加载后如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201103155703211.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM1NDIzMTU0,size_16,color_FFFFFF,t_70#pic_center)
以代码来实现的话

```cpp
class Image
{
public:
    virtual ~Image() = default;
    virtual void display() = 0; //显示图片
};

class RealImage : public Image
{
public:
    RealImage(const std::string& imageName)
        : _imageName(imageName)
    {
        loadImage();    //加载真实图片
    }

    void display() override
    {
        std::cout << "显示真实图片" << _imageName << std::endl;
    }

    void loadImage()
    {
        std::cout << "加载真实图片" << _imageName << std::endl;
    }
private:
    std::string _imageName;
};

class ImageProxy : public Image
{
public:
    ImageProxy(const std::string& imageName)
        : _imageName(imageName)
        , _image(nullptr)
    {}

    ~ImageProxy()
    {
        if(_image)
        {
            delete _image;
        }
    }
    
    void display() override
    {
    	/*
    		显示等待语句或者图片
    	*/
        
        //加载真实图片
        if(_image == nullptr)
        {
           _image = new RealImage(_imageName);
        }
        _image->display(); //显示真实图片
    }

private:
    Image* _image;  //真实图片的引用
    std::string _imageName;	//图片名
};

int main()
{
    Image* proxy = new ImageProxy("test.jpg");
    proxy->display();	//暂时显示虚拟代理

    delete proxy;
    return 0;
}
```
------

下面的几种应用比较简单，因此就简单描述一下
### 安全代理
<font color=red>**用来控制对真实对象访问时的权限，通常在对象有不同的访问权限时使用**</font>

最典型的应用即**防火墙**，通过设定黑白名单以及访问权限，来控制对真实对象的访问。


### 智能引用代理
<font color=red>**当真实对象被引用时，代理进行额外的动作**</font>

最典型的就是**C++中的智能指针中的share_ptr**，对于实体资源来说，智能指针就是它的代理。当智能指针第一次引用资源的时候，就会对其进行管理，而当智能指针的生命周期结束，没有智能指针再引用这个资源时，就将这个资源给释放掉。

### 写时拷贝代理
<font color=red>**延迟对象的复制，直到客户真正需要它时**</font>
写时拷贝代理其实就是将**虚拟代理与引用计数**机制相结合，最典型的就是**Linux中父子进程的写时拷贝**。当父进程创建子进程时，为了避免不必要的拷贝，只有当子进程需要修改数据时，才会将去拷贝父进程的数据，否则继续使用父进程的数据。

---------
# 总结

- 代理模式为其他对象提供一种代理以控制对这个对象的访问 
- 代理模式用于控制访问，装饰器模式用于增强功能，两者虽然结构相同，但是意图不同。
- 将业务逻辑与附加功能解耦合，实体只需要关注自己部分的功能，而不用关心代理所做的事情，职责更加清晰，拓展性更高
- 在客户端和实体之间增加代理对象，导致请求的处理速度可能会变慢
