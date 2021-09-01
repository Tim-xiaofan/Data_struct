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
#include "sqstack.h"
#include "graph_array.h"

using std::endl;
using std::cout;
using std::cerr;

#define MAX_NB_VEX 64

template <typename Graph, typename OP>
void DFS(const Graph & G, OP & op, bool recursion = true)
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
	bool is_empty(void)const{return stack.is_empty();}
	bool pop(int & v){return stack.pop(v);}
	bool push(int v){return stack.push(v);}
};


template <typename Graph, typename OP>
void post_DFS(const Graph & G, OP & op)
{
	int v;
	bool visited[64] = {false};

	for(v = 0; v < G.vexnum(); ++v)
	  if(!visited[v]) 
	  {
		  post_DFS(G, v, visited, op);
	  }
}

template <typename Graph, typename OP>
void post_DFS(const Graph & G, int v, bool * visited, OP & op)
{
	int w;
	typedef typename Graph::anode node;
	const node * p;

	visited[v] = true;
	for(p = G.first(v); p; p=p->next(v))
	{
		w = p->adj(v);
		if(!visited[w]) post_DFS(G, w, visited, op);
	}
	op(v);
}

template<typename Graph, typename OP>
int kosaraju(const Graph & G, const OP & op)
{
	int nb = G.vexnum(), v, ct = 0;
	finish f(nb);
	bool visited[MAX_NB_VEX] = {false};
	
	post_DFS(G, f);
	cout << "f : ";
	f.show();
	while(f.pop(v))
	{
		if(!visited[v]) 
		{
			cout << "scc-"<< ++ct << " : "; 
			rDFS(G, v, visited, op);
			cout << endl;
		}  
	}
	return ct;
}

template<typename Graph, typename OP>
int prime(const Graph & G, int u , const OP & op)
{
    typedef typename Graph::cost_type cost_type;
    int nb = G.vexnum(), v, w;
    bool visited[MAX_NB_VEX] = {false};

    //closedge[i - 1] = Min{cost(u,vi)|u属于U}, vi属于V-U
    struct {
        int adjvex;//依附在U中的顶点 
        cost_type lowcost;
    }closedge[MAX_NB_VEX];//记录从U到V一U具有最小代价的边

    closedge[u].cost = 0; // U={u}
    for(v = 0; v < nb; ++v)
    {
        if(v != u) closedge[v] = {u, G.cost(u, v)};//V-U
    }
    for(v = 1; v < nb; ++v)
    {
        u = min(closedge);//next node
    }
    return 0;
}
#endif
