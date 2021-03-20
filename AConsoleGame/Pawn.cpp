
#include <iterator>

#include "Pawn.h"
#include "Engine.h"
#include "ProjectileCollisionDetector.h"

void Pawn::Tick(float elapsedTime)
{
	if (state == IS_ALIVE) {
		ConsoleEngine::WrapAround(pos.x, pos.y, pos.x, pos.y);
		ConsoleEngine::DrawPattern(pos.x, pos.y, pattern);
	}

	std::list<Projectile*>::iterator it = projectiles.begin();
	while (it != projectiles.end())
	{
		Projectile &projectile = **it;
		if (ConsoleEngine::IsOutofBoundaries(projectile.GetPosition()) || projectile.hasProjectileHit()) {
			Projectile *pProj = *it;
			if (cd) {
				cd->Detach(*it);
			}
			delete pProj;
			it = projectiles.erase(it);
		}
		else {
			projectile.Tick(elapsedTime);
			it++;
		}
	}
}

void Pawn::FireProjectile()
{
	if (state == PAWN_STATE::IS_ALIVE) {
		ConsoleObject::Position projectilePos = UpdateProjectileDirection();
		Projectile *projectile = new Projectile(projectilePos, { 1,1 }, { 40.0f,40.0f }, direction);
		if (projectile) {
			projectiles.push_back(projectile);
			if (cd) {
				cd->Attach(projectile);
			}
		}
	}
}

ConsoleObject::Position const & Pawn::UpdateProjectileDirection()
{
	if (direction == FireDirection::RIGHT) {
		return { pos.x + size.length + 1, pos.y + (size.breadth / 2) };
	}
	else if (direction == FireDirection::LEFT) {
		return { pos.x - 1, pos.y + (size.breadth / 2) };
	}
	else if (direction == FireDirection::UP) {
		return { pos.y - 1, pos.x + (size.length / 2) };
	}
	else if (direction == FireDirection::DOWN) {
		return { pos.y + size.breadth + 1, pos.x + (size.length / 2) };
	}
}

bool Pawn::TogglePixel(int x, int y)
{
	// length - 1 and breadth - 1 for converting to co-ord. for array indexes
	// Comparison done from 0 to length/breadth because the function  only
	// considers local Pawn plane and not the global screen plane
	if (x >= 0 && x < size.length && y >= 0 && y < size.breadth) {

		int separatorOffset = (y * size.length + x) / size.length;
		if (pattern[y * (size.length) + x + separatorOffset] == '#')
		{
			pattern[y * (size.length) + x + separatorOffset] = '.';
			if (tilesLeft)
			{
				tilesLeft--;
				if (!tilesLeft){
					state = PAWN_STATE::IS_DEAD;
				}
			}
			return true;
		}
	}
	return false;
}

void Pawn::setCollisionDetector(CollisionDetector<Projectile>& cd)
{
	this->cd = &cd;
}

Pawn::PAWN_STATE Pawn::getPawnState()
{
	return state;
}
