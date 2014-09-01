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
using namespace std;

Test::Test()
{
}


Test::~Test()
{
}

void Test::run(char * argv)
{
	

	Config conf;
	conf.fIn = string(argv);
	Writer writer(conf);
	

	//cout << "rand: " << dist(gen) << endl;
	//conf.fIn = "instances/gr17.xml"; 

	//conf.fIn = "instances/1.dantzig42.xml";
	//conf.fIn = "instances/swiss42.xml";
	//conf.fIn = "instances/att48.xml";
	//conf.fIn = "instances/gr48.xml"; 
	//conf.fIn = "instances/hk48.xml";
	//conf.fIn = "instances/eil51.xml"; //+
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

	
	Reader reader(conf);
	Instance inst;
	reader.read(conf, inst);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> dist(0, 3123121);

	bool randConst = false, rvnd = false;
	bool bestImprovement = true;

	
	VNS vns(inst, gen, dist);
	
	//double x;
	//vns.sol.greedyConstruct();
	//vns.sol.reoptimizeDataStructures();
	////swapTwo okolina
	//Solution sol = vns.sol;
	//double bestCost = sol.cost;
	//for (int i = 1; i < sol.route.size() - 1; i++)
	//{
	//	for (int j = i + 1; j < sol.route.size(); j++)
	//	{
	//		if (i == j)
	//			continue;
	//		x = sol.costSwapTwo(i,j);
	//		sol.swapTwo(i,j);
	//		sol.totalCost();
	//		//cout << x - sol.cost << " ";
	//		if (fabs(x - sol.cost) > 0.0001)
	//		{
	//			cout << i;// << " " << j << endl;
	//		}
	//		sol.swapTwo(i,j);
	//	}
	//}
	

	time_t t = clock();
	vns.run(randConst, rvnd, bestImprovement);
	float time1 = ((float)(clock() - t)) / CLOCKS_PER_SEC;
	writer.writeCost(vns.sol);
	writer.out <<  time1 << endl;

	writer.close();
}