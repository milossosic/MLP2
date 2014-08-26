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

	Writer();
	Writer(Config & c);
	~Writer();



	void writeRoute(Solution & s, Instance &inst);

	void close();
};

