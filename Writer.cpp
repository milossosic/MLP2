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
	//out << "cost: " << s.cost << endl;
	//out << "real cost: " << s.totalCost() << endl;
}
void Writer::writeCost(Solution & s)
{
	//out << this->fin << endl;
	out << "cost with last: " << s.cost << endl;
	out << "real cost w.l.: " << s.totalCost() << endl;
	out << "cost w/o last:  " << s.totalCostWithoutLast() << endl;
	/*bool in[200];
	for (int i = 0; i < s.route.size(); i++)
	{
		in[i] = false;
	}
	for (int i = 0; i < s.route.size(); i++)
	{
		in[s.route[i]] = true;
	}
	bool flag = true;
	for (int i = 0; i < s.route.size(); i++)
	{
		if (!in[i])
			flag = false;
	}
	out << "all "<< s.route.size() <<" vertices on route: " << (flag?"true":"false") << endl;*/
}

void Writer::close()
{
	out.close();
}