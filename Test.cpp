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
using namespace std;

Test::Test()
{
}


Test::~Test()
{
}

void Test::run(char * argv)
{
	time_t t = clock();

	Config conf;
	conf.fIn = string(argv);
	Writer writer(conf);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> dist(0,3123121);
	//cout << "rand: " << dist(gen) << endl;
	//conf.fIn = "instances/gr17.xml"; 

	//conf.fIn = "instances/dantzig42.xml";
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
	//conf.fIn = "instances/lin318.xml";
	//conf.fIn = "instances/pr439.xml";


	//conf.fIn = "instances/att532.xml"; //ne moze

	
	Reader reader(conf);
	Instance inst;
	
	reader.read(conf, inst);

	VNS vns(inst, gen, dist);


	/*Algorithms::greedySolution(vns.sol);
	vns.sol.reoptimizeDataStructures();
	writer.out << "smart cost swap2 4,5: " << vns.sol.costSwapTwo(4,5)<< endl;

	vns.sol.swapTwo(4,5);
	writer.out << "real cost swap2   : " << vns.sol.totalCost() << endl;
*/
	

	bool randConst = true, rvnd = false;
	vns.run(randConst, rvnd);

	
	cout << conf.fIn << endl;
	cout << std::setprecision(10) << vns.sol.cost << endl;
	writer.out << conf.fIn << endl;
	//writer.writeRoute(vns.sol,vns.sol.inst);
	writer.writeCost(vns.sol);
	writer.out << "time: " << ((float)(clock() - t)) / CLOCKS_PER_SEC << endl << endl;

	writer.close();
}