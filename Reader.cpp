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
	const char *name = c.fIn.c_str();

	XMLDocument doc;

	bool loadOkay = doc.LoadFile(name);
	int dim;
	if (loadOkay)
	{
		printf("Could not load test file '%s'. Error='%s'. Exiting.\n", name, doc.GetErrorStr1());
		exit(1);
	}

	XMLElement *graph = doc.RootElement()->FirstChildElement("graph");
	if (graph)
	{
		//XMLElement *graph1 = new XMLElement(graph);
		double cost;
		int j;
		int i = 0;
		bool dimFound = false;

		for (XMLElement *vertex = graph->FirstChildElement("vertex"); vertex; vertex = vertex->NextSiblingElement("vertex"))
			i++;
		dim = i;
		i = 0;
		inst.cost = new double*[dim];
		for (XMLElement *vertex = graph->FirstChildElement("vertex"); vertex; vertex = vertex->NextSiblingElement("vertex"), i++)
		{
			inst.cost[i] = new double[dim];
			for (XMLElement *edge = vertex->FirstChildElement("edge"); edge; edge = edge->NextSiblingElement("edge"))
			{

				edge->QueryDoubleAttribute("cost", &cost);
				edge->QueryIntText(&j);

				inst.cost[i][j] = cost;
			}
		}
		for (int i = 0; i < dim; i++)
			inst.cost[i][i] = 0;
		inst.dimension = i;
	}
	else
	{
		vector<pair<int, int>> coords;

		double cost;
		int x, y;
		int j;
		int i = 0;
		for (XMLElement *vertex = doc.RootElement()->FirstChildElement("dim"); vertex; vertex = vertex->NextSiblingElement("coordinates"), i++)
		{
			if (i == 0)
			{
				vertex->QueryIntText(&inst.dimension);
				coords.resize(dim=++inst.dimension);
				inst.cost = new double*[dim];
			}
			else
			{
				inst.cost[i-1] = new double[dim];
				vertex->QueryIntAttribute("x", &x);
				vertex->QueryIntAttribute("y", &y);
				coords[i-1] = make_pair(x, y);
			}
		}

		for (int i = 0; i < inst.dimension; i++)
		{
			for (int j = 0; j < inst.dimension; j++)
			{
				if (i == j)
				{
					inst.cost[i][j] = 0;
					continue;
				}
				else
					inst.cost[i][j] = sqrt(pow(coords[i].first - coords[j].first, 2) + pow(coords[i].second - coords[j].second, 2));
			}
		}
	}
}

