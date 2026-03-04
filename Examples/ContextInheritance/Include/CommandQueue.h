#pragma once

#include <Object.h>
#include <string>
#include <string_view>
#include <cstdint>
#include <vector>

#include <utility>

//class CommandList : public Context
//{
//private:
//	using Base = Context;
//	using This = CommandList;
//	friend class Object;
//	friend class ThreadSafeObject;
//	friend class Context;
//	friend class Static;
//friend class ThreadSafeStatic;
//template<class T> friend struct Container;
//protected: 
//	class Impl;
//	static constexpr bool __AsConstEnabled = Base::__AsConstEnabled;
//	CommandList(BaseContainer *pContainer) : Base{ pContainer } {}
//	BaseContainer *Get() { return m_pContainer; }
//	const BaseContainer *Get() const { return m_pContainer; }
//public:
//	using Data = Container<This>;
//	CommandList(NullObjectType = Null) : Base{ Null } {}
//
//
//	template<class T, std::enable_if_t<std::is_base_of_v<CommandList, T> && __AsConstEnabled, int> = 0> CommandList(const T &other) : Base{ other } {}
//
//
//	template<class T, std::enable_if_t<std::is_base_of_v<CommandList, T> && std::is_same_v<std::decay_t<T>, T>, int> = 0> CommandList(T &&other) noexcept : Context{ std::forward<T>(other) } {}
//	template<class T, std::enable_if_t<std::is_base_of_v<CommandList, T> && __AsConstEnabled, int> = 0> CommandList &operator=(const T &other) { Base::operator=(other); return *this; }
//	template<class T, std::enable_if_t<std::is_base_of_v<CommandList, T>, int> = 0> CommandList &operator=(T &&other) { Base::operator=(std::forward<T>(other)); return *this; }
//	template<class T, std::enable_if_t<(std::is_base_of_v<CommandList, T> || std::is_base_of_v<T, CommandList>) && __AsConstEnabled, int> = 0> T As() const { return Base::As<T>(); }
//	template<class T, std::enable_if_t<(std::is_base_of_v<CommandList, T> || std::is_base_of_v<T, CommandList>) && !__AsConstEnabled, int> = 0> T As()  { return Base::As<T>(); }
//	friend class CommandQueue;
//
//	const std::string &name() const; // Despite not being Virtual, acts like one
//};
INTERFACE(CommandList, Context)
	friend class CommandQueue;

	const std::string &name() const; // Despite not being Virtual, acts like one
END;

INTERFACE(GraphicsCommandList, CommandList)
	friend class CommandQueue;

	void draw(std::string_view object);
END;

INTERFACE(CommandQueue, Object)
	friend class CommandList;

	CommandQueue(int type);
	
	CommandList getList();

	void execute(std::vector<CommandList> &commandLists);
END;