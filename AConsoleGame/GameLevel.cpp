#include "GameLevel.h"
#include "AIController.h"
#include "ProjectileCollisionDetector.h"
#include "Engine.h"

GameLevel::GameLevel() :
	isLevelCleared(false)
{
	Pawn *bot = new Pawn({ ConsoleEngine::screenWidth - 8.0f, 4.0f }, { 3,3 }, { 0,15 }, FireDirection::LEFT);
	bots.push_back(bot);
	bots.push_back(new Pawn({ ConsoleEngine::screenWidth - 8.0f, 16.0f }, { 3,3 }, { 0,25 }, FireDirection::LEFT));
	bots.push_back(new Pawn({ ConsoleEngine::screenWidth - 8.0f, 32.0f }, { 3,3 }, { 0,20 }, FireDirection::LEFT));
	//bots.push_back(new Pawn({ ConsoleEngine::screenWidth - 8.0f, 64.0f }, { 3,3 }, { 0,40 }, FireDirection::LEFT));
	for (auto bot: bots)
	{
		controllers.push_back(new AIController(bot));
	}
}

GameLevel::~GameLevel()
{
	for (size_t i = 0; i < controllers.size(); i++)
	{
		if (controllers[i]) {
			delete controllers[i];
		}
	}
	controllers.clear();

	for (std::list<Pawn*>::iterator it= bots.begin(); it != bots.end(); it++)
	{
		if (*it) {
			delete *it;
		}
	}
	bots.clear();
}

void GameLevel::Tick(float elapsedTime)
{
	for (size_t i = 0; i < controllers.size(); i++)
	{
		if (controllers[i]->isControllerValid()) {
			controllers[i]->GetInputs();
			controllers[i]->CheckInputs(elapsedTime);
		}
	}
	
	// Make improvements later on
	for (std::list<Pawn*>::iterator it = bots.begin(); it != bots.end();)
	{
		if (*it) {
			if ((*it)->getPawnState() == Pawn::IS_DEAD) {
				delete *it;
				it = bots.erase(it);
			}
			else {
				it++;
			}
		}
	}

	if (bots.size() <= 0) {
		isLevelCleared = true;
	}
}

void GameLevel::setPlayerCollisionDetector(CollisionDetector<Projectile>& cd)
{
	for (auto bot : bots)
	{
		bot->setCollisionDetector(cd);
	}
}

void GameLevel::AddAICollisionDetectorToBots(CollisionDetector<Projectile>& cd)
{
	for (auto bot : bots)
	{
		cd.addPawn(bot);
	}
}

bool GameLevel::hasLevelBeenCleared() const
{
	return isLevelCleared;
}
