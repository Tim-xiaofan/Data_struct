/** 20210802 21:04, zyj, GuangDong */
#ifndef _GRAPH_ARRAY_H
#define _GRAPH_ARRAY_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <new>
#include "array.h"

/** maybe weigth is typename*/
template<typename T>
class graph_array
{
	private:
		typedef array<T, 2> a2;
		typedef array<T, 1> a1;
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
	private:
		void DG_create(const a2 & arcs);
};

template<typename T>
graph_array<T>::
graph_array(const a1 & vexs, const a2 & arcs, graph_kind kind)
{
	_nb_vex = vexs.get_bound(0);
	_vexs = a1::instance(vexs);
	switch(kind)
	{
		case DG:
			break;
		case DN:
			break;
		case UDG:
			break;
		case UDN:
			break;
		default:;
	}
}
#endif
