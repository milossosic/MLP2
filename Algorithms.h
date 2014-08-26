#pragma once
#include <vector>
#include "Instance.h"
#include "Solution.h"
using namespace std;

class Algorithms
{
public:
	Algorithms();
	~Algorithms();

	static void reverseSegment(vector<int> & route, int start, int end);
	static void twoOpt(vector<int> & route, int a, int b);
	static void swapTwo(vector<int> & route, int a, int b);
	static bool comparePairBySecond(pair<int, double> & a, pair<int, double> & b);

	static void greedySolution(Solution & s);
};

