/** 20210409 09:04, zyj, GuangDong */
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include <iostream>
#include <iomanip>
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
		bool transpose(sparse_matrix & N)const;
		item & operator[](int pos){return base::operator[](pos);} 
		const item & operator[](int pos)const{return base::operator[](pos);} 
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
		  a2.value(k, i, j);
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
	std::cout << _m << ", " << _n 
		<< ", " << _tu << std::endl;

	int i, j, k, pos = 0;
	for(i = 0; i < _m; ++i)
	  for(j = 0; j < _n; ++j)
	  {
		  a2.value(k, i, j);
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
#endif
