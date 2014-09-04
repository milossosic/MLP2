#include "VNS.h"
#include <iostream>
#include "Algorithms.h"
#include "SA.h"
VNS::VNS()
{
	MAXIter = 20;
	kMax = 5;
	std::uniform_int_distribution<int> d1(0, 12312);
	distribution = d1;
}

VNS::VNS(Instance & inst, default_random_engine & gen, uniform_int_distribution<int> & dist, uniform_real_distribution<double> & distReal)
{
	generator = gen;
	distribution = dist;
	distributionReal = distReal;
	MAXIter = 20;
	kMax = 5;
	//kMax = 3;
	sol = *(new Solution(inst,gen,dist));
}

VNS::~VNS()
{
}

VNS::VNS(Solution & s)
{
	MAXIter = 20;
	kMax = 5;
	sol = s;
	std::uniform_int_distribution<int> d1(0, 12312);
	distribution = d1;
}

int VNS::rand(int p, int d)
{
	return distribution(generator) % (d - p) + p;
}
double VNS::randReal()
{
	return distributionReal(generator);
}



void VNS::swapTwoNeighborhoodSearch(bool fix, bool bestImprovement)
{
	double bestCost = sol.cost, x;
	int iBest = -1, jBest;
	bool found = false;
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 1; i++)
		{
			for (int j = i + 1; j < sol.route.size(); j++)
			{
				if (i == j)
					continue;
				if ((x = sol.costSwapTwo(i, j)) < bestCost)
				{
					bestCost = x;
					iBest = i;
					jBest = j;
					if (bestImprovement)
					{
						found = true;
						break;
					}
				}
			}
			if (found)
				break;
		}
	}
	else
	{
		int i = rand(1, sol.route.size());
		for (int j = 1; j < sol.route.size(); j++)
		{
			if (i == j)
				continue;
			if ((x = sol.costSwapTwo(i, j)) < bestCost)
			{
				bestCost = x;
				iBest = i;
				jBest = j;
				if (bestImprovement)
				{
					found = true;
					break;
				}
			}
		}
	}
	if (iBest != -1)
	{
		sol.cost = bestCost;
		sol.swapTwo(iBest,jBest);
	}
}
void VNS::swapAdjacentNeighborhoodSearch(bool fix, bool bestImprovement)
{
	double bestCost = sol.cost, x;
	int iBest=-1;
	bool found = false;
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 1; i++)
		{
			if ((x = sol.costSwapAdjacent(i)) < bestCost)
			{
				bestCost = x;
				iBest = i;
				if (bestImprovement)
				{
					found = true;
					break;
				}
			}
		}
	}
	else
	{
		int i = rand(1, sol.route.size() - 1);
		if ((x = sol.costSwapAdjacent(i)) < bestCost)
		{
			bestCost = x;
			iBest = i;
		}
		

	}
	if (iBest != -1)
	{
		sol.cost = bestCost;
		sol.swapAdjacent(iBest);
	}
}
void VNS::removeInsertNeighborhoodSearch(bool fix, bool bestImprovement)
{
	double bestCost = sol.cost, x;
	int iBest=-1, jBest;
	bool found = false;
	if (!fix)
	{
		for (int i = 1; i < sol.route.size(); i++)
		{
			for (int j = 1; j < sol.route.size(); j++)
			{
				if (i == j)
					continue;
				if ((x = sol.costRemoveInsert(i, j)) < bestCost)
				{
					bestCost = x;
					iBest = i;
					jBest = j;
					if (bestImprovement)
					{
						found = true;
						break;
					}
				}
			}
			if (found)
				break;
		}
	}
	else
	{
		int i = rand(1, sol.route.size());
		for (int j = 1; j < sol.route.size(); j++)
		{
			if (i == j)
				continue;
			if ((x = sol.costRemoveInsert(i, j)) < bestCost)
			{
				bestCost = x;
				iBest = i;
				jBest = j;
				if (bestImprovement)
				{
					found = true;
					break;
				}
			}
		}
	}
	
	if (iBest != -1)
	{
		sol.cost = bestCost;
		sol.removeInsert(iBest, jBest);
	}
}
void VNS::twoOptNeighborhoodSearch(bool fix, bool bestImprovement)
{
	double bestCost = sol.cost, x;
	int iBest=-1, jBest;
	bool found = false;
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 2; i++)
		{
			for (int j = i + 2; j < sol.route.size(); j++)
			{
				if ((x = sol.costTwoOpt(i,j))< bestCost)
				{
					bestCost = x;
					iBest = i;
					jBest = j;
					if (bestImprovement)
					{
						found = true;
						break;
					}
				}
			}
			if (found)
				break;
		}
	}
	else
	{
		int i = rand(1, sol.route.size() - 2);
		for (int j = i + 2; j < sol.route.size(); j++)
		{
			if ((x = sol.costTwoOpt(i, j))< bestCost)
			{
				bestCost = x;
				iBest = i;
				jBest = j;
				if (bestImprovement)
				{
					found = true;
					break;
				}
			}
		}
	}

	if (iBest != -1)
	{
		sol.cost = bestCost;
		sol.twoOpt(iBest, jBest);
	}
}
void VNS::orOptNeighborhoodSearch(bool fix, bool bestImprovement)
{
	double bestCost = sol.cost, x;
	int iBest = -1, jBest, kBest;
	bool found = false;
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 5; i++)
		{
			for (int j = i + 2; j < sol.route.size() - 3; j++)
			{
				for (int k = j + 2; k < sol.route.size() - 1; k++)
				{
					if ((x = sol.costOrOpt(i, j, k)) < bestCost)
					{
						bestCost = x;
						iBest = i;
						jBest = j;
						kBest = k;
						if (bestImprovement)
						{
							found = true;
							break;
						}
					}

				}
				if (found)
					break;
			}
			if (found)
				break;
		}
	}
	else
	{
		int i = rand(1, sol.route.size() - 5);
		for (int j = i + 2; j < sol.route.size() - 3; j++)
		{
			for (int k = j + 2; k < sol.route.size() - 1; k++)
			{
				if ((x = sol.costOrOpt(i, j, k)) < bestCost)
				{
					bestCost = x;
					iBest = i;
					jBest = j;
					kBest = k;
					if (bestImprovement)
					{
						found = true;
						break;
					}
				}
			}
			if (found)
				break;
		}
	}
	if (iBest != -1)
	{
		sol.cost = bestCost;
		sol.orOpt(iBest, jBest, kBest);
	}
}

void VNS::swapTwoShake()
{
	int i = rand(1, sol.route.size());
	int j;
	while (i == (j = rand(1, sol.route.size())));

	sol.cost = sol.costSwapTwo(i, j);
	sol.swapTwo(i, j);
}
void VNS::swapAdjacentShake()
{
	int i = rand(1, sol.route.size() - 1);
	sol.cost = sol.costSwapAdjacent(i);
	sol.swapAdjacent(i);
}
void VNS::removeInsertShake()
{
	int i = rand(1, sol.route.size());
	int j;
	while (i == (j = rand(1, sol.route.size())));
	sol.cost = sol.costRemoveInsert(i, j);
	sol.removeInsert(i, j);
}
void VNS::twoOptShake()
{
	int i = rand(1, sol.route.size() - 2);
	int j;
	j = rand(i + 2, sol.route.size());
	sol.cost = sol.costTwoOpt(i, j);
	sol.twoOpt(i, j);
}
void VNS::orOptShake()
{
	int i = rand(1, sol.route.size() - 5);
	int j = rand(i + 2, sol.route.size() - 3);
	int k = rand(j + 2, sol.route.size() - 1);
	sol.cost = sol.costOrOpt(i, j, k);
	sol.orOpt(i, j, k);
}

int VNS::swapTwoShake1(int &i, int &j)
{
	i = rand(1, sol.route.size());
	while (i == (j = rand(1, sol.route.size())));

	return sol.costSwapTwo(i, j);
}
int VNS::swapAdjacentShake1(int &i)
{
	i = rand(1, sol.route.size() - 1);
	return sol.costSwapAdjacent(i);
}
int VNS::removeInsertShake1(int &i, int &j)
{
	i = rand(1, sol.route.size());
	while (i == (j = rand(1, sol.route.size())));
	return sol.costRemoveInsert(i, j);
}
int VNS::twoOptShake1(int &i, int &j)
{
	i = rand(1, sol.route.size() - 2);
	j = rand(i + 2, sol.route.size());
	return sol.costTwoOpt(i, j);
}
int VNS::orOptShake1(int &i, int &j, int &k)
{
	i = rand(1, sol.route.size() - 5);
	j = rand(i + 2, sol.route.size() - 3);
	k = rand(j + 2, sol.route.size() - 1);
	return sol.costOrOpt(i, j, k);
}

void VNS::doubleBridgeMove()
{

	int i, j, k;
	int q = sol.inst.dimension / 4;
	i = q/2 + rand(1, q);
	j = i + 1 + rand(0, q);
	k = j + 1 + rand(0, q);

	sol.doubleBridge(i,j,k);
}
void VNS::neighborhoodSearch(bool bestImprovement)
{
	bool fix = false;
	switch (kVND)
	{
	case 0: swapAdjacentNeighborhoodSearch(fix, bestImprovement);
		break;
	case 1: swapTwoNeighborhoodSearch(fix, bestImprovement);
		break;
	case 2: removeInsertNeighborhoodSearch(fix, bestImprovement);
		break;
	case 3: twoOptNeighborhoodSearch(fix, bestImprovement);
		break;
	case 4: orOptNeighborhoodSearch(fix, bestImprovement);
		break;
	}
}

void VNS::shake(bool randShakeNeighborhood)
{
	bool fix;
	switch (randShakeNeighborhood ? rand(0, 5) : kVNS)
	{
	case 0: swapAdjacentShake();
		break;
	case 1: swapTwoShake();
		break;
	case 2: removeInsertShake();
		break;
	case 3: twoOptShake();
		break;
	case 4: orOptShake();
		break;
	}
}

void VNS::VND(bool bestImprovement)
{
	double oldCost, bestCost;
	oldCost = bestCost = sol.cost;
	vector<int> bestRoute, oldRoute;
	bestRoute = oldRoute = vector<int>(sol.route);

	kVND = 0;
	while (kVND < kMax)
	{
		sol.reoptimizeDataStructures();
		neighborhoodSearch(bestImprovement);
		if (sol.cost < bestCost)
		{
			kVND = 0;
			bestCost = sol.cost;
			bestRoute = vector<int>(sol.route);
		}
		else
		{
			kVND++;
			sol.cost = bestCost;
			sol.route = vector<int>(bestRoute);
		}

	}

	if (bestCost < sol.cost)
	{
		sol.cost = bestCost;
		sol.route = vector<int>(bestRoute);
	}
}
/*
 * random neighborhood
*/
void VNS::RVND(bool bestImprovement)
{
	double oldCost, bestCost;
	oldCost = bestCost = sol.cost;
	vector<int> bestRoute, oldRoute;
	bestRoute = oldRoute = vector<int>(sol.route);

	vector<int> neighborhoods;
	for (int i = 0; i < kMax; i++)
	{
		neighborhoods.clear();
		neighborhoods.push_back(i);
	}
	int x;

	
	while (neighborhoods.size())
	{
		kVND = rand(0, neighborhoods.size());
		 
		sol.reoptimizeDataStructures();
		neighborhoodSearch(bestImprovement);
		if (sol.cost < bestCost)
		{
			neighborhoods.clear();
			for (int i = 0; i < kMax; i++)
			{

				neighborhoods.push_back(i);
			}

			bestCost = sol.cost;
			bestRoute = vector<int>(sol.route);
		}
		else
		{
			for (int i = x; i < neighborhoods.size() - 1; i++)
			{
				neighborhoods[x] = neighborhoods[x + 1];

			}
			neighborhoods.pop_back();

			sol.cost = bestCost;
			sol.route = vector<int>(bestRoute);
		}

	}

	if (bestCost < sol.cost)
	{
		sol.cost = bestCost;
		sol.route = vector<int>(bestRoute);
	}
}
void VNS::run(bool randConst, bool rvnd, bool bestImprovement)
{
	int iter = 0;
	double oldCost, bestCost, globalBestCost;
	vector<int> oldRoute,bestRoute,globalBestRoute;
	int alpha;
	if(!randConst)
		sol.greedyConstruct();
	else
	{
		alpha = sol.inst.dimension / 5;
		sol.greedyRandomConstruct(alpha);
	}
	
	globalBestCost = sol.cost;
	globalBestRoute = vector<int>(sol.route);

	bool randShake = true;
	bool randomVND = false;
	while (iter++ < MAXIter)
	{
		kVNS = 0;
		while (kVNS < kMax)
		{
			sol.reoptimizeDataStructures();
			oldRoute = vector<int>(sol.route);
			oldCost = sol.cost;
			//shake
			
			
			for (int i = 0; i < 6; i++)
			{
				shake(randShake);
				randShake = !randShake;
				sol.reoptimizeDataStructures();
			}
			//doubleBridgeMove();

			//vnd/rvnd
			if (rvnd)
			{
				RVND(bestImprovement);
			}
			else
			{
				VND(bestImprovement);
			}
			
			//decision
			if (sol.cost < oldCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
  				kVNS = 0;
			}
			else
			{
				kVNS++;
				sol.route = oldRoute;
				sol.cost = oldCost;	
			}
		}
		if (bestCost < globalBestCost)
		{
			globalBestCost = bestCost;
			globalBestRoute = vector<int>(bestRoute);
		}
		if (randConst)
			sol.greedyRandomConstruct(alpha);
	}
	sol.cost = globalBestCost;
	sol.route = vector<int>(globalBestRoute);

}
void VNS::generalVNS(bool bestImprovement)
{
	int iter = 0;
	double oldCost, bestCost, globalBestCost;
	vector<int> oldRoute, bestRoute, globalBestRoute;
	
	sol.greedyConstruct();

	globalBestCost = sol.cost;
	globalBestRoute = vector<int>(sol.route);

	
	while (iter++ < MAXIter)
	{
		kVNS = 0;
		while (kVNS < kMax)
		{
			sol.reoptimizeDataStructures();
			oldRoute = vector<int>(sol.route);
			oldCost = sol.cost;

			//shake
			shake(false);
				
			//vnd
			VND(bestImprovement);
			

			//decision
			if (sol.cost < oldCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
				kVNS = 0;
			}
			else
			{
				kVNS++;
				sol.route = oldRoute;
				sol.cost = oldCost;
			}
		}
		if (bestCost < globalBestCost)
		{
			globalBestCost = bestCost;
			globalBestRoute = vector<int>(bestRoute);
		}
	}
	sol.cost = globalBestCost;
	sol.route = globalBestRoute;

}
void VNS::reducedVNS(bool randConst, bool bestImprovement)
{
	int iter = 0;
	double oldCost, bestCost, globalBestCost;
	vector<int> oldRoute, bestRoute, globalBestRoute;
	int alpha;
	if (!randConst)
		sol.greedyConstruct();
	else
	{
		alpha = sol.inst.dimension / 5;
		sol.greedyRandomConstruct(alpha);
	}

	globalBestCost = sol.cost;
	globalBestRoute = vector<int>(sol.route);

	bool randShake;
	while (iter++ < MAXIter)
	{
		kVNS = 0;
		while (kVNS < kMax)
		{
			sol.reoptimizeDataStructures();
			oldRoute = vector<int>(sol.route);
			oldCost = sol.cost;
			//shake
			shake(randShake);
			//decision
			if (sol.cost < oldCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
				kVNS = 0;
			}
			else
			{
				kVNS++;
				sol.route = oldRoute;
				sol.cost = oldCost;
			}
		}
		if (bestCost < globalBestCost)
		{
			globalBestCost = bestCost;
			globalBestRoute = vector<int>(bestRoute);
		}
		if (randConst)
			sol.greedyRandomConstruct(alpha);
	}
	sol.cost = globalBestCost;
	sol.route = vector<int>(globalBestRoute);

}
void VNS::VNS_SA()
{
	int iter = 0;
	double oldCost, bestCost, globalBestCost;
	vector<int> oldRoute, bestRoute, globalBestRoute;

	sol.greedyConstruct();

	globalBestCost = sol.cost;
	globalBestRoute = vector<int>(sol.route);


	while (iter++ < MAXIter)
	{
		kVNS = 0;
		while (kVNS < kMax)
		{
			sol.reoptimizeDataStructures();
			oldRoute = vector<int>(sol.route);
			oldCost = sol.cost;

			//shake
			shake(false);

			//vnd
			SA sa;
			sa.run(*this);

			//decision
			if (sol.cost < oldCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
				kVNS = 0;
			}
			else
			{
				kVNS++;
				sol.route = oldRoute;
				sol.cost = oldCost;
			}
		}
		if (bestCost < globalBestCost)
		{
			globalBestCost = bestCost;
			globalBestRoute = vector<int>(bestRoute);
		}
	}
	sol.cost = globalBestCost;
	sol.route = globalBestRoute;
}