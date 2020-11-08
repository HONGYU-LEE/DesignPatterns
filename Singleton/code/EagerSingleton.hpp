
namespace lee
{
	class EagerSingleton
	{
	public:
		static EagerSingleton* GetInstance()
		{
			return &_inst;
		}


		EagerSingleton& operator=(const EagerSingleton&) = delete; //c++11д��,Ϊ�˷�ֹ������ֱ�Ӱѿ�������͸�ֵ�����ɾ��
		EagerSingleton(const EagerSingleton&) = delete;
	private:
		//���캯��˽�л�����ʱֻ�ܴ�����̬������Ϊ��̬�������ڵ�ǰ��������
		EagerSingleton()
		{};

		/*
		c++98д��������Ա����˽�л���ʹ������޷�����
		EagerSingleton& operator=(const EagerSingleton&);
		EagerSingleton(const EagerSingleton&);
		*/

		static EagerSingleton _inst;
		//ʹ�þ�̬�ĳ�Ա����Ϊ��̬��Ա��������������Ψһ��һ�ݡ��ڳ���ʼ�׶δ���֮�������˻�ȡʱֻ��Ҫ����ָ����������ָ�뼴��
	};

	EagerSingleton EagerSingleton::_inst;
}

