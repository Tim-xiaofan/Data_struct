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
			int tailvex, headvex;//该弧的尾和头顶点的位置
			struct arcnode * tlink, *hlink;//分别为弧尾相同和弧头相同弧的链域
			U1 weigth;
			arcnode(int t = 0, int h = 0, arcnode * tlk = nullptr, 
						arcnode * hlk = nullptr, U1 w = 0) :
				tailvex(t), headvex(h), tlink(tlk), hlink(hlk), weigth(w){}
			friend std::ostream & 
                operator<<(std::ostream & os, const arcnode & a)
			{
				os << "{<" << a.tailvex << ", " << a.headvex << ">, "
					<< a.weigth << "}";
				return os;
			}
			const arcnode * next(int v) const {return tlink;}
			const arcnode * rnext(int v) const {return hlink;};
			int adj(int v) const {return headvex;}
			int radj(int v) const {return tailvex;}
		};
		template <typename T1, typename U1>
		struct vexnode
		{
			T1 data;
			arcnode<U1> *firstout, *firstin;//分别指向该顶点第一条入弧和出弧
			int outnum, innum;
			vexnode(arcnode<U1> *fo = nullptr, arcnode<U1> *fi = nullptr):
				firstout(fo), firstin(fi), outnum(0), innum(0){}
		};
		typedef vexnode<T, U> vnode;
		typedef array<T, 1> a1;
		typedef array<U, 2> a2;
	public:
		typedef enum {DG, DN} graph_kind;
		typedef arcnode<U> anode;
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
		const anode * first(int v) const {return _vexs[v].firstout;}
		const anode * rfirst(int v) const {return _vexs[v].firstin;}
};

/** O(n + n * n)*/
template <typename T, typename U>
graph_olist<T, U>::
graph_olist(const a1 & vexs, const a2 & arcs, graph_kind kind)
{
	int t, h;
	anode *p, *tail;
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
			p = new anode(t, h, nullptr, nullptr, w);
			/** append into two list */
            /** 同弧尾*/
			if(_vexs[t].firstout == nullptr)
			  _vexs[t].firstout = p;
			else
			{
			  for(tail = _vexs[t].firstout; 
                          tail->tlink; tail = tail->tlink);
			  tail->tlink = p; 
			}

            /** 同弧头*/
			if(_vexs[h].firstin == nullptr)
			  _vexs[h].firstin = p;
			else
			{
			  for(tail = _vexs[h].firstin; 
                          tail->hlink; tail = tail->hlink);
			  tail->hlink = p; 
			}
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
	const anode *p;

	for(i = 0; i < _vexnum; ++i)
	{
		cout << _vexs[i].data << ":\n";
		cout << "\tout("<< _vexs[i].outnum<<"):";
		for(p = first(i); p; p = p->next(i))
		  cout << *p << " ";
		cout << endl;

		//p = _vexs[i].firstout;
		//while(p)
		//{
		//	cout << *p << " ";
		//	p = p->tlink;
		//}
		//cout << endl;
		cout << "\tin("<< _vexs[i].innum<<"):";
		for(p = rfirst(i); p; p = p->rnext(i))
		  cout << *p << " ";
		cout << endl;
		//p = _vexs[i].firstin;
		//while(p)
		//{
		//	cout << *p << " ";
		//	p = p->hlink;
		//}
		//cout << endl;
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
