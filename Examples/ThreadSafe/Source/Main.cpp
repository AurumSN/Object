#include <iostream>

static constexpr unsigned long long Value = 100000000;

#include "Counter.h"

#include <thread>
#include <chrono>

void incrementalCB(CounterBad c)
{
	c.increment(Value);
}

void nullificatorCB(CounterBad c)
{
	c.nullify(Value);
}

void incrementalCG(CounterGood c)
{
	c.increment(Value);
}

void nullificatorCG(CounterGood c)
{
	c.nullify(Value);
}

void incrementalCBTS(CounterBadThreadSafe c)
{
	c.increment(Value);
}

void nullificatorCBTS(CounterBadThreadSafe c)
{
	c.nullify(Value);
}

void incrementalCGTS(CounterGoodThreadSafe c)
{
	c.increment(Value);
}

void nullificatorCGTS(CounterGoodThreadSafe c)
{
	c.nullify(Value);
}

void incrementalCGTS2(CounterGoodThreadSafe2 c)
{
	c.increment(Value);
}

void nullificatorCGTS2(CounterGoodThreadSafe2 c)
{
	c.nullify(Value);
}

void incrementalRAW(unsigned long long *c)
{
	for (size_t i = 0; i != Value; i++) {
		(*c)++;
	}
}

void nullificatorRAW(unsigned long long *c)
{
	for (size_t i = 0; i != Value; i++) {
		*c = 0;
	}
}

int main()
{
	std::cout << "CounterBad" << std::endl;

	{
		auto begin = std::chrono::high_resolution_clock::now();
		CounterBad c{ 0ull };

		std::thread a{ incrementalCB, c };
		std::thread b{ nullificatorCB, c };

		a.join();
		b.join();
		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Got:\t\t" << c.get() << "\nExpected:\t" << Value << "\nOr: 0\t\t\nTime: " << std::chrono::duration<double>(end - begin).count() << std::endl;
	}

	std::cout << "\nCounterGood" << std::endl;

	{
		auto begin = std::chrono::high_resolution_clock::now();
		CounterGood c{ 0ull };

		std::thread a{ incrementalCG, c };
		std::thread b{ nullificatorCG, c };

		a.join();
		b.join();
		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Got:\t\t" << c.get() << "\nExpected:\t" << Value << "\nOr: 0\t\t\nTime: " << std::chrono::duration<double>(end - begin).count() << std::endl;
	}

	std::cout << "\nCounterBadThreadSafe" << std::endl;

	{
		auto begin = std::chrono::high_resolution_clock::now();
		CounterBadThreadSafe c{ 0ull };

		std::thread a{ incrementalCBTS, c };
		std::thread b{ nullificatorCBTS, c };

		a.join();
		b.join();
		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Got:\t\t" << c.get() << "\nExpected:\t" << Value << "\nOr: 0\t\t\nTime: " << std::chrono::duration<double>(end - begin).count() << std::endl;
	}

	std::cout << "\nCounterGoodThreadSafe" << std::endl;

	{
		auto begin = std::chrono::high_resolution_clock::now();
		CounterGoodThreadSafe c{ 0ull };

		std::thread a{ incrementalCGTS, c };
		std::thread b{ nullificatorCGTS, c };

		a.join();
		b.join();
		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Got:\t\t" << c.get() << "\nExpected:\t" << Value << "\nOr: 0\t\t\nTime: " << std::chrono::duration<double>(end - begin).count() << std::endl;
	}

	std::cout << "\nCounterGoodThreadSafe2" << std::endl;

	{
		auto begin = std::chrono::high_resolution_clock::now();
		CounterGoodThreadSafe2 c{ 0ull };

		std::thread a{ incrementalCGTS2, c };
		std::thread b{ nullificatorCGTS2, c };

		a.join();
		b.join();
		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Got:\t\t" << c.get() << "\nExpected:\t" << Value << "\nOr: 0\t\t\nTime: " << std::chrono::duration<double>(end - begin).count() << std::endl;
	}

	std::cout << "\nRAW" << std::endl;

	{
		auto begin = std::chrono::high_resolution_clock::now();
		unsigned long long c = 0;

		std::thread a{ incrementalRAW, &c };
		std::thread b{ nullificatorRAW, &c };

		a.join();
		b.join();
		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "Got:\t\t" << c << "\nExpected:\t" << Value << "\nOr: 0\t\t\nTime: " << std::chrono::duration<double>(end - begin).count() << std::endl;
	}
}