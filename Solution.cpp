#include "Solution.h"
#include "Algorithms.h"
#include <algorithm>
#include <iostream>
#include "Part.h"
Solution::Solution()
{
}

Solution::Solution(Instance & inst1, default_random_engine & gen, uniform_int_distribution<int> & dist, bool _withoutLast)
{
	withoutLast = _withoutLast;
	inst = Instance(inst1);
	int dim = inst.dimension;
	nodesVisited.resize(dim);
	nodesVisited[0] = true;
	for (int i = 0; i < dim; i++)
	{
		vector<pair<int, long>> temp;
		for (int j = 0; j < dim; j++)
		{
			temp.push_back(make_pair(j, inst.cost[i][j]));
		}
		sort(temp.begin(), temp.end(), Algorithms::comparePairBySecond);
		inst.minCost.push_back(temp);
	}
	
	generator = gen;
	distribution = dist;

	T = new long *[dim];
	W = new int *[dim];
	C = new long *[dim];
	for (int i = 0; i < dim; i++)
	{
		T[i] = new long[dim];
		W[i] = new int[dim];
		C[i] = new long[dim];
	}
}

Solution::~Solution()
{
}

int Solution::rand(int p, int d)
{
	return distribution(generator) % (d - p) + p;
}
void Solution::greedyConstruct()
{
	setRouteNode(0, 0);
	for (int i = 0; i < inst.dimension; i++)
	{
		for (int j = 0; j < inst.dimension; j++)
		{
			int t = inst.minCost[i][j].first;
			if (i == t)
				continue;
			if (nodeFree(t))
			{
				setRouteNode(i, t);
				break;
			}
		}
	}
	if (withoutLast)
	{
		totalCostWithoutLast();
	}
	else
	{
		totalCost();
	}
}
void Solution::greedyRandomConstruct(int alpha)
{
	
	vector<int> temp;
	int x,r;
	for (int i = 1; i < inst.dimension; i++)
	{
		nodesVisited[i] = false;
	}
	route.clear();
	setRouteNode(0, 0);
	for (int i = 1; i < inst.dimension; i++)
	{
		temp.clear();
		x = 0;
		for (int j = 0; j < inst.dimension; j++)
		{
			int t = inst.minCost[i][j].first;
			if (i == t)
				continue;
			if (nodeFree(t))
			{
				if (x++ < alpha)
					temp.push_back(t);
				else
					break;
			}
			
		}
		if (temp.size() == 0)
		{
			cout << "";
			int sd = route[i - 1];
			route[i - 1] = i;
			temp.push_back(sd);
		}
		r = rand(0, temp.size());
		setRouteNode(i, temp[r]);
	}
	if (withoutLast)
	{
		totalCostWithoutLast();
	}
	else
	{
		totalCost();
	}
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

long Solution::costRemoveInsert(int i, int j)
{
	if (i < j)
	{
			Part l1(*this, 0, i - 1);
			Part l2(*this, i + 1, j);
			Part r1(*this, i, i);
			l1.add(l2, *this).add(r1, *this);
			if (j < route.size() - 1)
			{
				Part r2(*this, j + 1, route.size() - 1);
				l1.add(r2, *this);
			}
			return l1.finalCost(*this,withoutLast);
	}
	else
	{
			Part l1(*this, 0, j - 1);
			Part l2(*this, i,i);
			Part r1(*this, j, i - 1);
			l1.add(l2, *this).add(r1, *this);
			if (i < route.size() - 1)
			{
				Part r2(*this, i + 1, route.size() - 1);
				l1.add(r2, *this);	
			}
			return l1.finalCost(*this, withoutLast);
	}
	return 0;
}
long Solution::costSwapTwo(int i, int j)
{
	if (i > j)
	{
		int temp = i;
		i = j;
		j = temp;
	}
	Part l1(*this, 0,i-1);
	Part l2(*this, j, j);
	l1.add(l2, *this);
	if (i + 1 < j)
	{
		Part r1(*this, i + 1, j - 1);
		l1.add(r1, *this);
	}
	Part r2(*this, i, i);
	l1.add(r2, *this);
	if (j < route.size() - 1)
	{
		Part r3(*this, j + 1, route.size() - 1);
		l1.add(r3, *this);
	}
	return l1.finalCost(*this, withoutLast);
}
long Solution::costSwapAdjacent(int i)
{
	Part l1(*this, 0, i - 1);
	Part l2(*this, i + 1, i + 1);
	Part r1(*this, i, i);
	l1.add(l2, *this).add(r1, *this);
	if (i + 1 != route.size() - 1)
	{
		Part r2(*this, i + 2, route.size() - 1);
		l1.add(r2, *this);
	}
	return l1.finalCost(*this, withoutLast);
}
long Solution::costTwoOpt(int i, int j)
{
	Part l1(*this, 0, i);
	Part l2(*this, j, i+1);
	l2.C = (j - i)*l2.T - l2.C;
	l1.add(l2, *this);
	if (j < route.size() - 1)
	{
		Part r1(*this, j + 1, route.size() - 1);
		l1.add(r1, *this);
	}
	
	return l1.finalCost(*this, withoutLast);
}
long Solution::costOrOpt(int i, int j, int k)
{
	Part l1(*this, 0, i);
	Part l2(*this, j + 1, k);
	Part r1(*this, i + 1, j);
	Part r2(*this, k + 1, route.size() - 1);
	l1.add(l2, *this).add(r1, *this).add(r2, *this);
	return l1.finalCost(*this, withoutLast);
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

long Solution::totalCost()
{
	double totalCost = 0;
	int dim = route.size();
	
	for (int i = 1; i < route.size();i++)
	{
		totalCost += ((double)dim--)  * inst.cost[route[i - 1]][route[i]];
	}
	cost = totalCost+inst.cost[route[route.size()-1]][0];
	return cost;
}
long Solution::totalCostWithoutLast()
{
	double totalCost = 0;
	int dim = route.size()-1;

	for (int i = 1; i < route.size(); i++)
	{
		totalCost += ((double)dim--)  * inst.cost[route[i - 1]][route[i]];
	}
	cost = totalCost;
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

void Solution::doubleBridge(int i, int j, int k)
{
	Part p1(*this, 0, i);
	Part p2(*this, k + 1, route.size() - 1);
	Part p3(*this, j + 1, k);
	Part p4(*this, i + 1, j);
	p1.add(p2, *this).add(p3, *this).add(p4, *this);
	cost = p1.finalCost(*this, withoutLast);
}