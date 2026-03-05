#include "Object.h"

#include "ObjectPrivate.h"

Object::BaseContainer::BaseContainer() : nRefCount{ 0 }
{
}

Object::BaseContainer::~BaseContainer()
{
}

void Object::BaseContainer::Increment()
{
	nRefCount++;
}

bool Object::BaseContainer::Decrement()
{
	nRefCount--;
	return nRefCount != 0;
}

Object::Object(BaseContainer *pContainer, __KeyType) : m_pContainer{ pContainer }
{
	if (m_pContainer) {
		m_pContainer->Increment();
	}
}

Object::Object(NullObjectType) : m_pContainer{ nullptr }
{
}

Object::Object(const Object &other) : Object{ other.m_pContainer, __Key }
{
}

Object::Object(Object &&other) noexcept : m_pContainer{ std::exchange(other.m_pContainer, nullptr) }
{
}

Object::~Object()
{
	Release();
}

Object &Object::operator=(NullObjectType)
{
	Release();

	return *this;
}

Object &Object::operator=(const Object &other)
{
	if (m_pContainer != other.m_pContainer) {
		Release();
		m_pContainer = other.m_pContainer;

		if (m_pContainer) {
			m_pContainer->Increment();
		}
	}

	return *this;
}

Object &Object::operator=(Object &&other) noexcept
{
	if (m_pContainer != other.m_pContainer) {
		std::swap(m_pContainer, other.m_pContainer);
	}

	return *this;
}

void Object::Release()
{
	if (m_pContainer && !m_pContainer->Decrement()) {
		delete m_pContainer;
	}

	m_pContainer = nullptr;
}

bool Object::Holds() const
{
	return m_pContainer != nullptr;
}

//Object::operator bool() const
//{
//	return Holds();
//}



ThreadSafeObject::BaseContainer::BaseContainer() : nRefCount{ 0 }
{
#ifdef _WIN32
	InitializeCriticalSection(&CriticalSection);
#elif defined(__unix__)
	pthread_mutex_init(&Mutex, nullptr);
#endif
}

ThreadSafeObject::BaseContainer::~BaseContainer()
{
#ifdef _WIN32
	DeleteCriticalSection(&CriticalSection);
#elif defined(__unix__)
	pthread_mutex_destroy(&Mutex);
#endif
}

void ThreadSafeObject::BaseContainer::Increment()
{
#ifdef _WIN32
	EnterCriticalSection(&CriticalSection);
#elif defined(__unix__)
	pthread_mutex_lock(&Mutex);
#endif
	nRefCount++;
#ifdef _WIN32
	LeaveCriticalSection(&CriticalSection);
#elif defined(__unix__)
	pthread_mutex_unlock(&Mutex);
#endif
}

bool ThreadSafeObject::BaseContainer::Decrement()
{
#ifdef _WIN32
	EnterCriticalSection(&CriticalSection);
#elif defined(__unix__)
	pthread_mutex_lock(&Mutex);
#endif
	nRefCount--;
#ifdef _WIN32
	LeaveCriticalSection(&CriticalSection);
#elif defined(__unix__)
	pthread_mutex_unlock(&Mutex);
#endif
	return nRefCount != 0; // Can be equal to Zero but have multiple Objects referencing this Container only in case when multiple Threads access the same Object Instance using pointers which is not permitted. Each thread must have their own Instance of the Object.
}

ThreadSafeObject::ThreadSafeObject(BaseContainer *pContainer, __KeyType) : m_pContainer{ pContainer }
{
	if (m_pContainer) {
		m_pContainer->Increment();
	}
}

ThreadSafeObject::ThreadSafeObject(NullObjectType) : m_pContainer{ nullptr }
{
}

ThreadSafeObject::ThreadSafeObject(const ThreadSafeObject &other) : ThreadSafeObject{ other.m_pContainer, __Key }
{
}

ThreadSafeObject::ThreadSafeObject(ThreadSafeObject &&other) noexcept : m_pContainer{ std::exchange(other.m_pContainer, nullptr) }
{
}

ThreadSafeObject::~ThreadSafeObject()
{
	Release();
}

ThreadSafeObject &ThreadSafeObject::operator=(NullObjectType)
{
	Release();

	return *this;
}

ThreadSafeObject &ThreadSafeObject::operator=(const ThreadSafeObject &other)
{
	if (m_pContainer != other.m_pContainer) {
		Release();
		m_pContainer = other.m_pContainer;

		if (m_pContainer) {
			m_pContainer->Increment();
		}
	}

	return *this;
}

ThreadSafeObject &ThreadSafeObject::operator=(ThreadSafeObject &&other) noexcept
{
	if (m_pContainer != other.m_pContainer) {
		std::swap(m_pContainer, other.m_pContainer);
	}

	return *this;
}

void ThreadSafeObject::Release()
{
	if (m_pContainer && !m_pContainer->Decrement()) {
		delete m_pContainer;
	}

	m_pContainer = nullptr;
}

bool ThreadSafeObject::Holds() const
{
	return m_pContainer != nullptr;
}

//ThreadSafeObject::operator bool() const
//{
//	return Holds();
//}



Context::BaseContainer::BaseContainer()
{
}

Context::BaseContainer::~BaseContainer()
{
}

Context::Context(BaseContainer *pContainer, __KeyType) : m_pContainer{ pContainer }
{
}

Context::Context(NullObjectType) : m_pContainer{ nullptr }
{
}

Context::Context(Context &&other) noexcept : m_pContainer{ std::exchange(other.m_pContainer, nullptr) }
{
}

Context::~Context()
{
	Release();
}

Context &Context::operator=(NullObjectType)
{
	Release();

	return *this;
}

Context &Context::operator=(Context &&other) noexcept
{
	if (m_pContainer != other.m_pContainer) {
		std::swap(m_pContainer, other.m_pContainer);
	}

	return *this;
}

void Context::Release()
{
	delete m_pContainer;

	m_pContainer = nullptr;
}

bool Context::Holds() const
{
	return m_pContainer != nullptr;
}

//Context::operator bool() const
//{
//	return Holds();
//}



Static::BaseContainer::BaseContainer()
{
}

Static::BaseContainer::~BaseContainer()
{
}

Static::Static(BaseContainer *pContainer, __KeyType) : m_pContainer{ pContainer }
{
}

Static::Static(NullObjectType) : m_pContainer{ nullptr }
{
}

Static::Static(const Static &other) : Static{ other.m_pContainer, __Key }
{
}

Static::Static(Static &&other) noexcept : m_pContainer{ std::exchange(other.m_pContainer, nullptr) }
{
}

Static::~Static()
{
	Release();
}

Static &Static::operator=(NullObjectType)
{
	Release();

	return *this;
}

Static &Static::operator=(const Static &other)
{
	m_pContainer = other.m_pContainer;

	return *this;
}

Static &Static::operator=(Static &&other) noexcept
{
	if (m_pContainer != other.m_pContainer) {
		std::swap(m_pContainer, other.m_pContainer);
	}

	return *this;
}

void Static::Release()
{
	m_pContainer = nullptr;
}

bool Static::Holds() const
{
	return m_pContainer != nullptr;
}



ThreadSafeStatic::BaseContainer::BaseContainer()
{
}

ThreadSafeStatic::BaseContainer::~BaseContainer()
{
}

ThreadSafeStatic::ThreadSafeStatic(BaseContainer *pContainer, __KeyType) : m_pContainer{ pContainer }
{
}

ThreadSafeStatic::ThreadSafeStatic(NullObjectType) : m_pContainer{ nullptr }
{
}

ThreadSafeStatic::ThreadSafeStatic(const ThreadSafeStatic &other) : ThreadSafeStatic{ other.m_pContainer, __Key }
{
}

ThreadSafeStatic::ThreadSafeStatic(ThreadSafeStatic &&other) noexcept : m_pContainer{ std::exchange(other.m_pContainer, nullptr) }
{
}

ThreadSafeStatic::~ThreadSafeStatic()
{
	Release();
}

ThreadSafeStatic &ThreadSafeStatic::operator=(NullObjectType)
{
	Release();

	return *this;
}

ThreadSafeStatic &ThreadSafeStatic::operator=(const ThreadSafeStatic &other)
{
	m_pContainer = other.m_pContainer;

	return *this;
}

ThreadSafeStatic &ThreadSafeStatic::operator=(ThreadSafeStatic &&other) noexcept
{
	if (m_pContainer != other.m_pContainer) {
		std::swap(m_pContainer, other.m_pContainer);
	}

	return *this;
}

void ThreadSafeStatic::Release()
{
	m_pContainer = nullptr;
}

bool ThreadSafeStatic::Holds() const
{
	return m_pContainer != nullptr;
}