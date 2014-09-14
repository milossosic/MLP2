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
	VNS(Instance & inst, default_random_engine & gen, uniform_int_distribution<int> & dist, uniform_real_distribution<double> & distReal, bool withoutLast);
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
	void generalVNS(bool firstImprovement);
	void reducedVNS(bool randConst, bool firstImprovement);
	void basicVNS(bool firstImprovement);
	void run(bool randConst, bool rvnd, bool firstImprovement);

	void shake(bool randShakeNeighborhood);
	void VND(bool firstImprovement);
	void RVND(bool firstImprovement);

	void neighborhoodSearch(bool firstImprovement);
	
	void swapTwoNeighborhoodSearch(bool fix, bool firstImprovement);
	void swapAdjacentNeighborhoodSearch(bool fix, bool firstImprovement);
	void removeInsertNeighborhoodSearch(bool fix, bool firstImprovement);
	void twoOptNeighborhoodSearch(bool fix, bool firstImprovement);
	void orOptNeighborhoodSearch(bool fix, bool firstImprovement);

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

