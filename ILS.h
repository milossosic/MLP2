#pragma once
#include "Solution.h"
#include <random>
class ILS
{
public:
	Solution sol;

	ILS();
	ILS(Solution & s);
	~ILS();

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

	void initialSolution(Instance & isnt);
	void pertrurbation(Instance & inst);
	void localSearch(Instance & inst);
	void acceptCriterion(Instance & inst);

	void run(Instance & inst);
};

