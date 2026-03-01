#pragma once

#include <Object.h>

INTERFACE(Transport, Object)
	Transport(float speed = 1.0f);

	float getSpeed() const;
END;

INTERFACE(Car, Transport)
	Car(float speed = 1.0f, float weight = 1.0f);

	float getWeight() const;
END;

INTERFACE(WolksVagen, Car)
	WolksVagen(float speed = 1.0f, float weight = 1.0f, float wv = 1.0f);

	float getWV() const;
END;

INTERFACE(Audio, Car)
	Audio(float speed = 1.0f, float weight = 1.0f, float au = 1.0f);

	float getAU() const;
END;

INTERFACE(Airplane, Transport)
	Airplane(float speed = 1.0f, float height = 1.0f);

	float getHeight() const;
END;