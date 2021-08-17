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
#include <cstring>
#include "array.h"
#include "List.h"
#include "graph_AML.h"
#include "linkqueue.h"
#include "sqqueue.h"

using std::endl;
using std::cout;
using std::cerr;

#define MAX_NB_VEX 64

template <typename Graph, typename OP>
void DFS(const Graph & G, const OP & op, bool recursion = true)
{
	int v, w, u;
	bool visited[64] = {false};
	sqstack<int> stack(G.vexnum());
	typedef typename Graph::anode node;
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

template <typename Graph, typename OP>
void DFS(const Graph & G, int v, bool * visited, OP & op)
{
	int w;
	typedef typename Graph::anode node;
	const node * p;

	op(v);
	visited[v] = true;
	for(p = G.first(v); p; p=p->next(v))
	{
		w = p->adj(v);
		if(!visited[w]) DFS(G, w, visited, op);
	}
}

template <typename Graph, typename OP>
void rDFS(const Graph & G, OP & op, bool recursion = true)
{
	int v, w, u;
	bool rvisited[64] = {false};
	sqstack<int> stack(G.vexnum());
	typedef typename Graph::anode node;
	const node * p;

	if(recursion)
	{
		for(v = 0; v < G.vexnum(); ++v)
		  if(!rvisited[v]) rDFS(G, v, rvisited, op);
	}
	else
	{
		for(v = 0; v < G.vexnum(); ++v)
		  if(!rvisited[v])
		  {
			  op(v);
			  rvisited[v] = true;
			  stack.push(v);
			  while(!stack.is_empty())
			  {
				  stack.pop(w);
				  for(p = G.rfirst(w); p; p = p->rnext(w))// Is there any adjacency vex for w?
				  {
					  u = p->radj(w);
					  if(!rvisited[u])
					  {
						  op(u);
						  rvisited[u] = true;
						  stack.push(u);
						  break;//deep
					  }
				  }
			  }
		  }
	}
}

template <typename Graph, typename OP>
void rDFS(const Graph & G, int v, bool * rvisited, OP & op)
{
	int w;
	typedef typename Graph::anode node;
	const node * p;

	op(v);
	rvisited[v] = true;
	for(p = G.rfirst(v); p; p=p->rnext(v))
	{
		w = p->radj(v);
		if(!rvisited[w]) rDFS(G, w, rvisited, op);
	}
}

template <typename Graph, typename OP>
void BFS(const Graph & G, const OP & op)
{
	typedef typename Graph::anode node;
	int v, w, u;
	bool visited[MAX_NB_VEX] = {false};
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
			  q.dequeue(w);//first visited vex's adj is first to visit
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
}

struct finish
{
	sqstack<int> stack;
	finish(int capacity = MAX_NB_VEX):stack(capacity){}
	void operator()(int v){stack.push(v);}
	void show(void)const{stack.show();}
	void clear(void){stack.clear();}
	bool is_empty(void)const{return is_empty();}
};

template<typename Graph, typename OP>
void tarjan(const Graph & G, const OP & op)
{
	int v, u, nb = G.vexnum();
	bool * visited = new bool[nb];
	//bool * rvisited = new bool[nb];
	finish f(nb), f1(nb);

	memset(visited, 0, nb);
	for(v = 0; v < nb; ++v)
	  if(!visited[v]) 
	  {
		  DFS(G, v, visited, f);
		  cout << "finished : ";
		  f.show();
		  //memset(rvisited, 0, nb);
		  while(!f.is_empty())
	  }
}
#endif
