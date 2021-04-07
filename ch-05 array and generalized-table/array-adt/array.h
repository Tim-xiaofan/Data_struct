/** 20210407 21:13, zyj, GuangDong */
#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <new>
template<typename T>
class array
{
	private:
		enum{MAX_DIM = 8};
		T * _base;
		int _dim, *_bounds, *_constant;
	private:
		array(){}
		bool construct(int dim , va_list & ap);
	public:
		~array(){delete [] _base;}
		static array * instance(int dim, ...);
		void show_constant(void)const;
};

template<typename T>
bool array<T>::
construct(int dim, va_list & ap)
{
	if(dim <= 0 || dim > MAX_DIM) 
	{
		std::cerr << "invalid dim " << dim << std::endl;
		return false;
	}
	_dim = dim;
	std::cout <<"dim = " << dim << std::endl;
	_bounds = new(std::nothrow) int[dim];
	if(!_bounds) 
	{
		std::cerr << "cannot alloc memory fo _bounds\n";
		return false;
	}

	int elemtot = 1, i;
	//va_list ap;
	//va_start(ap, dim);/** store dim args in ap*/
	/** read length of each dimension*/
	for(i = 0; i < dim; i++)
	{
		_bounds[i] = va_arg(ap, int);
		if(_bounds[i] <= 0)
		{
			std::cerr << "invalid bound[" << i << "]" << _bounds[i] << std::endl;
			return false;
		}
		elemtot *= _bounds[i];
	}
	va_end(ap);/** free memory source*/

	std::cout << "elemtot = " << elemtot << std::endl;
	_base = new(std::nothrow) T[elemtot];
	if(!_base) 
	{
		std::cerr << "cannot alloc memory fo base\n";
		return false;
	}

	_constant = new(std::nothrow) int[dim];
	if(!_constant) 
	{
		std::cerr << "cannot alloc memory fo constant\n";
		return false;
	}
	_constant[dim - 1] = sizeof(T);
	for(i = dim - 2; i > 0; --i)
	  _constant[i] = _bounds[i + 1] * _constant[i + 1];
	return true;
}

template<typename T>
array<T>* array<T>::
instance(int dim, ...)
{
	array * ret = new array;
	va_list ap;
	va_start(ap, dim);/** store dim args in ap*/
	if(ret == nullptr || ret->construct(dim, ap) == false)
	{
		delete ret;
		ret = nullptr;
	}
	return ret;
}

template<typename T>
void array<T>::
show_constant(void)const
{
	int i;
	for(i = 0; i < _dim; i++)
	  std::cout << _constant[i] << " ";
	std::cout << "\n";
}
#endif
