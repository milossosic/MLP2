#include "Writer.h"
#include "Config.h"
#include <iostream>
using namespace std;

Writer::Writer()
{}

Writer::Writer(Config & c)
{
	out.open(c.fOut);
}

Writer::~Writer()
{}

void Writer::writeRoute(Solution & s, Instance &inst)
{
	out << "0 ";
	for (auto it = s.route.begin(); it != s.route.end(); it++)
		out << *it << " ";
	out << endl;
	out << "cost: " << s.cost << endl;
}

void Writer::close()
{
	out.close();
}