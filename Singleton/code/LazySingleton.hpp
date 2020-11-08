#include<mutex>
#include<thread>
#include<vector>
#include<iostream>
namespace lee
{
	class LazySingleton
	{
	public:
		//��ȡ����
		static LazySingleton* GetInstance()
		{
			//˫�ؼ�飬��һ�ؼ����Ƿ񴴽����󣬷�ֹ����Ҫ�ļ���
			if (_inst == nullptr)
			{
				//�ڶ��ؼ��鱣֤�̰߳�ȫ
				//_mtx.lock();
				std::unique_lock<std::mutex> lock(_mtx);//RAII��֤���쳣�׳����µİ�ȫ����
				if (_inst == nullptr)
				{
					_inst = new LazySingleton;
				}
				//_mtx.unlock();
			}
			return _inst;
		}

		//ɾ������
		static void DelInstance()
		{
			std::unique_lock<std::mutex> lock(_mtx);

			delete _inst;
			_inst = nullptr;
		}

		//����RAII��˼����Ƕһ��GC�࣬�������ʱ�Զ����������������ͷŵ�������
		class GC
		{
		public:
			~GC()
			{
				LazySingleton::DelInstance();
			}
		};
		static GC gc;

		LazySingleton& operator=(const LazySingleton&) = delete; //c++11д��,Ϊ�˷�ֹ������ֱ�Ӱѿ�������͸�ֵ�����ɾ��
		LazySingleton(const LazySingleton&) = delete;
	private:

		LazySingleton()
		{};

		/*
		c++98д��������Ա����˽�л���ʹ������޷�����
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

