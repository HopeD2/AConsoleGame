
#include "Projectile.h"
#include "Engine.h"

#include <list>

void Projectile::Tick(float elapsedTime) {	
	switch (direction) {
		case UP: 
		{
			pos.y -= velo.dy * elapsedTime;
			break;
		}
		case DOWN :
		{
			pos.y += velo.dy * elapsedTime;
			break;
		}
		case LEFT: 
		{
			pos.x -= velo.dx * elapsedTime;
			break;
		}
		case RIGHT:
		{
			pos.x += velo.dx * elapsedTime;
			break;
		}
		default:
			break;
	}

	ConsoleEngine::DrawRectangle(pos.x, pos.y, size.length, size.breadth);
	ConsoleEngine::Draw(pos.x, pos.y, 0x2588, FG_DARK_CYAN);
}

bool Projectile::hasProjectileHit() const
{
	return hasHit;
}

bool Projectile::Update()
{
	hasHit = true;

	return true;
}
