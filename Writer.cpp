#include "Writer.h"
#include "Config.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Writer::Writer()
{}

Writer::Writer(Config & c)
{
	out.open(c.fOut);
	//out << c.fIn << endl;
	//fin = *(new string(c.fIn));
}

Writer::~Writer()
{}

void Writer::writeRoute(Solution & s, Instance &inst)
{
	//out << "0 ";
	for (auto it = s.route.begin(); it != s.route.end(); it++)
		out << *it << " ";
	out << endl;
	//out << "cost: " << s.cost << endl;
	//out << "real cost: " << s.totalCost() << endl;
}
void Writer::writeCost(Solution & s)
{
	out << "cost with last: " << std::setprecision(10) << s.cost << endl;
	out << "real cost w.l.: " << std::setprecision(10) << s.totalCost() << endl;
	out << "cost w/o last:  " << std::setprecision(10) << s.totalCostWithoutLast() << endl;
}

void Writer::close()
{
	out.close();
}