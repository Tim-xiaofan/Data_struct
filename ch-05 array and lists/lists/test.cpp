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
	"()",
	"e",
	"a,(b,c,d)",
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

	SEP("htlist test0 start");
	htlists<char> htl(inputs[2]);
	//cout << "thl's depth : " << htl.depth() << endl;
	SEP("htlist test0 end");
	cout << endl;

	int i;
	char head[512];
	for(i = 0; i < 4; ++i)
	{
		SEP(i);
		cout << "input " << inputs[i] << " : ";
		istr is(inputs[i]);
		is.de_head(head);
		cout << "head = " << head << "\tremain = " << is.str << endl;
		istr::remove_lr(head);
		cout << "head = " << head << "\tremain = " << is.str << endl;
		SEP(i);
	}
}
