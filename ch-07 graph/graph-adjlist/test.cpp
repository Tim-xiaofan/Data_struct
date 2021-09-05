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

static char a[] = {'0', '1', '2', '3'};
static char b[] = {'0', '1', '2', '3', '4'};
static char c[] = {'0', '1', '2', '3', '4', '5'};

static int A[]={
	0,1,1,0,
	0,0,0,0,
	0,0,0,1,
	1,0,0,0
};

static int B[]={
	0,1,0,1,0,
	1,0,1,0,1,
	0,1,0,1,1,
	1,0,1,0,0,
	0,1,1,0,0
};

#define I INT_MAX
static int C[]={
	I,5,I,7,I,I,
	I,I,4,I,I,I,
	8,I,I,I,I,9,
	I,I,5,I,I,6,
	I,I,I,5,I,I,
	3,I,I,I,1,I,
};

int main(int ac, char * av[])
{
	//char * p;
	//cout << *p;
	cout << "INT_MAX = " << I << endl;
	a1 * vexs = a1::instance(4);
	if(!vexs) 
	{
		cerr << "vexs create error\n";
		exit(EXIT_FAILURE);
	}
	vexs->set_values(a, 4);
	a2 * arcs = a2::instance(4, 4);
	if(!arcs) 
	{
		cerr << "arcs create error\n";
		exit(EXIT_FAILURE);
	}
	arcs->set_values(A, 16);

	graph_adjlist<char, int> gl(*vexs, *arcs, graph_adjlist<char, int>::DG);
	cout << "*** kind : " << gl.kind_str() << " ***" << endl;
	cout << "adjlist : " << endl;
	gl.show_adjlists();
	cout << "radjlist : " << endl;
	gl.create_radjlists();
	gl.show_radjlists();
	cout << "iodegrees : " << endl;
	gl.show_iodegrees();

	//Graph UDG
	delete vexs;
	delete arcs;
	vexs = a1::instance(5);
	vexs->set_values(b, 5);
	arcs = a2::instance(5, 5);
	arcs->set_values(B, 25);
	graph_adjlist<char, int> gl1(*vexs, *arcs, graph_adjlist<char, int>::UDG);
	cout << "*** kind : " << gl1.kind_str() << " ***"<< endl;
	gl1.show_adjlists();
	cout << "degrees : " << endl;
	gl1.show_degrees();

	//Graph DN
	delete vexs;
	delete arcs;
	vexs = a1::instance(6);
	vexs->set_values(c, 6);
	arcs = a2::instance(6, 6);
	arcs->set_values(C, 6 * 6);
	graph_adjlist<char, int> gl2(*vexs, *arcs, graph_adjlist<char, int>::DN);
	cout << "*** kind : " << gl2.kind_str() << " ***"<< endl;
	gl2.show_adjlists();
	cout << "io degrees : " << endl;
	gl2.show_iodegrees();
	return 0;
}
