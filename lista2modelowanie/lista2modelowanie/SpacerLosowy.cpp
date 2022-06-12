#include "SpacerLosowy.h"

SpacerLosowy::SpacerLosowy(int N, int dimension)
{
	mt.seed(time(NULL));
	std::uniform_int_distribution<int> random(0, 256);
	board.resize(N, std::vector < std::vector<int> >(N, { 0,0,0 }));
	if (dimension == 2)
		for (int i = 0; i < 15; i++)
			kids.push_back(std::vector<int>{ N / 2, N / 2, random(mt), random(mt), random(mt) });
	if (dimension == 1)
		for (int i = 0; i < 15; i++)
			kids.push_back(std::vector<int>{ N / 2, std::uniform_int_distribution<int>(0, N)(mt), random(mt), random(mt), random(mt) });
	// Name your application
}

void SpacerLosowy::TwoDimension(int tick)
{

	std::uniform_int_distribution<int> random(0, 1);
	for (std::vector<int>& kid : kids) {
		Draw(kid.at(0), kid.at(1), olc::Pixel(kid.at(2), kid.at(3), kid.at(4)));
		board[kid.at(0)][kid.at(1)][0] = kid.at(2);
		board[kid.at(0)][kid.at(1)][1] = kid.at(3);
		board[kid.at(0)][kid.at(1)][2] = kid.at(4);
		if (random(mt) == 0) {
			kid.at(0) += (random(mt) == 1 ? 1 : -1);
			kid.at(0) += (kid.at(0) >= N ? -1 : 0);   // ochrona przed wyjœciem poza plansze
			kid.at(0) += (kid.at(0) < 0 ? 1 : 0);
		}
		else {
			kid.at(1) += (random(mt) == 1 ? 1 : -1);
			kid.at(1) += (kid.at(1) >= N ? -1 : 0);
			kid.at(1) += (kid.at(1) < 0 ? 1 : 0);
		}
	}
	if (tick % 50 == 0) {
		int down = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j].at(0) -= (board[i][j].at(0) - down > 0 ? down : 0);
				board[i][j].at(1) -= (board[i][j].at(1) - down > 0 ? down : 0);
				board[i][j].at(2) -= (board[i][j].at(2) - down > 0 ? down : 0);
				Draw(i, j, olc::Pixel(board[i][j].at(0), board[i][j].at(1), board[i][j].at(2)));
			}
		}
	}
}

void SpacerLosowy::OneDimension(int tick)
{

	std::uniform_int_distribution<int> random(0, 1);
	for (std::vector<int>& kid : kids) {
		Draw(kid.at(0), kid.at(1), olc::Pixel(kid.at(2), kid.at(3), kid.at(4)));
		board[kid.at(0)][kid.at(1)][0] = kid.at(2);
		board[kid.at(0)][kid.at(1)][1] = kid.at(3);
		board[kid.at(0)][kid.at(1)][2] = kid.at(4);
		if (random(mt) == 0) {
			kid.at(0) += (random(mt) == 1 ? 1 : -1);
			kid.at(0) += (kid.at(0) >= N ? -1 : 0);   // ochrona przed wyjœciem poza plansze
			kid.at(0) += (kid.at(0) < 0 ? 1 : 0);
		}
	}
	if (tick % 50 == 0) {
		int down = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j].at(0) -= (board[i][j].at(0) - down > 0 ? down : 0);
				board[i][j].at(1) -= (board[i][j].at(1) - down > 0 ? down : 0);
				board[i][j].at(2) -= (board[i][j].at(2) - down > 0 ? down : 0);
				Draw(i, j, olc::Pixel(board[i][j].at(0), board[i][j].at(1), board[i][j].at(2)));
			}
		}
	}
}
