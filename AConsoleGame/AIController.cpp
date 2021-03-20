#include <chrono>

#include "AIController.h"
#include "Engine.h"

AIController::AIController(Pawn *bot) :
	bot(bot),
	validController(true)
{	
	t1 = std::chrono::high_resolution_clock::now();
}

AIController::~AIController()
{
}

void AIController::GetInputs()
{
}

void AIController::CheckInputs(float elapsedTime)
{
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	if (bot) {
		// shitty by design, remove someday
		if (bot->getPawnState() == Pawn::IS_DEAD) {
			validController = false;
			return;
		}
		bot->Tick(elapsedTime);
		if (bot->getPawnState() == Pawn::PAWN_STATE::IS_ALIVE) {
			if (timeDiff > fireDelay) {
				t1 = t2;
				bot->FireProjectile();
			}

			ConsoleObject::Position p = bot->GetPosition();
			p.y += bot->GetVelocity().dy * elapsedTime;
			bot->setPosition(p);
		}
	}
}

bool AIController::isControllerValid() const
{
	return validController;
}
