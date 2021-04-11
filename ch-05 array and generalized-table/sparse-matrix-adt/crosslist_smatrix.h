/** 20210411 11:04, zyj, GuangDong */
// crosslist_smatrix.h -- sparse matrix's crosslist implement
#ifndef CROSSLIST_SMATRIX_H
#define CROSSLIST_SMATRIX_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include "List.h"
#include "array.h"
//#define MIN(a,b) (((a)<=(b))?(a):(b))

using std::cout;
using std::endl;

template<typename T = int> class crosslist;

template<typename T>
class crosslist
{
	private:
		template<typename U = int>
		struct Node
		{
			typedef T value_type;
			int i, j;/** position*/
			T e;/** value*/
			Node *right, *down; 
			Node(int mi = 0, int mj = 0, const T & t = 0, 
						Node *mright = nullptr, Node *mdown = nullptr)
				:i(mi), j(mj), e(t), right(mright), down(mdown){}
			Node & operator=(const Node &) = default;// no deep copy
			friend std::ostream & operator<<(std::ostream & os, const Node & nd)
			{
				os << "<(" << nd.i <<"," << nd.j << ")" << "," << nd.e << ">";
				return os;
			}
		};
	private:
		typedef Node<T> node;
		typedef Node<T>* pnode;
		enum{MAX_CAPACITY = 1024};
		pnode *_rlists, *_clists; 
		int _m, _n ,_tu;
	private:
		bool row_insert(const pnode & pn);
		bool col_insert(const pnode & pn);
	public:
		crosslist(int m, int n);
		crosslist(const array<T, 2> & a2);
		void show_rlist(void)const;
		void show_right(void)const;
};

template<typename T>
crosslist<T>::
crosslist(int m, int n)
{
	_m = m;
	_n = n;
	_tu = 0;
	_rlists = new pnode[_m];
	_clists = new pnode[_n];
}

template<typename T>
crosslist<T>::
crosslist(const array<T, 2> & a2):crosslist(a2.get_bound(1), a2.get_bound(2))
{
	int i, j;
	pnode pn;
	for(i = 0; i < _m; ++i)
	{
	  for(j = 0; j < _n; ++j)
	  {
		  if(a2.at(i, j))
		  {
			  pn = new node(i, j, a2.at(i, j));
		  }
	  }
	  //cout << endl;
	}
	cout << endl;
}
#endif
