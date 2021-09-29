/** 20210410 17:38, zyj, GuangDong*/
//muti_smatrix.cpp -- test sparse matrix mutiplication
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "sparse_matrix.h"
#include "rlsparse_matrix.h"

//#define N 100

//static int a[N];
//static int b[6][7]={
//	{0, 12,9, 0, 0,0,0},
//	{0, 0, 0, 0, 0,0,0},
//	{-3,0, 0, 0, 0,14,0},
//	{0, 0, 24,0, 0,0,0},
//	{0, 18,0, 0, 0,0,0},
//	{15, 0,0, -7,0,0,0}
//};

static int c[3][4]{
	{3,4,9,5},
	{0,-1,10,-5},
	{2,7,0,6}
};

static int d[4][2]
{
	{1,2},
	{1,3},
	{-2,4},
	{5,9},
};

typedef sparse_matrix<int> matrix_i;
typedef rlsparse_matrix<int> rlmatrix_i;


template<typename SMatrix, typename Array>
bool muti_smatrix(const SMatrix & M, const SMatrix & N, Array & a2);

static void a2_show(const array<int, 2> & a2);

int main()
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::srand;
	using std::rand;

	int i, j, tu;

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

	tu = rlmatrix_i::count_tu(*a21);
	rlmatrix_i M(*a21, tu);

	tu = rlmatrix_i::count_tu(*a22);
	rlmatrix_i N(*a22, tu);

	cout << "-----------muti_smatrix-----------\n";
	array<int, 2> * a2 = array<int, 2>::instance(M.rows(), N.cols());
	muti_smatrix(M, N, *a2);
	a2_show(*a2);
	return 0;
}

/** time: O(m1 * n2 + tu1 * tu2 / m2)*/
template<typename SMatrix, typename Array>
bool muti_smatrix(const SMatrix & M, const SMatrix & N, Array & a2)
{
	int m1, n1, m2, n2, mrow, nrow, *ctemp;
	m1 = M.rows();
	n1 = M.cols();
	m2 = N.rows();
	n2 = N.cols();

	if(n1 != m2)
	  return false;
	if(M.tu() * N.tu() == 0)
	  return true;

	ctemp = new int[n2];//Q[c][j]的一部分
	for(mrow = 0; mrow < m1; ++mrow)
	{
		int mfirst, mlast, nfirst, nlast, mpos, npos, ccol;

		/** initialize */
		for(ccol = 0; ccol < n2; ++ccol)
		  ctemp[ccol] = 0;
		mfirst = M.row_first(mrow);//M当前行的第一个元素
		mlast = M.row_last(mrow);
		std::cout << "-----------row "<< mrow <<"-----------\n";
		for(mpos = mfirst; mpos < mlast; ++mpos)//处理M的mrow一行
		{
			nrow = M[mpos].j;/** get row of coorresponding in N*/
			nfirst = N.row_first(nrow);//N当前行的第一个元素
			nlast = N.row_last(nrow);
			//std::cout << "N : [" << nfirst << ", "<< nlast << ")\n";
			for(npos = nfirst; npos < nlast; ++npos)
			{
				/** */
				std::cout << "{" << M[mpos] << " * " << N[npos] << "} "; 
				/** 设置累加器ctemp[N的列值]保存Q矩阵每行的值，结束后将ctemp中的值赋给C矩阵*/
				ctemp[N[npos].j]+= M[mpos].e * N[npos].e;
			}
			std::cout << "\n";
		}/** get non-zero elemets of Q's mrow-th row*/
		for(ccol = 0; ccol < n2; ++ccol)
		{
			//std::cout << triple<int>(mrow, ccol, ctemp[ccol]) << " ";
			a2.set_value(ctemp[ccol], mrow, ccol);
		}
		a2_show(a2);
		std::cout << "-----------row "<< mrow <<"-----------\n";
	}
	delete [] ctemp;
	return true;
}

static void 
a2_show(const array<int, 2> & a2)
{
	int i, j, k;
	for(i = 0; i < a2.get_bound(1); ++i)
	{
		for(j = 0; j < a2.get_bound(2); ++j)
		{
			//a2.value(k, i, j);
			k = a2.at(i, j);
			std::cout << k << " ";
		}
		std::cout << "\n";
	}
}
