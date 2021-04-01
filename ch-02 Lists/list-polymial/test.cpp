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
	{7, 0},
	{3, 1},
	{9, 8},
	{5, 17}};

static item is1[3] = {
	{8, 1},
	{22, 7},
	{-9, 8}};

int main()
{
	using namespace std;
	P p(is, 4), p1(is1, 3), p2;
	p.show();
	p1.show();
	p2 = p1 + p;
	cout << p2.size() << endl;
	cout << p2.length() << endl;

	cout << "p + p1 : ";
	p2.show();
}
