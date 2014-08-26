#include "Solution.h"
#include "Algorithms.h"
#include <algorithm>

Solution::Solution()
{
}

Solution::Solution(Instance & inst1)
{
	inst = inst1;
	int dim = inst.dimension;
	nodesVisited.resize(dim);
	nodesVisited[0] = true;
	//route.resize(dim);
	for (int i = 0; i < dim; i++)
	{
		vector<pair<int, double>> temp;
		for (int j = 0; j < dim; j++)
		{
			temp.push_back(make_pair(j, inst.cost[i][j]));
		}
		sort(temp.begin(), temp.end(), Algorithms::comparePairBySecond);
		inst.minCost.push_back(temp);
	}
}

Solution::~Solution()
{
}

void Solution::setRouteNode(int i, int j)
{
	route.push_back(j);
	//route[i] = j;
	nodesVisited[j] = true;
}

bool Solution::nodeFree(int j)
{
	return !nodesVisited[j];
}

double Solution::totalCost()
{
	double totalCost = 0;
	int dim = route.size()+1;
	totalCost = dim-- * inst.cost[0][route.front()];
	
	for (auto itPrev = route.begin(), itNext = itPrev; ++itNext!=route.end();)
	{
		//itNext++;
		///offset += inst.cost[*itPrev][*(itNext)];
		totalCost += (dim--)  * inst.cost[*itPrev][*(itNext)];
		itPrev++;
	}
	cost = totalCost+inst.cost[route.back()][0];
	return cost;
}


void Solution::removeInsert(int i, int j)
{
	int temp = route[i];
	if (i < j)
	{
		for (int t = i; t < j; t++)
			route[t] = route[t + 1];
	}
	else
	{
		for (int t = i; t > j; t--)
			route[t] = route[t - 1];
	}
	route[j] = temp;
}
void Solution::swapTwo(int i, int j)
{
	int dim = route.size();
	int temp, t1, t2;
	/*if (i == 0)
	{
		t1 = (dim - i)*(inst.cost[0][route[i]]);
	}
	else
	{
		t1 = (dim - i)*(inst.cost[route[i - 1]][route[i]]);
	}
	t2 = (dim - i - 1)*(inst.cost[route[i]][route[i + 1]]);
	cost -= t1 + t2;
	if (i + 1 != j)
	{
		t1 = (dim - j)*(inst.cost[route[j - 1]][route[j]]);
		cost -= t1;
	}
	if (j < dim - 1)
	{
		t1 = (dim - j - 1)*(inst.cost[route[j]][route[j + 1]]);
		cost -= t1;
	}*/
	temp = route[i];
	route[i] = route[j];
	route[j] = temp;
	/*if (i == 0)
	{
		t1 = (dim - i)*(inst.cost[0][route[i]]);
	}
	else
	{
		t1 = (dim - i)*(inst.cost[route[i - 1]][route[i]]);
	}
	t2 = (dim - i - 1)*(inst.cost[route[i]][route[i + 1]]);
	cost += t1 + t2;
	if (i + 1 != j)
	{
		t1 = (dim - j)*(inst.cost[route[j - 1]][route[j]]);
		cost += t1;
	}
	if (j < dim - 1)
	{
		t1 = (dim - j - 1)*(inst.cost[route[j]][route[j + 1]]);
		cost += t1;
	}*/
}
void Solution::swapAdjacent(int i)
{
	int temp;	
	temp = route[i];
	route[i] = route[i + 1];
	route[i + 1] = temp;
}
void Solution::twoOpt(int a, int b)
{
	if (a == b || a + 1 == b || a == b + 1 || a + 1 == b + 1)
		return;
	Algorithms::reverseSegment(route, a + 1, b);
}
void Solution::orOpt(int i, int j, int k)
{
	vector<int> temp;
	for (int t = i + 1; t < j + 1; t++)
	{
		temp.push_back(route[t]);
	}
	for (int t = j + 1, s = 0; t < k + 1; t++, s++)
	{
		route[i + 1 + s] = route[t];
	}
	for (int t = i + 1 + k - j, s = 0; s < temp.size(); t++, s++)
	{
		route[t] = temp[s];
	}
	temp.clear();
}