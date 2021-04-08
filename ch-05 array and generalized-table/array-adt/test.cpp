/** 20210407 21:20, zyj, GuangDong*/
//test.c -- test array.h
#include <iostream>
#include <iomanip>
#include <string>

#include "array.h"

#define N 60

int a[N];

int main()
{
	using std::cout;
	using std::endl;
	using std::cin;
	int i, j, x, k;

	for(i = 0; i < N; i++)
	  a[i] = i;

	array<int> * a_1d = array<int>::instance(1, 3);
	a_1d->set_values(a, N);
	cout << "1d :" << endl;
	for(i = 0; i <3; ++i)
	{
		a_1d->value(k, i);
		cout << k << " ";
	}
	cout << endl;

	array<int> * a_2d = array<int>::instance(2, 3, 4);
	a_2d->set_values(a, N);
	cout << "2d :" << endl;
	for(i = 0; i <3; ++i)
	{
		for(j = 0; j < 4; ++j) 
		{
			a_2d->value(k, i, j);
			cout << std:: setw(2) << std::left << k << " ";
		}
		cout << endl;
	}


	array<int> * a_3d = array<int>::instance(3, 3, 4, 5);
	a_3d->set_values(a, N);
	cout << "3d :" << endl;
	for(i = 0; i <3; ++i)
	{
	  for(j = 0; j < 4; ++j) 
	  {
		  for(x = 0; x < 5; ++x) 
		{
			a_3d->value(k, i, j, x);
			cout << std:: setw(2) << std::left << k << " ";
		}
		  cout << endl;
	  }
	  cout << endl;
	}

	return 0;
}
