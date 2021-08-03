/** 20210802 21:20, zyj, GuangDong*/
//test.c -- test graph_array.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "graph_array.h"

using std::cout;
using std::endl;
using std::cerr;
typedef array<int, 2> a2;
typedef array<char, 1> a1;

static int a[]={
	0,1,1,0,
	0,0,0,0,
	0,0,0,1,
	1,0,0,0
};

static char b[] = {'A', 'B', 'C', 'D'};

int main(int ac, char * av[])
{
	int i, j;
	a1 * vexs = a1::instance(4);
	if(!vexs) 
	{
		cerr << "vexs create error\n";
		exit(EXIT_FAILURE);
	}
	vexs->set_values(b, 4);
	for(i = 0; i < 4; ++i)
	{
		cout << vexs->at(i) << " ";
	}
	cout << endl;
	a2 * arcs = a2::instance(4, 4);
	if(!arcs) 
	{
		cerr << "arcs create error\n";
		exit(EXIT_FAILURE);
	}
	arcs->set_values(a, 16);
	cout << "arcs :" << endl;
	for(i = 0; i <4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			cout << std:: setw(2) << std::left << arcs->at(i, j) << " ";
		}
		cout << endl;
	}

	graph_array<char, int> ga(*vexs, *arcs, graph_array<char, int>::UDG);
	cout << ga.kind_str() << endl;
	return 0;
}
