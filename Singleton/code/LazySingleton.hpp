#include<mutex>
#include<thread>
#include<vector>
#include<iostream>
namespace lee
{
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
};

