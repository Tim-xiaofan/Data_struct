/** 20210412 20:38, zyj, GuangDong*/
//test.c -- test lists.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
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

#define N 9

static const char * inputs[N] = {
	"", /** invalid*/
	"x",/** invalid*/
	"()",
	"(e)",
	"(a,b,c,d,e)",
	"(a,(b,c,d))",
	"((),(e),(a,(b,c,d)))",
	"((),(e),(a,(b,c,d,(h,i,(j)))),f,g,())",
	"((),(e),(a,(b,c,d,(h,i,(j,((k)))))),f,g,())"
};

int main()
{
	//using std::type_info;
	//arg a1;
	//a1.ct = 0;
	//a1.vals = (char *)"string";
	//cout << a1.vals << endl;
	//a1.val = 'c';
	//cout << a1.val << endl;
	////cout << a1.vals << endl;
    //cout<<typeid(int).name() <<" | " <<typeid(int).hash_code() <<endl;
    //cout<<typeid(char).name() <<" | " <<typeid(char).hash_code() <<endl;
	//int j;
	//if(typeid(j) == typeid(int))
	//  cout << "j is an integer\n";

	SEP("htlist test0 start");
	int i;
	for(i = 0; i < N; i++)
	{
		htlists<char> htl(inputs[i]);
		cout <<"\"" <<inputs[i] <<"\"'s depth : " << htl.depth() << ", lists = ";
		htl.show();
	}
	SEP("htlist test0 end");
	cout << endl;

	//int i;
	//char head[512];
	//for(i = 0; i < 4; ++i)
	//{
	//	SEP(i);
	//	cout << "input " << inputs[i] << " : ";
	//	istr is(inputs[i]);
	//	is.de_head(head);
	//	cout << "head = " << head << "\tremain = " << is.str << endl;
	//	istr::remove_lr(head);
	//	cout << "head = " << head << "\tremain = " << is.str << endl;
	//	SEP(i);
	//}
}
