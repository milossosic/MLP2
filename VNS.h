#pragma once
#include <random>
#include "Solution.h"
#include "Instance.h"
class VNS
{
public:
	VNS();
	VNS(Instance & inst, default_random_engine & gen, uniform_int_distribution<int> & dist);
	VNS(Solution & s);
	~VNS();

	int kVND, kVNS, kMax;
	int MAXIter;
	Solution sol;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

	int rand(int p, int d);

	void run(bool randConst, bool rvnd);

	void shake(bool randShakeNeighborhood);
	void VND();
	void RVND();

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

	void doubleBridgeMove();
};

