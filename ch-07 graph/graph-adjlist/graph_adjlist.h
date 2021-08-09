/** 20210809 12:50, zyj, GuangDong */
#ifndef _GRAPH_ADJLIST_H
#define _GRAPH_ADJLIST_H
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

template <typename T, typename U>
class graph_adjlist
{
	private:
		template <typename U1>
		struct arcnode
		{
			int adjvex;
			struct arcnode * nextarc;
			U1 weigth;
		};
		typedef arcnode<U> node;
		typedef enum {DG, DN, UDG, UDN} graph_kind;
	private:
		int _nb_vex, _nb_arc;
		graph_kind _kind;
		T * _vex;
		node *_adjlist;
};

#endif
