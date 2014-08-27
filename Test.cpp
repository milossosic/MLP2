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
	conf.fIn = "instances/gr17.xml"; 
	//conf.fIn = "instances/dantzig42.xml";
	//conf.fIn = "instances/swiss42.xml";
	//conf.fIn = "instances/gr48.xml"; 
	//conf.fIn = "instances/att48.xml";
	//conf.fIn = "instances/hk48.xml";
	//conf.fIn = "instances/eil51.xml";
	//conf.fIn = "instances/berlin52.xml";
	
	//conf.fIn = "instances/st70.xml";
	Reader reader(conf);
	Instance inst;
	
	reader.read(conf, inst);

	VNS vns(inst);

	
	Algorithms::greedySolution(vns.sol);
	writer.out << "start total cost: " << vns.sol.totalCost() << endl;
	//writer.writeRoute(vns.sol, inst);

	vns.sol.reoptimizeDataStructures();
	writer.out << "start smart cost: " << (vns.sol.C[0][vns.sol.route.size() - 1] + vns.sol.T[0][vns.sol.route[vns.sol.route.size() - 1]] + vns.sol.inst.cost[vns.sol.route[vns.sol.route.size() - 1]][0]) << endl;
	//vns.run();
	//writer.out << "removeInsert - 1, 8" << endl;
	//
	vns.sol.cost = vns.sol.costRemoveInsert(1, 8);
	writer.out << "rmIns smart cost: " << vns.sol.cost << endl;
	//writer.writeRoute(vns.sol, inst);

	vns.sol.removeInsert(1, 8);
	//writer.writeRoute(vns.sol, inst);
	writer.out << endl << "totalcost after rmIns: " << vns.sol.totalCost() << endl;
	//vns.sol.removeInsert(8, 0);
	//vns.sol.cost = vns.sol.costRemoveInsert(8, 0);
	//writer.writeRoute(vns.sol, inst);



	//writer.writeRoute(vns.sol,inst);
	//writer.out << "time: " << ((float)(clock() - t)) / CLOCKS_PER_SEC;
	

	/*writer.out << "swapAdjacent - 0" << endl;
	s.swapAdjacent(0);
	writer.writeRoute(s, inst);
	s.swapAdjacent(0);
	writer.writeRoute(s, inst);

	
	writer.out << "swapTwo - 0, 8" << endl;
	s.swapTwo(0,8);
	writer.writeRoute(s, inst);
	s.swapTwo(0,8);
	writer.writeRoute(s, inst);
	/*
	writer.out << "removeInsert - 0, 8" << endl;
	s.removeInsert(0,8);
	writer.writeRoute(s, inst);
	s.removeInsert(8,0);
	writer.writeRoute(s, inst);

	writer.out << "twoOpt - 0, 10" << endl;
	s.twoOpt(0,10);
	writer.writeRoute(s, inst);
	s.twoOpt(0,10);
	writer.writeRoute(s, inst);

	writer.out << "orOpt - 5, 10, 14" << endl;
	s.orOpt(5,10,14);
	writer.writeRoute(s, inst);
	s.orOpt(5, 9, 14);
	writer.writeRoute(s, inst);
	
	for (int i = 1; i < s.route.size()-1;i++)
	for (int j = i+1; j < s.route.size(); j++)
	//	for (int k = j + 2; k < s.route.size() - 1; k++)
	{
		
		s.swapTwo(i,j);
		s.totalCost();
		writer.writeRoute(s,inst);
		s.swapTwo(i,j);
		//s.totalCost();
		writer.writeRoute(s, inst);
		writer.out << endl;
	}*/
	
	

	
	
	writer.close();
}