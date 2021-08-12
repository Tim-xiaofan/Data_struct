/** 20210811 09:14, zyj, GuangDong */
#ifndef _GRAPH_AML_H
#define _GRAPH_AML_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <climits>
#include <cfloat>
#include <new>
#include <typeinfo>
#include "array.h"
#include "List.h"
using std::endl;
using std::cout;
using std::cerr;

template <typename T, typename U>
class graph_AML
{
	private:
		template <typename U1>
		struct arcnode
		{
			bool mark;
			int ivex, jvex;
			struct arcnode * ilink, *jlink;//依附于顶点ivex, jvex
			U1 weigth;
			arcnode(int i = 0, int j = 0, arcnode * ilk = nullptr, 
						arcnode * jlk = nullptr, U1 w = 0) :
				mark(false), ivex(i), jvex(j), ilink(ilk), jlink(jlk), weigth(w){}
			friend std::ostream & operator<<(std::ostream & os, const arcnode & a)
			{
				os << "{(" << a.ivex << ", " << a.jvex << "), "
					<< a.weigth << ", " << std::boolalpha << a.mark <<"}";
				return os;
			}
			const arcnode * next(int v) const;
			int adj(int v) const;
		};
		template <typename T1, typename U1>
		struct vexnode
		{
			T1 data;
			arcnode<U1> *firstarc;
			int degree;
			bool mark;
			vexnode(arcnode<U1> *fa = nullptr):
				firstarc(fa), degree(0), mark(false){}
		};
		typedef vexnode<T, U> vnode;
		typedef array<T, 1> a1;
		typedef array<U, 2> a2;
	public:
		typedef enum {UDG, UDN} graph_kind;
		typedef arcnode<U> anode;
	private:
		int _vexnum, _arcnum;
		vnode * _vexs;
	public:
		~graph_AML(){delete _vexs;}
		graph_AML():_vexnum(0),_arcnum(0),_vexs(nullptr){}
		graph_AML(const a1 & vex, const a2 & arcs, graph_kind kind);
		void show_AML(void) const;
		int get_degree(int v)const{return _vexs[v].degree;}
		void show_degree(void) const;
		int vexnum(void)const{return _vexnum;}
		int arcnum(void)const{return _arcnum;}
		anode * first(int v) {return _vexs[v].firstarc;}
		const anode * first(int v) const {return _vexs[v].firstarc;}
		bool is_marked(int v) const {return _vexs[v].mark;}
		void markup(int v) {_vexs[v].mark = true;}
		void markdown(int v) {_vexs[v].mark = false;}
};

template <typename T, typename U>
template <typename U1>
const typename graph_AML<T, U>:: template arcnode<U1> * 
graph_AML<T, U>::arcnode<U1>::
next(int v) const
{
	if(ivex == v) return ilink;
	if(jvex == v) return jlink;
	return nullptr;
}

template <typename T, typename U>
template <typename U1>
int graph_AML<T, U>::arcnode<U1>::
adj(int v) const
{
	if(v == ivex) return jvex;
	if(v == jvex) return ivex;
	return -1;//error
}

template <typename T, typename U>
graph_AML<T, U>::
graph_AML(const a1 & vexs, const a2 & arcs, graph_kind kind)
{
	int i, j;
	U w;
	anode * p, *cur, *test;

	_vexnum = vexs.get_bound(1);
	_arcnum = 0;
	_vexs = new vnode[_vexnum];
	for(i = 0; i < _vexnum; ++i)
	  _vexs[i].data = vexs.at(i);
	for(i = 0; i <_vexnum; ++i)
	{
		for(j = i; j < _vexnum; ++j)
		{
			if((w = arcs.at(i, j)) != 0)
			{
				/** insert into two list */
				p = new anode(i, j, nullptr, nullptr, w);

				/** adjacency with i*/
				if(!_vexs[i].firstarc)
				{
					_vexs[i].firstarc = p;
				}
				else
				{//not empty
					cur = _vexs[i].firstarc;
					do{
						if(i == cur->ivex)
						  test = cur->ilink;
						else
						  test = cur->jlink;
						if(test) cur = test;
					}while(test);
					if(i == cur->ivex) cur->ilink = p;
					else cur->jlink = p;
				}

				/** adjacency with j*/
				if(!_vexs[j].firstarc)
				{
					_vexs[j].firstarc = p;
				}
				else
				{//not empty
					cur = _vexs[j].firstarc;
					do{
						if(j == cur->ivex)
						  test = cur->ilink;
						else
						  test = cur->jlink;
						if(test) cur = test;
					}while(test);
					if(j == cur->ivex) cur->ilink = p;
					else cur->jlink = p;
				}
				_vexs[i].degree++;
				_vexs[j].degree++;
				_arcnum++;
				//cout << "after new : " << *p << endl;
				//show_AML();
			}
		}
	}
}

template <typename T, typename U>
void graph_AML<T, U>::
show_AML(void) const
{
	int i;
	anode *cur;

	for(i = 0; i < _vexnum; ++i)
	{
		cout << "#" << i << " "<< _vexs[i].data << ":";
		cout << "\ti("<< _vexs[i].degree<<"):";
		cur = _vexs[i].firstarc;
		while(cur)
		{
			if(i == cur->ivex)
			{
				cout << *cur << "ilink ";
				cur = cur->ilink;
			}
			else
			{
				cout << *cur << "jlink ";
				cur = cur->jlink;
			}
		};
		cout << endl;
	}
}

#endif
