/** 20210802 21:20, zyj, GuangDong*/
//test.c -- test graph_array.h
#include <iostream>
#include <iomanip>
#include <string>
#include "graph_array.h"

using std::cout;
using std::endl;
typedef array<int, 2> a2;

static int a[]={
	0,1,1,0,
	0,0,0,0,
	0,0,0,1,
	1,0,0,0
};

static char vex[] = {'A', 'B', 'C', 'D'};

int main(int ac, char * av[])
{
	int i, j;
	a2 * a_2d = a2::instance(4, 4);
	if(!a_2d) return 0;
	a_2d->set_values(a, 16);
	cout << "2d :" << endl;
	for(i = 0; i <4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			//a_2d->value(k, i, j);
			cout << std:: setw(2) << std::left << a_2d->at(i, j) << " ";
		}
		cout << endl;
	}

	return 0;
}
