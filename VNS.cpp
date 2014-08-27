#include "VNS.h"
#include <iostream>

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
	switch (kVNS)
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
	int bestCost = sol.cost;
	vector<int> bestRoute = vector<int>(sol.route);

	kVND = 0;
	while (kVND < kMax)
	{
		//cout << ".";
		neighborhoodSearch();
		if (sol.cost < bestCost)
		{
			kVND = 0;
			bestCost = sol.cost;
			bestRoute = vector<int>(sol.route);
			
			//std::cout << sol.cost;
		}
		else
		{
			kVND++;
			sol.cost = bestCost;
			sol.route = vector<int>(bestRoute);
		}
		sol.reoptimizeDataStructures();
	}
	sol.cost = bestCost;
	sol.route = vector<int>(bestRoute);
}

void VNS::swapTwoNeighborhoodSearch(bool fix)
{
	int oldCost = sol.cost;
	int bestCost = sol.cost;
	vector<int> bestRoute = vector<int>(sol.route);

	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 1; i++)
		{
			for (int j = i + 1; j < sol.route.size(); j++)
			{
				if (i == j)
					continue;
				sol.swapTwo(i, j);
				sol.totalCost();
				if (sol.cost < bestCost)
				{
					bestCost = sol.cost;
					bestRoute = vector<int>(sol.route);
				}
				sol.cost = oldCost;
				sol.swapTwo(i, j);
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
			oldCost = sol.cost;
			sol.swapTwo(i, j);
			sol.totalCost();
			if (sol.cost < bestCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
			}
			sol.cost = oldCost;
			sol.swapTwo(i, j);
		}
	}
	sol.cost = bestCost;
	sol.route = vector<int>(bestRoute);
}
void VNS::swapAdjacentNeighborhoodSearch(bool fix)
{
	int oldCost = sol.cost;
	int bestCost = sol.cost;
	vector<int> bestRoute = vector<int>(sol.route);
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 1; i++)
		{
			oldCost = sol.cost;
			sol.swapAdjacent(i);
			sol.totalCost();
			if (sol.cost < bestCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
			}
			sol.cost = oldCost;
			sol.swapAdjacent(i);
		}
	}
	else
	{
		int i = rand(1, sol.route.size() - 1);
		oldCost = sol.cost;
		sol.swapAdjacent(i);
		sol.totalCost();
		if (sol.cost < bestCost)
		{
			bestCost = sol.cost;
			bestRoute = vector<int>(sol.route);
		}
		sol.cost = oldCost;
		sol.swapAdjacent(i);

	}
	sol.cost = bestCost;
	sol.route = vector<int>(bestRoute);
}
void VNS::removeInsertNeighborhoodSearch(bool fix)
{
	int oldCost = sol.cost;
	int bestCost = sol.cost;
	int iBest=-1, jBest;
	int x;
	vector<int> bestRoute = vector<int>(sol.route);
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
				/*oldCost = sol.cost;
				
				x = sol.costRemoveInsert(i, j);
				sol.removeInsert(i, j);
				sol.totalCost();
				if (x != sol.cost)
				{
					cout << "asdad";
				}
				if (sol.cost < bestCost)
				{
					bestCost = sol.cost;
					bestRoute = vector<int>(sol.route);
				}
				sol.cost = oldCost;
				sol.removeInsert(j, i);*/

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
			/*oldCost = sol.cost;
			sol.removeInsert(i, j);
			sol.totalCost();
			if (sol.cost < bestCost)
			{
				bestCost = sol.cost;
				bestRoute = vector<int>(sol.route);
			}
			sol.cost = oldCost;
			sol.removeInsert(j, i);*/
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
	int oldCost = sol.cost;
	int bestCost = sol.cost;
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
	int oldCost = sol.cost;
	int bestCost = sol.cost;
	vector<int> bestRoute = vector<int>(sol.route);
	if (!fix)
	{
		for (int i = 1; i < sol.route.size() - 5; i++)
		{
			for (int j = i + 2; j < sol.route.size() - 3; j++)
			{
				for (int k = j + 2; k < sol.route.size() - 1; k++)
				{
					//cout << "-" << i << "," << j << "," << k << "-";
					oldCost = sol.cost;
					sol.orOpt(i, j, k);
					sol.totalCost();
					if (sol.cost < bestCost)
					{
						bestCost = sol.cost;
						bestRoute = vector<int>(sol.route);
					}
					sol.cost = oldCost;
					sol.orOpt(i, i + k - j, k);

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

				oldCost = sol.cost;
				sol.orOpt(i, j, k);
				sol.totalCost();
				if (sol.cost < bestCost)
				{
					bestCost = sol.cost;
					bestRoute = vector<int>(sol.route);
				}
				sol.cost = oldCost;
				sol.orOpt(i, i + k - j, k);

			}
		}
	}
	sol.cost = bestCost;
	sol.route = vector<int>(bestRoute);
}

void VNS::swapTwoShake()
{
	int i = rand(1, sol.route.size());
	int j;
	while (i == (j = rand(1, sol.route.size())));
	sol.swapTwo(i, j);
	sol.totalCost();
}
void VNS::swapAdjacentShake()
{
	int i = rand(1, sol.route.size() - 1);
	sol.swapAdjacent(i);
	sol.totalCost();
}
void VNS::removeInsertShake()
{
	int i = rand(1, sol.route.size());
	int j;
	while (i == (j = rand(1, sol.route.size())));
	sol.removeInsert(i, j);
	sol.totalCost();
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
	int k = rand(j + 2, sol.route.size());
	sol.orOpt(i, j, k);
}

void VNS::run()
{
	int iter = 0;
	int oldCost;
	vector<int> oldRoute;

	while (iter++ < MAXIter)
	{
		std::cout << "iter: " << iter << endl;
		kVNS = 0;
		while (kVNS < kMax)
		{
			oldRoute = vector<int>(sol.route);
			oldCost = sol.cost;

			//shake
			shake();

			//vnd
			VND();

			//decision
			if (sol.cost < oldCost)
			{
				kVNS = 0;
				//std::cout << "cost: " << sol.cost << endl;
			}
			else
			{
				kVNS++;
				sol.route = oldRoute;
				sol.cost = oldCost;
			}
		}
	}

}