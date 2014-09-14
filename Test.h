#pragma once
#include <vector>
using namespace std;
class Test
{
public:
	Test();
	~Test();

	double minCost;
	double avgCost, avgCost2;
	double avgTime;


	void runVNS(char * argv, int iter);
	void calcAll(int iter, vector<double> & costs, vector<double> & times);
};

