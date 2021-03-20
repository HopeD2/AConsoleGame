
#include <iostream>
#include <conio.h>

#include "Engine.h"
#include "Pawn.h"

int ConsoleEngine::screenWidth = 80;
int ConsoleEngine::screenHeight = 50;
CHAR_INFO *ConsoleEngine::m_bufScreen;

ConsoleEngine::ConsoleEngine()
{
}

ConsoleEngine::ConsoleEngine(GameLevel *_level): level(_level)
{
}

ConsoleEngine::~ConsoleEngine()
{
}

void ConsoleEngine::Init() {
	if (m_hConsole == INVALID_HANDLE_VALUE) {
		printf("Error!\n");
	}

	// Change console visual size to a minimum so ScreenBuffer can shrink
	// below the actual visual size
	m_rectWindow = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

	// Set the size of the screen buffer
	COORD coord = { (short)screenWidth, (short)screenHeight };
	if (!SetConsoleScreenBufferSize(m_hConsole, coord))
		printf("Error!\n");

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(m_hConsole))
		printf("Error!\n");

	// Set the font size now that the screen buffer has been assigned to the console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Consolas");
	if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi))
		printf("Error!\n");

	// Get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(m_hConsole, &csbi))
		printf("Error!\n");
	if (screenHeight > csbi.dwMaximumWindowSize.Y)
		printf("Error!\n");
	if (screenWidth > csbi.dwMaximumWindowSize.X)
		printf("Error!\n");

	// Set Physical Console Window Size
	m_rectWindow = { 0, 0, (short)screenWidth - 1, (short)screenHeight - 1 };
	if (!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow))
		printf("Error!\n");

	// Set flags to allow mouse input		
	if (!SetConsoleMode(m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		printf("Error!\n");

	// Allocate memory for screen buffer
	m_bufScreen = new CHAR_INFO[screenWidth*screenHeight];
	memset(m_bufScreen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);
}

void ConsoleEngine::Draw(/*col*/int x, /*row*/ int y, short c, short col)
{
	if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
	{
		m_bufScreen[y * screenWidth + x].Char.UnicodeChar = c;
		m_bufScreen[y * screenWidth + x].Attributes = col;
	}
}

void ConsoleEngine::DrawRectangle(int x, int y, int size1, int size2) {
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			float wx, wy;
			WrapAround(x + i, y + j, wx, wy);
			Draw(wx, wy);
		}
	}
}

/*
pattern += "###,";
pattern += "###,";
pattern += "###,";
*/

void ConsoleEngine::DrawPattern(int x, int y, std::string const& pattern)
{
	for (size_t k = 0,i = 0, j = 0; k < pattern.size(); k++)
	{
		if (pattern[k] == '#') {
			float wx, wy;
			WrapAround(x + i, y + j, wx, wy);
			Draw(wx, wy);
			i++;
		}
		else if (pattern[k] == ',') {
			j++;
			i = 0;
		}
		else if(pattern[k] == '.'){
			float wx, wy;
			WrapAround(x + i, y + j, wx, wy);
			Draw(wx, wy, PIXEL_SOLID, FG_BLACK);
			i++;
		}
		
	}
}

void ConsoleEngine::clearScreen() {
	for (int i = 0; i < screenWidth; i++)
	{
		for (int j = 0; j < screenHeight; j++)
		{
			Draw(i, j, PIXEL_SOLID, 0x0000);
		}
	}

}

BOOL ConsoleEngine::CloseHandler(DWORD evt)
{
	// Note this gets called in a seperate OS thread, so it must
	// only exit when the game has finished cleaning up, or else
	// the process will be killed before OnUserDestroy() has finished
	if (evt == CTRL_CLOSE_EVENT)
	{
		//m_bAtomActive = false;

		// Wait for thread to be exited
	//	std::unique_lock<std::mutex> ul(m_muxGame);
	//	m_cvGameFinished.wait(ul);
	}
	return true;
}

bool ConsoleEngine::IsOutofBoundaries(ConsoleObject::Position const& pos)
{
	if (pos.x >= screenWidth || pos.x < 0 || pos.y >= screenHeight || pos.y < 0) {
		return true;
	}
	else {
		return false;
	}
}

void ConsoleEngine::Task()
{
	using namespace std::chrono;
	Init();
	clearScreen();
	prevTick = curClock::now();

	// Set Player CD's
	// Each bot will carry the CD so that the same CD can monitor projectiles
	level->setPlayerCollisionDetector(playerCollisionDetector);
	// Player Pawn added to CD in order to check for damage
	playerCollisionDetector.addPawn(player);
	// Set AI CD's
	// Monitor Player Pawn projectiles
	player->setCollisionDetector(collisionDetectorForAi);
	// Each AI pawn is added to CD in order to check for damage
	level->AddAICollisionDetectorToBots(collisionDetectorForAi);

	while (player->getPawnState() == Pawn::IS_ALIVE) {
		clearScreen();
		curClock::time_point curTick = curClock::now();
		duration<float> elapsedTime = duration<float>(curTick - prevTick);
		prevTick = curTick;
		float felapsedTime = elapsedTime.count();
		if (player) {
			player->Tick(felapsedTime);
		}
		if (playerController) {
			playerController->GetInputs();
			playerController->CheckInputs(felapsedTime);
		}
		if (level) {
			level->Tick(felapsedTime);
		}
		// check collisions
		playerCollisionDetector.CollisionTask();
		collisionDetectorForAi.CollisionTask();
		if (level->hasLevelBeenCleared()) {
			break;
		}

		WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)screenWidth, (short)screenHeight }, { 0,0 }, &m_rectWindow);
	}
	clearScreen();
	WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)screenWidth, (short)screenHeight }, { 0,0 }, &m_rectWindow);
}

void ConsoleEngine::setPlayer(Pawn& pawn)
{
	this->player = &pawn;
}

void ConsoleEngine::setPlayerController(PlayerController & controller)
{
	this->playerController = &controller;
}

void ConsoleEngine::Clip(int &x, int &y)
{
	if (x < 0) x = 0;
	if (x >= screenWidth) x = screenWidth;
	if (y < 0) y = 0;
	if (y >= screenHeight) y = screenHeight;
}

void ConsoleEngine::Fill(int x1, int y1, int x2, int y2, short c, short col)
{
	Clip(x1, y1);
	Clip(x2, y2);
	for (int x = x1; x < x2; x++)
		for (int y = y1; y < y2; y++)
			Draw(x, y, c, col);
}

void ConsoleEngine::WrapAround(float x, float y, float &wx, float &wy) {
	wx = x;
	wy = y;
	if (x < 0) {
		wx = x + screenWidth;
	}

	if (y < 0) {
		wy = y + screenHeight;
	}

	if (x >= screenWidth) {
		wx = x - screenWidth;
	}

	if (y >= screenHeight) {
		wy = y - screenHeight;
	}
}