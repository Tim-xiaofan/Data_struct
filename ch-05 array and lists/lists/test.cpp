/** 20210412 20:38, zyj, GuangDong*/
//test.c -- test lists.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include "lists.h"

using std::cout;
using std::endl;

struct arg{
	int ct;
	union{
		char val;
		char *vals;
	};
};

int main()
{
	arg a1;
	a1.ct = 0;
	a1.vals = (char *)"string";
	cout << a1.vals << endl;
	a1.val = 'c';
	cout << a1.val << endl;
	cout << a1.vals << endl;

	htlists<char> htl;
	cout << "thl's depth : " << htl.depth() << endl;
}
