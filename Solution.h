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
	int T[100][100];
	int C[100][100];
	int W[100][100];


	void reoptimizeDataStructures();
	int mergeT(int l1, int r1, int l2, int r2);
	int mergeW(int l1, int r1, int l2, int r2);
	int mergeC(int l1, int r1, int l2, int r2);
	int costRemoveInsert(int i, int j);
	int costSwapTwo(int i, int j);
	int costSwapAdjacent(int i);
	int costTwoOpt(int i, int j);
	int costOrOpt(int i, int j, int k);

	void setRouteNode(int i, int j);
	bool nodeFree(int j);
	double totalCost();
	double totalCostWithoutLast();

	void removeInsert(int i, int j);
	void swapTwo(int i, int j);
	void swapAdjacent(int i);
	void twoOpt(int a, int b);
	void orOpt(int i, int j, int k);
	void orOpt2(int i);
	void orOpt3(Instance & inst, int i);
};

