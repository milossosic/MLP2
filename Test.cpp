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

void Test::runVNS(char * argv, int iterations)
{
	

	Config conf;
	//conf.fIn = string(argv);
	
	Writer writer(conf);
	

	//cout << "rand: " << dist(gen) << endl;
	//conf.fIn = "instances/gr17.xml"; 

	//conf.fIn = "instances/01.dantzig42.xml";
	//conf.fIn = "instances/swiss42.xml";
	//conf.fIn = "instances/att48.xml";
	//conf.fIn = "instances/gr48.xml"; 
	//conf.fIn = "instances/hk48.xml";
	conf.fIn = "instances/06.eil51.xml"; //+
	//conf.fIn = "instances/berlin52.xml"; //+
	//conf.fIn = "instances/brazil58.xml"; 
	//conf.fIn = "instances/st70.xml"; //+
	//conf.fIn = "instances/eil76.xml"; 
	//conf.fIn = "instances/pr76.xml"; 

	//conf.fIn = "instances/gr96.xml"; 
	//conf.fIn = "instances/rat99.xml";
	//conf.fIn = "instances/kroA100.xml";
	//conf.fIn = "instances/kroB100.xml";
	//conf.fIn = "instances/kroC100.xml";
	//conf.fIn = "instances/kroD100.xml";
	//conf.fIn = "instances/kroE100.xml";
	//conf.fIn = "instances/rd100.xml";
	//conf.fIn = "instances/eil101.xml";
	//conf.fIn = "instances/lin105.xml";
	//conf.fIn = "instances/pr107.xml";

	//conf.fIn = "instances/rat195.xml";
	//conf.fIn = "instances/pr226.xml";
	//conf.fIn = "instances/vece/lin318.xml";
	//conf.fIn = "instances//vece/pr439.xml";
	//conf.fIn = "instances/vece/att532.xml";

	cout << conf.fIn << endl;

	Reader reader(conf);
	Instance inst;
	reader.read(conf, inst);

	vector<double> costs;
	vector<double> times;
	

	// 0  1000   300    10  0.91 10254 10586 1.870399976
	// 0   400   300    20  0.97 10297 10760.4 1.108599973
	SA sa;
	for (int iter = 0; iter < 11;iter+=5)
	{
		for (int iterDiv = 1400; iterDiv >= 400;iterDiv-=200)
		{
			for (int maxTemp = 300; maxTemp < 1001;maxTemp+=200)
			{
				if (iterDiv <= maxTemp)
					continue;
				for (int minTemp = 10; minTemp < 41;minTemp+=10)
				{
					for (double cool = 0.75; cool < 1;cool+=0.02)
					{
						for (int i = 0; i < iterations; i++)
						{
							unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
							std::default_random_engine gen(seed);
							std::uniform_int_distribution<int> dist(0, 3123121);
							std::uniform_real_distribution<double> distReal(0.0, 1.0);
							bool randConst = false, rvnd = false;
							bool firstImprovement = false;

							VNS vns(inst, gen, dist, distReal);
							sa.init(maxTemp, cool, minTemp, iter, iterDiv);
							time_t t = clock();
							vns.VNS_SA(sa);
							float time1 = ((float)(clock() - t)) / CLOCKS_PER_SEC;

							costs.push_back(vns.sol.cost);
							times.push_back(time1);

							cout << setprecision(10) << vns.sol.cost << " " << setprecision(10) << time1 << endl;
						}
						calcAll(iterations, costs, times);
						
						if (minCost < 10700)
						{
							writer.out << setw(5) << iter << " ";
							writer.out << setw(5) << iterDiv << " ";
							writer.out << setw(5) << maxTemp << " ";
							writer.out << setw(5) << minTemp << " ";
							writer.out << setw(5) << cool << " ";
							writer.out << setprecision(10) << minCost << " " << avgCost << " " << avgTime << endl;
						}
							
						times.clear();
						costs.clear();
					}
				}
				
			}
		}
	}
	
	writer.close();
}

void Test::calcAll(int iter, vector<double> & costs, vector<double> & times)
{
	minCost = DBL_MAX;
	double sumCosts = 0, sumTimes = 0;
	for (int i = 0; i < iter; i++)
	{
		if (costs[i] < minCost)
		{
			minCost = costs[i];
		}
		sumCosts += costs[i];
		sumTimes += times[i];
	}
	avgCost = sumCosts / iter;
	avgTime = sumTimes / iter;

}