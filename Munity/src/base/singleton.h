#pragma once
namespace munity
{
	template <typename T>
	class singleton
	{
	public:
		singleton() {}
		virtual ~singleton() {}
		static T* Instance()
		{
			if (_inst == nullptr)
				_inst = new T();
			return _inst;
		}
	protected:
		static T* _inst;
	};

	template <typename T>
	T* singleton<T>::_inst = nullptr;
}