
namespace lee
{
	class EagerSingleton
	{
	public:
		static EagerSingleton* GetInstance()
		{
			return &_inst;
		}


		EagerSingleton& operator=(const EagerSingleton&) = delete; //c++11写法,为了防止拷贝，直接把拷贝构造和赋值运算符删除
		EagerSingleton(const EagerSingleton&) = delete;
	private:
		//构造函数私有化，此时只能创建静态对象，因为静态对象属于当前整个类域
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

	EagerSingleton EagerSingleton::_inst;
}

