#pragma once
#include "Solution.h"
class Part
{
public:
	Part();
	Part(Solution & s, int l, int r);
	~Part();

	int l, r;
	double T=-1, W=-1, C=-1;

	Part & add(Part & a, Solution & s);
	long finalCost(Solution & s, bool withoutLast);
};

