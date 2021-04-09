/** 20210407 21:13, zyj, GuangDong */
#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <new>

#define MIN(x,y) (((x)<=(y))?(x):(y))

template<typename T, int dim = 1>
class array
{
	private:
		enum{MAX_DIM = 8};
		T * _base;
		int *_bounds, *_constant, _elemtot;
	private:
		bool construct(int b1 , va_list & ap);
		bool locate(va_list & ap, int & off)const;
	public:
		array():_base(nullptr),_bounds(nullptr),_constant(nullptr),_elemtot(0){}
		~array(){delete [] _base; delete[]_constant; delete[]_bounds;}
		static array * instance(int b1, ...);
		bool value(T & t, ...) const;
		bool set_value(const T & t, ...);
		void show_constant(void)const;
		void show_bounds(void)const;
		int get_bound(int mdim)const;
		array & set_values(T * ts, int n);
};

template<typename T, int dim>
bool array<T, dim>::
construct(int b1, va_list & ap)
{
	if(dim <= 0 || dim > MAX_DIM) 
	{
		std::cerr << "invalid dim " << dim << std::endl;
		return false;
	}
	//std::cout <<"dim = " << dim << std::endl;
	try	
	{
		_bounds = new int[dim];
	}
	catch(std::bad_alloc & e)
	{
		std::cerr << "cannot alloc memory fo bounds : " 
			<< e.what() << std::endl;
		return false;
	}

	int i;
	//va_list ap;
	//va_start(ap, dim);/** store dim args in ap*/
	/** read length of each dimension*/
	_bounds[0] = b1;/** fist dimension's length*/
	_elemtot = 1;
	_elemtot *= b1;
	for(i = 1; i < dim; i++)
	{/** remaining*/
		_bounds[i] = va_arg(ap, int);
		if(_bounds[i] <= 0)
		{
			std::cerr << "invalid bound[" << i << "]" << _bounds[i] << std::endl;
			return false;
		}
		_elemtot *= _bounds[i];
	}

	//std::cout << "_elemtot = " << _elemtot << std::endl;
	try
	{
		_base = new T[_elemtot];
	}
	catch(std::exception & e) 
	{
		std::cerr << "cannot alloc memory fo base : "
			<< e.what() << std::endl;
		return false;
	}

	try
	{
		_constant = new int[dim];
	}
	catch(std::bad_alloc & e) 
	{
		std::cerr << "cannot alloc memory fo constant : "
			<< e.what() << std::endl;
		return false;
	}
	_constant[dim - 1] = 1;
	for(i = dim - 2; i >= 0; --i)
	  _constant[i] = _bounds[i + 1] * _constant[i + 1];
	return true;
}


template<typename T, int dim>
bool array<T, dim>::
locate(va_list & ap, int & off)const
{
	off = 0;
	int ind, i;
	for(i = 0; i < dim; i++)
	{
		ind = va_arg(ap, int);
		//std::cout << "ind = " << ind << std::endl;
		if(ind < 0 || ind >= _bounds[i])return false;
		off += ind * _constant[i];
	}
	return true;
}

template<typename T, int dim>
bool array<T, dim>::
value(T & t, ...) const
{
	bool ret = false;
	int off;
	va_list ap;
	va_start(ap, t);
	if((ret = locate(ap, off)))
	  t = _base[off];
	//std::cout << "off = " << off << std::endl;
	va_end(ap);
	return ret;
}

template<typename T, int dim>
bool array<T, dim>::
set_value(const T & t, ...)
{
	bool ret = false;
	int off;
	va_list ap;
	va_start(ap, t);
	if((ret = locate(ap, off)))
	_base[off] = t;
	//std::cout << "off = " << off << std::endl;
	va_end(ap);
	return ret;
}

template<typename T, int dim>
array<T, dim>* array<T, dim>::
instance(int d1, ...)
{
	array * ret = new array;
	va_list ap;
	va_start(ap, d1);/** store dim args in ap*/
	if(ret == nullptr || ret->construct(d1, ap) == false)
	{
		delete ret;
		ret = nullptr;
	}
	va_end(ap);/** free memory source*/
	return ret;
}

template<typename T, int dim>
void array<T, dim>::
show_constant(void)const
{
	int i;
	for(i = 0; i < dim; i++)
	  std::cout << _constant[i] << " ";
	std::cout << "\n";
}


template<typename T, int dim>
void array<T, dim>:: 
show_bounds(void)const
{
	int i;
	for(i = 0; i < dim; i++)
	  std::cout << _bounds[i] << " ";
	std::cout << "\n";
}

template<typename T, int dim>
array<T, dim>& array<T, dim>:: 
set_values(T * ts, int n)
{
	int min = MIN(n, _elemtot), i;

	for(i = 0; i < min; i++)
	  _base[i] = ts[i];

	//std::cout << "after setting:\n";
	//for(i = 0; i < min; i++)
	//  _base[i] = ts[i];
	return *this;
}

/**
  * get dim length
  * @param mdim start from 1
 **/
template<typename T, int dim>
int array<T, dim>::
get_bound(int mdim)const
{
	int ret;
	if(mdim <= 0 || mdim > MAX_DIM)
	{
		std::cerr << "invalid dim " << mdim << std::endl;
		ret = -1;
	}
	else
		ret = _bounds[mdim - 1];
	return ret;
}
#endif
