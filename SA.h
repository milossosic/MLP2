#pragma once
#include "VNS.h"
//class VNS;
class SA
{
public:
	SA();
	~SA();
	double maxTemp;
	double currentTemp;
	double coolingRate;
	double minTemp;
	int iter;
	int iterDiv;

	void init(int & _maxTemp, double & cool, int & _minTemp, int & _iter, int & _iterDiv);

	void run(VNS & s);
};

