#pragma once
#include <vector>
#include <iostream>
#include <random>

class zadanie34
{

public:
	std::mt19937 mt;
	int N = 0;
	int dimension = 1;
	int tick = 0;
	int Tmax = 1000;
	float offset = 0.0;
	int obstacle = 50;   // zad 7
	long int StartPointCounter = 0;
	std::vector<std::pair<int, int>> kids;
	std::vector<std::vector<int>> board;
	std::vector<int> histogram;

	zadanie34(int N, int dimension, int obstacle);

public:
	void OnUserUpdate();

	void TwoDimension();

	void OneDimension();

};

