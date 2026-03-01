#include "Terminal.h"

#include <thread>
#include <string>
#include <vector>

Terminal::Data terminal;

void func(Terminal term, size_t from, size_t to)
{
	for (size_t i = from; i != to; i++) {
		bool b = i >= 2;
		for (size_t j = 2; j * j <= i; j++) {
			if (i % j == 0) {
				b = false;
				break;
			}
		}
		if (b) {
			term.writeLine("Number " + std::to_string(i) + " is a Prime!");
		}
	}
}

int main()
{
	const size_t Num = 8;
	const size_t Max = 100000;
	const size_t Count = Max / Num;

	std::vector<std::thread> v;
	v.reserve(8);

	for (size_t i = 0; i != Num; i++) {
		v.emplace_back(func, terminal.Create(), i * Count, std::min(i * Count + Count, Max));
	}

	for (auto &i : v) {
		i.join();
	}
}