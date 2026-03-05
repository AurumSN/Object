#pragma once

#include "CommandQueue.h"

#include <ObjectPrivate.h>
#include <queue>

IMPLEMENTATION(CommandList)
	friend class CommandQueue;

	uint8_t index;
	CommandQueue parent;
	std::vector<std::string> list;

	Impl(CommandQueue queue, uint8_t idx);
	~Impl();

	virtual const std::string &name() const;
END;

IMPLEMENTATION(GraphicsCommandList)
	Impl(CommandQueue queue, uint8_t idx);

	void draw(std::string_view object);

	virtual const std::string &name() const override;
END;

IMPLEMENTATION(CommandQueue)
	std::queue<uint8_t> lists;

	Impl();

	CommandList getList();

	void execute(std::vector<CommandList> &commandLists) const;

//private:
	uint8_t createList();

	void returnList(uint8_t listId);
END;