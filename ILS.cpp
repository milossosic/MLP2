#include "ILS.h"
#include "Algorithms.h"
#include <iostream>
#include <random>
#include <cmath>
ILS::ILS()
{}

ILS::ILS(Solution & s)
{
	sol = s;
	std::uniform_int_distribution<int> d1(0,12312);
	distribution = d1;
}

ILS::~ILS()
{}

void ILS::initialSolution(Instance & inst)
{
	Algorithms::greedySolution(sol);
	sol.totalCost();
}

void ILS::localSearch(Instance & inst)
{
	for (int i = 0; i < inst.dimension - 2; i++)
	{
		for (int j = i + 1; j < inst.dimension-1; j++)
		{

		//int j = (distribution(generator) + i + 2) % inst.dimension;
			int cost = sol.cost;
			sol.twoOpt(i, j);
			//sol.swapTwo(inst, i, j);
			sol.totalCost();
			if (sol.cost >= cost)
			{
				sol.twoOpt(i, j);
				sol.cost = cost;
			}
			else
			{
				cout << sol.cost << "\t:";
				return;
			}
			
		}
	}
}

void ILS::run(Instance & inst)
{
	initialSolution(inst);
	int iter = 0;
	int prevCost;
	while (iter++ < 1500)
	{
		prevCost = sol.cost;
		localSearch(inst);
		if (sol.cost < prevCost)
			cout << iter << endl;
		if (sol.cost - floor(sol.cost) > 0)
		{
			cout << "";
		}
	}
}

void ILS::pertrurbation(Instance & inst)
{
	
}

void ILS::acceptCriterion(Instance & inst)
{
	
}