/** 20210810 12:35, zyj, GuangDong*/
//test.c -- test graph_array.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cfloat>
#include "graph_olist.h"

using std::cout;
using std::endl;
using std::cerr;
typedef array<int, 2> a2;
typedef array<char, 1> a1;

static int a[]={
	0,1,1,0,
	0,0,0,0,
	1,0,0,1,
	1,1,1,0
};

static int c[]={
	0,1,0,1,0,
	1,0,1,0,1,
	0,1,0,1,1,
	1,0,1,0,0,
	0,1,1,0,0
};

static char b[] = {'A', 'B', 'C', 'D'};
static char d[] = {'A', 'B', 'C', 'D', 'E'};

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
	graph_olist<char, int> go(*vexs,  *arcs, graph_olist<char, int>::DG);
	go.show_olist();
	go.show_iodegree();
	cout << "vexnum = " << go.vexnum() << endl;
	cout << "arcnum = " << go.arcnum() << endl;

	delete vexs;
	delete arcs;
	vexs = a1::instance(5);
	vexs->set_values(d, 5);
	arcs = a2::instance(5, 5);
	arcs->set_values(c, 25);
	// to do
	return 0;
}

