#include <iostream>

#include "Transport.h"

void print(Transport t)
{
	std::cout << "Transport " << t.getSpeed() << std::endl;
}

void print(Car c)
{
	std::cout << "Car " << c.getSpeed() << " " << c.getWeight() << std::endl;
}

void print(WolksVagen wv)
{
	std::cout << "WolksVagen " << wv.getSpeed() << " " << wv.getWeight() << " " << wv.getWV() << std::endl;
}

void print(Audio au)
{
	std::cout << "Audio " << au.getSpeed() << " " << au.getWeight() << " " << au.getAU() << std::endl;
}

void print(Airplane a)
{
	std::cout << "Airplane " << a.getSpeed() << " " << a.getHeight() << std::endl;
}

#include "TransportImpl.h"

int main()
{
	WolksVagen wv{ 1.2f, 2.3f, 3.4f };
	Transport t = wv;
	Car c = t.As<Car>();
	Audio au = wv.As<Car>().As<Audio>();
	Airplane a = wv.As<Transport>().As<Airplane>();

	WolksVagen::Data d{ 1.2f, 2.3f, 3.4f };
	d.Get();

	print(wv);
	print(t);
	print(c);
	print(au);
	print(a);
}