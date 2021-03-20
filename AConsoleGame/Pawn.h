#pragma once

#include <list>
#include <string>

#include "ConsoleObject.h"
#include "Projectile.h"
#include "ACollisionDetector.h"

//forward declaration because of cyclic dependancy
template <>
class CollisionDetector<Projectile>;

class Pawn : public ConsoleObject {
public:
	enum PAWN_STATE{
		IS_ALIVE,
		IS_DEAD
	};
	Pawn() {

	}

	Pawn(Position p, Size s, Velocity v, FireDirection dir, CollisionDetector<Projectile>& _cd) :
		Pawn(p, s, v, dir)
	{
		cd = &_cd;
	}

	Pawn(Position p, Size s, Velocity v, FireDirection dir) :
		ConsoleObject(p, s, v),
		direction(dir)
	{
		pattern += "###,";
		pattern += "###,";
		pattern += "###,";
		tilesLeft = s.breadth * s.length;
	}

	~Pawn() {

	}

	virtual void Tick(float elapsedTime);

	void FireProjectile();
	Position const& UpdateProjectileDirection();
	bool TogglePixel(int x, int y);
	virtual void setCollisionDetector(CollisionDetector<Projectile>& cd);
	PAWN_STATE getPawnState();
private:
	std::list<Projectile*> projectiles;
	FireDirection direction;
	std::string pattern;
	CollisionDetector<Projectile>* cd;
	uint32_t tilesLeft;
	PAWN_STATE state;
};

