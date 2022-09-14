#pragma once
#include <iostream>
struct Current
{
public:
	float value=0;
	int n1=0, n2=0;
	Current()
	{
	}
	Current(int n1,int n2,float value)
		:n1(n1),n2(n2),value(value)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const Current& t);
};
