#include "Reader.h"
#include "Config.h"
#include "tinyxml2.h"
#include <iostream>
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
	for (XMLElement *vertex = graph->FirstChildElement("vertex"); vertex; vertex = vertex->NextSiblingElement("vertex"), i++)
	{
		for (XMLElement *edge = vertex->FirstChildElement("edge"); edge; edge = edge->NextSiblingElement("edge"))
		{
			edge->QueryDoubleAttribute("cost", &cost);
			edge->QueryIntText(&j);
			inst.cost[i][j] = cost;
		}
		
	}
	inst.dimension = i;
}

