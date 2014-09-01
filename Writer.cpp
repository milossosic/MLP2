#include "Writer.h"
#include "Config.h"
#include <iostream>
#include <string>
#include <iomanip>
//#include <cstdio>
#include <algorithm>
using namespace std;

Writer::Writer()
{}

Writer::Writer(Config & c)
{
	out.open(c.fOut,ios_base::app);
	//out << c.fIn << endl;
	//fin = *(new string(c.fIn));
}

Writer::~Writer()
{}

void Writer::writeRoute(Solution & s, Instance &inst)
{
	for (auto it = s.route.begin(); it != s.route.end(); it++)
		out << *it << " ";
	out << endl;
}
void Writer::writeCost(Solution & s)
{
	/*int dim = s.route.size();
	bool *nodes = new bool[dim];
	vector<int> temp = vector<int>(s.route);
	sort(temp.begin(), temp.end());
	for (int i = 0; i < dim; i++)
	{
		if (temp[i] != i)
		{
			out << "nije dobro\n";
			exit(-1);
		}
	}*/
	
	/*char buffer[500];
	
	
	for (int i = 0; i < s.inst.dimension; i++)
	{
		for (int j = 0; j < s.inst.dimension; j++)
		{
			sprintf(buffer, "%5.10f ", s.inst.cost[i][j]);
			string s1(buffer);
			out << s1;
		}
		out << endl;
	}*/

	//char buffer1[100];
	//double cost = s.cost;
	//double totalCost = s.totalCost();
	//double totalCostWithoutLast = s.totalCostWithoutLast();
	//double costC = s.C[0][s.route.size() - 1];
	//sprintf(buffer1, "%-12.4f %-12.4f %-12.4f ", cost, totalCost, totalCostWithoutLast);
	//string s1(buffer1);
	out << setprecision(15) << s.cost << " ";
	out << setprecision(15) << s.totalCost() << " ";
	out << setprecision(15) << s.totalCostWithoutLast() << " ";
}

void Writer::close()
{
	out.close();
}