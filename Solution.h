#pragma once
#include <vector>
#include <random>
#include "Instance.h"
#include <chrono>
using namespace std;
class Solution
{
public:
	Solution();
	Solution(Instance & inst1, default_random_engine & gen, uniform_int_distribution<int> & dist);
	~Solution();

	Instance inst;
	vector<bool> nodesVisited;
	vector<int> route;
	double cost;
	//double T[110][110];
	//double C[110][110];
	//int W[110][110];
	double **T;
	double **C;
	int **W;
	
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	int rand(int p, int d);

	void greedyConstruct();
	void greedyRandomConstruct(int alpha);

	void reoptimizeDataStructures();
	double costRemoveInsert(int i, int j);
	double costSwapTwo(int i, int j);
	double costSwapAdjacent(int i);
	double costTwoOpt(int i, int j);
	double costOrOpt(int i, int j, int k);

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
	
	void doubleBridge(int i, int j, int k);
};

