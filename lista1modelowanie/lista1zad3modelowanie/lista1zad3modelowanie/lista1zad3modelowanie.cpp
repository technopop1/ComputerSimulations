#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void CheckAndDraw(std::vector<std::vector<int>>& boardBeforeTick, std::vector<std::vector<int>>& boardAfterTick, int screen_w, int screen_h, float p0) {

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
			}

			if (((AliveCounter == 2 || AliveCounter == 3) && boardBeforeTick[x][y] == 1) || AliveCounter == 3 && boardBeforeTick[x][y] == 0) {
				boardAfterTick[x][y] = 1;
			}
			else {
				boardAfterTick[x][y] = 0;
			}

			if (boardAfterTick[x][y] == 1)
				AliveInTick++;
		}
	}

	//density << AliveInTick / 10000.0f << "\t" << ticks << "\n";
}

void SetStartValues(std::vector<std::vector<int>> &boardBeforeTick, std::vector<std::vector<int>> &boardAfterTick, int screen_w, int screen_h, float p0, float ticks) {

	boardBeforeTick.clear();
	boardAfterTick.clear();

	boardBeforeTick.resize(screen_w, std::vector<int>(screen_h, 0));
	boardAfterTick.resize(screen_w, std::vector<int>(screen_h, 0));

	float AliveInTick = 0.0f;
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
	//density << AliveInTick / 10000.0f << "\t" << ticks << "\n";
	boardBeforeTick = boardAfterTick;
}

int main()
{
	std::vector<std::vector<int>> boardBeforeTick;
	std::vector<std::vector<int>> boardAfterTick;
	std::vector<int32_t> LStats;
	int N = 1;
	float ticks = 0.0f;
	float Tmax = 1000.0f;
	float p0 = 0.6f;// 0.1, 0.3, 0.6, 0.75, 0.8;
	float Mysize = 0.0f;
	int screen_w = 0, screen_h = 0;

	// "wynikiBledu_10_06_100.txt", "wynikiBledu_100_06_100.txt", "wynikiBledu_200_06_100.txt", "wynikiBledu_500_06_100.txt", "wynikiBledu_1000_06_100.txt", 
	std::vector<std::string> txtfiles{ "wynikiBledu_500_06_100.txt" };
	std::ofstream file;

	srand(time(NULL));

	std::vector <std::pair<float, int>> NextStepValues{ { 0.6, 1000} };//{0.6, 10}, { 0.6, 100 },  { 0.6, 200 }, { 0.6, 500}, { 0.6, 1000}
	int licz = 0;
	for (auto i : NextStepValues) {

		screen_w = i.second;
		screen_h = i.second;
		Mysize = screen_w * screen_h;
		p0 = i.first;
		N = 1;
		ticks = 0.0f;
		SetStartValues(boardBeforeTick, boardAfterTick, screen_w, screen_h, p0, ticks);
		while (ticks < Tmax) {

			CheckAndDraw(boardBeforeTick, boardAfterTick, screen_w, screen_h, p0);

			ticks++;
			//std::cout << ticks << " ";
			if (ticks >= Tmax && N <= 100) {
				ticks = 0.0f;
				float AliveAtLastTick = 0.0;
				for (std::vector<int> row : boardBeforeTick) {
					for (int j : row) {
						AliveAtLastTick += j;
					}
				}
				std::cout << N << "\t" << AliveAtLastTick / Mysize << "\n";
				std::string name = txtfiles[licz];
				file.open(name, std::ios::app);
				file << AliveAtLastTick / Mysize << "\t" << N << "\n";
				file.close();
				
				++N;
				SetStartValues(boardBeforeTick, boardAfterTick, screen_w, screen_h, p0, ticks);
			}
			else if (N > 100) {
				ticks = Tmax + 1;
			}
		}
		licz++;
	
	}
	
	return 0;
}