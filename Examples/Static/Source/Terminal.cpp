#include "Terminal.h"

#include <ObjectPrivate.h>
#include <iostream>

void Terminal::writeLine(std::string_view line) const
{
	UNSURE(writeLine(line));
}

Terminal::Impl::Impl()
{
}

Terminal::Impl::~Impl()
{
}

void Terminal::Impl::writeLine(std::string_view line) const
{
	std::cout << line << std::endl;
}