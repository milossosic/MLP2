#include "Part.h"


Part::Part()
{
}
Part::Part(Solution & s, int _l, int _r)
{
	l = _l;
	r = _r;
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
	C += a.W*(T + s.inst.cost[s.route[r]][s.route[a.l]]) + a.C;
	T += s.inst.cost[s.route[r]][s.route[a.l]] + a.T;
	r = a.r;// -a.l + r + 1;
	return *this;
}
int Part::finalCost(Solution & s)
{
	return C + T + s.inst.cost[s.route[r]][0];
}
