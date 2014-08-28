#include "VNS.h"
#include <iostream>
#include "Algorithms.h"

VNS::VNS()
{
	MAXIter = 20;
	kMax = 5;
	std::uniform_int_distribution<int> d1(0, 12312);
	distribution = d1;
}

VNS::VNS(Instance & inst)
{
	MAXIter = 20;
	kMax = 5;
	//kMax = 3;
	std::uniform_int_distribution<int> d1(0, 12312);
	distribution = d1;
	sol = *(new Solution(inst));
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

void VNS::neighborhoodSearch()
{
	bool fix = false;
	switch (kVND)
	{
	case 0: swapAdjacentNeighborhoodSearch(fix);
		break;
	case 1: swapTwoNeighborhoodSearch(fix);
		break;
	case 2: removeInsertNeighborhoodSearch(fix);
		break;
	case 3: twoOptNeighborhoodSearch(fix);
		break;
	case 4: orOptNeighborhoodSearch(true);
		break;
	}
}

void VNS::shake()
{
	bool fix;
	switch (kVNS/*rand(0,5)*/)
	//switch (rand(0,5))
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

void VNS::VND()
{
	double bestCost = sol.cost;
	vector<int> bestRoute = vector<int>(sol.route);

	kVND = 0;
	while (kVND < kMax)
	{
		sol.reoptimizeDataStructures();
		neighborhoodSearch();
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
	/*int x = sol.cost;
	cout << "cost       :" << x << "total cost: " << sol.totalCost() << endl;
	sol.cost = x;*/
}

void VNS::swapTwoNeighborhoodSearch(bool fix)
{
	double bestCost = sol.cost;
	int iBest = -1, jBest, x;
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
				}
			}
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
			}
		}
	}
	if (iBest != -1)
	{
		sol.cost = bestCost;
		sol.swapTwo(iBest,jBest);
	}
}
void VNS::swapAdjacentNeighborhoodSearch(bool fix)
{
	double bestCost = sol.cost;
	int iBest=-1;
	int x;
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 1; i++)
		{
			if ((x = sol.costSwapAdjacent(i)) < bestCost)
			{
				bestCost = x;
				iBest = i;
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
void VNS::removeInsertNeighborhoodSearch(bool fix)
{
	double bestCost = sol.cost;
	int iBest=-1, jBest;
	int x;
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
				}
			}
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
			}
		}
	}
	
	if (iBest != -1)
	{
		sol.cost = bestCost;
		sol.removeInsert(iBest, jBest);
	}
}
void VNS::twoOptNeighborhoodSearch(bool fix)
{
	double oldCost = sol.cost;
	double bestCost = sol.cost;
	vector<int> bestRoute = vector<int>(sol.route);
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 2; i++)
		{
			for (int j = i + 2; j < sol.route.size(); j++)
			{
				oldCost = sol.cost;
				sol.twoOpt(i, j);
				sol.totalCost();
				if (sol.cost < bestCost)
				{
					bestCost = sol.cost;
					bestRoute = vector<int>(sol.route);
				}
				sol.cost = oldCost;
				sol.twoOpt(i, j);

			}
		}
	}
	else
	{
		int i = rand(1, sol.route.size() - 2);
		for (int j = i + 2; j < sol.route.size(); j++)
		{
			oldCost = sol.cost;
			sol.twoOpt(i, j);
			sol.totalCost();
			if (sol.cost < bestCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
			}
			sol.cost = oldCost;
			sol.twoOpt(i, j);

		}
	}
	sol.cost = bestCost;
	sol.route = vector<int>(bestRoute);
}
void VNS::orOptNeighborhoodSearch(bool fix)
{
	double bestCost = sol.cost;
	int iBest = -1, jBest, kBest, x;
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
					}

				}
			}
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
				}
			}
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
	sol.twoOpt(i, j);
	sol.totalCost();
}
void VNS::orOptShake()
{
	int i = rand(1, sol.route.size() - 5);
	int j = rand(i + 2, sol.route.size() - 3);
	int k = rand(j + 2, sol.route.size() - 1);
	sol.cost = sol.costOrOpt(i, j, k);
	sol.orOpt(i, j, k);
}

void VNS::run()
{
	int iter = 0;
	double oldCost, bestCost;
	vector<int> oldRoute,bestRoute;

	Algorithms::greedySolution(sol);

	while (iter++ < MAXIter)
	{
		//std::cout << "iter: " << iter << endl;
		kVNS = 0;
		while (kVNS < kMax)
		{
			sol.reoptimizeDataStructures();
			oldRoute = vector<int>(sol.route);
			oldCost = sol.cost;

			//shake
			shake();

			//vnd
			VND();

			//decision
			if (sol.cost < oldCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
				kVNS = 0;
				/*int x = sol.cost;
				cout << "smartCost:   " << sol.cost << " realCost:    " << sol.totalCost() << endl;
				sol.cost = x;*/
			}
			else
			{
				kVNS++;
				sol.route = oldRoute;
				sol.cost = oldCost;
				
			}
			
		}
	}
	sol.cost = bestCost;
	sol.route = bestRoute;

}