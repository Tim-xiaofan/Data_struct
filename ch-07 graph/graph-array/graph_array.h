/** 20210802 21:04, zyj, GuangDong */
#ifndef _GRAPH_ARRAY_H
#define _GRAPH_ARRAY_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <climits>
#include <cfloat>
#include <new>
#include <typeinfo>
#include "array.h"
using std::endl;
using std::cout;
using std::cerr;

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
		int get_degree(int v) const;
		void show_degree(void) const;
		void show_iodegree(void) const;
		int get_odegree(int v) const;
		int get_idegree(int v) const;
	private:
		void create(const a2 & arcs);
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
	create(arcs);
}

template<typename T, typename U>
void graph_array<T, U>::
create(const a2 & arcs)
{
	int i, j;
	_nb_arc = 0;
	for(i = 0; i < _nb_vex; ++i)
	  for(j = 0; j < _nb_vex; ++j)
		if(arcs.at(i, j) != 0) _nb_arc++;
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
		  cout << std::setw(2) << a.at(i) << " ";
		cout << endl;
	}
	else
	{
		for(i = 0; i < a.get_bound(1); ++i)
		{
			for(j = 0; j < a.get_bound(2); ++j)
			  cout << std::setw(2)<< a.at(i, j) << " ";
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

template<typename T, typename U>
int graph_array<T, U>::
get_degree(int v) const
{
	int j, d = 0;
	if(_kind != UDN && _kind != UDG) return -1;
	for(j = 0; j < _nb_vex; ++j)
	  if(_arcs->at(v, j) != 0) d++;
	return d;
}

template<typename T, typename U>
int graph_array<T, U>::
get_odegree(int v) const
{
	int j, d = 0;
	if(_kind != DN && _kind != DG) 
	{
		cerr << "Not direct\n";
		return -1;
	}
	for(j = 0; j < _nb_vex; ++j)
	  if(_arcs->at(v, j) != 0) d++;
	return d;
}

template<typename T, typename U>
int graph_array<T, U>::
get_idegree(int v) const
{
	int j, d = 0;
	if(_kind != DN && _kind != DG) 
	{
		cerr << "Not direct\n";
		return -1;
	}
	for(j = 0; j < _nb_vex; ++j)
	  if(_arcs->at(j, v) != 0) d++;
	return d;
}

template<typename T, typename U>
void graph_array<T, U>::
show_degree(void) const
{
	int i;
	for(i = 0; i < _nb_vex; ++i)
	{
		cout << _vexs->at(i) << " : ";
		cout << get_degree(i) << endl;
	}
}

template<typename T, typename U>
void graph_array<T, U>::
show_iodegree(void) const
{
	int i;
	for(i = 0; i < _nb_vex; ++i)
	{
		cout << _vexs->at(i) << " : ";
		cout << "idgress = "<< get_idegree(i) 
			<< ", odgress = "<< get_odegree(i) << endl;
	}
}
#endif
