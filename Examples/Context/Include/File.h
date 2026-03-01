#pragma once

#include <Object.h>

#include <string>
#include <string_view>

INTERFACE(File, Context)
	friend class Directory;

	void writeLine(std::string_view line);
END;