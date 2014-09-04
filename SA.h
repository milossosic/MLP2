#pragma once
#include "VNS.h"
class SA
{
public:
	SA();
	~SA();

	double currentTemp;
	double coolingRate;
	double minTemp;

	void run(VNS & s);
};

