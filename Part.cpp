#include "Part.h"
#include <iostream>

Part::Part()
{
}
Part::Part(Solution & s, int _l, int _r)
{
	l = _l;
	r = _r;
	if(l>r)
		T = s.T[r][l];
	else
		T = s.T[l][r];
	W = s.W[l][r];
	C = s.C[l][r];
}

Part::~Part()
{
}

Part & Part::add(Part & a, Solution & s)
{
	
	W += a.W;
	C += ((double)a.W)*(T + s.inst.cost[s.route[r]][s.route[a.l]]) + a.C;
	T += s.inst.cost[s.route[r]][s.route[a.l]] + a.T;
	r = a.r;// -a.l + r + 1;
	return *this;
}
double Part::finalCost(Solution & s, bool withoutLast)
{
	if (withoutLast==false)
	{
		return (C + T + s.inst.cost[s.route[r]][0]);
	}
	else
	{
		return C;
	}
}
