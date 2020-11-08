[TOC]

-------------
# 单例模式
**一个类只能创建一个对象，即单例模式，该模式可以保证系统中该类只有一个实例，并提供一个访问它的全
局访问点，该实例被所有程序模块共享。** 比如在某个服务器程序中，该服务器的配置信息存放在一个文件
中，这些配置数据由一个单例对象统一读取，然后服务进程中的其他对象再通过这个单例对象获取这些配置
信息，这种方式简化了在复杂环境下的配置管理。

单例模式有两种常见的实现方法，分别是**懒汉模式**和**饿汉模式**。

---------
# 饿汉模式
作为一个饿汉，自然不会等到饥饿的时候才去做饭，而是马上就去提前做，等到饭点到了，就立刻开始吃。饿汉模式的核心就是**预加载**，**即不管你之后会不会用，程序启动时就会去加载所有的资源。**

```cpp
class EagerSingleton
{
public:
	//提供给外界一个唯一的对象
	static EagerSingleton* GetInstance()
	{
		return &_inst;
	}


	EagerSingleton& operator=(const EagerSingleton&) = delete; //c++11写法,为了防止拷贝，直接把拷贝构造和赋值运算符删除
	EagerSingleton(const EagerSingleton&) = delete;
private:
	//构造函数私有化，此时只能创建静态对象。
	EagerSingleton()
	{};

	/*
	c++98写法，将成员函数私有化，使得外界无法调用
	EagerSingleton& operator=(const EagerSingleton&);
	EagerSingleton(const EagerSingleton&);
	*/

	static EagerSingleton _inst;
	//使用静态的成员，因为静态成员属于整个类域，是唯一的一份。在程序开始阶段创建之后，其他人获取时只需要返回指向这个对象的指针即可
};

EagerSingleton EagerSingleton::_inst; //程序启动时则创建对象
```
从上面可以看到，因为一开始就直接加载了资源，所以饿汉模式并不存在线程安全的问题。在多线程高并发的环境下，性能需求较高时，就可以考虑使用饿汉模式来避免资源的竞争，提高响应速度。
但是他的缺点也正是这一点，因为无论后面用不用得到，都会提前加载资源，此时就会导致初始化的时间过长，导致效率不高。

----------
# 懒汉模式
故名思意，懒汉有严重的拖延症，只有事情到了，他才会去做，不会提前去做，与饿汉刚好相反。
他的核心就是**延时加载**，**只有使用到某一个资源的时候，才会去加载他**。这个特点就保证了他的高效，他**不会花费大量的时间在初始化上，并且只会去加载即将使用到的资源**。

但是也正因为懒汉模式在使用时才去创建，这就导致了可能会在多线程高并发的情况下争抢资源，导致线程安全的问题。

具体思路都在注释中
**核心**
1. double-cheak（提高效率）
2. 加锁防止争抢资源（保证线程安全）
3. 内嵌GC（程序结束即自动销毁资源）
```cpp
class LazySingleton
{
public:
	//获取对象
	static LazySingleton* GetInstance()
	{
		//双重检查，第一重检验是否创建对象，防止不必要的加锁
		if (_inst == nullptr)
		{
			//第二重检验保证线程安全
			//_mtx.lock();
			std::unique_lock<std::mutex> lock(_mtx);//RAII保证因异常抛出导致的安全问题
			if (_inst == nullptr)
			{
				_inst = new LazySingleton;
			}
			//_mtx.unlock();
		}
		return _inst;
	}

	//删除对象
	static void DelInstance()
	{
		std::unique_lock<std::mutex> lock(_mtx);

		delete _inst;
		_inst = nullptr;
	}

	//运用RAII的思想内嵌一个GC类，程序结束时自动调用析构函数来释放单例对象
	class GC
	{
	public:
		~GC()
		{
			LazySingleton::DelInstance();
		}
	};
	static GC gc;

	LazySingleton& operator=(const LazySingleton&) = delete; //c++11写法,为了防止拷贝，直接把拷贝构造和赋值运算符删除
	LazySingleton(const LazySingleton&) = delete;
private:

	LazySingleton()
	{};

	/*
	c++98写法，将成员函数私有化，使得外界无法调用
	LazySingleton& operator=(const LazySingleton&);
	LazySingleton(const LazySingleton&);
	*/

	static LazySingleton* _inst;
	static std::mutex _mtx;
};

LazySingleton::GC gc;
LazySingleton* LazySingleton::_inst = nullptr;
std::mutex LazySingleton::_mtx;
```

-------

# 懒汉和饿汉的区别
1. 懒汉模式需要考虑线程安全和资源释放的问题，实现来说相对复杂一点。饿汉模式不存在这类问题，实现相对简单。
2. 懒汉是一种懒加载模式，只在需要时才会创建对象，不会影响程序的启动。而饿汉模式刚好相反，程序启动阶段就创建对象，导致程序启动速度慢，影响用户体验。
3. 如果有多个单例类，假设之间存在着依赖关系，例如B依赖A，要求A单例先创建初始化，B单例再创建初始化
此时就不能够使用饿汉，因为无法保证其初始化顺序，而使用懒汉模式则可以手动控制