#include "DirectoryImpl.h"

Directory::Directory(std::string_view path) : IMPLEMENTATION_CONSTRUCTOR(path)
{
}

File Directory::createFile(std::string_view name)
{
	return UNSURE(createFile(name), Null);
}