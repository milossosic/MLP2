#include "Writer.h"
#include "Config.h"
#include <iostream>
#include <string>
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
	out << "cost: " << s.cost << endl;
	//out << "real cost: " << s.totalCost() << endl;
}
void Writer::writeCost(Solution & s)
{
	//out << this->fin << endl;
	out << s.cost << endl;
}

void Writer::close()
{
	out.close();
}