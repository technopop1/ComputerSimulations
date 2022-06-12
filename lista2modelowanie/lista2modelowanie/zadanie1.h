#pragma once

#include <random>
#include <time.h>
#include <array>
#include <iostream>

class zadanie1
{
public:
	zadanie1() {};
	void start() {
		srand(time(NULL));
		std::mt19937 mt(time(NULL));
		std::array<int, 10000> histogram1;
		histogram1.fill(0);
		std::array<int, 10000> histogram2;
		histogram2.fill(0);

		const int N = 10000;
		std::uniform_real_distribution<double> random(0, N);
		const unsigned long amount = 10000000;
		for (int i = 0; i < amount; ++i) {
			histogram1[random(mt)] ++;
			histogram2[rand() / (float)(RAND_MAX + 1) * N] ++;
		}
		for (int i = 0; i < histogram1.size(); ++i) {
			std::cout << i << "\t" << histogram1[i] << "\t" << histogram2[i] << "\n";
		}
	}
};

