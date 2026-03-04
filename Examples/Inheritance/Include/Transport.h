#pragma once

#include <Object.h>

INTERFACE(Transport, Object)
	Transport(float speed = 1.0f);

	float getSpeed() const;
	void setSpeed(float speed);
END;

INTERFACE(Car, Transport)
	Car(float speed = 1.0f, float weight = 1.0f);

	float getWeight() const;
	void setWeight(float weight);
END;

INTERFACE(WolksVagen, Car)
	WolksVagen(float speed = 1.0f, float weight = 1.0f, float wv = 1.0f);

	float getWV() const;
	void setWV(float wv);
END;

INTERFACE(Audio, Car)
	Audio(float speed = 1.0f, float weight = 1.0f, float au = 1.0f);

	float getAU() const;
	void setAU(float au);
END;

INTERFACE(Airplane, Transport)
	Airplane(float speed = 1.0f, float height = 1.0f);

	float getHeight() const;
	void setHeight(float height);
END;