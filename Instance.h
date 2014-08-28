#pragma once
#include <vector>
#include <utility>

class Instance
{
public:
	Instance();
	~Instance();

	int dimension;
	double  cost[200][200];
	std::vector < std::vector < std::pair < int, double> > > minCost;
};

