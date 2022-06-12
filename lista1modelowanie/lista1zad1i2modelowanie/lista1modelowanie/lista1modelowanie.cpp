#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

// Override base class with your custom functionality
class GameOfLife : public olc::PixelGameEngine
{
public:
	std::vector<std::vector<int>> boardBeforeTick;
	std::vector<std::vector<int>> boardAfterTick;
	std::vector<int32_t> LStats;
	int screen_w;
	int screen_h;
	int N = 1;
	float ticks = 0.0f;
	float Tmax = 100.0f;
	float p0 = 0.6f;// 0.1, 0.3, 0.6, 0.75, 0.8;
	float size = 0.0f;
	bool bspace = false;

	std::ofstream density;

	GameOfLife(int screen_w, int screen_h, int Tmax) : screen_w(screen_w), screen_h(screen_h), size(screen_w* screen_h), Tmax(Tmax)
	{
		// Name your application
		sAppName = "GameOfLife";
	}

public:

	bool OnUserCreate() override
	{

		// Called once at the start, so create things here
		density.open("wynikiGestosci_06.txt");
		SetStartValues();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (bspace && ticks < Tmax) // && ticks < Tmax
			CheckAndDraw();

		if (GetMouse(0).bHeld) {
			boardAfterTick[GetMouseX()][GetMouseY()] = 1;
		}
		if (GetMouse(1).bHeld) {
			boardAfterTick[GetMouseX()][GetMouseY()] = 0;
		}
		if (GetKey(olc::Key::SPACE).bPressed && !bspace) {
			bspace = true;
		}
		else if (GetKey(olc::Key::SPACE).bPressed && bspace) {
			bspace = false;
		}
		return true;
	}
private:
	void CheckAndDraw() {

		boardBeforeTick = boardAfterTick;

		float AliveInTick = 0.0f;
		for (int x = 0; x < screen_w - 1; x++) { // 191
			for (int y = 0; y < screen_h - 1; y++) { // 175
				int AliveCounter = 0;
				{

					AliveCounter += boardBeforeTick[(x - 1 + screen_w) % screen_w][(y - 1 + screen_h) % screen_h];
					AliveCounter += boardBeforeTick[(x - 1 + screen_w) % screen_w][(y + screen_h) % screen_h];
					AliveCounter += boardBeforeTick[(x - 1 + screen_w) % screen_w][(y + 1 + screen_h) % screen_h];
					AliveCounter += boardBeforeTick[(x + 1 + screen_w) % screen_w][(y + 1 + screen_h) % screen_h];
					AliveCounter += boardBeforeTick[(x + 1 + screen_w) % screen_w][(y + screen_h) % screen_h];
					AliveCounter += boardBeforeTick[(x + 1 + screen_w) % screen_w][(y - 1 + screen_h) % screen_h];
					AliveCounter += boardBeforeTick[(x + screen_w) % screen_w][(y + 1 + screen_h) % screen_h];
					AliveCounter += boardBeforeTick[(x + screen_w) % screen_w][(y - 1 + screen_h) % screen_h];

					// dodatkowe
					//if (boardBeforeTick[x][y] == 1) { ++AliveCounter; }

				}
				if (boardBeforeTick[x][y] == 1)
					Draw(x, y, olc::Pixel(olc::WHITE));
				else
					Draw(x, y, olc::Pixel(olc::BLACK));

				// std::cout << AliveCounter << "\n";

				if (((AliveCounter == 2 || AliveCounter == 3) && boardBeforeTick[x][y] == 1) || AliveCounter == 3 && boardBeforeTick[x][y] == 0) {
					boardAfterTick[x][y] = 1;
				}
				else {
					boardAfterTick[x][y] = 0;
				}
				/*
				/// dodatkowe
				if (AliveCounter == 4 || AliveCounter == 6 || AliveCounter == 7 || AliveCounter == 8 || AliveCounter == 9) {
					boardAfterTick[x][y] = 1;
				}
				else {
					boardAfterTick[x][y] = 0;
				}*/

				if (boardAfterTick[x][y] == 1)
					AliveInTick++;
			}
		}

		ticks++;

		density << AliveInTick / 10000.0f << "\t" << ticks << "\n";
	}

	void SetStartValues() {

		boardBeforeTick.resize(screen_w, std::vector<int>(screen_h, 0));
		boardAfterTick.resize(screen_w, std::vector<int>(screen_h, 0));

		float AliveInTick = 0.0f;
		srand(time(NULL));
		for (int i = 0; i < screen_w - 1; ++i) {
			for (int j = 0; j < screen_h - 1; ++j) {
				float los = (rand() % 100) / 100.0f;
				if (los < p0) {
					boardAfterTick[i][j] = 1;
					AliveInTick++;
				}
				else {
					boardAfterTick[i][j] = 0;
				}
			}
		}

		ticks++;
		density << AliveInTick / 10000.0f << "\t" << ticks << "\n";
		boardBeforeTick = boardAfterTick;
	}
};

int main()
{
	int32_t screen_w = 5000, screen_h = 5000, pixel_w = 1, pixel_h = 1, Tmax = 1000; // 256 - 256 / 4, 240 - 256 / 4
	GameOfLife demo(screen_w, screen_h, Tmax);
	if (demo.Construct(screen_w, screen_h, pixel_w, pixel_h))
		demo.Start();
	/*for (int i = 0; i < 15; ++i) {
		GameOfLife demo(screen_w, screen_h, Tmax);
		if (demo.Construct(screen_w, screen_h, pixel_w, pixel_h))
			demo.Start();
	}*/
	return 0;
}