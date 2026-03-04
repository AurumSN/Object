#include "CommandQueueImpl.h"

#include <iostream>

const std::string &CommandList::name() const
{
	static std::string str = "";
	return UNSURE_VALUE(name(), str);
}

void GraphicsCommandList::draw(std::string_view object)
{
	UNSURE(draw(object));
}

CommandQueue::CommandQueue(int type) : IMPLEMENTATION_CONSTRUCTOR(type) {}

CommandList CommandQueue::getList()
{
	return UNSURE_VALUE(getList(), Null);
}

void CommandQueue::execute(std::vector<CommandList> &commandLists)
{
	UNSURE(execute(commandLists));
}



CommandList::Impl::Impl(const CommandQueue queue, uint8_t idx) : index{ idx }, parent{ queue }, list{} {}

const std::string &CommandList::Impl::name() const
{
	static std::string str = "CommandList";
	return str;
}

GraphicsCommandList::Impl::Impl(const CommandQueue queue, uint8_t idx) : Base::Impl{ queue, idx } {}

void GraphicsCommandList::Impl::draw(std::string_view object)
{
	list.push_back(std::string{ object });
}

const std::string &GraphicsCommandList::Impl::name() const
{
	static std::string str = "GraphicsCommandList";
	return str;
}

CommandQueue::Impl::Impl(int type) : lists{}, list_count{ 0 } {}

CommandList CommandQueue::Impl::getList()
{
	if (lists.empty()) {
		return createList();
	}

	CommandList list = std::move(lists.front());
	lists.pop();
	return list;
}

void CommandQueue::Impl::execute(std::vector<CommandList> &commandLists)
{
	for (auto &v : commandLists) {
		std::cout << v.name() << " " << (int)GET_IMPL(v)->index << " :" << std::endl;
		for (const auto &i : GET_IMPL(v)->list) {
			std::cout << "\t" << i << std::endl;
		}
		std::cout << std::endl;
		returnList(std::move(v));
	}
}

CommandList CommandQueue::Impl::createList()
{
	return CONSTRUCTOR(GraphicsCommandList, SELF, list_count++);
}

void CommandQueue::Impl::returnList(CommandList list)
{
	lists.push(std::move(list));
}