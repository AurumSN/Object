#pragma once

#include "Counter.h"

#include <ObjectPrivate.h>

IMPLEMENTATION(CounterBad)
	unsigned long long value;

	Impl(unsigned long long value) : value{ value } {}
END;

IMPLEMENTATION(CounterGood)
	unsigned long long value;

	Impl(unsigned long long value) : value{ value } {}

	void increment()
	{
		value++;
	}

	void multiply()
	{
		value <<= 1;
	}

	void nullify()
	{
		value = 0;
	}

	void increment(size_t n)
	{
		for (size_t i = 0; i != n; i++) {
			value++;
		}
	}

	void multiply(size_t n)
	{
		for (size_t i = 0; i != n; i++) {
			value <<= 1;
		}
	}

	void nullify(size_t n)
	{
		for (size_t i = 0; i != n; i++) {
			value = 0;
		}
	}
END;

IMPLEMENTATION(CounterBadThreadSafe)
	unsigned long long value;

	Impl(unsigned long long value) : value{ value } {}
END;

IMPLEMENTATION(CounterGoodThreadSafe)
	unsigned long long value;

	Impl(unsigned long long value) : value{ value } {}

	void increment()
	{
		value++;
	}

	void multiply()
	{
		value <<= 1;
	}

	void nullify()
	{
		value = 0;
	}

	void increment(size_t n)
	{
		for (size_t i = 0; i != n; i++) {
			value++;
		}
	}

	void multiply(size_t n)
	{
		for (size_t i = 0; i != n; i++) {
			value <<= 1;
		}
	}

	void nullify(size_t n)
	{
		for (size_t i = 0; i != n; i++) {
			value = 0;
		}
	}
END;

IMPLEMENTATION(CounterGoodThreadSafe2)
	unsigned long long value;

	Impl(unsigned long long value) : value{ value } {}
END;