#pragma once

#include <vector>
#include <list>
#include <iterator>

#include "ConsoleObject.h"
#include "Pawn.h"
#include "AIController.h"
//#include "ProjectileCollisionDetector.h"
template<>
class CollisionDetector<Projectile>;

class GameLevel : public ConsoleObject {
public:
	GameLevel();
	~GameLevel();
	virtual void Tick(float elapsedTime);
	void setPlayerCollisionDetector(CollisionDetector<Projectile>& cd);
	void AddAICollisionDetectorToBots(CollisionDetector<Projectile>& cd);
	bool hasLevelBeenCleared() const;
private:
	std::vector<AIController *> controllers;
	std::list<Pawn*> bots;
	bool isLevelCleared;
};