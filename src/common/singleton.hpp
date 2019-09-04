#ifndef WATER_SINGLETON_HPP
#define WATER_SINGLETON_HPP

namespace water
{
	// !It is not thread safe up to now
	template<class T>
	class Singleton
	{
	public:
		static T* Instance() {
			if (m_instance == nullptr)
			{
				m_instance = new T;
			}
			assert(m_instance);
			return m_instance;
		}
	protected:
		Singleton();
		~Singleton();
	private:
		Singleton(Singleton const&) = delete;
		Singleton& operator=(Singleton const&) = delete;
		static T* m_instance;
	};

	template<class T> T* Singleton<T>::m_instance = nullptr;
}

#endif // !WATER_SINGLETON_HPP
