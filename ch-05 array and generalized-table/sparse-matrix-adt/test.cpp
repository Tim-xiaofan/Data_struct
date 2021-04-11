/** 20210409 09:06, zyj, GuangDong*/
//test.c -- test sparse_matrix.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "sparse_matrix.h"
#include "rlsparse_matrix.h"
#include "crosslist_smatrix.h"


#define SEPARATE(info) std::cout << "-----------" << info << "-----------\n"

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

static int c[3][4]{
	{3,0,0,5},
	{0,-1,0,0},
	{2,0,0,0}
};

static int d[4][2]
{
	{0,2},
	{1,0},
	{-2,4},
	{0,0},
};

typedef sparse_matrix<int> matrix_i;
typedef rlsparse_matrix<int> rlmatrix_i;

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

	array<int, 2> * a21 = array<int, 2>::instance(3, 4);
	if(!a21) return 0;
	for(i = 0; i <3; ++i)
	  for(j = 0; j < 4; ++j)
		a21->set_value(c[i][j], i, j);

	array<int, 2> * a22 = array<int, 2>::instance(4, 2);
	if(!a22) return 0;
	for(i = 0; i <4; ++i)
	  for(j = 0; j < 2; ++j)
		a22->set_value(d[i][j], i, j);

	cout << "-----------test sparse_matrix-----------\n";
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

	cout << "\n\n-----------test rlsparse_matrix-----------\n";
	tu = rlmatrix_i::count_tu(*a22);
	rlmatrix_i M1(*a22, tu);
	M1.show();
	cout << "rpos : ";
	M1.show_rpos();

	SEPARATE("test crosslist_smatrix");
	crosslist<int> cl(3, 4);
	crosslist<int> cl1(*a2);
	//cout << "show_rlist: \n";
	//cl1.show_rlist();
	//cout << "show_right: \n";
	//cl1.show_right();
	return 0;
}
