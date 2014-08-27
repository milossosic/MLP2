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

void Solution::reoptimizeDataStructures()
{
	for (int i = 0; i < route.size(); i++)
	{
		for (int j = 0; j < route.size(); j++)
		{
			if (i == j)
			{
				T[i][j] = 0;
				C[i][j] = 0;
				if (i == 0) W[0][0] = 0;
				else W[i][j] = 1;
			}
			if (i < j)
			{
				T[i][j] = T[i][j - 1] + inst.cost[route[j-1]][route[j]];
				W[i][j] = W[i][j - 1] + 1;
				C[i][j] = C[i][j - 1] + T[i][j - 1] + inst.cost[route[j - 1]][route[j]];
			}
			else
			{
				T[i][j] = T[j][i];
				W[i][j] = W[j][i];
				C[i][j] = C[j][i];
			}
		}
	}
}
int Solution::mergeT(int l1, int r1, int l2, int r2)
{
	return T[route[l1]][route[r1]] + inst.cost[route[r1]][route[l2]] + T[route[l2]][route[r2]];
}
int Solution::mergeW(int l1, int r1, int l2, int r2)
{
	return W[route[l1]][route[r1]] + W[route[l2]][route[r2]];
}
int Solution::mergeC(int l1, int r1, int l2, int r2)
{
	return C[route[l1]][route[r1]] + W[route[l2]][route[r2]] * (T[route[l1]][route[r1]] + inst.cost[route[r1]][route[l2]]) + C[route[l2]][route[r2]];
}
int Solution::costRemoveInsert(int i, int j)
{
	int t1, t2, t3, t4;
	int w1, w2, w3, w4;
	int c1, c2, c3, c4;
	if (i < j)
	{
		if (i > 0)
		{
			if (j < route.size() - 1)
			{
				t1 = mergeT(0, i - 1, i + 1, j);
				t2 = mergeT(i, i, j + 1, route.size() - 1);
				w1 = mergeW(0, i - 1, i + 1, j);
				w2 = mergeW(i, i, j + 1, route.size() - 1);
				c1 = mergeC(0, i - 1, i + 1, j);
				c2 = mergeC(i, i, j + 1, route.size() - 1);
				return (c1 + c2 + w2*(t1 + inst.cost[route[j]][route[i]])) + t1 + t2 + inst.cost[route[j]][route[i]] + inst.cost[route[route.size() - 1]][0];
			}
			else
			{
				t1 = T[0][route[i - 1]] + inst.cost[route[i - 1]][route[i + 1]] + T[route[i + 1]][route[j]];
				t2 = T[route[i]][route[i]];
				w1 = W[0][route[i - 1]] + W[route[i + 1]][route[j]];
				w2 = W[route[i]][route[i]];
				c1 = C[0][route[i - 1]] + W[route[i + 1]][route[j]] * (T[0][route[i - 1]] + inst.cost[route[i - 1]][route[i + 1]]) + C[route[i + 1]][route[j]];
				c2 = C[route[i]][route[i]];
			}
		}
		else
		{
			if (j < route.size() - 1)
			{
				t1 = T[route[i + 1]][route[j]];
				t2 = T[route[i]][route[i]] + inst.cost[route[i]][route[j + 1]] + T[route[j + 1]][route[route.size() - 1]];
				w1 = W[route[i + 1]][route[j]];
				w2 = W[route[i]][route[i]] + W[route[j + 1]][route[route.size() - 1]];
				c1 = C[route[i + 1]][route[j]];
				c2 = C[route[i]][route[i]] + W[route[j + 1]][route[route.size() - 1]] * (T[route[i]][route[i]] + inst.cost[route[i]][route[j + 1]]) + C[route[j + 1]][route[route.size() - 1]];
			}
			else
			{
				t1 = T[route[i + 1]][route[j]];
				t2 = T[route[i]][route[i]];
				w1 = W[route[i + 1]][route[j]];
				w2 = W[route[i]][route[i]];
				c1 = C[route[i + 1]][route[j]];
				c2 = C[route[i]][route[i]];
			}
		}
	}
	return 0;
}
int Solution::costSwapTwo(int i, int j)
{

	return 0;
}
int Solution::costSwapAdjacent(int i)
{
	return 0;
}
int Solution::costTwoOpt(int i, int j)
{
	return 0;
}
int Solution::costOrOpt(int i, int j, int k)
{
	return 0;
}

void Solution::setRouteNode(int i, int j)
{
	route.push_back(j);
	nodesVisited[j] = true;
}

bool Solution::nodeFree(int j)
{
	return !nodesVisited[j];
}

double Solution::totalCost()
{
	double totalCost = 0;
	int dim = route.size();
	//totalCost = dim-- * inst.cost[0][route.front()];
	
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
	int dim = route.size()+1;
	if (i > j)
	{
		int temp = i;
		i = j;
		j = temp;
	}
	int temp, t1, t2;

	temp = route[i];
	route[i] = route[j];
	route[j] = temp;

	
	
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