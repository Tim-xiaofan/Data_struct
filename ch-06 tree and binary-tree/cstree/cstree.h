/** 20210813 12:45, zyj, GuangDong*/
// cstree.h -- child and sibling
#ifndef CSTREE_H
#define CSTREE_H
#include <iostream>
#include "graph_AML.h"
#include "sqqueue.h"
using std::cout;
using std::endl;

template<typename T>
void show(T data)
{
	cout << data << " ";
}

template <typename T>
class cstree
{
	private:
		template <typename T1>
		struct Node
		{
			T1 data;
			struct Node * firstchild, *nextsibling;//孩子，孩子的兄弟
			Node(Node * fc = nullptr, Node * fs = nullptr):
				firstchild(fc), nextsibling(fs){}
			friend std::ostream & operator<<(std::ostream & os, const Node & nd)
			{
				os << "(addr = "<< &nd << ", data = " << nd.data << ", fc = " << nd.firstchild << ", ns = " << nd.nextsibling <<")";
				return os;
			}
		};
		typedef Node<T> node;
	private:
		node *_root, *_R;
		int _nb_vex;
	public:
		cstree():_root(nullptr),_nb_vex(0){}
		//建立无向图G的深度优先生成森林的
		template<typename U>
		cstree(const graph_AML<T, U> & G);
		template<typename OP>
		void levelorder_traverse(const OP & op = show<T>) const;
	private:
		/**
		 * O(e)
		 * 从第v个顶点出发深度优先遒历图G，建立以T为根的生成树。
		 * */
		template<typename U>
		void DFS_tree(const graph_AML<T, U> & G, int v, node * t, bool * visited);
};

template<typename T>
template<typename U>
cstree<T>::
cstree(const graph_AML<T, U> & G):_root(nullptr), _nb_vex(0)
{
#define MAX_NB_VEX 64
	int v, nb_vex =  G.vexnum();
	bool visited[MAX_NB_VEX] = {false};
	node *p, *q = nullptr;

	for(v = 0; v < nb_vex; ++v)
	  if(!visited[v])
	  {
		  p = new node();
		  _nb_vex++;
		  p->data = G.data(v);
		  if(q)
			cout << "q = "  << q << ", q->data = " << q->data << ", q->nextsibling = " << q->nextsibling  << endl;
		  cout << "p = "  << p << ", p->data = " << p->data << endl;
		  cout << "after adding " << p->data << ":";
		  if(!_root) 
		  {
			  _root = p;//是第一棵生成树的根
			  _R = new node();
			  _R->firstchild = _root; 
			  //cout << "first tree : ";
			  //levelorder_traverse(show<T>);
		  }
		  else 
		  {
			q->nextsibling = p;// 是其他生成树的根（前一棵的根的"兄弟")
			//cout << "next tree : ";
			//levelorder_traverse(show<T>);
		  }
		  q = p;//q指示当前生成树的根
		  DFS_tree(G, v, p, visited);//建立以p为根的生成树
		  cout << "tree from " << v << " : ";
		  levelorder_traverse(show<T>);
	  }
}

template<typename T>
template<typename U>
void cstree<T>::
DFS_tree(const graph_AML<T, U> & G, int v, node *  t, bool *visited)
{
	typedef typename graph_AML<T, U>::anode arcnode;
	const arcnode * arc;
	int w;
	node *p = nullptr, *q = nullptr;
	bool first = true;

	visited[v] = true;
	//cout << "entering ----t = " << t->data << ", v = " << v << "-----------" <<endl;
	for(arc = G.first(v); arc; arc = arc->next(v))
	{
		w = arc->adj(v);
		if(!visited[w])
		{
			p = new node();
			_nb_vex++;
			p->data = G.data(w);
			if(first) 
			{
				t->firstchild = p;//第一个邻接点, 根的左孩子结点
				first = false;
				//cout << "first " << p->data << " : ";
				//levelorder_traverse(show<T>);
			}
			else 
			{
				q->nextsibling = p; //是上一邻接顶点的右兄弟结点
				//cout << "next " << q->nextsibling->data << " : ";
				//levelorder_traverse(show<T>);
			}
			q = p;
			DFS_tree(G, w, p, visited);
		}
		//else cout << "w = " << w << " is visited\n";    
	}
	//cout << "leaving ----t = " << t->data << ", v = " << v << "-----------" <<endl;
	//levelorder_traverse(show<T>);
}

template<typename T>
template<typename OP>
void cstree<T>::
levelorder_traverse(const OP & op) const
{
	sqqueue<const node *> q(_nb_vex);
	const node * cur, *it;

	if(!_root) return;

	q.enqueue(_R);
	//q.show();
	cout << "nb = " << _nb_vex << " : \n";
	//op(_root->data);
	while(!q.is_empty())
	{
		q.dequeue(cur);
		if(!cur) continue;
		cout << cur->data<<"==>{";
		for(it = cur->firstchild; it; it = it->nextsibling)
		{
			//cout << "{it = "<< *it << "}";
			op(it->data);
			q.enqueue(it);
		}
		cout << "} ";
	}
	cout << endl;
	//cout << "leaving levelorder_traverse\n";
}

#endif
