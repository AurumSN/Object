#pragma once

#include <Object.h>

INTERFACE(CounterBad, Object)
	CounterBad(unsigned long long value);

	void increment();
	void multiply();
	void nullify();

	void increment(size_t n);
	void multiply(size_t n);
	void nullify(size_t n);

	unsigned long long get() const;
END;

INTERFACE(CounterGood, Object)
	CounterGood(unsigned long long value);

	void increment();
	void multiply();
	void nullify();

	void increment(size_t n);
	void multiply(size_t n);
	void nullify(size_t n);

	unsigned long long get() const;
END;

INTERFACE(CounterBadThreadSafe, ThreadSafeObject)
	CounterBadThreadSafe(unsigned long long value);

	void increment();
	void multiply();
	void nullify();

	void increment(size_t n);
	void multiply(size_t n);
	void nullify(size_t n);

	unsigned long long get() const;
END;

INTERFACE(CounterGoodThreadSafe, ThreadSafeObject)
	CounterGoodThreadSafe(unsigned long long value);

	void increment();
	void multiply();
	void nullify();

	void increment(size_t n);
	void multiply(size_t n);
	void nullify(size_t n);

	unsigned long long get() const;
END;

INTERFACE(CounterGoodThreadSafe2, ThreadSafeObject)
	CounterGoodThreadSafe2(unsigned long long value);

	void increment();
	void multiply();
	void nullify();

	void increment(size_t n);
	void multiply(size_t n);
	void nullify(size_t n);

	unsigned long long get() const;
END;