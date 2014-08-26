#pragma once
#include <vector>
#include "Instance.h"
using namespace std;
class Solution
{
public:
	Solution();
	Solution(Instance & inst1);
	~Solution();

	Instance inst;
	vector<bool> nodesVisited;
	vector<int> route;
	double cost;

	void setRouteNode(int i, int j);
	bool nodeFree(int j);
	double totalCost();

	void removeInsert(int i, int j);
	void swapTwo(int i, int j);
	void swapAdjacent(int i);
	void twoOpt(int a, int b);
	void orOpt(int i, int j, int k);
	void orOpt2(int i);
	void orOpt3(Instance & inst, int i);
};

