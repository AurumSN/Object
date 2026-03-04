#pragma once

#include "Directory.h"
#include "FileImpl.h"

IMPLEMENTATION(Directory)
	std::string path;

	Impl(std::string_view path) : path{ path } {}

	File createFile(std::string_view name)
	{
		return CONSTRUCTOR(File, path, name);
	}
END;