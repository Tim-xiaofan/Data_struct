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
		else cout << std::setw(2) << a[i];
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

static inline void 
print(int v)
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

void show_S(bool *finalx, int size)
{
	int i;
	cout << "S : ";

	for(i = 0; i < size; ++i)
	{
		if(finalx[i]) cout << i << " ";
	}
	cout << endl;
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
                  // Is there any adjacency vex for w?
				  for(p = G.first(w); p; p = p->next(w))
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
                  // Is there any adjacency vex for w?
				  for(p = G.rfirst(w); p; p = p->rnext(w))
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

/** 有向图的强连通分量*/
template<typename Graph, typename OP>
int kosaraju(const Graph & G, const OP & op)
{
	int nb = G.vexnum(), v, ct = 0;
	finish f(nb);
	bool visited[MAX_NB_VEX] = {false};

	post_DFS(G, f);//正向DFS
	cout << "f : ";
	f.show();
	while(f.pop(v))//从最后的完成的点开始，倒序做逆向DFS
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
			cout << "(" << u << "," << k << ")";
			cost += min;
		}
	}
	cout <<  endl;
	return cost;
}

/** 
  最小生成树
  O(n * n)边数无关，因此适用于求边稠密的网的最小生成树
TODO:未实现对邻接表，十字链表，多重邻接表的支持
 */
template<typename Graph>
int prime_O2(const Graph & G, int u)
{
    /**用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边。*/
    typedef typename Graph::cost_type cost_type;
    int nb = G.vexnum(), v, w, min_vex, cost = 0, ct = 0;
    cost_type min_cost;

    /**记录从顶点集U到V- U的代价最小的边的辅助数组定义	
    closedge[i - 1] = Min{cost(u,vi)|u属于U}, vi属于V-U*/
    struct tmp{
        int adjvex;//依附在U中的顶点 
        cost_type lowcost;//0表示已经并入U
        tmp(int a = 0, cost_type lc = 0):adjvex(a), lowcost(lc){}
    }closedge[MAX_NB_VEX];//记录从U到V一U具有最小代价的边

    /** 进入初态*/
    closedge[u].lowcost = 0; // U={u}
    ++ct;
    for(v = 0; v < nb; ++v)
    {
        if(v != u) closedge[v] = {u, G.cost(u, v)};//V-U
    }

    for(v = 0; v < nb && ct < nb; ++v)
    {//选择其余 G.vexnum -1个顶点
        min_cost = INT_MAX;
        for(w = 0; w < nb; ++w)//V-U中与U邻接且cost最小的顶点
        {
            if(closedge[w].lowcost)//属于V - U
            {
                if(closedge[w].lowcost < min_cost) 
                {
                    min_cost = closedge[w].lowcost;
                    min_vex = w;
                }
            }
        }
        cout << "(" << closedge[min_vex].adjvex << "," << min_vex << ") | ";
        cost += min_cost;
        closedge[min_vex].lowcost = 0;//k并入U,重新选择最小边
        ++ct;
        for(w = 0; w < nb; ++w)
        {//更新closedge
            if(closedge[w].lowcost > G.cost(min_vex, w))
            {
                closedge[w] = {min_vex, G.cost(min_vex, w)};
            }
        }
        cout << "selected " << min_vex << ": ";
        show_closedge(closedge, nb);
    }
    return cost;
}

/** 寻找连通图的关节点: O(n + e)*/
template<typename Graph, typename OP>
void find_articul(const Graph & G, const OP & op = print)
{
	int v, count = 0, visited[MAX_NB_VEX] = {0},//顶点v的在DFS中访问次序
        vexnum = G.vexnum();
	int low[MAX_NB_VEX] = {0};//深度优先搜索树中顶点w所能回溯到的最浅层的点

    for(v = 0; v < vexnum;++v)
      if(!visited[v])
      {
          DFS_articul(G, v, visited, low, count, print);
          if(count < vexnum)
            op(v);
      }
	cout << endl;
}

/**
  从v开始做深度优先遍历, 并输出关键点
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
	const typename Graph::anode * p;
	bool first = true;
	visited[v] = min;

	for(p = G.first(v); p; p = p->next(v))
	{
		w = p->adj(0);
		if(!visited[w])//w未曾访问，w是v的孩子
		{
			DFS_articul(G, w, visited, low, count, op);
			if(low[w] < min) min = low[w];
			if(low[w] >= visited[v] && first)//关节点<--没有回边
			{
				op(v);
				first = false;
			}
		}
		else if(visited[w] < min)//visited[k] 
		  min = visited[w];//w已访问，w是v的祖先
	}
	low[v] = min;
	//cout << "\nvisited : ";
	//show_array(visited, G.vexnum());
	//cout << "low     : ";
	//show_array(low, G.vexnum());
}

/** 
 * 邻接表有向图 G：
 * G无回路，则输出G的顶点的一个拓扑序列并返回 OK，否则 ERROR。
 * O(n + e)
 */
template<typename Graph, typename OP>
bool topological_sort(const Graph & G, const OP & op)
{
	int vexnum = G.vexnum(), v, w, count = 0;//输出的顶点计数
	int indegress[MAX_NB_VEX];//各个顶点的入度
	sqstack<int> stack(vexnum);//存放入度为0的顶点
	const typename Graph::anode * p;

	for(v = 0; v < vexnum; ++v)
    {
        indegress[v] = G.get_idegree(v);
	    if(!indegress[v]) stack.push(v);//入度为0的入栈
    }

	while(!stack.is_empty())
	{
		stack.pop(v);
		op(v); ++count;//输出顶点并计数
		//每个邻接点入度减一（模拟删除v）
		for(p = G.first(v); p; p = p->next(v))
		{
			w = p->adj(v);
			if(!(--indegress[w])) stack.push(w);//出现新的入度为零的顶点
		}
	}
	if(count < vexnum) return false;//有顶点不在拓扑有序序列中，存在回路
	else return true;
}

/** 
  邻接表有向图 G：O(n + e)
  G无回路，则输出 G 的顶点的一个拓扑序列并返回 OK，否则ERROR。
  有向网G采用邻接表存储结构，求各顶点事件的最早发生时间ve
  T为拓扑序列顶点栈，S为零入度顶点栈。
  若G无回路，则用栈T返回G的一个拓扑序列，且函数值为OK，否则为 ERROR。
 */
template<typename Graph>
bool cricticalpath_topologicalsort(const Graph & G, 
			sqstack<int> & T, 
			typename Graph::cost_type *ve)
{
	int vexnum = G.vexnum(), v, w, count = 0;//输出的顶点计数
	int indegress[MAX_NB_VEX];//各个顶点的入度
	sqstack<int> S(vexnum);//存放入度为0的顶点
	const typename Graph::anode * p;

	for(v = 0; v < vexnum; ++v)
	  indegress[v] = G.get_idegree(v);

	for(v = 0; v < vexnum; ++v)
	  if(!indegress[v]) S.push(v);//入度为0的入栈

	while(!S.is_empty())
	{
		S.pop(v);
		T.push(v);
		++count;//输出顶点并计数
		for(p = G.first(v); p; p = p->next(v))
		{//每个邻接点入度减一（模拟删除v）
			w = p->adj(v);
			if(!(--indegress[w])) S.push(w);//出现新的入度为零的顶点
			if(ve[v] + p->cost(v) > ve[w])
              ve[w] = ve[v] + p->cost(v);
		}
	}
	if(count < vexnum) return false;//有顶点不在拓扑有序序列中，存在回路
	else return true;
}

/** 
  G为有向网，输出G的各项关键活动。
  O(n + e)
 */
template<typename Graph>
bool cricticalpath(const Graph & G)
{
	int vexnum = G.vexnum(), v, w;
	sqstack<int> T(MAX_NB_VEX);//T为拓扑序列顶点栈，S为零入度顶点栈。
	typename Graph::cost_type ve[MAX_NB_VEX] = {0},//最早发生时
			 vl[MAX_NB_VEX], //最迟发生时间
             dut, ee, el;
	const typename Graph::anode * p;
	char tag;

	if(!cricticalpath_topologicalsort(G, T, ve)) 
	  return false;
	cout << "T : ";
	T.show();
	cout << "ve : ";
	show_array(ve, vexnum);

	for(v = 0; v < vexnum; ++v)
	  vl[v] = ve[vexnum - 1];

	while(!T.is_empty())
	{//vl:向后递推
		T.pop(v);
		for(p = G.first(v); p; p = p->next(v))
		{
			w = p->adj(v);
			dut = p->cost(v);
			if(vl[w] - dut< vl[v]) 
              vl[v] = vl[w] - dut;
		}
	}
	cout << "vl : ";
	show_array(vl, vexnum);

	for(v = 0; v < vexnum; ++v)
	{
		for(p = G.first(v); p ; p = p->next(v))
		{
			w = p->adj(v);
			dut = p->cost(v);
			ee = ve[v];
			el = vl[w] - dut;
			tag = (ee == el) ? '*':' ';
			cout << "{a=(" << v << "," << w 
				<< "), dut=" << dut
				<< ", ee=" << ee
				<< ", el=" << el
				<< ", " << tag << "}" << endl;
		}
	}
	return true;
}

/**
  用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权长度D[v].
  若P[v][w]为TRUE，则w是从v0到v当前求得最短路径上的顶点。
  final[v]为TRUE当且仅当v∈S，即已经求得从v0到v的最短路径。
  O(n * n)
 */
template<typename Graph>
void dijkstra(const Graph & G, 
			int v0, bool P[][MAX_NB_VEX], 
			typename Graph::cost_type * D)
{
	int i, j, v, w, vexnum = G.vexnum();
	bool _final[MAX_NB_VEX];
	typename Graph::cost_type min;

	for(v = 0; v < vexnum; ++v)
	{
		_final[v] = false;
		D[v] = G.cost(v0, v);
		for(w = 0; w < vexnum; ++w) 
		  P[v][w] = false;
		if(D[v] < Graph::INF)
		{
			P[v][v0] = true;//起点
			P[v][v] = true;//终点
		}
	}
	D[v0] = 0;//vi到v0的最短路径 
	_final[v0] = true; //v0加入集合S
	for(i = 0; i < vexnum; ++i)
	{
		cout << "---- i = " << i  << " ------"<< endl;
		show_S(_final, vexnum);
		cout << "D : ";
		show_array(D, vexnum);
		min = Graph::INF;//V-S中，当前离v0最近的距离节点vj
		for(w = 0; w < vexnum; ++w)
		  if(!_final[w] && D[w] < min) //V-S中的w离v0更近
		  {
			  v = w;
			  min = D[w];
		  }
		_final[v] = true; //加入S
		for(w = 0; w < vexnum; ++w)//更新V-S到v0的最短路径
		  if(!_final[w] && (G.cost(v, w) != Graph::INF)
					  && (G.cost(v, w) + min < D[w]))
		  {
			  D[w] = min + G.cost(v, w);
			  for(j = 0; j < vexnum; ++j)
				P[w][j] = P[v][j];//j在Path(v0...v)-->j在Path(v0...w)
			  P[w][w] = true;
		  }
	}
}

/** 
  用Floyd算法求有向网G中各对顶点v和w之间的最短路径 P[v][w]及其
  带权长度 D[v][w]。若 P[v][w][u]为TRUE，则u是从v到w当前求得最
  短路径上的顶点。
 */
typedef array<bool, 3> a3;
static inline void show_path(const a3 & P, const int D[][MAX_NB_VEX]);

template<typename Graph>
void floyd(const Graph & G , a3 & P, 
			typename Graph::cost_type D[MAX_NB_VEX][MAX_NB_VEX])
{
	int v, w, u, vexnum = G.vexnum(), i;

	/** 各对结点之间初始已知路径及距离*/
	for(v = 0; v < vexnum; ++v)
	  for(w = 0; w < vexnum; ++w)
	  {
		  D[v][w] = G.cost(v, w);
		  for(u = 0; u < vexnum; ++u) 
			P.at(v, w, u) = false;

		  if(D[v][w] < Graph::INF)
		  {
			  P.at(v, w, v) = true;
			  P.at(v, w, w) = true;
		  }
	  }
	cout << "------------" << -1 << "---------------" << endl;
	show_path(P, D);

	/* shorter one?*/
	for(u = 0; u < vexnum; ++u)
	{
		for(v = 0; v < vexnum; ++v)
		  for(w = 0; w < vexnum; ++w)
		  {
			  if((D[v][u] < Graph::INF) 
						  && (D[u][w] < Graph::INF) 
						  && (D[v][u] + D[u][w] < D[v][w]))
			  {
				  D[v][w] = D[v][u] + D[u][w];
				  for(i = 0; i < vexnum; ++i)
					P.at(v, w, u) = (P.at(v, u, i) || P.at(u, w, i));
			  }
		  }
		cout << "------------" << u << "---------------" << endl;
		show_path(P, D);
	}
}

static inline void 
show_path(const a3 & P, const int D[][MAX_NB_VEX])
{
	int u, v, w, vexnum = P.get_bound(1);

	for(v = 0; v < vexnum; ++v)
	  for(w = 0; w < vexnum; ++w)
	  {
		  cout << "path<" << v << ","<< w <<">, len="; 
		  if(D[v][w] == INT_MAX ) cout << "INT_MAX" << " : { ";
		  else cout << D[v][w] << ": { ";
		  for(u = 0; u < vexnum; ++u)
		  {
			  if(P.at(v, w, u)) cout << u << " ";
		  }
		  cout << "}" << endl;;
	  }
}
#endif
