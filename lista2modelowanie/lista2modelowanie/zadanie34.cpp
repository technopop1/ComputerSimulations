#include "zadanie34.h"
#include <cmath>

zadanie34::zadanie34(int N, int dimension, int obstacle = 50) : N(N), dimension(dimension), obstacle(obstacle)
{
	histogram.resize(N, 0);
	board.resize(N, std::vector<int>(N, 0));

	mt.seed(time(NULL));
	std::uniform_int_distribution<int> random(0, 256);

	// zad 7
	std::uniform_int_distribution<int> randomObstacle(0, N);
	while (--obstacle >= 0) {
		int x = randomObstacle(mt), y = randomObstacle(mt);
		if (x != N / 2 && y != N / 2 && x != 0 && x != N && y != 0 && y != N) {
			board[x][x] = 1;
			board[x+1][x] = 1;
			board[x][x+1] = 1;
			board[x-1][x] = 1;
			board[x][x-1] = 1;
			board[x+1][x+1] = 1;
			board[x-1][x-1] = 1;
			board[x-1][x+1] = 1;
			board[x+1][x-1] = 1;
		}
	}///


	if (dimension == 2)
		for (int i = 0; i < 1000000; i++)
			kids.push_back(std::pair<int, int>{ N / 2, N / 2});
	/*if (dimension == 1)
		for (int i = 0; i < 1000000; i++)
			kids.push_back(std::pair<int, int>{ N / 2, std::uniform_int_distribution<int>(0, N)(mt)});
	 */// zad2345
	if (dimension == 1)
		for (int i = 0; i < 1000000; i++)
			kids.push_back(std::pair<int, int>{ N / 2, N / 2 });
		
}

void zadanie34::OnUserUpdate()
{
	if (tick < Tmax) {
		if (dimension == 1)
			OneDimension();
		else
			TwoDimension();
	}

	// zad 2 w onedimension()

	// zad 3
	/*if (tick == Tmax && dimension == 1) {
		int distance = 0;
		for (std::pair<int, int>& kid : kids) {
			distance = (kid.first > N / 2 ? kid.first - N / 2 : -(N / 2 - kid.first)); // index -> histogram
			int index = distance + N / 2;
			histogram.at(index) += 1;
		}
		for (int i = 0; i < N; ++i) {
			//int index = i + N / 2;
			std::cout << i - N / 2 << "\t" << histogram.at(i) << "\n";
		}
		exit(0);
	}*/

	// zad 4
	/*for (std::pair<int, int>& kid : kids) {

		if ( (dimension == 2 && kid.first == N / 2 && kid.second == N / 2) || (dimension == 1 && kid.first == N/2) ) {
			++StartPointCounter;
		}
	}*/
	
	// zad 6
	if (tick == Tmax && dimension == 2) {
		for (std::pair<int, int>& kid : kids) {
			//offset += std::sqrt((kid.first - N / 2) * (kid.first - N / 2) + (kid.second - N / 2) * (kid.second - N / 2));
			offset += (kid.first - N / 2) * (kid.first - N / 2) + (kid.second - N / 2) * (kid.second - N / 2);
		}
	}
	++tick;
}

void zadanie34::TwoDimension()
{

	std::uniform_int_distribution<int> random(0, 1);
	//std::uniform_int_distribution<int> random(0, 3); // zad 6
	std::uniform_int_distribution<int> randomXY(0, 1);
	for (std::pair<int, int>& kid : kids) {

		int los = random(mt);
		bool ifnotmove = true; // zad 7 
		int xP = kid.first, yP = kid.second; // zad 7
		while (ifnotmove) { // zad 7
			if (los == 0)
				kid.first += (randomXY(mt) == 1 ? 1 : -1);
			else if (los == 1)
				kid.second += (randomXY(mt) == 1 ? 1 : -1);
			// zad 6 / 7
			else if (los == 2) {
				if (randomXY(mt) == 1) {
					++kid.first;
					--kid.second;
				}
				else {
					--kid.first;
					++kid.second;
				}
			}
			else {
				if (randomXY(mt) == 1) {
					++kid.first;
					++kid.second;
				}
				else {
					--kid.first;
					--kid.second;
				}
			}
			if (board[kid.first][kid.second] == 1) {
				kid.first = xP;
				kid.second = yP;
			}
			else
				ifnotmove = false;
		}
	}
}

void zadanie34::OneDimension()
{

	std::uniform_int_distribution<int> random(0, 1);
	for (std::pair<int, int>& kid : kids) {
		kid.first += (random(mt) == 1 ? 1 : -1);
		kid.first += (kid.first >= N ? -2 : 0);   // ochrona przed wyjœciem poza plansze
		kid.first += (kid.first < 0 ? 2 : 0);
		//zad2
		//std::cout << kid.first << "\t";
	}
	//std::cout << "\n";
}
