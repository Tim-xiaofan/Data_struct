/** 20210408 22:15, zyj, GuangDong*/
//test.c -- test symmetric_matrices.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "triangular_matrix.h"

#define N 100

static int a[N];

int main()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::srand;
	using std::rand;
	
	srand(time(NULL));
	int i;
	for(i = 0; i < N; ++i)
	  a[i] = rand() % 100;
	  //a[i] = i + 1;

	triangular_matrix<int> tm(4);
	cout << "down: \n";
	tm.set_values(a, N);
	tm.show();
	
	cout << "up: \n";
	tm.type(triangular_matrix<int>::UP);
	tm.show();

	for(i = 0; i < N; ++i)
	  a[i] = rand() % 100;
	cout << endl;
	triangular_matrix<int> tm1(5, triangular_matrix<int>::UP);
	cout << "up: \n";
	tm1.set_values(a, N);
	tm1.show();
	
	cout << "down: \n";
	tm1.type(triangular_matrix<int>::DOWN);
	tm1.show();
	return 0;
}
