#pragma once
#include <vector>
#include <utility>

class Instance
{
public:
	Instance();
	//Instance(Instance & inst);
	~Instance();

	int dimension;
	//double  cost[550][550];
	double **cost;
	std::vector < std::vector < std::pair < int, double> > > minCost;
};

