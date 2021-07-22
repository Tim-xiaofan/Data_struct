/** 20210721 21:15, zyj, GuangDong*/
//huffman_tree.h -- huffman tree
#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

template <typename Data>
class huffman_tree
{
	private:
		template <typename Data1>
		struct Node
		{
			float weigth;
			int parent, lchild, rchild;
			friend std::ostream & operator<<(std::ostream & os, const struct Node nd)
			{
				os << "weigth = " <<nd.weigth << 
					", parent = " <<nd.parent << 
					", lchild = " <<nd.lchild << 
					", rchild = " <<nd.rchild ;
				return os;
			}
		};
	public:
		typedef Node<Data> node;
	private:
		node *_nds;//node array
		int _ct;//node count : 2n - 1
		int _n;//character count
		char **_codes;//encode for each character 
		Data *_chars;// character array
	public:
		huffman_tree() : _nds(nullptr), _ct(0), _n(0), _codes(nullptr), _chars(nullptr){}
		~huffman_tree();
		huffman_tree(Data * codes, float * weigths, int n);
		void print_codes() const ;
		void print_nds(void) const;
	private:
		void select_2s(int high, int & s1, int & s2);
};

template <typename Data>
huffman_tree<Data>::
huffman_tree(Data * chars, float * weigths, int n)
{
	int i, j, s1, s2;//small

	_ct = 2 * n - 1;
	_n = n;
	_nds = new node[_ct + 1];// 0 is unused
	_codes = new char*[n];
	_chars = new Data[n + 1];

	memcpy(_chars, chars, sizeof(Data) * n);
	_chars[n] = '\0';

	/** initiate node array*/
	for(i = 1, j = 0; i <= n && j < n; ++i, ++j)
	{//leaves
		_nds[i].weigth = weigths[j];
		_nds[i].parent = 0;
		_nds[i].lchild = 0;
		_nds[i].rchild = 0;
	}
	for(i = n + 1; i <= _ct; ++i)
	{//non-leaves
		_nds[i].weigth = 0;
		_nds[i].parent = 0;
		_nds[i].lchild = 0;
		_nds[i].rchild = 0;
	}
	
	/** construct the tree*/
	for(i = n + 1; i <= _ct; ++i)
	{
		//cout << "------------------------------------------------\n";
		//print_nds();
		select_2s(i - 1, s1, s2);//select the two smallest
		//printf("s1 = %d, s2 =%d\n", s1, s2);
		//cout << _nds[s1] << endl;
		//cout << _nds[s2] << endl;
		//cout << endl << endl;
		_nds[i].lchild = s1;
		_nds[i].rchild = s2;
		_nds[i].weigth = _nds[s1].weigth + _nds[s2].weigth;
		_nds[s1].parent = i;
		_nds[s2].parent = i;
	}
	//print_nds();

	/** get code for each character : from leaves to root*/
	char * cd = new char[n];
	int start, parent, current;
	cd[n -1] = '\0';
	for(i = 1; i <= n; ++i)
	{
		start =  n - 1;
		for(current = i, parent = _nds[current].parent;
					parent != 0; 
					current = parent, parent = _nds[current].parent)
		{
			/** from left 0, from right 1*/
			if(_nds[parent].lchild == current) cd[--start] = '0';
			else cd[--start] = '1';
		}
		_codes[i - 1] = new char[n - start];//malloc memory according to real encode-len
		strcpy(_codes[i - 1], &cd[start]);
		//cout <<  "cd : " << &cd[start] << endl;
	}
	delete [] cd;
}

template <typename Data>
huffman_tree<Data>::
~huffman_tree()
{
	int i;

	delete [] _nds;
	delete [] _chars;
	for(i = 0; i < _n; ++i)
	  delete [] _codes[i];
	delete [] _codes;
}

/** parent is 0 and weigth is small*/
template <typename Data>
void huffman_tree<Data>::
select_2s(int high, int & s1, int & s2)
{
	int i;
	s1 = s2 = -1;
	for(i = 1; i <= high; ++i)
	{
		if(_nds[i].parent == 0)
		{
			s1 = i;
			break;
		}
	}
	if(s1 == -1) return;
	//cout << "s1 :" << _nds[s1] << endl;
	for(i = s1 + 1; i <= high; ++i)
	{
		if(_nds[i].parent == 0)
		{
			s2 = i;
			break;
		}
	}
	if(s2 == -1) return;
	//cout << "s2 :" << _nds[s2] << endl;

	for(i = s1; i <= high; ++i)
	{
		//cout << "current  : " << _nds[i] << endl;
		if(_nds[i].parent == 0)
		{
			if(_nds[i].weigth < _nds[s1].weigth)
			{
				s2 = s1;
				s1 = i;
				//cout << "update s1 : " << _nds[s1] << endl;
				//cout << "update s2 : " << _nds[s2] << endl;
			}
			else if(_nds[i].weigth < _nds[s2].weigth && i != s1)
			{
				s2 = i;
				//cout << "update s2 : " << _nds[s2] << endl;
			}
		}
	}
}


template <typename Data>
void huffman_tree<Data>::
print_nds(void) const
{
	int i;

	for(i = 1; i <=_ct; ++i)
	  cout <<  "# " << i << " "
		  << _nds[i] << endl;
}

template <typename Data>
void huffman_tree<Data>::
print_codes() const
{
	int i;
	for(i = 0; i < _n; ++i)
	{
		cout << _chars[i] << " : ";
		cout << _codes[i] << endl;
	}
}
#endif
