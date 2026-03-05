#include "CommandQueueImpl.h"

#include <iostream>

const std::string &CommandList::name() const
{
	static std::string str = "";
	return UNSURE(name(), str);
}

void GraphicsCommandList::draw(std::string_view object)
{
	UNSURE(draw(object));
}

CommandQueue::CommandQueue(uint8_t) : IMPLEMENTATION_CONSTRUCTOR() {}

CommandList CommandQueue::getList()
{
	return UNSURE(getList(), Null);
}

void CommandQueue::execute(std::vector<CommandList> &commandLists) const
{
	UNSURE(execute(commandLists));
}



CommandList::Impl::Impl(CommandQueue queue, uint8_t idx) : index{ idx }, parent{ queue }, list{} {}
CommandList::Impl::~Impl()
{
	if (parent.Holds()) {
		GET_IMPL(parent)->returnList(index);
	}
}

const std::string &CommandList::Impl::name() const
{
	static std::string str = "CommandList";
	return str;
}

GraphicsCommandList::Impl::Impl(CommandQueue queue, uint8_t idx) : Base::Impl{ queue, idx } {}

void GraphicsCommandList::Impl::draw(std::string_view object)
{
	list.push_back(std::string{ object });
}

const std::string &GraphicsCommandList::Impl::name() const
{
	static std::string str = "GraphicsCommandList";
	return str;
}

CommandQueue::Impl::Impl() : lists{} {}

CommandList CommandQueue::Impl::getList()
{
	if (lists.empty()) {
		return CONSTRUCTOR(GraphicsCommandList, SELF, createList());
	}

	CommandList list = CONSTRUCTOR(GraphicsCommandList, SELF, lists.front());
	lists.pop();
	return list;
}

void CommandQueue::Impl::execute(std::vector<CommandList> &commandLists) const
{
	for (auto &v : commandLists) {
		if (v.Holds()) {
			std::cout << v.name() << " " << (int)GET_IMPL(v)->index << " :" << std::endl;
			for (const auto &i : GET_IMPL(v)->list) {
				std::cout << "\t" << i << std::endl;
			}
			std::cout << std::endl;
		}
	}
}

uint8_t CommandQueue::Impl::createList()
{
	static uint8_t value = 0;
	return value++;
}

void CommandQueue::Impl::returnList(uint8_t listId)
{
	lists.push(listId);
}