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
class crosslist_matrix
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
		crosslist_matrix(int m, int n);
		crosslist_matrix(const array<T, 2> & a2);
		void show_rlists(void)const;
		void show_clists(void)const;
};

template<typename T>
crosslist_matrix<T>::
crosslist_matrix(int m, int n)
{
	//int i;
	_m = m;
	_n = n;
	_tu = 0;
	_rlists = new pnode[_m];
	_clists = new pnode[_n];

}

/** time: O(tu * (m+n))*/
template<typename T>
crosslist_matrix<T>::
crosslist_matrix(const array<T, 2> & a2):crosslist_matrix(a2.get_bound(1), a2.get_bound(2))
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
			  row_insert(pn);
			  col_insert(pn);
		  }
	  }
	  //cout << endl;
	}
	//cout << endl;
}

/** time:O(n)*/
template<typename T>
bool crosslist_matrix<T>::
row_insert(const pnode & pn)
{
	pnode & list = _rlists[pn->i];
	pnode cur;
	//int pos = 0;
	/** 0-->1 or before head*/
	if(list == nullptr || pn->j < list->j)
	{
		//cout << "0-->1 or before head\n";
		pn->right = list;
		list = pn;
		//cout << "#1 : " << *list << endl;
	}
	else
	{/** n-->n+1 */
		//cout << "n-->n + 1\n";
		for(cur = list; cur->right && cur->right->j < pn->j; cur = cur->right)
		  ;
		pn->right = cur->right;
		cur->right = pn;
	}
	//cout << "rlist[" << pn->i<< "]"<< " insert " << *pn << " at " << pos << endl;
	return true;
}

/** time:O(m)*/
template<typename T>
bool crosslist_matrix<T>::
col_insert(const pnode & pn)
{
	pnode & list = _clists[pn->j];
	pnode cur;
	int pos = 0;
	/** 0-->1 or before head*/
	if(list == nullptr || pn->i < list->i)
	{
		//cout << "0-->1 or before head\n";
		pn->down = list;
		list = pn;
		//cout << "#1 : " << *list << endl;
	}
	else
	{/** n-->n+1 */
		//cout << "n-->n + 1\n";
		for(cur = list; cur->down && cur->down->i < pn->i; cur = cur->down)
		  pos++;
		pn->down = cur->down;
		cur->down = pn;
	}
	//cout << "rlist[" << pn->i<< "]"<< " insert " << *pn << " at " << pos << endl;
	return true;
}

template<typename T>
void crosslist_matrix<T>::
show_rlists(void)const
{
	int i;
	pnode cur;
	for(i = 0; i < _m; ++i)
	{
		for(cur = _rlists[i]; cur; cur = cur->right)
		  cout << *cur;
		cout << endl;
	}
}

template<typename T>
void crosslist_matrix<T>::
show_clists(void)const
{
	int i;
	pnode cur;
	for(i = 0; i < _n; ++i)
	{
		for(cur = _clists[i]; cur; cur = cur->down)
		  cout << *cur;
		cout << endl;
	}
}
#endif
