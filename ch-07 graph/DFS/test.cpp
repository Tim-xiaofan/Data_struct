/** 20210811 22:01, zyj, GuangDong*/
//test.c -- test DFS.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cfloat>
#include "DFS.h"

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

static int c[]={
	0,1,0,1,0,
	1,0,1,0,1,
	0,1,0,1,1,
	1,0,1,0,0,
	0,1,1,0,0
};

/** 8 x 8*/
static int e[]={
	0,1,1,0,0,0,0,0,
	1,0,0,1,1,0,0,0,
	1,0,0,0,0,1,1,0,
	0,1,0,0,0,0,0,1,
	0,1,0,0,0,0,0,1,
	0,0,1,0,0,0,1,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
};

static char b[] = {'A', 'B', 'C', 'D'};
static char d[] = {'A', 'B', 'C', 'D', 'E'};
static char f[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

static void visit(int i)
{
	cout << i << " ";
}

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
	//to do
	delete vexs;
	delete arcs;
	vexs = a1::instance(5);
	vexs->set_values(d, 5);
	arcs = a2::instance(5, 5);
	arcs->set_values(c, 25);
	graph_AML<char, int> gaml(*vexs,  *arcs, graph_AML<char, int>::UDG);
	gaml.show_AML();
	cout << "vexnum = " << gaml.vexnum() << endl;
	cout << "arcnum = " << gaml.arcnum() << endl;
	DFS(gaml, visit);
	cout << endl;

	//to do
	delete vexs;
	delete arcs;
	vexs = a1::instance(8);
	vexs->set_values(f, 8);
	arcs = a2::instance(8, 8);
	arcs->set_values(e, 64);
	graph_AML<char, int> gaml1(*vexs,  *arcs, graph_AML<char, int>::UDG);
	gaml1.show_AML();
	cout << "vexnum = " << gaml1.vexnum() << endl;
	cout << "arcnum = " << gaml1.arcnum() << endl;
	DFS(gaml1, visit);
	cout << endl;

	return 0;
}

