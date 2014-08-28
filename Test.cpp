#include "Test.h"
#include "Algorithms.h"
#include "Config.h"
#include "Writer.h"
#include "Reader.h"
#include <iostream>
#include "ILS.h"
#include "VNS.h"
#include <ctime>
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
	conf.fIn = "instances/swiss42.xml";
	//conf.fIn = "instances/gr48.xml"; 
	//conf.fIn = "instances/att48.xml";
	//conf.fIn = "instances/hk48.xml";
	//conf.fIn = "instances/eil51.xml"; //dobijam 9.787 resenje
	//conf.fIn = "instances/berlin52.xml"; // 143.399
	//conf.fIn = "instances/st70.xml"; // 20.543
	//conf.fIn = "instances/eil76.xml"; //+
	//conf.fIn = "instances/pr76.xml"; //+
	//conf.fIn = "instances/gr96.xml"; //opt
	//conf.fIn = "instances/rat99.xml";

	
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

	writer.out << conf.fIn << endl;
	writer.writeCost(vns.sol);
	writer.out << "time: " << ((float)(clock() - t)) / CLOCKS_PER_SEC;

	writer.close();
}