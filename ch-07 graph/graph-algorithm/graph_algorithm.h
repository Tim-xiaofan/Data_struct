/** 20210811 22:00, zyj, GuangDong */
#ifndef _GRAPHA_ALGRITHM_H
#define _GRAPHA_ALGRITHM_H
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
#include "linkqueue.h"
#include "sqstack.h"

using std::endl;
using std::cout;
using std::cerr;

template <typename T, typename U, typename OP>
void DFS(const graph_AML<T, U> & G, const OP & op, bool recursion = true)
{
	int v, w, u;
	bool visited[G.vexnum()] = {false};
	sqstack<int> stack(G.vexnum());
	typedef typename graph_AML<T, U>::anode node;
	const node * p;

	if(recursion)
	{
	  for(v = 0; v < G.vexnum(); ++v)
		if(!visited[v]) DFS(G, v, visited, op);
	}
	else
	{
		for(v = 0; v < G.vexnum(); ++v)
		  if(!visited[v])
		  {
			  op(v);
			  visited[v] = true;
			  stack.push(v);
			  while(!stack.is_empty())
			  {
				  stack.pop(w);
				  for(p = G.first(w); p; p = p->next(w))// Is there any adjacency vex for w?
				  {
					  u = p->adj(w);
					  if(!visited[u])
					  {
						  op(u);
						  visited[u] = true;
						  stack.push(u);
						  break;//deep
					  }
				  }
			  }
		  }
	}
}

template <typename T, typename U, typename OP>
void DFS(const graph_AML<T, U> & G, int v, bool * visited, const OP & op)
{
	int w;
	typedef typename graph_AML<T, U>::anode node;
	const node * p;

	op(v);
	visited[v] = true;
	for(p = G.first(v); p; p=p->next(v))
	{
		w = p->adj(v);
		if(!visited[w]) DFS(G, w, visited, op);
	}
}

template <typename T, typename U, typename OP>
void BFS(graph_AML<T, U> & G, const OP & op)
{
	typedef typename graph_AML<T, U>::anode node;
	int v, w, u;
	bool visited[G.vexnum()] = {false};
	linkqueue<int> q(G.vexnum());
	const node * p;

	for(v = 0; v < G.vexnum(); ++v)
	  if(!visited[v])
	  {
		  q.enqueue(v);
		  op(v);
		  visited[v] = true;
		  while(!q.is_empty())
		  {
			  q.dequeue(w);//"先被访问的顶点的邻接点"先于"后被访问的顶点的邻接点"被访问
			  for(p = G.first(w); p; p = p->next(w))
			  {
				  u = p->adj(w);
				  if(!visited[u])
				  {
					  op(u);
					  visited[u] = true;
					  q.enqueue(u);
				  }
			  }
		  }//while
	  }
}//BFS
#endif
