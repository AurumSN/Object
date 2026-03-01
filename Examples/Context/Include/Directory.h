#pragma once

#include "File.h"

INTERFACE(Directory, Object)
	Directory(std::string_view path);
	
	File createFile(std::string_view name);
END;