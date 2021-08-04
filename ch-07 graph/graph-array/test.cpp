/** 20210802 21:20, zyj, GuangDong*/
//test.c -- test graph_array.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cfloat>
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

static float c[]={
	0,5,0,7,0,0,
	0,0,4,0,0,0,
	8,0,0,0,0,9,
	0,0,5,0,0,6,
	0,0,0,5,0,0,
	3,0,0,0,1,0
};

static char b[] = {'A', 'B', 'C', 'D'};
static char d[] = {'A', 'B', 'C', 'D', 'E', 'F'};

int main(int ac, char * av[])
{
	a1 * vexs = a1::instance(4);
	if(!vexs) 
	{
		cerr << "vexs create error\n";
		exit(EXIT_FAILURE);
	}
	vexs->set_values(b, 4);
	a2 * arcs = a2::instance(4, 4);
	if(!arcs) 
	{
		cerr << "arcs create error\n";
		exit(EXIT_FAILURE);
	}
	arcs->set_values(a, 16);

	graph_array<char, int> ga(*vexs, *arcs, graph_array<char, int>::UDG);
	cout << ga.kind_str() << endl;

	array<char, 1> * vexs1 = array<char, 1>::instance(6);
	if(!vexs1) 
	{
		cerr << "vexs1 create error\n";
		exit(EXIT_FAILURE);
	}
	vexs1->set_values(d, 6);
	array<float, 2> * arcs1 = array<float, 2>::instance(6, 6);
	if(!arcs1) 
	{
		cerr << "arcs1 create error\n";
		exit(EXIT_FAILURE);
	}
	arcs1->set_values(c, 36);
	graph_array<char, float> ga1(*vexs1, *arcs1, graph_array<char, float>::UDN);
	cout << ga1.kind_str() << endl;

	graph_array<char, float> ga2(*vexs1, *arcs1, graph_array<char, float>::DG);
	cout << ga2.kind_str() << endl;
	ga.show_degree();
	cout << "----------\n";
	ga1.show_degree();
	cout << "----------\n";
	ga2.show_degree();
	return 0;
}
