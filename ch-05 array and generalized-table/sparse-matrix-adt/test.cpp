/** 20210409 09:06, zyj, GuangDong*/
//test.c -- test sparse_matrix.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "sparse_matrix.h"

//#define N 100

//static int a[N];
static int b[6][7]={
	{0, 12,9, 0, 0,0,0},
	{0, 0, 0, 0, 0,0,0},
	{-3,0, 0, 0, 0,14,0},
	{0, 0, 24,0, 0,0,0},
	{0, 18,0, 0, 0,0,0},
	{15, 0,0, -7,0,0,0}
};

typedef sparse_matrix<int> matrix_i;

int main()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::srand;
	using std::rand;

	int i, j, tu;

	array<int, 2> * a2 = array<int, 2>::instance(6, 7);
	if(!a2) return 0;
	for(i = 0; i <6; ++i)
	  for(j = 0; j < 7; ++j)
		a2->set_value(b[i][j], i, j);
	tu = matrix_i::count_tu(*a2);

	matrix_i M(*a2, tu);
	M.show();

	/** test transpose algorithm one*/
	matrix_i N(7, 6, tu);
	if(M.transpose(N))
	  N.show();

	/** test transpose algorithm two*/
	int num[7], cpot[7], cols;
	cols = M.get_num(num);
	for(i = 0; i < cols; ++i)
	  cout << num[i] << " ";
	cout << endl;

	cols = M.get_cpot(cpot, num);
	for(i = 0; i < cols; ++i)
	  cout << cpot[i] << " ";
	cout << endl;

	if(M.transposex(N))
	  N.show();
	return 0;
}
