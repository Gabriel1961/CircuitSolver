#pragma once
#include "Resistor.h"
class VoltageSource
{
public:
	float voltage;
	Resistor internalResistor;
	VoltageSource(float voltage, float internalRes)
		:voltage(voltage),
		internalResistor(internalRes)
	{
		
	}
};

