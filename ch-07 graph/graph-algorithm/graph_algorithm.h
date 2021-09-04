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

template <typename Array>
void show_array(const Array & a, int size)
{
    int i;
    for(i = 0; i < size; ++i)
    {
		if(a[i] == INT_MAX) cout << 'I';
		else cout << a[i];
        if(i ==  size - 1) cout << endl;
        else cout << " ";
    }
}

template <typename closedges>
void show_closedge(const closedges & cds, int size)
{
    int i;
    for(i = 1; i < size; ++i)
    {
		cout << "{(" << i << "," << cds[i].adjvex << "): ";
		if(cds[i].lowcost == INT_MAX) cout << "I}";
		else cout << cds[i].lowcost << "}";
        if(i ==  size - 1) cout << endl;
        else cout << " ";
    }
}

void print(int v)
{
	cout << v << " ";
}

template <typename Array, typename DataType>
void init_array(Array & a, int size, DataType d = 0)
{
    int i;
    for(i = 0; i < size; ++i)
    {
        a[i] = d;
    }
}

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

template<typename Graph>
int prime_O3(const Graph & G, int t)
{
    typedef typename Graph::cost_type cost_type;
    int nb = G.vexnum(), i, j, ct = 0, u, k, cost = 0;
    cost_type min;
    int U[MAX_NB_VEX];

    init_array(U, nb, -1);
    U[t] = t;
    ct++;
    //cout << "U : ";
    //show_array(U, nb);
    while(ct < nb)
    {
        for(i = 0; i < nb && ct < nb; ++i)
        {
			min = INT_MAX;
            u = U[i];
            if(u == -1) continue;
            k = 0;
            for(j = 0; j < nb; ++j)
            {
                //cout << "(u=" << u << ",j=" << j << "):" 
                //    << G.cost(u, j) << ", " << U[j] << endl;
                if(G.cost(u, j) != INT_MAX && U[j] == -1)//not in U and adj
                {
                    if(G.cost(u, j) < min)
                    {
                        min = G.cost(u, j);
                        k = j;
                    }
                }
            }
            U[k] = k;
            ct++;
            //cout << "chois is " << k << ", " << "ct = " << ct << ": ";
            //show_array(U, nb);
            cout << "(" << u << "," << k << ")";
			cost += min;
        }
    }
    cout <<  endl;
    return cost;
}

/** O(n * n)边数无关，因此适用于求边稠密的网的最小生成树
 * TODO: 未实现对邻接表，十字链表，多重邻接表的支持*/
template<typename Graph>
int prime_O2(const Graph & G, int u)
{
	//用普里姆算法从第 u个顶点出发构造网 G的最小生成树 T，输出 T的各条边。
    typedef typename Graph::cost_type cost_type;
    int nb = G.vexnum(), v, w, min_vex, cost = 0;
    cost_type min_cost;

	// 记录从顶点集U到V- U的代价最小的边的辅助数组定义	
    //closedge[i - 1] = Min{cost(u,vi)|u属于U}, vi属于V-U
    struct tmp{
        int adjvex;//依附在U中的顶点 
        cost_type lowcost;
        tmp(int a = 0, cost_type lc = 0):adjvex(a), lowcost(lc){}
    }closedge[MAX_NB_VEX];//记录从U到V一U具有最小代价的边

    closedge[u].lowcost = 0; // U={u}
    for(v = 0; v < nb; ++v)
    {
        if(v != u) closedge[v] = {u, G.cost(u, v)};//V-U
    }
    //cout << "after init from "<< u << ": ";
	//show_closedge(closedge, nb);
    for(v = 1; v < nb; ++v)
    {
		min_cost = INT_MAX;
        for(w = 0; w < nb; ++w)//V-U中与U邻接,cost最小的顶点
        {
            if(closedge[w].lowcost)
            {
                if(closedge[w].lowcost < min_cost) 
                {
                    min_cost = closedge[w].lowcost;
                    min_vex = w;
                }
            }
        }
        //cout << "choice is " << min_vex << " : ";
        cout << "(" << closedge[min_vex].adjvex << "," << min_vex << ") | ";
		cost += min_cost;
        closedge[min_vex].lowcost = 0;//k并入U,重新选择最小边
        for(w = 1; w < nb; ++w)
        {
			//cout << "test w = " << w << ":(min_vex=" << min_vex
			//	<< ",lowcost=" << closedge[w].lowcost << ",cost=" 
			//	<< G.cost(min_vex, w) << ")" << endl;
            if(closedge[w].lowcost > G.cost(min_vex, w))
            {
				//cout << "update w = " << w << endl;
                closedge[w] = {min_vex, G.cost(min_vex, w)};
            }
        }
        cout << "selected " << min_vex << ": ";
		show_closedge(closedge, nb);
    }
	//cout << endl;
    return cost;
}

template<typename Graph, typename OP>
void find_articul(const Graph & G, const OP & op = print)
{
	int v, count = 1, visited[MAX_NB_VEX] = {0}, vexnum = G.vexnum();
	int low[MAX_NB_VEX] = {0};//深度优先搜索树中点i所能回溯到的最浅层的点
	const typename Graph::anode * p;
	visited[0] = 1;//v0最先访问(先序遍历)
	//cout << "visited : ";
	//show_array(visited, vexnum);
	
	p = G.first(0);
	//cout << "find : *p = "<< *p << endl;
	v = p->adj(0);
	//cout << "find : v = " << v << endl;
	DFS_articul(G, v, visited, low, count, op);//从v0开始做DFS
	if(count < vexnum)
	{
		op(0);
		//cout << endl;
		while(p->next(0))
		{
			p = p->next(0);
			v = p->adj(0);
			if(!visited[v])
			  DFS_articul(G, v, visited, low, count, op);
		}
	}
	cout << endl;
	//cout << "visited : ";
	//show_array(visited, vexnum);
	//cout << "low     : ";
	//show_array(low, vexnum);
}

/**
  从v开始做深度优先遍历
 */
template<typename Graph, typename OP>
void DFS_articul(const Graph & G, 
			int v, 
			int *visited, 
			int *low,
			int & count,
			const OP & op = print)
{
	int min = ++count, w;
	visited[v] = min;
	//cout << "visited : ";
	//show_array(visited, G.vexnum());
	const typename Graph::anode * p;
	bool first = true;
	//cout << "v = " << v << endl;

	for(p = G.first(v); p; p = p->next(v))
	{
		w = p->adj(0);
		//cout << "w = " << w << endl;
		if(!visited[w])//w未曾访问，w是v的孩子
		{
			DFS_articul(G, w, visited, low, count, op);
			if(low[w] < min) min = low[w];
			if(low[w] >= visited[v] && first)//关节点<--没有回边
			{
				//cout << "found : v = " << v << 
				//	", w = " << w << endl;
				op(v);
				first = false;
				//cout << endl;
			}
		}
		else if(visited[w] < min) 
		  min = visited[w];//w已访问，w是v的祖先
	}
	low[v] = min;
	//cout << "low : ";
	//show_array(low, G.vexnum());
}
#endif
