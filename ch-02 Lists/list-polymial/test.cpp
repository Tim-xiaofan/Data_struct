/** 20210323 22:37, zyj, GuangDong*/
//test.c -- test list.h
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iterator>

#include "Polymial.h"
#define SIZE 16

typedef Item<float, int> item;
typedef Polymial<item> P;

static item is[4] = {
	{1, 0},
	{3, 2},
	{2, 1},
	{4, 3}};

int main()
{
	using namespace std;
	P p(is, 4);
	p.show();
	P::input_iterator it;
	for(it = p.begin(); it != p.end(); ++it)
	  cout << *it << " ";
	cout << endl;
}
