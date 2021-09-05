/** 20210811 22:01, zyj, GuangDong*/
//test.c -- test DFS.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cfloat>
#include "graph_algorithm.h"
#include "graph_olist.h"
#include "graph_adjlist.h"

//#define PRIME 1
//#define ARTICUL 1

using std::cout;
using std::endl;
using std::cerr;
typedef array<int, 2> a2;
typedef array<char, 1> a1;

#ifdef PRIME
static void
test_prime(void)
{
#define I INT_MAX
	int a[]={
		//  1 2 3 4 5 6
		I,6,1,5,I,I,//1
		6,I,5,I,3,I,//2
		1,5,I,5,6,4,//3
		5,I,5,I,I,2,//4
		I,3,6,I,I,6,//5
		I,I,4,2,6,I //6
	};
	char b[] = {'1', '2', '3', '4', '5', '6'};
	int cost;
	a1 * vexs;
	a2 * arcs;
	vexs = a1::instance(6);
	vexs->set_values(b, 6);
	arcs = a2::instance(6, 6);
	arcs->set_values(a, 6 * 6);
	graph_array<char, int> G(*vexs,  *arcs, graph_array<char, int>::UDN);
	cout << "** AML **\n";
	//cout << "vexnum = " << G.vexnum() << endl;
	//cout << "arcnum = " << G.arcnum() << endl;
	cout << "--prime_O3(not work) : " << endl;
	cost = prime_O3(G, 0);
	cout << "cost = " << cost << endl;
	cout << "--prime_O2 : " << endl;
	cost = prime_O2(G, 0);
	cout << "cost = " << cost << endl;
	cout << "--prime_O2 1 : " << endl;
	prime_O2(G, 1);
	cout << "cost = " << cost << endl;
}
#endif

#ifdef ARTICUL
static void 
test_articul(void)
{
	int a[]={
		  //1 2 3 4 5 6 7 8 9 a b c d
	/*1*/	0,1,1,0,0,1,0,0,0,0,0,1,0,
	/*2*/	1,0,1,1,0,0,1,1,0,0,0,0,1,
	/*3*/	1,1,0,0,0,0,0,0,0,0,0,0,0,
	/*4*/	0,1,0,0,1,0,0,0,0,0,0,0,0,
	/*5*/	0,0,0,1,0,0,0,0,0,0,0,0,0,
	/*6*/	1,0,0,0,0,0,0,0,0,0,0,0,0,
	/*7*/	0,1,0,0,0,0,0,1,1,0,1,0,0,
	/*8*/	0,1,0,0,0,0,1,0,0,0,1,0,0,
	/*9*/	0,0,0,0,0,0,1,0,0,0,0,0,0,
	/*a*/	0,0,0,0,0,0,0,0,0,0,0,1,1,
	/*b*/	0,0,0,0,0,0,1,1,0,0,0,0,0,
	/*c*/	1,0,0,0,0,0,0,0,0,1,0,0,1,
	/*d*/	0,1,0,0,0,0,0,0,0,1,0,1,0
	};
	char b[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G',
		'H', 'I', 'G', 'K', 'L', 'M'
	};
	a1 * vexs;
	a2 * arcs;
	vexs = a1::instance(13);
	vexs->set_values(b, 13);
	arcs = a2::instance(13, 13);
	arcs->set_values(a, 13 * 13);
	graph_adjlist<char, int> G(*vexs, *arcs, graph_adjlist<char, int>::UDG);
	cout << "** UDG **" << endl;
	G.show_adjlists();
	cout << "ARTICUL:" << endl;
	find_articul(G, print);
}
#endif

//#define TOPO_SORT
#ifdef TOPO_SORT
static void
test_topo_sort(void)
{
#define I 0
	int a[]={
		  //1 2 3 4 5 6 
	/*1*/	I,1,1,1,I,I,
	/*2*/	I,I,I,I,I,I,
	/*3*/	I,I,I,I,1,I,
	/*4*/	I,I,I,I,1,I,
	/*5*/	I,I,I,I,I,I,
	/*6*/	I,I,I,1,1,I
	};
	char b[] = {
		'A', 'B', 'C', 'D', 'E', 'F'
	};
	a1 * vexs;
	a2 * arcs;
	vexs = a1::instance(6);
	vexs->set_values(b, 6);
	arcs = a2::instance(6, 6);
	arcs->set_values(a, 6 * 6);
	graph_adjlist<char, int> G(*vexs, *arcs, graph_adjlist<char, int>::DG);
	cout << "** DG **" << endl;
	G.show_adjlists();
	cout << "topological_sort : ";
	bool noloop = topological_sort(G, print);
	cout << endl; 
	if(!noloop) cout << "there are loop(s)." << endl;
	else cout << "there are not loop(s)." << endl;
}
#endif

//#define CRITICAL_PATH 1
#ifdef CRITICAL_PATH
static void
test_criticalpath(void)
{
#define I INT_MAX
	int a[]={
		  //1 2 3 4 5 6 
	/*1*/	I,3,2,I,I,I,
	/*2*/	I,I,I,2,3,I,
	/*3*/	I,I,I,4,I,3,
	/*4*/	I,I,I,I,I,2,
	/*5*/	I,I,I,I,I,1,
	/*6*/	I,I,I,I,I,I
	};
	char b[] = {'1', '2', '3', '4', '5', '6'};
	a1 * vexs;
	a2 * arcs;
	vexs = a1::instance(6);
	vexs->set_values(b, 6);
	arcs = a2::instance(6, 6);
	arcs->set_values(a, 6 * 6);
	graph_adjlist<char, int> G(*vexs, *arcs, graph_adjlist<char, int>::DN);
	cout << "** DN **" << endl;
	G.show_adjlists();
	cout << "topological_sort : ";
	topological_sort(G, print);
	cout << endl;
	bool noloop = cricticalpath(G);
	if(!noloop) cout << "there are loop(s)." << endl;
	else cout << "there are not loop(s)." << endl;
}
#endif

#define DIJ 1
#ifdef DIJ
static void
test_dijkstra(void)
{
#define I INT_MAX
	int a[]={
		  //1 2 3 4 5 6 
	/*1*/	I,I,10,I,30,100,
	/*2*/	I,I,5,I,I,I,
	/*3*/	I,I,I,50,I,I,
	/*4*/	I,I,I,I,I,10,
	/*5*/	I,I,I,20,I,60,
	/*6*/	I,I,I,I,I,I
	};
	char b[] = {'1', '2', '3', '4', '5', '6'};
	a1 * vexs;
	a2 * arcs;
	vexs = a1::instance(6);
	vexs->set_values(b, 6);
	arcs = a2::instance(6, 6);
	arcs->set_values(a, 6 * 6);
	graph_array<char, int> G(*vexs, *arcs, graph_array<char, int>::DN);
	cout << "** DN **" << endl;
	//G.show_adjlists();
	
	bool P[MAX_NB_VEX][MAX_NB_VEX];
	int D[MAX_NB_VEX], v, w, v0 = 0;
	cout << "DIJ from " << v0 << " : "<< endl;
	dijkstra(G, v0, P, D);
	cout << "Paths : " << endl;
	for(v = 0; v < G.vexnum(); ++v)
	{
		cout << "to "<< v << " : ";
		for(w = 0; w < G.vexnum(); ++w)
		  if(P[v][w]) cout << w << " ";
		cout << " len=" << D[v] << endl;
	}
}
#endif

int main(int ac, char * av[])
{
#ifdef PRIME
	test_prime();
#endif
#ifdef ARTICUL
	test_articul();
#endif
#ifdef TOPO_SORT
	test_topo_sort();
#endif
#ifdef CRITICAL_PATH
	test_criticalpath();
#endif
#ifdef DIJ 
	test_dijkstra();
#endif
	return 0;
}
