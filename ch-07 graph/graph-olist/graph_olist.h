/** 20210810 12:35, zyj, GuangDong */
#ifndef _GRAPH_OLIST_H
#define _GRAPH_OLIST_H
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
class graph_olist
{
	private:
		template <typename U1>
		struct arcnode
		{
			int tailvex, headvex;
			struct arcnode * tlink, *hlink;
			U1 weigth;
			arcnode(int t = 0, int h = 0, arcnode * tlk = nullptr, 
						arcnode * hlk = nullptr, U1 w = 0) :
				tailvex(t), headvex(h), tlink(tlk), hlink(hlk), weigth(w){}
			friend std::ostream & operator<<(std::ostream & os, const arcnode & a)
			{
				os << "{<" << a.tailvex << ", " << a.headvex << ">, "
					<< a.weigth << "}";
				return os;
			}
		};
		template <typename T1, typename U1>
		struct vexnode
		{
			T1 data;
			arcnode<U1> *firstout, *firstin;
			int outnum, innum;
			vexnode(arcnode<U1> *fo = nullptr, arcnode<U1> *fi = nullptr):
				firstout(fo), firstin(fi), outnum(0), innum(0){}
		};
		typedef arcnode<U> anode;
		typedef vexnode<T, U> vnode;
		typedef array<T, 1> a1;
		typedef array<U, 2> a2;
	public:
		typedef enum {DG, DN} graph_kind;
	private:
		int _vexnum, _arcnum;
		vnode * _vexs;
	public:
		~graph_olist(){delete _vexs;}
		graph_olist():_vexnum(0),_arcnum(0),_vexs(nullptr){}
		graph_olist(const a1 & vex, const a2 & arcs, graph_kind kind);
		void show_olist(void) const;
		int get_idegree(int v)const{return _vexs[v].innum;}
		int get_odegree(int v)const{return _vexs[v].outnum;}
		void show_iodegree(void) const;
		int vexnum(void) const{return _vexnum;}
		int arcnum(void) const{return _arcnum;}
};

/** O(n + n * n)*/
template <typename T, typename U>
graph_olist<T, U>::
graph_olist(const a1 & vexs, const a2 & arcs, graph_kind kind)
{
	int t, h;
	anode *p;
	U w;

	_vexnum = vexs.get_bound(1);
	_arcnum = 0;
	_vexs = new vnode[_vexnum];
	for(t = 0; t < _vexnum; ++t)
	  _vexs[t].data = vexs.at(t);

	for(t = 0; t <_vexnum; ++t)
	  for(h = 0; h < _vexnum; ++h)
		if((w = arcs.at(t, h)) != 0)
		{
			/** insert into two list */
			p = new anode(t, h, _vexs[t].firstout, _vexs[h].firstin, w);
			_vexs[t].firstout = p;
			_vexs[h].firstin = p;
			_vexs[t].outnum++;
			_vexs[h].innum++;
			_arcnum++;
		}
}


template <typename T, typename U>
void graph_olist<T, U>::
show_olist(void) const
{
	int i;
	anode *p;

	for(i = 0; i < _vexnum; ++i)
	{
		cout << _vexs[i].data << ":\n";
		cout << "\tout("<< _vexs[i].outnum<<"):";
		p = _vexs[i].firstout;
		while(p)
		{
			cout << *p << " ";
			p = p->tlink;
		}
		cout << endl;
		cout << "\tin("<< _vexs[i].innum<<"):";
		p = _vexs[i].firstin;
		while(p)
		{
			cout << *p << " ";
			p = p->hlink;
		}
		cout << endl;
	}
}

template<typename T, typename U>
void graph_olist<T, U>::
show_iodegree(void) const
{
	int i;
	for(i = 0; i < _vexnum; ++i)
	{
		cout << _vexs[i].data << " : ";
		cout << "idgress = "<< get_idegree(i)
			<< ", odgress = "<< get_odegree(i) << endl;
	}
}

#endif
