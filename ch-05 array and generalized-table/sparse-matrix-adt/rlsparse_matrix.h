/** 20210410 15:49, zyj, GuangDong */
// rlsparse_matrix.h --  row logical triple list implement
#ifndef RLSPARSE_MATRIX_H
#define RLSPARSE_MATRIX_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include "SqList.h"
#include "array.h"
#include "sparse_matrix.h"

template<typename T>/** value type*/
class rlsparse_matrix : public sparse_matrix<T>
{
	private:
		typedef sparse_matrix<T> base;
		typedef typename base::item item;
	public:
		typedef T value_type;
	private:
		int * _rpos;
	public:
		~rlsparse_matrix(){delete [] _rpos;};
		rlsparse_matrix(const array<T, 2> & a2, int tu);
		/** FIXME: need to handle new exception*/
		rlsparse_matrix(int m, int n, int tu):base(m, n, tu){_rpos = new int[m];}
		void show_rpos(void)const;
		int row_first(int row)const{return _rpos[row];}
		int row_last(int row)const;
};

template<typename T>
rlsparse_matrix<T>::
rlsparse_matrix(const array<T, 2> & a2, int tu):base(a2, tu)
{
	/** FIXME: need to handle new exception*/
	int *num, pos, rows = base::rows();
	_rpos =new int[rows];
	num = new int[rows];
	memset(num, 0, rows);
	for(pos = 0; pos < base::tu(); ++pos)
	  num[base::operator[](pos).i] += 1;
	//for(pos = 0; pos < rows; ++pos)
	//  std::cout << num[pos] << " " ;
	//std::cout << "\n";

	_rpos[0] = 0;
	for(pos = 1; pos < rows; ++pos)
	  _rpos[pos] = _rpos[pos-1] + num[pos-1];
	delete num;
}

template<typename T>
void rlsparse_matrix<T>::
show_rpos(void)const
{
	int i, rows = base::rows();
	for(i = 0; i < rows; i++)
	  std::cout << _rpos[i] << " ";
	std::cout << std::endl;
}

/** get last position of row*/
template<typename T>
int rlsparse_matrix<T>::
row_last(int row)const
{
	int ret;
	if(row == base::rows() - 1)
	  ret = base::tu();
	else ret = row_first(row + 1);
	return ret;
}
#endif
