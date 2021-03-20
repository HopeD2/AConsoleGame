#pragma once

#include <chrono>

#include"AController.h"
#include "Pawn.h"

class AIController : public AController {
public:
	AIController(Pawn *bot);
	~AIController();

	virtual void GetInputs() override;
	virtual void CheckInputs(float elapsedTime) override;
	bool isControllerValid() const;
private:
	Pawn *bot;
	float fireDelay = 400;
	std::chrono::high_resolution_clock::time_point t1;
	bool validController;
};
