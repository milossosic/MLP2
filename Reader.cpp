#include "Reader.h"
#include "Config.h"
#include "tinyxml2.h"
#include <iostream>
#include <vector>
using namespace tinyxml2;
Reader::Reader()
{}

Reader::Reader(Config & c)
{
	fin.open(c.fIn);
}

Reader::~Reader()
{}

void Reader::close()
{
	fin.close();
}

void Reader::read(Config & c, Instance & inst)
{
	XMLDocument doc;
	const char *name = c.fIn.c_str();
	bool loadOkay = doc.LoadFile(name);

	if (loadOkay)
	{
		printf("Could not load test file '%s'. Error='%s'. Exiting.\n", name, doc.GetErrorStr1());
		exit(1);
	}

	XMLElement *graph = doc.RootElement()->FirstChildElement("graph");
	double cost;
	int j;
	int i = 0;
	bool dimFound = false;
	vector < double > temp;
	for (XMLElement *vertex = graph->FirstChildElement("vertex"); vertex; vertex = vertex->NextSiblingElement("vertex"), i++)
	{
		for (XMLElement *edge = vertex->FirstChildElement("edge"); edge; edge = edge->NextSiblingElement("edge"))
		{

			edge->QueryDoubleAttribute("cost", &cost);
			edge->QueryIntText(&j);
			/*if (i == 0)
			{
				temp.push_back(cost);
			}
			else*/
			inst.cost[i][j] = cost;
		}
		//if (i == 0)
		//{
		//	dimFound = true;
		//	inst.cost = new double*[j+1];
		//	/*for (int i = 0; i < j+1; i++)
		//	{
		//		inst.cost[i] = new double[j+1];
		//		if (i == j)
		//			continue;
		//		inst.cost[0][i + 1] = temp[i];
		//	}
		//	temp.clear();*/
		//}
	}
	inst.dimension = i;
}

