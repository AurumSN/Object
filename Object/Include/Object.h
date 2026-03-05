#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <utility>
#include <cstddef>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#elif defined(__unix__)
#include <pthread.h>
#endif

struct NullObjectType {};
static constexpr NullObjectType Null{};

#define INTERFACE_PRIVATE(NAME, PARENT) using Base = PARENT; \
using This = NAME; \
friend class Object; \
friend class ThreadSafeObject; \
friend class Context; \
friend class Static; \
friend class ThreadSafeStatic; \
template<class T> friend struct Container;
#define INTERFACE_PROTECTED(NAME) class Impl; \
static constexpr bool __AsConstEnabled = Base::__AsConstEnabled; \
NAME(BaseContainer *pContainer, __KeyType) : Base{ pContainer, __Key } {} \
BaseContainer *Get() { return m_pContainer; } \
const BaseContainer *Get() const { return m_pContainer; }
#define INTERFACE_PUBLIC(NAME) using Data = Container<This>; \
NAME(NullObjectType = Null) : Base{ Null } {} \
template<class T, std::enable_if_t<std::is_base_of_v<NAME, T> && __AsConstEnabled && std::is_same_v<std::decay_t<T>, T>, int> = 0> NAME(const T &other) : Base{ other } {} \
template<class T, std::enable_if_t<std::is_base_of_v<NAME, T> && std::is_same_v<std::decay_t<T>, T>, int> = 0> NAME(T &&other) noexcept : Base{ std::move(other) } {} \
template<class T, std::enable_if_t<std::is_base_of_v<NAME, T> && __AsConstEnabled && std::is_same_v<std::decay_t<T>, T>, int> = 0> NAME &operator=(const T &other) { Base::operator=(other); return *this; } \
template<class T, std::enable_if_t<std::is_base_of_v<NAME, T> && std::is_same_v<std::decay_t<T>, T>, int> = 0> NAME &operator=(T &&other) { Base::operator=(std::move(other)); return *this; } \
template<class T, std::enable_if_t<(std::is_base_of_v<NAME, T> || std::is_base_of_v<T, NAME>) && __AsConstEnabled, int> = 0> T As() const { return Base::As<T>(); } \
template<class T, std::enable_if_t<(std::is_base_of_v<NAME, T> || std::is_base_of_v<T, NAME>) && !__AsConstEnabled, int> = 0> T As()  { return Base::As<T>(); }

#define INTERFACE(NAME, PARENT) class NAME : public PARENT \
{ \
private: \
	INTERFACE_PRIVATE(NAME, PARENT) \
protected: \
	INTERFACE_PROTECTED(NAME)\
public: \
	INTERFACE_PUBLIC(NAME)
#define END }

#define IMPL (static_cast<Container<This> *>(this->m_pContainer)->Get())
#define SURE(X) (IMPL-> X)
#define UNSURE_VALUE(X, DEFAULT) (Holds() ? SURE(X) : (DEFAULT))
#define UNSURE_EXPRESSION(X, ...) do { if (Holds()) { SURE(X); } } while (0)

#define __UNSURE(X, Arg, Type, ...) UNSURE ## Type (X, Arg)
#define UNSURE(X, ...) __UNSURE(X __VA_OPT__(,) __VA_ARGS__, _VALUE, _EXPRESSION)

#define THREAD_UNSAFE_IMPL (&static_cast<Container<This> *>(this->m_pContainer)->Impl)
#define THREAD_UNSAFE_SURE(X) (THREAD_UNSAFE_IMPL-> X)
#define THREAD_UNSAFE_UNSURE_VALUE(X, DEFAULT) (Holds() ? THREAD_UNSAFE_SURE(X) : (DEFAULT))
#define THREAD_UNSAFE_UNSURE_EXPRESSION(X) do { if (Holds()) { THREAD_UNSAFE_SURE(X); } } while (0)

#define __THREAD_UNSAFE_UNSURE(X, Arg, Type, ...) THREAD_UNSAFE_UNSURE ## Type ## (X, Arg)
#define THREAD_UNSAFE_UNSURE(X, ...) __THREAD_UNSAFE_UNSURE(X __VA_OPT__(,) __VA_ARGS__, _EXPRESSION, _VALUE)

#define IMPLEMENTATION(NAME) class NAME::Impl : public Base::Impl \
{ \
	using Interface = NAME; \
public:

#define IMPLEMENTATION_CONSTRUCTOR(...) This{ new Container<This>{ __VA_ARGS__ }, __Key }

#define CONSTRUCTOR(Type, ...) Type{ new Type::Container<Type>{ __VA_ARGS__ }, Type::__Key }

#define GET_IMPL(X) (static_cast<std::conditional_t<std::is_const_v<std::remove_reference_t<decltype(X)>>, const std::remove_reference_t<decltype(X)>::Container<std::remove_reference_t<decltype(X)>::This> *, std::remove_reference_t<decltype(X)>::Container<std::remove_reference_t<decltype(X)>::This> *>>(X.m_pContainer)->Get())
#define SELF (Interface::__AsConstEnabled ? Interface{ const_cast<BaseContainer *>(const_cast<Impl *>(this)->m_pSelf), Interface::__Key } : Null)

class Object
{
protected:
	struct __KeyType {};
	static constexpr __KeyType __Key{};

	static constexpr bool __AsConstEnabled = true;

	struct BaseContainer
	{
		size_t nRefCount;

		BaseContainer();
		virtual ~BaseContainer();

		void Increment();
		bool Decrement();
	};

	template<class T>
	struct Container;

	class Impl { friend class Object; protected: BaseContainer *const m_pSelf{ nullptr }; };

	BaseContainer *m_pContainer;

	Object(BaseContainer *pContainer, __KeyType);

public:
	Object(NullObjectType = Null);
	Object(const Object &other);
	Object(Object &&other) noexcept;
	~Object();

	Object &operator=(NullObjectType);
	Object &operator=(const Object &other);
	Object &operator=(Object &&other) noexcept;

	void Release();
	bool Holds() const;

	//operator bool() const;

	template<class T, std::enable_if_t<std::is_base_of_v<Object, T> || std::is_base_of_v<T, Object>, int> = 0>
	T As() const;
};

template<class T, std::enable_if_t<std::is_base_of_v<Object, T> || std::is_base_of_v<T, Object>, int>>
T Object::As() const
{
	T res = Null;
	res.m_pContainer = m_pContainer;
	if (m_pContainer) {
		m_pContainer->Increment();
	}
	return res;
}

class ThreadSafeObject
{
protected:
	struct __KeyType {};
	static constexpr __KeyType __Key{};

	static constexpr bool __AsConstEnabled = true;

	struct BaseContainer
	{
		size_t nRefCount;

#ifdef _WIN32
		CRITICAL_SECTION CriticalSection;
#elif defined(__unix__)
		pthread_mutex_t Mutex;
#endif

		BaseContainer();
		virtual ~BaseContainer();

		void Increment();
		bool Decrement();
	};

	template<class T>
	struct Container;

	class Impl { friend class ThreadSafeObject; protected: BaseContainer *const m_pSelf{ nullptr }; };

	BaseContainer *m_pContainer;

	ThreadSafeObject(BaseContainer *pContainer, __KeyType);

public:
	ThreadSafeObject(NullObjectType = Null);
	ThreadSafeObject(const ThreadSafeObject &other);
	ThreadSafeObject(ThreadSafeObject &&other) noexcept;
	~ThreadSafeObject();

	ThreadSafeObject &operator=(NullObjectType);
	ThreadSafeObject &operator=(const ThreadSafeObject &other);
	ThreadSafeObject &operator=(ThreadSafeObject &&other) noexcept;

	void Release();
	bool Holds() const;

	//operator bool() const;

	template<class T, std::enable_if_t<std::is_base_of_v<ThreadSafeObject, T> || std::is_base_of_v<T, ThreadSafeObject>, int> = 0>
	T As() const;
};

template<class T, std::enable_if_t<std::is_base_of_v<ThreadSafeObject, T> || std::is_base_of_v<T, ThreadSafeObject>, int>>
T ThreadSafeObject::As() const
{
	T res = Null;
	res.m_pContainer = m_pContainer;
	if (m_pContainer) {
		m_pContainer->Increment();
	}
	return res;
}

class Context
{
	Context(const Context &) = delete;
	Context &operator=(const Context &) = delete;
protected:
	struct __KeyType {};
	static constexpr __KeyType __Key{};

	static constexpr bool __AsConstEnabled = false;

	struct BaseContainer
	{
		BaseContainer();
		virtual ~BaseContainer();
	};

	template<class T>
	struct Container;

	class Impl { friend class Context; protected: BaseContainer *const m_pSelf{ nullptr }; };

	BaseContainer *m_pContainer;

	Context(BaseContainer *pContainer, __KeyType);

public:
	Context(NullObjectType = Null);
	Context(Context &&other) noexcept;
	~Context();

	Context &operator=(NullObjectType);
	Context &operator=(Context &&other) noexcept;

	void Release();
	bool Holds() const;

	//operator bool() const;

	template<class T, std::enable_if_t<std::is_base_of_v<Context, T> || std::is_base_of_v<T, Context>, int> = 0>
	T As();
};

template<class T, std::enable_if_t<std::is_base_of_v<Context, T> || std::is_base_of_v<T, Context>, int>>
T Context::As()
{
	T res = Null;
	res.m_pContainer = m_pContainer;
	m_pContainer = nullptr;
	return res;
}

class Static
{
protected:
	struct __KeyType {};
	static constexpr __KeyType __Key{};

	static constexpr bool __AsConstEnabled = true;

	struct BaseContainer
	{
		BaseContainer();
		virtual ~BaseContainer();
	};

	class Impl { friend class Static; protected: BaseContainer *const m_pSelf{ nullptr }; };

	BaseContainer *m_pContainer;

	Static(BaseContainer *pContainer, __KeyType);

public:
	template<class T>
	struct Container : public BaseContainer
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

		T Create()
		{
			return T{ this };
		}
	};

	Static(NullObjectType = Null);
	Static(const Static &other);
	Static(Static &&other) noexcept;
	~Static();

	Static &operator=(NullObjectType);
	Static &operator=(const Static &other);
	Static &operator=(Static &&other) noexcept;

	void Release();
	bool Holds() const;

	//operator bool() const;

	template<class T, std::enable_if_t<std::is_base_of_v<Static, T> || std::is_base_of_v<T, Static>, int> = 0>
	T As() const;
};

template<class T, std::enable_if_t<std::is_base_of_v<Static, T> || std::is_base_of_v<T, Static>, int>>
T Static::As() const
{
	T res = Null;
	res.m_pContainer = m_pContainer;
	return res;
}

class ThreadSafeStatic
{
protected:
	struct __KeyType {};
	static constexpr __KeyType __Key{};

	static constexpr bool __AsConstEnabled = true;

	struct BaseContainer
	{
		BaseContainer();
		virtual ~BaseContainer();
	};

	class Impl { friend class ThreadSafeStatic; protected: BaseContainer *const m_pSelf{ nullptr }; };

	BaseContainer *m_pContainer;

	ThreadSafeStatic(BaseContainer *pContainer, __KeyType);

public:
	template<class T>
	struct Container : public BaseContainer
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

#ifdef _WIN32
		CRITICAL_SECTION CriticalSection;
#elif defined(__unix__)
		pthread_mutex_t Mutex;
#endif

		template<typename... Args>
		Container(Args... args) : Impl{ args... }
		{
			*const_cast<BaseContainer **>(&Impl.m_pSelf) = this;
#ifdef _WIN32
			InitializeCriticalSection(&CriticalSection);
#elif defined(__unix__)
			pthread_mutex_init(&Mutex, nullptr);
#endif
		}

		virtual ~Container()
		{
#ifdef _WIN32
			DeleteCriticalSection(&CriticalSection);
#elif defined(__unix__)
			pthread_mutex_destroy(&Mutex);
#endif
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

		T Create()
		{
			return T{ this, __Key };
		}
	};

	ThreadSafeStatic(NullObjectType = Null);
	ThreadSafeStatic(const ThreadSafeStatic &other);
	ThreadSafeStatic(ThreadSafeStatic &&other) noexcept;
	~ThreadSafeStatic();

	ThreadSafeStatic &operator=(NullObjectType);
	ThreadSafeStatic &operator=(const ThreadSafeStatic &other);
	ThreadSafeStatic &operator=(ThreadSafeStatic &&other) noexcept;

	void Release();
	bool Holds() const;

	//operator bool() const;

	template<class T, std::enable_if_t<std::is_base_of_v<ThreadSafeStatic, T> || std::is_base_of_v<T, ThreadSafeStatic>, int> = 0>
	T As() const;
};

template<class T, std::enable_if_t<std::is_base_of_v<ThreadSafeStatic, T> || std::is_base_of_v<T, ThreadSafeStatic>, int>>
T ThreadSafeStatic::As() const
{
	T res = Null;
	res.m_pContainer = m_pContainer;
	return res;
}

#endif