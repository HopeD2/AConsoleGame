#include <Windows.h>

#include "PlayerController.h"
#include "ConsoleObject.h"
#include "Pawn.h"

PlayerController::PlayerController(Pawn & _player) : player(_player)
{
	for (size_t i = 0; i < 5; i++)
	{
		keyStateMap[i] = false;
	}
}

void PlayerController::GetInputs()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (GetAsyncKeyState(i + VK_LEFT) & 0x8000) {
			keyStateMap[i] = true;
		}
		else {
			keyStateMap[i] = false;
		}
	}

	//check for space
	if (GetAsyncKeyState(VK_SPACE) & 0x01) {
		keyStateMap[4] = true;
	}

}

void PlayerController::CheckInputs(float elapsedTime)
{
	// TODO : replace staticVelocity by player velo
	ConsoleObject::Position playerPosition = player.GetPosition();
	ConsoleObject::Velocity playerVelo = player.GetVelocity();

	if (keyStateMap[0]) {	//LEFT
		playerPosition.x -= playerVelo.dx * elapsedTime;
	}

	if (keyStateMap[1]) {	//UP
		playerPosition.y -= playerVelo.dx * elapsedTime;
	}

	if (keyStateMap[2]) {	//RIGHT
		playerPosition.x += playerVelo.dx * elapsedTime;
	}

	if (keyStateMap[3]) {	//DOWN
		playerPosition.y += playerVelo.dx * elapsedTime;
	}

	player.setPosition(playerPosition);

	if (keyStateMap[4]) {	//SPACE
		player.FireProjectile();
		keyStateMap[4] = false;
	}

}
