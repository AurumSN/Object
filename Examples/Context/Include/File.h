#pragma once

#include <Object.h>

#include <string>
#include <string_view>
#include <filesystem>

INTERFACE(File, Object)
	friend class Directory;

	void writeLine(std::string_view line);
END;