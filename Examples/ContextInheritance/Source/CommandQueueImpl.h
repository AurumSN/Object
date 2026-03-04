#pragma once

#include "CommandQueue.h"

#include <ObjectPrivate.h>
#include <queue>

IMPLEMENTATION(CommandList)
	friend class CommandQueue;

	uint8_t index;
	CommandQueue parent;
	std::vector<std::string> list;

	Impl(const CommandQueue queue, uint8_t idx);

	virtual const std::string &name() const;
END;

IMPLEMENTATION(GraphicsCommandList)
	Impl(const CommandQueue queue, uint8_t idx);

	void draw(std::string_view object);

	virtual const std::string &name() const override;
END;

IMPLEMENTATION(CommandQueue)
	std::queue<CommandList> lists;
	uint8_t list_count;

	Impl(int type);

	CommandList getList();

	void execute(std::vector<CommandList> &commandLists);

//private:
	CommandList createList();

	void returnList(CommandList list);
END;