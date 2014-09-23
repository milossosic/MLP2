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
	double avgGap;

	void runVNS(char * argv, int iter);
	void calcAll(int iter, vector<long> & costs, vector<double> & times, long opt);
};

