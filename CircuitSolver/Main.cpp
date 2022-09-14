// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CircuitSolver.h"
#include "Common.h"
using namespace std;

int main()
{
    CircuitSolver solver = CircuitSolver({
        Edge(1,0,{Resistor(5)},{VoltageSource(205,1)}),
        Edge(0,1,{Resistor(2)},{VoltageSource(-136,1)}),
        Edge(0,2,{Resistor(2)},{VoltageSource(-10,1)}),
        Edge(2,0,{Resistor(1)},{}),
        Edge(2,1,{Resistor(4)},{}),
        });
    Print(solver.GetIndependentLoops());
    Print(solver.Solve());
    cout << endl;
    Print(solver._mat->a);

    /*Mat m(5, 6, {
        {1,1,-1,-1,0,0},
        {1,1,0,0,-1,0},
        {0,3,0,1,4,136},
        {0,0,-3,1,0,10},
        {6,-3,0,0,0,69},
        });
    Print(m.Solve());*/
    
}

//15.3951 7.79012 3.2963 19.8889 23.1852