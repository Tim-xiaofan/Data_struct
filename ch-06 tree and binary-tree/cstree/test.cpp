/** 20210813 09:28, zyj, GuangDong*/
//test.c -- test cstree.h
#include <iostream>
#include <iomanip>
#include <string>
#include "cstree.h"

using std::cout;
using std::cin;
using std::endl;

typedef array<int, 2> a2;
typedef array<char, 1> a1;

static int a[] = {
//  0 1 2 3 4 5 6 7 8 9 a b c
	0,1,1,0,0,1,0,0,0,0,0,1,0, //0
	1,0,0,0,0,0,0,0,0,0,0,0,1, //1
	1,0,0,0,0,0,0,0,0,0,0,0,0, //2
	0,0,0,0,1,0,0,0,0,0,0,0,0, //3
	0,0,0,1,0,0,0,0,0,0,0,0,0, //4
	1,0,0,0,0,0,0,0,0,0,0,0,0, //5
	0,0,0,0,0,0,0,1,1,0,1,0,0, //6
	0,0,0,0,0,0,1,0,0,0,1,0,0, //7
	0,0,0,0,0,0,1,0,0,0,0,0,0, //8
	0,0,0,0,0,0,0,0,0,0,0,1,1, //9
	0,0,0,0,0,0,1,1,0,0,0,0,0, //a
	1,0,0,0,0,0,0,0,0,1,0,0,1, //b
	0,1,0,0,0,0,0,0,0,1,0,1,0, //c
};

static char b[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};

int main(int ac, char *av[])
{
	a1 *vexs;
	a2 *arcs;
	vexs = a1::instance(13);
	vexs->set_values(b, 13);
	arcs = a2::instance(13, 13);
	arcs->set_values(a, 13 * 13);
	graph_AML<char, int> 
        gaml(*vexs,  *arcs, graph_AML<char, int>::UDG);
	//gaml.show_AML();
	//cout << "numvex = " << gaml.vexnum() << endl;
	//cout << "numarc = " << gaml.arcnum() << endl;

	cstree<char> tree(gaml);
	tree.levelorder_traverse(show<char>);
	return 0;
}
