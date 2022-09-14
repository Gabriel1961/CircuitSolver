#include "Edge.h"

Edge::Edge(int n1, int n2, const std::vector<Resistor>& resistors, const std::vector<VoltageSource>& voltageSources) :
	n1(n1), n2(n2), resistors(resistors), voltageSources(voltageSources)
{
}
