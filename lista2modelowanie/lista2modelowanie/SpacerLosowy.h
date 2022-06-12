
#include "olcPixelGameEngine.h"
#include <vector>
#include <time.h>
#include <iostream>
#include <random>

class SpacerLosowy : public olc::PixelGameEngine
{
public:
	std::mt19937 mt;
	int N = 0;
	int dimension = 2;
	int tick = 0;
	std::vector<std::vector<int>> kids;
	std::vector<std::vector<std::vector<int>>> board;
	SpacerLosowy(int N, int dimension = 2);

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		if (dimension == 1)
			OneDimension(tick);
		else
			TwoDimension(tick);
		++tick;

		return true;
	}
	void check() {
		if (this->Construct(N, N, 4, 4, true))
			this->Start();
	}
	void TwoDimension(int tick);
	void OneDimension(int tick);
};

