/** 20210409 09:04, zyj, GuangDong */
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include <iostream>
#include <iomanip>
#include "SqList.h"
#include "array.h"
#define MIN(a,b) (((a)<=(b))?(a):(b))

template<typename T = int>
struct triple
{
	typedef T value_type;
	int i, j;/** position*/
	T e;/** value*/
	triple(int mi = 0, int mj = 0, const T & me = 0)
		:i(mi), j(mj), e(me){}
};

template<typename T>
class sparse_matrix : public SqList<triple<T>>
{
	private:
		typedef SqList<triple<T>> base;
		typedef triple<T> item;
	private:
		enum {MAX_SIZE = 12500};
		int _m, _n, _tu;/** rows, cols and non-zero count*/
		sparse_matrix(){}
		//bool construct(int m, int n , array<Item>);
	public:
};
#endif
