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
using namespace std;

Test::Test()
{
}


Test::~Test()
{
}

void Test::run()
{
	time_t t = clock();

	Config conf;
	Writer writer(conf);


	//conf.fIn = "instances/gr17.xml"; 

	//conf.fIn = "instances/dantzig42.xml";
	//conf.fIn = "instances/swiss42.xml";
	//conf.fIn = "instances/att48.xml";
	//conf.fIn = "instances/gr48.xml"; 
	//conf.fIn = "instances/hk48.xml";
	//conf.fIn = "instances/eil51.xml"; 
	//conf.fIn = "instances/berlin52.xml"; 
	//conf.fIn = "instances/brazil58.xml"; 
	//conf.fIn = "instances/st70.xml"; 
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
	conf.fIn = "instances/eil101.xml";
	//conf.fIn = "instances/lin105.xml";
	//conf.fIn = "instances/pr107.xml";

	//conf.fIn = "instances/rat195.xml";
	//conf.fIn = "instances/pr226.xml";
	//conf.fIn = "instances/lin318.xml";
	//conf.fIn = "instances/pr439.xml";
	//conf.fIn = "instances/att532.xml";

	
	Reader reader(conf);
	Instance inst;
	
	reader.read(conf, inst);

	VNS vns(inst);


	/*Algorithms::greedySolution(vns.sol);
	vns.sol.reoptimizeDataStructures();
	writer.out << "smart cost swap2 4,5: " << vns.sol.costSwapTwo(4,5)<< endl;

	vns.sol.swapTwo(4,5);
	writer.out << "real cost swap2   : " << vns.sol.totalCost() << endl;
*/
	
	vns.run();

	
	cout << conf.fIn << endl;
	cout << std::setprecision(10) << vns.sol.cost << endl;
	writer.out << conf.fIn << endl;
	//writer.writeRoute(vns.sol,vns.sol.inst);
	writer.writeCost(vns.sol);
	writer.out << "time: " << ((float)(clock() - t)) / CLOCKS_PER_SEC;

	writer.close();
}