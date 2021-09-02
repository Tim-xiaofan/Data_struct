/** 20210811 22:01, zyj, GuangDong*/
//test.c -- test DFS.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cfloat>
#include "graph_algorithm.h"
#include "graph_olist.h"

using std::cout;
using std::endl;
using std::cerr;
typedef array<int, 2> a2;
typedef array<char, 1> a1;

static int a[]={
//  1 2 3 4 5 6
	0,6,1,5,0,0,//1
	6,0,5,0,3,0,//2
	1,5,0,5,6,4,//3
	5,0,5,0,0,2,//4
	0,3,6,0,0,6,//5
	0,0,4,2,6,0 //6
};

static char b[] = {'1', '2', '3', '4', '5', '6'};

//static void visit(int i)
//{
//    cout << i << " ";
//}

int main(int ac, char * av[])
{
    a1 * vexs;
    a2 * arcs;
	vexs = a1::instance(6);
	vexs->set_values(b, 6);
	arcs = a2::instance(6, 6);
	arcs->set_values(a, 6 * 6);
	graph_array<char, int> G(*vexs,  *arcs, graph_array<char, int>::UDN);
	cout << "** AML **\n";
	cout << "vexnum = " << G.vexnum() << endl;
	cout << "arcnum = " << G.arcnum() << endl;
    prime(G, 0);
    return 0;
}

