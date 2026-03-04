#include <iostream>

#include "Transport.h"

void print(const Transport t)
{
	std::cout << "Transport " << t.getSpeed() << std::endl;
}

void print(const Car c)
{
	std::cout << "Car " << c.getSpeed() << " " << c.getWeight() << std::endl;
}

void print(const WolksVagen wv)
{
	std::cout << "WolksVagen " << wv.getSpeed() << " " << wv.getWeight() << " " << wv.getWV() << std::endl;
}

void print(const Audio au)
{
	std::cout << "Audio " << au.getSpeed() << " " << au.getWeight() << " " << au.getAU() << std::endl;
}

void print(const Airplane a)
{
	std::cout << "Airplane " << a.getSpeed() << " " << a.getHeight() << std::endl;
}

int main()
{
	WolksVagen wv{ 1.2f, 2.3f, 3.4f };
	Transport t = wv;
	Car c = t.As<Car>();
	Audio au = wv.As<Car>().As<Audio>();
	Airplane a = wv.As<Transport>().As<Airplane>();

	print(wv);
	print(t);
	print(c);
	print(au);
	print(a);
}