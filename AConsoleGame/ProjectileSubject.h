#pragma once

#include "Subject.h"
#include "Projectile.h"
#include "Observer.h"

template <>
class Subject<Projectile> {
public:
	virtual ~Subject() {};
	virtual bool Attach(Projectile *observer) = 0;
	virtual bool Detach(Projectile *observer) = 0;
	virtual void Notify(Projectile *observer) = 0;
};
