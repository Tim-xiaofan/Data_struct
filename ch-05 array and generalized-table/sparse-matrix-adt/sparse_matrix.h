/** 20210409 09:04, zyj, GuangDong */
// sparse_matrix.h -- triple list implement
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include "SqList.h"
#include "array.h"
//#define MIN(a,b) (((a)<=(b))?(a):(b))

template<typename T = int>
struct triple
{
	typedef T value_type;
	int i, j;/** position*/
	T e;/** value*/
	triple(int mi = 0, int mj = 0, const T & me = 0)
		:i(mi), j(mj), e(me){}
	triple & operator=(const triple &) = default;
	template<typename U>
	friend std::ostream & operator<<(std::ostream & os, const triple<U> & trp);
};

template<typename U>
std::ostream & operator<<(std::ostream & os, const triple<U> & trp)
{
	os << "<(" << trp.i <<"," << trp.j << ")" << "," << trp.e << ">";
	return os;
}

template<typename T>/** value type*/
class sparse_matrix : public SqList<triple<T>>
{
	private:
		typedef SqList<triple<T>> base;
	protected:
		typedef triple<T> item;
	private:
		enum {MAX_SIZE = 12500};
		int _m, _n, _tu;/** rows, cols and non-zero elements count*/
	public:
		sparse_matrix(const array<T, 2> & a2, int tu);
		sparse_matrix(int m, int n, int tu)
			:base(tu), _m(m), _n(n), _tu(tu){}
		int tu(void)const{return _tu;}
		static int count_tu(const array<T, 2> & a2);
		void show(void)const;
		/** matrix transpose algorithm*/
		bool transpose(sparse_matrix & N)const;
		bool transposex(sparse_matrix & N)const;
		item & operator[](int pos){return base::operator[](pos);} 
		const item & operator[](int pos)const{return base::operator[](pos);} 
		/** get number of non-zero elements in each column*/
		int get_num(int * num)const;
		/** get postion first non-zero elements in each column*/
		int get_cpot(int * cpot, const int * num)const;
		int rows(void)const{return _m;}
		int cols(void)const{return _n;}
};

/** count number of non-zero elements*/
template<typename T>
int sparse_matrix<T>::
count_tu(const array<T, 2> & a2)
{
	int i, j, k, tu = 0;
	int m = a2.get_bound(1);
	int n = a2.get_bound(2);
	for(i = 0; i < m; ++i)
	  for(j = 0; j < n; ++j)
	  {
		  k = a2.at(i, j);
		  if(k != 0) tu+=1;
	  }
	return tu;
}

template<typename T>
sparse_matrix<T>::
sparse_matrix (const array<T, 2> & a2, int tu):base(tu)
{
	_m = a2.get_bound(1);
	_n = a2.get_bound(2);
	_tu = tu;
	//std::cout << _m << ", " << _n 
	//	<< ", " << _tu << std::endl;

	int i, j, k, pos = 0;
	for(i = 0; i < _m; ++i)
	  for(j = 0; j < _n; ++j)
	  {
		  //a2.value(k, i, j);
		  k = a2.at(i, j);
		  if(k != 0)
			base::operator[](pos++) = item(i, j, k);
	  }
}


template<typename T>
void sparse_matrix<T>:: 
show(void)const
{
	int i;
	for(i = 0; i < _tu; ++i)
	  std::cout << base::operator[](i) << " ";
	std::cout << "\n";
}

/** M(m x n) --> N(n x m)
  * time:O(M.nu * tu)
 **/
template<typename T>
bool sparse_matrix<T>:: 
transpose(sparse_matrix & N)const
{
	/** TODO: to suport that target matrix is matrix self*/
	if(N._m != _n || N._n != _m || N._tu < _tu || &N == this)
	  return false;

	/** get a col in M*/
	int col, pos, pos1 = 0;
	for(col = 0; col < _n; ++col)
	  for(pos = 0; pos < _tu; ++pos)
		if(base::operator[](pos).j == col)
		{
			N[pos1].i = base::operator[](pos).j;
			N[pos1].j = base::operator[](pos).i;
			N[pos1].e = base::operator[](pos).e;
			++pos1;
		}
	return true;
}

/** M(m x n) --> N(n x m)
  * time:O(2 * n + tu)
 **/
template<typename T>
bool sparse_matrix<T>:: 
transposex(sparse_matrix & N)const
{
	/** TODO: to suport that target matrix is matrix self*/
	if(N._m != _n || N._n != _m || N._tu < _tu || &N == this)
	{
		std::cerr << "invalid target matrix\n";
		return false;
	}

	/** FIXME: need to catch the exception of new operator*/
	int *num = new int[_n], *cpot = new int[_n];
	if(get_num(num) == -1 || get_cpot(cpot, num) == -1)
	{
		std::cerr << "cannot get num or cpot\n";
		return false;
	}

	int pos, pos1, col;
	for(pos = 0; pos < _tu; ++pos)
	{
		col = base::operator[](pos).j;
		pos1 = cpot[col];
		N[pos1].i = base::operator[](pos).j; 
		N[pos1].j = base::operator[](pos).i; 
		N[pos1].e = base::operator[](pos).e;
		cpot[col]+=1;
	}
	delete num;
	delete cpot;
	return true;
}
/** 
  * time:O(n)
  * get number of non-zero elements in each column
  * @return -1 for failed, or number of column
  **/
template<typename T>
int sparse_matrix<T>::
get_num(int * num)const
{
	if(num == nullptr)
	{
		std::cerr << "no space to store\n";
		return -1;
	}

	memset(num, 0, _n * sizeof(int));
	int pos;
	for(pos = 0; pos < _tu; ++pos)
	  num[base::operator[](pos).j]+=1;
	return _n;
}

/** time : O(n)*/
template<typename T>
int sparse_matrix<T>::
get_cpot(int * cpot, const int * num)const
{
	if(num == nullptr || cpot == nullptr)
	  return -1;
	int col;
	cpot[0] = 0;
	for(col = 1; col < _n; ++col)
	  cpot[col] = cpot[col - 1] + num[col - 1];
	return _n;
}
#endif
