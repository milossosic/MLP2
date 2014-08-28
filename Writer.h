#pragma once
#include <vector>
#include "Config.h"
#include <fstream>
#include "Solution.h"
#include "Instance.h"
using namespace std;

class Writer
{
public:
	
	ofstream out;
	string fin;

	Writer();
	Writer(Config & c);
	~Writer();


	void writeCost(Solution & s);
	void writeRoute(Solution & s, Instance &inst);

	void close();
};

