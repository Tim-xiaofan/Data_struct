/** 20210802 21:20, zyj, GuangDong*/
//test.c -- test graph_array.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cfloat>
#include "graph_adjlist.h"

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

	graph_adjlist<char, int> gl(*vexs, *arcs, graph_adjlist<char, int>::DG);
	cout << "kind : " << gl.kind_str() << endl;
	cout << "adjlist : " << endl;
	gl.show_adjlists();
	cout << "radjlist : " << endl;
	gl.create_radjlists();
	gl.show_radjlists();
	gl.show_iodegrees();

	delete vexs;
	delete arcs;
	vexs = a1::instance(5);
	vexs->set_values(d, 5);
	arcs = a2::instance(5, 5);
	arcs->set_values(c, 25);
	graph_adjlist<char, int> gl1(*vexs, *arcs, graph_adjlist<char, int>::UDG);
	cout << "kind : " << gl1.kind_str() << endl;
	gl1.show_adjlists();
	gl1.show_degrees();
	return 0;
}

