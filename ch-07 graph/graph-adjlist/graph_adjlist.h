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
#include "List.h"
using std::endl;
using std::cout;
using std::cerr;

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
			arcnode(int i = 0, U1 w = 0):
				adjvex(i), weigth(w){}
			friend std::ostream & operator<<(std::ostream & os, const struct arcnode & a)
			{
				os << "(adjvex=" << a.adjvex << ", weigth=" << a.weigth << ")";
				return os;
			}
		};
		template<typename T1, typename U1>
		struct vexnode
		{
			T1 data;
			List<arcnode<U1>> adjlist;
			vexnode():adjlist(MAX_NB_VEXS){}
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
	public:
		~graph_adjlist(){delete _vexs, delete [] _adjlists;}
		graph_adjlist():_nb_vex(0), _nb_arc(0), _kind(DG), _vexs(nullptr), _adjlists(nullptr){}
		graph_adjlist(const a1 & vexs, const a2 & arcs, graph_kind kind);
		void show_adjlists(void)const;
		/** O(1)*/
		int get_degree(int i) const {return (_kind == UDN || _kind == UDG) ?
			_adjlists[i].adjlist.length() : -1;}
		void show_degrees(void) const;
		/** O(1)*/
		int get_odegree(int i) const {return (_kind == DN || _kind == DG) ?
			_adjlists[i].adjlist.length() : -1;}
		/** O(2 * e)*/
		int get_idegree(int i) const;
		void show_iodegrees(void) const;
		const char * kind_str(void) const;
		bool is_adj(int i, int j) const;
};

/** O(n*n)*/
template <typename T, typename U>
graph_adjlist<T, U>::
graph_adjlist(const a1 & vexs, const a2 & arcs, graph_kind kind)
{
	int i, j;
	T current;
	
	_nb_vex = vexs.get_bound(1);
	_vexs = a1::instance(vexs);// O(n)
	_nb_arc = 0;
	_adjlists = new vnode[_nb_vex];//O(n * n)
	for(i = 0; i < _nb_vex; ++i)
	  for(j = 0; j < _nb_vex; ++j)
		if((current = arcs.at(i, j)) != 0)
		{
			_adjlists[i].adjlist.append(anode(j, current));
			_nb_arc++;
		}
	_kind = kind;
}

template <typename T, typename U>
void graph_adjlist<T, U>::
show_adjlists(void)const
{
	int i;

	for(i = 0; i <_nb_vex; ++i)
	{
		cout << _vexs->at(i) << " : ";
		_adjlists[i].adjlist.show();
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

template<typename T, typename U>
int graph_adjlist<T, U>::
get_idegree(int i) const
{
	int k, d = 0;
	typename List<anode>::const_iterator it;
	for(k = 0; k < _nb_vex; ++k)
	  for(it = _adjlists[k].adjlist.begin();
				  it !=  _adjlists[k].adjlist.end(); ++it)
		  if((*it).adjvex == i) d++;//adj is i
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
	typename List<anode>::const_iterator it;
	for(it = _adjlists[i].adjlist.begin();
				it !=  _adjlists[i].adjlist.end(); ++it)
	  if((*it).adjvex == j) return true;
	return false;
}
#endif
