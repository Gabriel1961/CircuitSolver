#pragma once
#include <vector>
#include "Resistor.h"
#include "VoltageSource.h"
class Edge
{
public:
	std::vector<Resistor> resistors;
	std::vector<VoltageSource> voltageSources;
	int n1=0, n2=0;
	Edge(int n1, int n2, const std::vector<Resistor>& resistors = {}, const std::vector<VoltageSource>& voltageSources = {});

	bool operator==(const Edge& e1)
	{
		return e1.n1 == e1.n1 && e1.n2 == n2;
	}
};

