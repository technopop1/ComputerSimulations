#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
//#include "SpacerLosowy.h"
#include <vector>
#include <time.h>
#include <random>
#include "lista2modelowanie.h"
#include "zadanie1.h"
#include "zadanie34.h"

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	std::mt19937 mt;
	int N = 0;
	int dimension = 1;
	int tick = 0;
	int Tmax = 10000;
	std::vector<std::vector<int>> kids;
	std::vector<std::vector<std::vector<int>>> board;
	std::vector<int> histogram;

	Example(int N, int dimension) : N(N), dimension(dimension)
	{
		histogram.resize(N, 0);

		mt.seed(time(NULL));
		std::uniform_int_distribution<int> random(0, 256);
		board.resize(N, std::vector < std::vector<int> >(N, {0,0,0}));

		if (dimension == 2)
			for (int i = 0; i < 8; i++)
				kids.push_back(std::vector<int>{ N / 2, N / 2, random(mt), random(mt), random(mt) });
		if (dimension == 1)
			for (int i = 0; i < N; i++)
				kids.push_back(std::vector<int>{ N / 2, std::uniform_int_distribution<int>(0, N)(mt), random(mt), random(mt), random(mt) });
		
		// Name your application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (tick < Tmax) {
			if (dimension == 1)
				OneDimension();
			else
				TwoDimension();
		}
		else
			exit(0);
		// zad 3
		/*if (tick == Tmax && dimension == 1) {
			int distance = 0;
			for (std::vector<int> &kid : kids) {
				distance = (kid.at(0) > N/2 ? kid.at(0) - N/2 : -(N/2 - kid.at(0)) ); // 33
				int index = distance + N / 2; 
				histogram.at(index) += 1;
			}
			for (int i = 0; i < N; ++i) {
				//int index = i + N / 2;
				std::cout << i - N / 2 << "\t" << histogram.at( i ) << "\n";
			}
			exit(0);
		}*/
		++tick;

		return true;
	}

	void TwoDimension()
	{

		std::uniform_int_distribution<int> random(0, 1);
		for (std::vector<int>& kid : kids) {
			Draw(kid.at(0), kid.at(1), olc::Pixel(kid.at(2), kid.at(3), kid.at(4)));
			board[kid.at(0)][kid.at(1)][0] = kid.at(2);
			board[kid.at(0)][kid.at(1)][1] = kid.at(3);
			board[kid.at(0)][kid.at(1)][2] = kid.at(4);
			if (random(mt) == 0) {
				kid.at(0) += (random(mt) == 1 ? 1 : -1);
			}
			else {
				kid.at(1) += (random(mt) == 1 ? 1 : -1);
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
	void OneDimension()
	{

		std::uniform_int_distribution<int> random(0, 1);
		for (std::vector<int>& kid : kids) {
			Draw(kid.at(0), kid.at(1), olc::Pixel(kid.at(2), kid.at(3), kid.at(4)));
			board[kid.at(0)][kid.at(1)][0] = kid.at(2);
			board[kid.at(0)][kid.at(1)][1] = kid.at(3);
			board[kid.at(0)][kid.at(1)][2] = kid.at(4);
			if (random(mt) == 0) {
				kid.at(0) += (random(mt) == 1 ? 1 : -1);
				kid.at(0) += (kid.at(0) >= N ? -1 : 0);   // ochrona przed wyjściem poza plansze
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

};

int main()
{
	int N = 1000;
	int dimension = 2;
	srand(time(NULL));
	

	//Example demo(N, dimension);
	//if (demo.Construct(N, N, 1, 1, true))
	//	demo.Start();
	
	// zad 2
	/*zadanie34 zad2(N, dimension, 0);
	int i = zad2.Tmax + 1;
	while (i-- > 0) {
		zad2.OnUserUpdate();
	}*/

	// zad 3
	/*zadanie34 zad3(N, dimension, 0);
	int i = zad3.Tmax+1;
	while (i-- > 0) {
		zad3.OnUserUpdate();
	}*/

	// zad 4
	/*while (dimension > 0) {
		N = 10;
		while (N < 1000) {
			zadanie34 zad4(N, dimension, 0);
			zad4.Tmax = N;
			int i = zad4.Tmax + 1;
			while (i-- > 0) {
				zad4.OnUserUpdate();
			}
			std::cout << zad4.StartPointCounter << "\t" << N << "\t" << dimension << "\n";
			N += 10;
		}
		dimension--;
	}*/

	// zad 5
	/*zadanie34 zad5(N, dimension, 0);
	int i = zad5.Tmax + 1;
	while (i-- > 0) {
		zad5.OnUserUpdate();
	}
	float dyfuzja = (zad5.offset / 1000000)/(2*dimension*N);
	std::cout << "przemieszczenie srednie kwadratowe = " << zad5.offset / 1000000 <<"\n";
	std::cout << "dyfuzja = " << dyfuzja;
	*/

	// zad 7
	zadanie34 zad7(N, dimension, 200);
	int i = zad7.Tmax + 1;
	while (i-- > 0) {
		zad7.OnUserUpdate();
	}
	float dyfuzja = (zad7.offset / 1000000) / (2 * dimension * N);
	std::cout << "przemieszczenie srednie kwadratowe = " << zad7.offset / 1000000 << "\n";
	std::cout << "dyfuzja = " << dyfuzja;

	return 0;
}