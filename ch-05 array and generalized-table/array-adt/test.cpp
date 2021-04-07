/** 20210407 21:20, zyj, GuangDong*/
//test.c -- test array.h
#include <iostream>
#include <string>

#include "array.h"

int main()
{
	using std::cout;
	using std::endl;

	array<int> * a_2d = array<int>::instance(2, 3, 4);
	a_2d->show_constant();

	return 0;
}
