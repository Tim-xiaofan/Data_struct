/** 20210408 21:54, zyj, GuangDong */
#ifndef TRIANGULAR_MATRIX_H
#define TRIANGULAR_MATRIX_H
#include <iostream>
#include <iomanip>

#define MIN(a,b) (((a)<=(b))?(a):(b))

template<typename Item>
class triangular_matrix
{
	private:
		Item * _base, _c;
		int _size, _n, _type;
		int map(int i, int j) const;
	public:
		enum{UP = 0, DOWN = 1};
		~triangular_matrix(){delete [] _base;}
		triangular_matrix(int n, int type = DOWN, const Item & c = 0);
		Item & at(int i, int j);
		const Item & at(int i, int j) const;
		void set_values(const Item * is, int ct);
		void show(void)const;
		int type(void)const{return type;}
		bool type(int new_type);
};

template<typename Item>
triangular_matrix<Item>::
triangular_matrix(int n, int type, const Item & c)
{
	_size = (n + 1) *n / 2 + 1;
	_base = new Item[_size]; 
	_n = n;
	_c = c;
	_base[_size - 1] = c;
	if(type != UP && type != DOWN)
	  _type = DOWN;
	else
	  _type = type;
}

template<typename Item>
Item & triangular_matrix<Item>::
at(int i, int j)
{
	if(_type == DOWN)
	 return _base[map(i, j)]; 
	else
	 return _base[map(j, i)]; 
}

template<typename Item>
const Item & triangular_matrix<Item>::
at(int i, int j) const
{
	if(_type == DOWN)
	 return _base[map(i, j)]; 
	else
	 return _base[map(j, i)]; 
}

template<typename Item>
int triangular_matrix<Item>::
map(int i, int j) const
{
	/** start from 0 and down*/
	int k = 0;
	if(i >= j)
	  k = (i + 1) * i / 2 + j;
	else
	  k = _size - 1;
	return k;
}

template<typename Item>
void triangular_matrix<Item>::
set_values(const Item * is, int ct)
{
	int min = MIN(ct, _size - 1), i;
	for(i = 0; i < min; i++)
	  _base[i] = is[i];
}

template<typename Item>
void triangular_matrix<Item>::
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


template<typename Item>
bool triangular_matrix<Item>::
type(int new_type)
{
	if(new_type != UP && new_type != DOWN)
	  return false;
	_type = new_type;
	return true;
}
#endif
