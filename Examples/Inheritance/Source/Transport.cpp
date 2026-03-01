#include "TransportImpl.h"

#include <iostream>

Transport::Transport(float speed) : IMPLEMENTATION_CONSTRUCTOR(speed)
{
	std::cout << "Transport(float)" << std::endl;
}

float Transport::getSpeed() const
{
	return UNSURE_VALUE(speed, 0.0f);
}

Car::Car(float speed, float weight) : IMPLEMENTATION_CONSTRUCTOR(speed, weight)
{
	std::cout << "Car(float, float)" << std::endl;
}

float Car::getWeight() const
{
	return UNSURE_VALUE(weight, 0.0f);
}

WolksVagen::WolksVagen(float speed, float weight, float wv) : IMPLEMENTATION_CONSTRUCTOR(speed, weight, wv)
{
	std::cout << "WolksVagen(float, float, float)" << std::endl;
}

float WolksVagen::getWV() const
{
	return UNSURE_VALUE(wv, 0.0f);
}

Audio::Audio(float speed, float weight, float au) : IMPLEMENTATION_CONSTRUCTOR(speed, weight, au)
{
	std::cout << "Audio(float, float, float)" << std::endl;
}

float Audio::getAU() const
{
	return UNSURE_VALUE(au, 0.0f);
}

Airplane::Airplane(float speed, float height) : IMPLEMENTATION_CONSTRUCTOR(speed, height)
{
	std::cout << "Airplane(float, float)" << std::endl;
}

float Airplane::getHeight() const
{
	return UNSURE_VALUE(height, 0.0f);
}