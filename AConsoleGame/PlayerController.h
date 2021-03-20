#pragma once

#include "AController.h"

class Pawn;

class PlayerController : public AController{
public:
	PlayerController(Pawn &player);
	// Inherited via AController
	virtual void GetInputs() override;
	virtual void CheckInputs(float elapsedTime) override;
private:
	Pawn &player;
	bool keyStateMap[5];
};