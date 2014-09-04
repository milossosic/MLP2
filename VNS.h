#pragma once
#include <random>
#include "Solution.h"
#include "Instance.h"
//#include "SA.h"
class SA;
class VNS
{
public:
	VNS();
	VNS(Instance & inst, default_random_engine & gen, uniform_int_distribution<int> & dist, uniform_real_distribution<double> & distReal);
	VNS(Solution & s);
	~VNS();

	int kVND, kVNS, kMax;
	int MAXIter;
	Solution sol;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	std::uniform_real_distribution<double> distributionReal;

	int rand(int p, int d);
	double randReal();

	void VNS_SA(SA & sa);
	void generalVNS(bool bestImprovement);
	void reducedVNS(bool randConst, bool bestImprovement);
	void basicVNS(bool bestImprovement);
	void run(bool randConst, bool rvnd, bool bestImprovement);

	void shake(bool randShakeNeighborhood);
	void VND(bool bestImprovement);
	void RVND(bool bestImprovement);

	void neighborhoodSearch(bool bestImprovement);
	
	void swapTwoNeighborhoodSearch(bool fix, bool bestImprovement);
	void swapAdjacentNeighborhoodSearch(bool fix, bool bestImprovement);
	void removeInsertNeighborhoodSearch(bool fix, bool bestImprovement);
	void twoOptNeighborhoodSearch(bool fix, bool bestImprovement);
	void orOptNeighborhoodSearch(bool fix, bool bestImprovement);

	void swapTwoShake();
	void swapAdjacentShake();
	void removeInsertShake();
	void twoOptShake();
	void orOptShake();

	int swapTwoShake1(int &i, int &j);
	int swapAdjacentShake1(int &i);
	int removeInsertShake1(int &i, int &j);
	int twoOptShake1(int &i, int &j);
	int orOptShake1(int &i, int &j, int &k);

	void doubleBridgeMove();
};

