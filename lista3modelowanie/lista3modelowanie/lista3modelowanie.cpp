#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <vector>
#include <random>
#include <time.h>

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	std::vector<std::vector<bool>> boardAfter;
	std::vector<std::vector<bool>> boardBefore;
	std::vector<std::vector<int>> cells;
	int N = 0;
	int counter = 0;
	std::mt19937 mt;
	float clock = 0.0;
	float maxRadius = 0.0;
	int furthestAlive = 0.0;	//	OPTYMALIZACJA	
	bool btimeStop = false;

	Example(int N) : N(N)
	{
		mt.seed(time(NULL));
		// zad 1  2////////////////////////////////////////////////////
		boardBefore.resize(N, std::vector<bool>(N, false));
		boardBefore[N / 2][N / 2] = true;
		boardBefore[N / 2 + 1][N / 2] = true;
		boardBefore[N / 2][N / 2 + 1 ] = true;
		boardBefore[N / 2][N / 2 + 1] = true;
		boardBefore[N / 2 + 1][N / 2 + 1] = true;
		boardBefore[N / 2 - 1][N / 2 - 1] = true;
		boardBefore[N / 2 + 1][N / 2 -1] = true;
		boardBefore[N / 2 - 1][N / 2 + 1] = true;
		boardAfter = boardBefore;
		// zad 2 ////////////////////////////////////////////////////
		for (int i = 0; i < N * 50; ++i) {
			cells.push_back(std::vector<int>{1, std::uniform_int_distribution<int>(0, N-1)(mt), std::uniform_int_distribution<int>(0, N-1)(mt)});
		}


		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (btimeStop){
			//zad1();
			zad2();
			//zad3();
		}
		if (GetMouse(0).bHeld) {
			boardAfter[GetMouseX()][GetMouseY()] = true;
		}
		if (GetMouse(1).bHeld) {
			boardAfter[GetMouseX()][GetMouseY()] = false;
		}
		if (GetKey(olc::Key::SPACE).bPressed && !btimeStop) {
			btimeStop = true;
		}
		else if (GetKey(olc::Key::SPACE).bPressed && btimeStop) {
			btimeStop = false;
		}


		return true;
	}

	void zad1() {
		if (counter < N*50) {
			boardBefore = boardAfter;

				int totalmass = 0;
				int totalx = 0;
				int totaly = 0;
				float sumOfRadiuses = 0.0;
				float sumOfGrowing = 0.0;
				int FurthestCELL = 0; //	OPTYMALIZACJA	
				std::vector<std::pair<int, int>> cangrow;
				//for (int x = 0 ; x < N ; ++x) {
				//	for (int y = 0 ; y < N ; ++y) {
				for (int x = (N/2)- furthestAlive - 1; x < (N / 2) + furthestAlive + 1; ++x) { //	OPTYMALIZACJA	
					for (int y = (N / 2) - furthestAlive - 1; y < (N / 2) + furthestAlive + 1; ++y) { //	OPTYMALIZACJA
						if (boardBefore[x][y] == true) {
							totalmass += 1;
							totalx += x;
							totaly += y;
							//	OPTYMALIZACJA	
							if (sqrt(pow(x - N / 2, 2) + pow(y - N / 2, 2)) > FurthestCELL)
								FurthestCELL = sqrt(pow(x - N / 2, 2) + pow(y - N / 2, 2));
						}
						if (boardBefore[x][y] == true && (
							boardBefore[(x + N) % N][(y - 1 + N) % N] == false ||
							boardBefore[(x + 1 + N) % N][(y + N) % N] == false ||
							boardBefore[(x + N) % N][(y + 1 + N) % N] == false ||
							boardBefore[(x - 1 + N) % N][(y + N) % N] == false))
						{
							cangrow.push_back(std::pair<int, int>{x, y});
							sumOfGrowing++;
						}
						//else boardBefore[x][y] = false;
					}
				}

				int losAliveCell = std::uniform_int_distribution<int>(0, cangrow.size() - 1)(mt);
				std::vector<std::pair<int, int>> neighbors;
				// WARIANT C
				if (boardBefore[cangrow[losAliveCell].first][cangrow[losAliveCell].second] == true) {
					if (boardBefore[(cangrow[losAliveCell].first + N) % N][(cangrow[losAliveCell].second - 1 + N) % N] == false) neighbors.push_back(std::pair<int, int>{(cangrow[losAliveCell].first + N) % N, (cangrow[losAliveCell].second - 1 + N) % N});
					if (boardBefore[(cangrow[losAliveCell].first + 1 + N) % N][(cangrow[losAliveCell].second + N) % N] == false) neighbors.push_back(std::pair<int, int>{(cangrow[losAliveCell].first + 1 + N) % N, (cangrow[losAliveCell].second + N) % N});
					if (boardBefore[(cangrow[losAliveCell].first + N) % N][(cangrow[losAliveCell].second + 1 + N) % N] == false) neighbors.push_back(std::pair<int, int>{(cangrow[losAliveCell].first + N) % N, (cangrow[losAliveCell].second + 1 + N) % N});
					if (boardBefore[(cangrow[losAliveCell].first - 1 + N) % N][(cangrow[losAliveCell].second + N) % N] == false) neighbors.push_back(std::pair<int, int>{(cangrow[losAliveCell].first - 1 + N) % N, (cangrow[losAliveCell].second + N) % N});

					if (!neighbors.empty()) {
						int newCellindex = std::uniform_int_distribution<int>(0, neighbors.size() - 1)(mt);
						boardAfter[neighbors[newCellindex].first][neighbors[newCellindex].second] = true;
					}
				}

				//for (int x = 0; x < N; ++x) {
				//	for (int y = 0; y < N; ++y) {
				for (int x = (N / 2) - furthestAlive - 1; x < (N / 2) + furthestAlive + 1; ++x) {
					for (int y = (N / 2) - furthestAlive - 1; y < (N / 2) + furthestAlive + 1; ++y) {
						if (boardBefore[x][y] == true) {
							Draw(x, y, olc::Pixel(138, 144, 74));
						}
					}
				}
				/**/
				std::pair<int, int> CenterOfMass{ totalx / totalmass, totaly / totalmass };
				for (std::pair<int, int> &AliveCell : cangrow) {
					sumOfRadiuses += sqrt(pow(AliveCell.first - CenterOfMass.first, 2) + pow(AliveCell.second - CenterOfMass.second, 2));
				}

				DrawCircle(CenterOfMass.first, CenterOfMass.second, sumOfRadiuses / sumOfGrowing, olc::RED);

				float time = sqrt(counter);
				//std::cout << time << "\t" << sumOfRadiuses / sumOfGrowing << "\n";
				std::cout << counter << "\t" << time << "\t" << sumOfRadiuses / sumOfGrowing << "\n";
				//std::cout << time << "\t" << counter << "\n";
				
				furthestAlive = FurthestCELL; //	OPTYMALIZACJA	

			++counter;
			}
			else
			{
				//std::cout << maxRadius << "\t" << sqrt(N);
				exit(0);
			}
	}
	void zad2() {

		if (counter < N * 50) {
			boardBefore = boardAfter;

			std::uniform_int_distribution<int> random(0, 3);
			for (std::vector<int>& cell : cells) {
				if (cell.at(0) == 1) {
					//Draw(cell.at(1), cell.at(2), olc::BLACK);
					if (boardBefore[(cell.at(1) + 1 + N) % N][(cell.at(2) + N) % N] == true ||
						boardBefore[(cell.at(1) - 1 + N) % N][(cell.at(2) + N) % N] == true ||
						boardBefore[(cell.at(1) + N) % N][(cell.at(2) + 1 + N) % N] == true ||
						boardBefore[(cell.at(1) + N) % N][(cell.at(2) - 1 + N) % N] == true ||

						boardBefore[(cell.at(1) + 1 + N) % N][(cell.at(2) + 1 + N) % N] == true ||
						boardBefore[(cell.at(1) - 1 + N) % N][(cell.at(2) - 1 + N) % N] == true ||
						boardBefore[(cell.at(1) + 1 + N) % N][(cell.at(2) - 1 + N) % N] == true ||
						boardBefore[(cell.at(1) - 1 + N) % N][(cell.at(2) + 1 + N) % N] == true)
					{
						boardAfter[cell.at(1)][cell.at(2)] = true;
						cell.at(0) = 0;
					}
					else {
						int los = random(mt);
						if (los == 0) {
							cell.at(1) = (std::uniform_int_distribution<int>(0, 1)(mt) == 1 ? (cell.at(1) + 1 + N) % N : (cell.at(1) - 1 + N) % N);
						}
						else if (los == 1) {
							cell.at(2) = (std::uniform_int_distribution<int>(0, 1)(mt) == 1 ? (cell.at(2) + 1 + N) % N : (cell.at(2) - 1 + N) % N);
						}
						else if (los == 2) {
							if (std::uniform_int_distribution<int>(0, 1)(mt) == 1) {
								cell.at(1) = (cell.at(1) + 1 + N) % N;
								cell.at(2) = (cell.at(2) - 1 + N) % N;
							}
							else {
								cell.at(1) = (cell.at(1) - 1 + N) % N;
								cell.at(2) = (cell.at(2) + 1 + N) % N;
							}
						}
						else {
							if (std::uniform_int_distribution<int>(0, 1)(mt) == 1) {
								cell.at(1) = (cell.at(1) - 1 + N) % N;
								cell.at(2) = (cell.at(2) - 1 + N) % N;
							}
							else {
								cell.at(1) = (cell.at(1) + 1 + N) % N;
								cell.at(2) = (cell.at(2) + 1 + N) % N;
							}
						}
					}
					//Draw(cell.at(1), cell.at(2), olc::Pixel(100, 100, 50));
				}
			}

			int totalmass = 0;
			int totalx = 0;
			int totaly = 0;
			int FurthestCELL = 0; //	OPTYMALIZACJA	
			float sumOfGrowing = 0.0;
			float sumOfRadiuses = 0.0;
			std::vector<std::pair<int, int>> cangrow;

			Clear(olc::BLACK);

			if (furthestAlive < N / 2) {
				for (int x = (N / 2) - furthestAlive - 1; x < (N / 2) + furthestAlive + 1; ++x) { //	OPTYMALIZACJA	
					for (int y = (N / 2) - furthestAlive - 1; y < (N / 2) + furthestAlive + 1; ++y) { //	OPTYMALIZACJA
						if (boardBefore[x][y] == true) {
							totalmass += 1;
							totalx += x * 1;
							totaly += y * 1;
							//	OPTYMALIZACJA	
							if (sqrt(pow(x - N / 2, 2) + pow(y - N / 2, 2)) > FurthestCELL)
								FurthestCELL = sqrt(pow(x - N / 2, 2) + pow(y - N / 2, 2));
						}
						if (boardBefore[x][y] == true && (
								boardBefore[(x + N) % N][(y - 1 + N) % N] == false ||
								boardBefore[(x + 1 + N) % N][(y + N) % N] == false ||
								boardBefore[(x + N) % N][(y + 1 + N) % N] == false ||
								boardBefore[(x - 1 + N) % N][(y + N) % N] == false)) 
						{
							sumOfGrowing++;
							cangrow.push_back(std::pair<int, int>{x, y});
						}
					}
				}
			}
			furthestAlive = FurthestCELL;

			for (int x = 0; x < N; ++x) {
				for (int y = 0; y < N; ++y) {
					if (boardBefore[x][y] == true) {
						//if (maxRadius < sqrt(pow(x - CenterOfMass.first, 2) + pow(y - CenterOfMass.second, 2))) maxRadius = sqrt(pow(x - CenterOfMass.first, 2) + pow(y - CenterOfMass.second, 2));
						
						Draw(x, y, olc::Pixel(38, 164, 223));
					}
					//else 
						//Draw(x, y, olc::BLACK);
				}
			}
			std::pair<int, int> CenterOfMass{ totalx / totalmass, totaly / totalmass };
			for (std::pair<int, int>& AliveCell : cangrow) {
				sumOfRadiuses += sqrt(pow(AliveCell.first - CenterOfMass.first, 2) + pow(AliveCell.second - CenterOfMass.second, 2));
			}

			DrawCircle(CenterOfMass.first, CenterOfMass.second, sumOfRadiuses / sumOfGrowing, olc::RED);

			std::cout << totalmass << "\t" << sumOfRadiuses / sumOfGrowing << "\n"; // promien do ilosci czasteczek
			//DrawCircle(CenterOfMass.first, CenterOfMass.second, maxRadius, olc::RED);
			counter++;
		}
		else
			exit(0);
	}
	void zad3() {

		if (counter < N / 1.5) {
			boardBefore = boardAfter;

			for (int x = 0; x < N; ++x) {
				for (int y = 0; y < N; ++y) {
					int neighbors = 0;
					if (boardBefore[(x + 1 + N) % N][(y + N) % N] == true) { ++neighbors; }
					if (boardBefore[(x - 1 + N) % N][(y + N) % N] == true) { ++neighbors; }
					if (boardBefore[(x + N) % N][(y + 1 + N) % N] == true) { ++neighbors; }
					if (boardBefore[(x + N) % N][(y - 1 + N) % N] == true) { ++neighbors; }
					if ( y % 2 != 0 ){
						if (boardBefore[(x + 1 + N) % N][(y + 1 + N) % N] == true) { ++neighbors; }
						if (boardBefore[(x + 1 + N) % N][(y - 1 + N) % N] == true) { ++neighbors; }
					}
					else {
						if (boardBefore[(x - 1 + N) % N][(y - 1 + N) % N] == true) { ++neighbors; }
						if (boardBefore[(x - 1 + N) % N][(y + 1 + N) % N] == true) { ++neighbors; }
					}
					if (neighbors == 4)
						boardAfter[x][y] = true;
				}
			}
			for (int x = 0; x < N; ++x) {
				for (int y = 0; y < N; ++y) {
					if (boardBefore[x][y] == true) {
						Draw(x, y, olc::Pixel(38, 164, 223));
					}
				}
			}
			counter++;
		}
		//else
			//exit(0);
	}
};

int main()
{
	int N = 1000;
	Example demo(N);
	if (demo.Construct(N, N, 1, 1, true))
		demo.Start();
	return 0;
}