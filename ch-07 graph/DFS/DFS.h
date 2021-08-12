/** 20210811 22:00, zyj, GuangDong */
#ifndef _DFS_H
#define _DFS_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <climits>
#include <cfloat>
#include <new>
#include <typeinfo>
#include "array.h"
#include "List.h"
#include "graph_AML.h"

using std::endl;
using std::cout;
using std::cerr;

template <typename T, typename U, typename OP>
void DFS(graph_AML<T, U> & G, const OP & op)
{
	int v;

	for(v = 0; v < G.vexnum(); ++v)
	  if(!G.is_marked(v)) DFS(G, v, op);
}

template <typename T, typename U, typename OP>
void DFS(graph_AML<T, U> & G, int v, const OP & op)
{
	int w;
	typedef typename graph_AML<T, U>::anode node;
	node * p;
	op(v);
	G.markup(v);
	for(p = G.first(v); p; p=p->next(v))
	{
		w = p->adj(v);
		if(!G.is_marked(w)) DFS(G, w, op);
	}
}

#endif
