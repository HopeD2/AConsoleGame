#pragma once

#include <Windows.h>
#include <chrono>
#include <thread>
#include <string>

#include "ConsoleObject.h"
#include "PlayerController.h"
#include "GameLevel.h"
#include "ACollisionDetector.h"
#include "ProjectileCollisionDetector.h"
#include "Pawn.h"

enum PIXEL_TYPE
{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};

enum COLOUR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, // Thanks MS :-/
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

//typedef std::chrono::system_clock curClock;
typedef std::chrono::high_resolution_clock curClock;
class GameLevel;
//template<>
//class CollisionDetector<Projectile>;
//class Pawn;

class ConsoleEngine {
public:
	ConsoleEngine();
	ConsoleEngine(GameLevel *level);
	~ConsoleEngine();
	void Init();
	static void Draw(/*col*/int x, /*row*/ int y, short c = 0x2588, short col = 0x000F);
	static void DrawRectangle(int x, int y, int size1, int size2);
	static void DrawPattern(int x, int y, std::string const& pattern);
	static void Clip(int &x, int &y);
	static void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);
	void clearScreen();
	static void WrapAround(float x, float y, float &wx, float &wy);
	static BOOL CloseHandler(DWORD evt);
	static bool IsOutofBoundaries(ConsoleObject::Position const& pos);
	void Task();
	static int screenWidth;
	static int screenHeight;
	void setPlayer(Pawn& pawn);
	void setPlayerController(PlayerController &controller);
private:
	int fontw = 16;
	int fonth = 16;
	float staticVelocity = 50.0f;

	curClock::time_point prevTick;
	SMALL_RECT m_rectWindow;
	static CHAR_INFO *m_bufScreen;
	std::wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
	HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	Pawn *player;
	PlayerController *playerController;
	GameLevel *level;

	CollisionDetector<Projectile> playerCollisionDetector;
	CollisionDetector<Projectile> collisionDetectorForAi;
};