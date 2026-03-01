#pragma once

#include <Object.h>

#include <string_view>

INTERFACE(Terminal, ThreadSafeStatic)
	void writeLine(std::string_view line) const;
END;

IMPLEMENTATION(Terminal)
	Impl();
	~Impl();

	void writeLine(std::string_view line) const;
END;