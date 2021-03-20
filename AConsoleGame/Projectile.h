#pragma once

#include "ConsoleObject.h"
#include "Observer.h"

class Projectile : public ConsoleObject, public Observer {
public:
	enum {

	};

	Projectile() {

	}

	Projectile(Position p, Size s, Velocity v, FireDirection dir) : 
		ConsoleObject(p, s, v),
		direction(dir),
		hasHit(false)
	{

	}

	~Projectile() {

	}

	virtual void Tick(float elapsedTime);

	bool hasProjectileHit()const;

	// Inherited via Observer
	virtual bool Update() override;
private:
	FireDirection direction;
	bool hasHit;

};