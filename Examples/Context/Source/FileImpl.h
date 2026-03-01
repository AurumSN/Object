#pragma once

#include <ObjectPrivate.h>

#include "File.h"

#include <iostream>
#include <fstream>
#include <filesystem>

IMPLEMENTATION(File)
	std::string name;
	std::ofstream stream;

	Impl(std::filesystem::path directory_path, std::string_view name) : name{ name }, stream{ directory_path / name } {}
	~Impl() { stream.close(); }

	void writeLine(std::string_view line)
	{
		stream << line << std::endl;
	}
END;