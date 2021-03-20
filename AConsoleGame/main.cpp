#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
//#include <vector>
#include <list>
#include <iterator>

#include "ConsoleObject.h"
#include "Pawn.h"
#include "Projectile.h"
#include "Engine.h"
#include "GameLevel.h"
#include "CollisionDetectorManager.h"



int main()
{
	Pawn *player = new Pawn({ 2,2 }, { 3,3 }, { 50,50 }, Pawn::FireDirection::RIGHT);
	PlayerController *controller = new PlayerController(*player);
	GameLevel level;
	ConsoleEngine engine(&level);
	engine.setPlayer(*player);
	engine.setPlayerController(*controller);
	engine.Init();
	engine.Task();  
	_getch();
}