#include "CounterImpl.h"

void CounterBad::increment()
{
	UNSURE(value++);
}

void CounterBad::multiply()
{
	UNSURE(value <<= 1);
}

void CounterBad::nullify()
{
	UNSURE(value = 0);
}

void CounterBad::increment(size_t n)
{
	for (size_t i = 0; i != n; i++) {
		UNSURE(value++);
	}
}

void CounterBad::multiply(size_t n)
{
	for (size_t i = 0; i != n; i++) {
		UNSURE(value <<= 1);
	}
}

void CounterBad::nullify(size_t n)
{
	for (size_t i = 0; i != n; i++) {
		UNSURE(value = 0);
	}
}

unsigned long long CounterBad::get() const
{
	return UNSURE_VALUE(value, 0);
}

CounterBad::CounterBad(unsigned long long value) : IMPLEMENTATION_CONSTRUCTOR(value)
{
}



void CounterGood::increment()
{
	UNSURE(increment());
}

void CounterGood::multiply()
{
	UNSURE(multiply());
}

void CounterGood::nullify()
{
	UNSURE(nullify());
}


void CounterGood::increment(size_t n)
{
	UNSURE(increment(n));
}

void CounterGood::multiply(size_t n)
{
	UNSURE(multiply(n));
}

void CounterGood::nullify(size_t n)
{
	UNSURE(nullify(n));
}

unsigned long long CounterGood::get() const
{
	return UNSURE_VALUE(value, 0);
}

CounterGood::CounterGood(unsigned long long value) : IMPLEMENTATION_CONSTRUCTOR(value)
{
}



void CounterBadThreadSafe::increment()
{
	UNSURE(value++);
}

void CounterBadThreadSafe::multiply()
{
	UNSURE(value <<= 1);
}

void CounterBadThreadSafe::nullify()
{
	UNSURE(value = 0);
}

void CounterBadThreadSafe::increment(size_t n)
{
	for (size_t i = 0; i != n; i++) {
		UNSURE(value++);
	}
}

void CounterBadThreadSafe::multiply(size_t n)
{
	for (size_t i = 0; i != n; i++) {
		UNSURE(value <<= 1);
	}
}

void CounterBadThreadSafe::nullify(size_t n)
{
	for (size_t i = 0; i != n; i++) {
		UNSURE(value = 0);
	}
}

unsigned long long CounterBadThreadSafe::get() const
{
	return UNSURE_VALUE(value, 0);
}

CounterBadThreadSafe::CounterBadThreadSafe(unsigned long long value) : IMPLEMENTATION_CONSTRUCTOR(value)
{
}



void CounterGoodThreadSafe::increment()
{
	UNSURE(increment());
}

void CounterGoodThreadSafe::multiply()
{
	UNSURE(multiply());
}

void CounterGoodThreadSafe::nullify()
{
	UNSURE(nullify());
}


void CounterGoodThreadSafe::increment(size_t n)
{
	UNSURE(increment(n));
}

void CounterGoodThreadSafe::multiply(size_t n)
{
	UNSURE(multiply(n));
}

void CounterGoodThreadSafe::nullify(size_t n)
{
	UNSURE(nullify(n));
}

unsigned long long CounterGoodThreadSafe::get() const
{
	return UNSURE_VALUE(value, 0);
}

CounterGoodThreadSafe::CounterGoodThreadSafe(unsigned long long value) : IMPLEMENTATION_CONSTRUCTOR(value)
{
}



void CounterGoodThreadSafe2::increment()
{
	UNSURE(value++);
}

void CounterGoodThreadSafe2::multiply()
{
	UNSURE(value <<= 1);
}

void CounterGoodThreadSafe2::nullify()
{
	UNSURE(value = 0);
}

void CounterGoodThreadSafe2::increment(size_t n)
{
	auto impl = IMPL;
	if (!impl) {
		return;
	}
	for (size_t i = 0; i != n; i++) {
		impl->value++;
	}
}

void CounterGoodThreadSafe2::multiply(size_t n)
{
	auto impl = IMPL;
	if (!impl) {
		return;
	}
	for (size_t i = 0; i != n; i++) {
		impl->value <<= 1;
	}
}

void CounterGoodThreadSafe2::nullify(size_t n)
{
	auto impl = IMPL;
	if (!impl) {
		return;
	}
	for (size_t i = 0; i != n; i++) {
		impl->value = 0;
	}
}

unsigned long long CounterGoodThreadSafe2::get() const
{
	return UNSURE_VALUE(value, 0);
}

CounterGoodThreadSafe2::CounterGoodThreadSafe2(unsigned long long value) : IMPLEMENTATION_CONSTRUCTOR(value)
{
}