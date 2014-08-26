#pragma once
#include <fstream>
#include "Config.h"
#include "Instance.h"
class Reader
{
public:
	ifstream fin;

	Reader();
	Reader(Config & c);
	~Reader();

	void close();
	void read(Config & c, Instance & inst);
};

