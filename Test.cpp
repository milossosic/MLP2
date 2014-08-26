#include "Test.h"
#include "Algorithms.h"
#include "Config.h"
#include "Writer.h"
#include "Reader.h"
#include <iostream>
#include "ILS.h"
#include "VNS.h"
using namespace std;

Test::Test()
{
}


Test::~Test()
{
}

void Test::run()
{
	Config conf;
	Writer writer(conf);
	//conf.fIn = "instances/gr17.xml"; 
	//conf.fIn = "instances/dantzig42.xml";
	//conf.fIn = "instances/swiss42.xml";
	//conf.fIn = "instances/gr48.xml"; 
	//conf.fIn = "instances/att48.xml";
	//conf.fIn = "instances/hk48.xml";
	conf.fIn = "instances/eil51.xml";
	//conf.fIn = "instances/berlin52.xml";
	
	conf.fIn = "instances/st70.xml";
	Reader reader(conf);
	Instance inst;


	reader.read(conf, inst);

	Solution s(inst);


	Algorithms::greedySolution(s);
	s.totalCost();

	writer.writeRoute(s, inst);
	writer.out << endl;
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
	for (int i = 0; i < s.route.size()-1;i++)
	///for (int j = i+1; j < s.route.size(); j++)
	//for (int k = j + 2; k < s.route.size() - 1; k++)
	{
		
		s.swapAdjacent(i);
		s.totalCost();
		writer.writeRoute(s,inst);
		s.swapAdjacent(i);
		s.totalCost();
		writer.writeRoute(s, inst);
		writer.out << endl;
	}*/

	VNS vns(s);

	vns.run();
	writer.writeRoute(vns.sol,inst);

	writer.close();
}