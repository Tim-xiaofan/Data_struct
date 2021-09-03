/** 20210809 12:50, zyj, GuangDong */
#ifndef _GRAPH_ADJLIST_H
#define _GRAPH_ADJLIST_H
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <climits>
#include <cfloat>
#include <new>
#include <typeinfo>
#include "array.h"
using std::endl;
using std::cout;
using std::cerr;

#define INF INT_MAX

template <typename T, typename U>
class graph_adjlist
{
	private:
		enum {MAX_NB_VEXS = 128};
		template <typename U1>
		struct arcnode
		{
			int adjvex;
			U1 weigth;
			struct arcnode * nextarc;
			arcnode(int i = 0, U1 w = 0, arcnode * na = nullptr):
				adjvex(i), weigth(w), nextarc(na){}
			friend std::ostream & operator<<(std::ostream & os, const struct arcnode & a)
			{
				os << "(adjvex=" << a.adjvex << ", weigth=" << a.weigth << ")";
				return os;
			}
			int adj(int v) const {return adjvex;}
		};
		template<typename T1, typename U1>
		struct vexnode
		{
			T1 data;
			arcnode<U1> * firstarc;
			arcnode<U1> * lastarc;
			int size;
			vexnode(arcnode<U1> *fa = nullptr, arcnode<U1> *la = nullptr, int sz = 0):
				firstarc(fa), lastarc(la), size(sz){}
			void append(arcnode<U1> * an);
			void show(void)const;
		};
		typedef vexnode<T, U> vnode;
		typedef arcnode<U> anode;
		typedef array<T, 1> a1;
		typedef array<U, 2> a2;
	public:
		typedef enum {DG, DN, UDG, UDN} graph_kind;
	private:
		int _nb_vex, _nb_arc;
		graph_kind _kind;
		a1* _vexs;
		vnode *_adjlists;
		vnode *_radjlists;
	public:
		~graph_adjlist(){delete _vexs; delete [] _adjlists; delete [] _radjlists;}
		graph_adjlist():_nb_vex(0), _nb_arc(0), _kind(DG), _vexs(nullptr), _adjlists(nullptr), _radjlists(nullptr){}
		graph_adjlist(const a1 & vexs, const a2 & arcs, graph_kind kind);
		void show_adjlists(void)const;
		/** O(1)*/
		int get_degree(int i) const {return (_kind == UDN || _kind == UDG) ?
			_adjlists[i].size : -1;}
		void show_degrees(void) const;
		/** O(1)*/
		int get_odegree(int i) const {return (_kind == DN || _kind == DG) ?
			_adjlists[i].size : -1;}
		/** O(2 * e) or O(1)*/
		int get_idegree(int i) const;
		void show_iodegrees(void) const;
		const char * kind_str(void) const;
		bool is_adj(int i, int j) const;
		void create_radjlists(void);
		void show_radjlists(void)const;
		int vexnum(void) const{return _nb_vex;}
		int arcnum(void) const{return _nb_arc;}
	private:
};

/** O(n*n)*/
template <typename T, typename U>
graph_adjlist<T, U>::
graph_adjlist(const a1 & vexs, const a2 & arcs, graph_kind kind)
{
	int i, j;
	U current;
	
	_nb_vex = vexs.get_bound(1);
	_vexs = a1::instance(vexs);// O(n)
	_nb_arc = 0;
	_adjlists = new vnode[_nb_vex];
	/** O(n * n) */
	for(i = 0; i < _nb_vex; ++i) 
	{
		_adjlists[i].data = _vexs->at(i);
		for(j = 0; j < _nb_vex; ++j)
		  if(kind == DG || kind == UDG)
		  {
			  if((current = arcs.at(i, j)) != 0)
			  {
				  _adjlists[i].append(new anode(j, current, nullptr));
				  _nb_arc++;
			  }
		  }
		  else
		  {
			  if((current = arcs.at(i, j)) != INF)
			  {
				  _adjlists[i].append(new anode(j, current, nullptr));
				  _nb_arc++;
			  }
		  }
	}
	_kind = kind;
	_radjlists = nullptr;
}

template <typename T, typename U>
void graph_adjlist<T, U>::
show_adjlists(void)const
{
	int i;

	for(i = 0; i <_nb_vex; ++i)
	{
		cout << _vexs->at(i) << " : ";
		_adjlists[i].show();
	}
}

template<typename T, typename U>
const char *  graph_adjlist<T, U>::
kind_str(void) const
{
	switch(_kind)
	{
		case DG: return "DG";
		case DN: return "DN";
		case UDG: return "UDG";
		case UDN: return "UDN";
		default: return "UNKOWN";
	}
}

template <typename T, typename U>
void graph_adjlist<T, U>::
show_degrees(void) const
{
	int i;
	for(i = 0; i <_nb_vex; ++i)
	{
		cout << _vexs->at(i) << " : "
			<< get_degree(i) << endl;
	}
}


/** O(2 * e)*/
template<typename T, typename U>
void  graph_adjlist<T, U>::
create_radjlists(void)
{
	int k;
	const anode * p;
	
	if(_radjlists) return;//avoid repeating
	_radjlists = new vnode[_nb_vex];
	for(k = 0; k <_nb_vex; ++k)//traverse all adjlist
	{
		for(p = _adjlists[k].firstarc; p; p = p->nextarc)
		  _radjlists[p->adjvex].append(new anode(k, p->weigth, nullptr));
	}
}


template<typename T, typename U>
int graph_adjlist<T, U>::
get_idegree(int i) const
{
	int k, d = 0;
	const anode *p;

	if(_radjlists) return _radjlists[i].size;

	for(k = 0; k < _nb_vex; ++k)
	  for(p = _adjlists[k].firstarc; p; p = p->nextarc)
		  if(p->adjvex == i) d++;//adj is i
	return d;
}

template<typename T, typename U>
void graph_adjlist<T, U>::
show_iodegrees(void) const
{
	int i;
	for(i = 0; i < _nb_vex; ++i)
	{
		cout << _vexs->at(i) << " : ";
		cout << "idgress = "<< get_idegree(i)
			<< ", odgress = "<< get_odegree(i) << endl;
	}
}

/** O(e)*/
template<typename T, typename U>
bool graph_adjlist<T, U>::
is_adj(int i, int j) const
{
	const anode *p;
	for(p = _adjlists[i].firstarc; p; p = p->nextarc)
	  if(p->adjvex == j) return true;
	return false;
}


template <typename T, typename U>
void graph_adjlist<T, U>::
show_radjlists(void)const
{
	int i;

	for(i = 0; i <_nb_vex; ++i)
	{
		cout << _vexs->at(i) << " : ";
		_radjlists[i].show();
	}
}

template <typename T, typename U>
template <typename T1, typename U1>
void graph_adjlist<T, U>::vexnode<T1, U1>::
append(typename graph_adjlist<T, U>::arcnode<U1> * an)
{
	//0 --> 1
	if(firstarc == nullptr)
	{
		firstarc = an;
		lastarc = an;
	}
	else
	{
		lastarc->nextarc = an;
		lastarc = an;
	}
	size++;
}


template <typename T, typename U>
template <typename T1, typename U1>
void graph_adjlist<T, U>::vexnode<T1, U1>::
show(void) const
{
	const typename graph_adjlist<T, U>::arcnode<U1> * p;
	for(p = firstarc; p; p = p->nextarc)
	{
		cout << *p << " ";
	}
	cout << endl;
}
#endif
