/** 20210408 20:29, zyj, GuangDong*/
//test.c -- test symmetric_matrices.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "symmetric_matrix.h"

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

	symmetric_matrix<int> sai(4);
	sai.set_values(a, N);
	sai.show();
}
