#pragma once

#include <Object.h>
#include <string>
#include <string_view>
#include <cstdint>
#include <vector>

#include <utility>

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

	CommandQueue(uint8_t idx);
	
	CommandList getList();

	void execute(std::vector<CommandList> &commandLists) const;
END;