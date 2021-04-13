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

static const char * inputs[4] = {
	"",
	"e",
	"(a,(b,c,d))",
	"((),(e),(a,(b,c,d)))"
};

int main()
{
	arg a1;
	a1.ct = 0;
	a1.vals = (char *)"string";
	cout << a1.vals << endl;
	a1.val = 'c';
	cout << a1.val << endl;
	//cout << a1.vals << endl;

	htlists<char> htl(inputs[3]);
	cout << "thl's depth : " << htl.depth() << endl;

	int i;
	char head[512], tail[512];
	for(i = 0; i < 4; ++i)
	{
		cout << "input " << inputs[i] << " : ";
		istr is(inputs[i]);
		is.get_ht(head, tail);
		cout << "head = " << head << ", tail = " << tail << endl;
		istr::remove_lr(head);
		istr::remove_lr(tail);
		cout << "head = " << head << ", tail = " << tail << endl;
	}
}
