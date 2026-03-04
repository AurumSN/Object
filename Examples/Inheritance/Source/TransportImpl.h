#pragma once

#include "Transport.h"

#include <ObjectPrivate.h>

IMPLEMENTATION(Transport)
	float speed;

	Impl(float speed) : speed{ speed } {}
END;

IMPLEMENTATION(Car)
	float weight;

	Impl(float speed, float weight) : Base::Impl{ speed }, weight{ weight } {}
END;

IMPLEMENTATION(WolksVagen)
	float wv;

	Impl(float speed, float weight, float wv) : Base::Impl{ speed, weight }, wv{ wv } {}
END;

IMPLEMENTATION(Audio)
	float au;

	Impl(float speed, float weight, float au) : Base::Impl{ speed, weight }, au{ au } {}
END;

IMPLEMENTATION(Airplane)
	float height;

	Impl(float speed, float height) : Base::Impl{ speed }, height{ height } {}
END;