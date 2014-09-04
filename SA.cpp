#include "SA.h"
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
SA::SA()
{
	/*currentTemp = 500;
	coolingRate = 0.96;
	minTemp = 30;*/
}


SA::~SA()
{
}

void SA::init(int & _maxTemp, double & cool, int & _minTemp, int & _iter, int & _iterDiv)
{
	maxTemp = _maxTemp;
	coolingRate = cool;
	minTemp = _minTemp;
	iter = _iter;
	iterDiv = _iterDiv;
}

void SA::run(VNS & vns)
{
	currentTemp = maxTemp;
	vector<int> oldRoute,bestRoute = vector<int>(vns.sol.route);
	double oldCost,bestCost = vns.sol.cost;
	double cost;
	double delta;
	double prob, r;
	int i, j, k;
	vns.kVND = vns.kVNS;
	while (currentTemp > minTemp)
	{
		for (int it = 0; it < iterDiv/currentTemp + iter; it++)
		{
			vns.sol.reoptimizeDataStructures();

			switch (vns.kVNS)
			{
			case 0: cost = vns.swapAdjacentShake1(i);
				break;
			case 1: cost = vns.swapTwoShake1(i, j);
				break;
			case 2: cost = vns.removeInsertShake1(i, j);
				break;
			case 3: cost = vns.twoOptShake1(i, j);
				break;
			case 4: cost = vns.orOptShake1(i, j, k);
				break;
			}

			delta = cost - oldCost;
			if (delta<0 || (delta > 0 && (vns.randReal() < exp(-delta / currentTemp))))
			{
				/*r = vns.randReal();
				prob = exp(-delta / currentTemp);
				if (r < prob)
				{

				}*/
				switch (vns.kVNS)
				{
				case 0: vns.sol.swapAdjacent(i); vns.sol.cost = cost;
					break;
				case 1: vns.sol.swapTwo(i, j); vns.sol.cost = cost;
					break;
				case 2: vns.sol.removeInsert(i, j); vns.sol.cost = cost;
					break;
				case 3: vns.sol.twoOpt(i, j); vns.sol.cost = cost;
					break;
				case 4: vns.sol.orOpt(i, j, k); vns.sol.cost = cost;
					break;
				}
				if (vns.sol.cost < bestCost)
				{
					bestCost = vns.sol.cost;
					bestRoute = vector<int>(vns.sol.route);
				}
			}
		}

		currentTemp *=coolingRate;
	}

	//vns.sol.route.clear();
	vns.sol.route = vector<int>(bestRoute);
	vns.sol.cost = bestCost;
}
