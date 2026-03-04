#ifndef __OBJECT_PRIVATE_H__
#define __OBJECT_PRIVATE_H__

#include "Object.h"

template<class T>
struct Object::Container : public Object::BaseContainer
{
	typename T::Impl Impl;

	template<typename... Args>
	Container(Args... args) : Impl{ args... }
	{
		*const_cast<BaseContainer **>(&Impl.m_pSelf) = this;
	}

	virtual ~Container()
	{
	}

	typename T::Impl *Get()
	{
		return &Impl;
	}
};

template<class T>
struct ThreadSafeObject::Container : public ThreadSafeObject::BaseContainer
{
	struct __Temp
	{
		typename T::Impl *Ptr;

		__Temp() = delete;
#ifdef _WIN32
		LPCRITICAL_SECTION pCriticalSection;

		explicit __Temp(typename T::Impl *ptr, LPCRITICAL_SECTION pCriticalSection) : Ptr{ ptr }, pCriticalSection{ pCriticalSection }
		{
		}
#elif defined(__unix__)
		pthread_mutex_t *pMutex;

		explicit __Temp(typename T::Impl *ptr, pthread_mutex_t *pMutex) : Ptr{ ptr }, pMutex{ pMutex }
		{
		}
#endif

		~__Temp()
		{
#ifdef _WIN32
			LeaveCriticalSection(pCriticalSection);
#elif defined(__unix__)
			pthread_mutex_unlock(pMutex);
#endif
		}

		typename T::Impl *operator->()
		{
			return Ptr;
		}

		operator bool() const
		{
			return Ptr != nullptr;
		}
	};

	typename T::Impl Impl;

	template<typename... Args>
	Container(Args... args) : Impl{ args... }
	{
		*const_cast<BaseContainer **>(&Impl.m_pSelf) = this;
	}

	virtual ~Container()
	{
	}

	__Temp Get()
	{
#ifdef _WIN32
		EnterCriticalSection(&CriticalSection);
		return __Temp{ &Impl, &CriticalSection };
#elif defined(__unix__)
		pthread_mutex_lock(&Mutex);
		return __Temp{ &Impl, &Mutex };
#endif
	}
};

template<class T>
struct Context::Container : public Context::BaseContainer
{
	typename T::Impl Impl;

	template<typename... Args>
	Container(Args... args) : Impl{ args... }
	{
		*const_cast<BaseContainer **>(&Impl.m_pSelf) = this;
	}

	virtual ~Container()
	{
	}

	typename T::Impl *Get()
	{
		return &Impl;
	}
};

#endif