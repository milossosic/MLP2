#include "Algorithms.h"


Algorithms::Algorithms()
{
}


Algorithms::~Algorithms()
{
}

void Algorithms::reverseSegment(vector<int> & route, int start, int end)
{
	if (start < 0 || end >= route.size())
		return;

	for (int i = start, j = end, t = 0; i < j; i++, j--)
	{
		t = route[i];
		route[i] = route[j];
		route[j] = t;
	}
}

void Algorithms::twoOpt(vector<int> & route, int a, int b)
{
	if (a == b || a+1 == b || a == b+1 || a+1 == b+1)
		return;
	reverseSegment(route, a+1, b);
}

void Algorithms::swapTwo(vector<int> & route, int a, int b)
{
	int temp = route[a];
	route[a] = route[b];
	route[b] = temp;
}

bool Algorithms::comparePairBySecond(pair<int, double> & a, pair<int, double> & b)
{
	return a.second < b.second;
}

void Algorithms::greedySolution(Solution & s)
{
	s.setRouteNode(0, 0);
	for (int i = 0; i < s.inst.dimension; i++)
	{
		for (int j = 0; j < s.inst.dimension; j++)
		{
			int t = s.inst.minCost[i][j].first;
			if (i == t)
				continue;
			if (s.nodeFree(t))
			{
				s.setRouteNode(i, t);
				break;
			}
		}
	}
}