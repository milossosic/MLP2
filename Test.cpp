#include "Test.h"
#include "Algorithms.h"
#include "Config.h"
#include "Writer.h"
#include "Reader.h"
#include <iostream>
#include "ILS.h"
#include "VNS.h"
#include <ctime>
#include <iomanip>
#include <random>
#include <chrono>
#include <cmath>
#include "SA.h"


using namespace std;

Test::Test()
{
}


Test::~Test()
{
}
int min(int x, int y)
{
	return (x < y ? x : y);
}
int max(int x, int y)
{
	return (x > y ? x : y);
}
void Test::runVNS(char * argv, int iterations)
{
	

	Config conf;
	conf.fIn = string(argv);
	
	Writer writer(conf);

	cout << conf.fIn << endl;

	Reader reader(conf);
	Instance inst;
	reader.read(conf, inst);

	vector<long> costs;
	vector<double> times;
	

	
	

	SA sa;

	int maxTemp = max(300 + inst.dimension * 2, 400);
	double cool = .8;
	int minTemp = min((inst.dimension / 4), 20);
	int iter = 0;
	int iterDiv = max(700 + inst.dimension * 2, 1000);

	long optCost = inst.optCost;
	
	//for (iter = 0; iter<= 15; iter+= 1)
	//{
		//cout << "iter: " << iter << " cost: ";
		sa.init(maxTemp, cool, minTemp, iter, iterDiv);

		costs.clear();
		times.clear();
		for (int i = 0; i < iterations; i++)
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine gen(seed);
			std::uniform_int_distribution<int> dist(0, 3123121);
			std::uniform_real_distribution<double> distReal(0.0, 1.0);
			bool randConst = false, rvnd = false;
			bool firstImprovement = false;
			bool finalResultWithoutLast = true;
			

			VNS vns(inst, gen, dist, distReal, finalResultWithoutLast);

			time_t t = clock();
			vns.VNS_SA(sa);
			//vns.run(false, false, false);
			float time1 = ((float)(clock() - t)) / CLOCKS_PER_SEC;

			costs.push_back(vns.sol.cost);
			times.push_back(time1);

			//for (int i = 0; i < vns.sol.route.size(); i++)
			//{
			//	cout << vns.sol.route[i] << " " ;
			//}
			//cout << endl << vns.sol.cost<<endl;
		}
		calcAll(iterations, costs, times, optCost);

		cout << setprecision(10) << minCost << " " << setprecision(10) << avgCost << " " << setprecision(5) << avgGap << " " << avgTime << endl;
		
		writer.out << setprecision(10) << minCost << " " << setprecision(10) << avgCost << " " << setprecision(5) << avgGap << " " << avgTime << endl;

	//}
	writer.close();
}

void Test::calcAll(int iter, vector<long> & costs, vector<double> & times, long opt)
{
	minCost = DBL_MAX;
	
	double sumCosts = 0;
	double sumTimes = 0;

	double sumGap = 0;
	double gap;
	for (int i = 0; i < iter; i++)
	{
		gap = (costs[i] - opt)*1.0 / opt;
		sumGap += gap;
		if (costs[i] < minCost)
		{
			minCost = costs[i];
		}
		sumCosts += costs[i];
		sumTimes += times[i];
	}

	avgGap = 100.0*sumGap / iter;
	avgCost = sumCosts / iter;
	avgTime = sumTimes / iter;
}