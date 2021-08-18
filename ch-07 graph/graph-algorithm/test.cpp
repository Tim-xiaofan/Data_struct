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
	0,0,0,1,1,0,0,0
};

static int g[]={
	0,1,1,0,
	0,0,0,0,
	1,0,0,1,
	1,1,1,0
};


static int h[]={
	0,1,1,0,
	0,0,0,0,
	0,0,0,1,
	1,1,0,0
};

static int A[] = {
//  1 2 3 4 5 6 7 8 9
	0,1,0,1,0,0,0,0,0,//1
	0,0,1,0,0,0,0,0,0,//2
	1,0,0,0,0,0,0,0,0,//3
	0,0,0,0,1,0,0,0,0,//4
	0,0,0,0,0,1,1,1,0,//5
	0,0,0,1,0,0,0,0,0,//6
	0,0,0,0,0,1,0,0,0,//7
	0,0,0,0,0,0,0,0,1,//8
	0,0,0,0,0,0,0,1,0 //9
};

static char b[] = {'A', 'B', 'C', 'D'};
static char d[] = {'A', 'B', 'C', 'D', 'E'};
static char f[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
static char B[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};

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
	cout << "** AML **\n";
	gaml.show_AML();
	cout << "vexnum = " << gaml.vexnum() << endl;
	cout << "arcnum = " << gaml.arcnum() << endl;
	cout << "DFS : ";
	DFS(gaml, visit);
	cout << endl;

	cout << "DFS1 : ";
	DFS(gaml, visit, false);
	cout << endl;

	cout << "BFS : ";
	BFS(gaml, visit);
	cout << endl;



	//to do
	delete vexs;
	delete arcs;
	vexs = a1::instance(8);
	vexs->set_values(f, 8);
	arcs = a2::instance(8, 8);
	arcs->set_values(e, 64);
	graph_AML<char, int> gaml1(*vexs,  *arcs, graph_AML<char, int>::UDG);
	cout << "\n** AML **\n";
	gaml1.show_AML();
	cout << "vexnum = " << gaml1.vexnum() << endl;
	cout << "arcnum = " << gaml1.arcnum() << endl;
	cout << "DFS : ";
	DFS(gaml1, visit);
	cout << endl;

	cout << "DFS1 : ";
	DFS(gaml1, visit, false);
	cout << endl;

	cout << "BFS : ";
	BFS(gaml1, visit);
	cout << endl;

	cout << "\n** olist **\n";
	delete vexs;
	delete arcs;
	vexs = a1::instance(4);
	vexs->set_values(b, 4);
	arcs = a2::instance(4, 4);
	arcs->set_values(g, 4 * 4);
	graph_olist<char, int> go(*vexs,  *arcs, graph_olist<char, int>::DG);
	go.show_olist();
	cout << "vexnum = " << go.vexnum() << endl;
	cout << "arcnum = " << go.arcnum() << endl;
	cout << "DFS : ";
	DFS(go, visit);
	cout << endl;
	
	cout << "DFS1 : ";
	DFS(go, visit, false);
	cout << endl;
	
	cout << "Reverse DFS : ";
	rDFS(go, visit);
	cout << endl;
	
	cout << "BFS : ";
	BFS(go, visit);
	cout << endl;
	
	cout << "kosaraju : ";
	kosaraju(go, visit);

	
	cout << "\n** olist **\n";
	delete vexs;
	delete arcs;
	vexs = a1::instance(9);
	vexs->set_values(B, 9);
	arcs = a2::instance(9, 9);
	arcs->set_values(A, 9 * 9);
	graph_olist<char, int> go1(*vexs,  *arcs, graph_olist<char, int>::DG);
	go1.show_olist();
	cout << "vexnum = " << go1.vexnum() << endl;
	cout << "arcnum = " << go1.arcnum() << endl;
	cout << "DFS : ";
	DFS(go1, visit);
	cout << endl;
	
	cout << "DFS1 : ";
	DFS(go1, visit, false);
	cout << endl;
	
	cout << "Reverse DFS : ";
	rDFS(go1, visit);
	cout << endl;
	
	cout << "Post DFS : ";
	post_DFS(go1, visit);
	cout << endl;
	
	cout << "BFS : ";
	BFS(go1, visit);
	cout << endl;
	
	cout << "kosaraju : ";
	kosaraju(go1, visit);

	return 0;
}
