/** 20210408 20:35, zyj, GuangDong */
#ifndef SYMMETRIC_MATRIX_H
#define SYMMETRIC_MATRIX_H
#include <iostream>
#include <iomanip>

#define MIN(a,b) (((a)<=(b))?(a):(b))

template<typename Item>
class symmetric_matrix
{
	private:
		Item * _base;
		int _size, _n;
		static int map(int i, int j);
	public:
		~symmetric_matrix(){delete [] _base;}
		symmetric_matrix(int n){_size = (n + 1) *n / 2; _base = new Item[_size];  _n = n;}
		Item & at(int i, int j){return _base[map(i, j)]; }
		const Item & at(int i, int j) const{return _base[map(i, j)];}
		void set_values(const Item * is, int ct);
		void show(void)const;
};

template<typename Item>
int symmetric_matrix<Item>::
map(int i, int j)
{
	/** start from 0*/
	int k = 0;
	if(i >= j)
	  k = (i + 1) * i / 2 + j;
	else
	  k = (j + 1) *j / 2 + i;
	return k;
}

template<typename Item>
void symmetric_matrix<Item>::
set_values(const Item * is, int ct)
{
	int min = MIN(ct, _size), i;
	for(i = 0; i < min; i++)
	  _base[i] = is[i];
}


template<typename Item>
void symmetric_matrix<Item>::
show(void)const
{
	int i, j;
	for(i = 0; i < _n; i++)
	{
	  for(j = 0; j < _n; j++)
		std::cout << std::setw(2) 
			<< at(i, j) << " ";
	  std::cout << std::endl;
	}
}
#endif
