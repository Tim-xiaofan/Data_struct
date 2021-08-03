/** 20210802 21:04, zyj, GuangDong */
#ifndef _GRAPH_ARRAY_H
#define _GRAPH_ARRAY_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <new>
#include "array.h"
using std::endl;
using std::cout;

/** maybe weigth is typename*/
template<typename T, typename U = int>
class graph_array
{
	private:
		typedef array<T, 1> a1;
		typedef array<U, 2> a2;
	public:
		typedef enum {DG, DN, UDG, UDN} graph_kind;
	private:
		int _nb_vex, _nb_arc;
		graph_kind _kind;
		a1 *_vexs;
		a2 *_arcs;
	public:
		graph_array(const a1 & vex, const a2 & arcs, graph_kind kind);
		~graph_array(){delete _vexs; delete _arcs;}
		template<typename V, int dim = 1>
		static void show_array(const array<V, dim> & a);
		const char * kind_str(void) const;
		graph_kind kind(void) const {return _kind;}
	private:
		void UDG_create(const a2 & arcs);
		void UDN_create(const a2 & arcs);
};

template<typename T, typename U>
graph_array<T, U>::
graph_array(const a1 & vexs, const a2 & arcs, graph_kind kind)
{
	_nb_vex = vexs.get_bound(1);
	cout << "_nb_vex = " << _nb_vex << endl;
	_vexs = a1::instance(vexs);
	cout << "_vexs :\n";
	show_array(*_vexs);
	_kind = kind;
	switch(kind)
	{
		case DG:
			break;
		case DN:
			break;
		case UDG:
			UDG_create(arcs);
			break;
		case UDN:
			UDN_create(arcs);
			break;
		default:;
	}
}

template<typename T, typename U>
void graph_array<T, U>::
UDG_create(const a2 & arcs)
{
	int i, j;
	_nb_arc = 0;
	for(i = 0; i < _nb_vex; ++i)
	  for(j = 0; j < _nb_vex; ++j)
		if(arcs.at(i, j) == 1) _nb_arc++;
	cout << "_nb_arc = " << _nb_arc << endl;
	_arcs = a2::instance(arcs);
	cout << "_arcs :\n";
	show_array(*_arcs);
}

template<typename T, typename U>
void graph_array<T, U>::
UDN_create(const a2 & arcs)
{
	int i, j;
	_nb_arc = 0;
	for(i = 0; i < _nb_vex; ++i)
	  for(j = 0; j < _nb_vex; ++j)
		if(arcs.at(i, j) == 1) _nb_arc++;
	cout << "_nb_arc = " << _nb_arc << endl;
	_arcs = a2::instance(arcs);
	cout << "_arcs :\n";
	show_array(*_arcs);
}

template<typename T, typename U>
template<typename V, int dim>
void graph_array<T, U>::
show_array(const array<V, dim> & a)
{
	int i, j;
	if(dim == 1)
	{
		for(i = 0; i < a.get_bound(1); ++i)
		  cout << a.at(i) << " ";
		cout << endl;
	}
	else
	{
		for(i = 0; i < a.get_bound(1); ++i)
		{
			for(j = 0; j < a.get_bound(2); ++j)
			  cout << a.at(i, j) << " ";
			cout << endl;
		}
	}
}
		
template<typename T, typename U>
const char *  graph_array<T, U>::
kind_str(void) const
{
	switch(_kind)
	{
		case DG: return "DG";
		case DN: return "DN";
		case UDG: return "UDG";
		case UDN: return "UDN";
		default: return "UNKOWN";
	}
}
#endif
