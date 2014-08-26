#pragma once
#include <random>
#include "Solution.h"
#include "Instance.h"
class VNS
{
public:
	VNS();
	VNS(Instance & inst);
	VNS(Solution & s);
	~VNS();

	int kVND, kVNS, kMax;
	int MAXIter;
	Solution sol;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

	int rand(int p, int d);

	void run();

	void shake();
	void VND();

	void neighborhoodSearch();
	
	void swapTwoNeighborhoodSearch(bool fix);
	void swapAdjacentNeighborhoodSearch(bool fix);
	void removeInsertNeighborhoodSearch(bool fix);
	void twoOptNeighborhoodSearch(bool fix);
	void orOptNeighborhoodSearch(bool fix);

	void swapTwoShake();
	void swapAdjacentShake();
	void removeInsertShake();
	void twoOptShake();
	void orOptShake();
};

