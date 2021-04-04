/** 20210323 22:37, zyj, GuangDong*/
//test.c -- test list.h
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <iterator>

#include "line_edit.h"

#define SIZE 16

int main()
{
	using namespace std;

	line_edit le('#', '@');
	string input;

	input = le.get_line();
	cout << "inupt actually : "<< input << endl;
}
