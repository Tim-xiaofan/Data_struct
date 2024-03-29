/** 20210721 21:15, zyj, GuangDong*/
//huffman_tree.h -- huffman tree
#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H
#include <iostream>
#include <cstring>

using std::cout;
using std::cerr;
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
			friend std::ostream & 
                operator<<(std::ostream & os, const struct Node nd)
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
		enum {OK, INVALAV, INVALCD};
	private:
		node *_nds;//node array
		int _ct;//node count : 2n - 1
		int _n;//character count
		char **_codes;//encode for each character 
		Data *_chars;// character array
	public:
		huffman_tree() : _nds(nullptr), _ct(0), 
        _n(0), _codes(nullptr), _chars(nullptr){}
		~huffman_tree();
		huffman_tree(Data * codes, float * weigths, int n);
		int decode(const char *code, int ilen,  char *decode, int & olen);
		void print_codes() const ;
		void print_nds(void) const;
	private:
		void select_2s(int high, int & s1, int & s2);
};

/**
  @param    n   需要编码的符号数量
 */

template <typename Data>
huffman_tree<Data>::
huffman_tree(Data * chars, float * weigths, int n)
{
	int i, j, s1, s2;//smalls

	_ct = 2 * n - 1;//huffman树只有0度和2度节点,正则二叉树(严格二叉树)
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
        //select the fisrt smallest and second smallest
		select_2s(i - 1, s1, s2);
		_nds[i].lchild = s1;
		_nds[i].rchild = s2;
		_nds[i].weigth = _nds[s1].weigth + _nds[s2].weigth;
		_nds[s1].parent = i;
		_nds[s2].parent = i;
	}

	/** get code for each character : from leaves to root*/
	char * cd = new char[n];
	int start, parent, current;
	cd[n -1] = '\0';
	for(i = 1; i <= n; ++i)
	{
		start =  n - 1;
		for(current = i, parent = _nds[current].parent;
					parent != 0; 
					current = parent, 
                    parent = _nds[current].parent)
		{
			/** from left 0, from right 1*/
			if(_nds[parent].lchild == current) cd[--start] = '0';
			else cd[--start] = '1';
		}
        //malloc memory according to real encode-len
		_codes[i - 1] = new char[n - start];
		strcpy(_codes[i - 1], &cd[start]);
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

/** 
  parent is 0 and weigth is small
  选择最小的两棵树：
 */
template <typename Data>
void huffman_tree<Data>::
select_2s(int high, int & s1, int & s2)
{
	int i;
	s1 = s2 = -1;

    /** lookup first*/
	for(i = 1; i <= high; ++i)
	{
		if(_nds[i].parent == 0)
		{
			s1 = i;
			break;
		}
	}
	
    if(s1 == -1) return;

	for(i = s1 + 1; i <= high; ++i)
	{
		if(_nds[i].parent == 0)
		{
			s2 = i;
			break;
		}
	}

	if(s2 == -1) return;

	for(i = s1; i <= high; ++i)
	{
		if(_nds[i].parent == 0)
		{
			if(_nds[i].weigth < _nds[s1].weigth)
			{//第一小
				s2 = s1;
				s1 = i;
			}
			else if(_nds[i].weigth < _nds[s2].weigth && i != s1)
			{//第二小
				s2 = i;
			}
		}
	}
}

template <typename Data>
int huffman_tree<Data>::
decode(const char *code, int ilen,  char *decode, int & olen)
{
	int current, process = 0;
	if(olen == 0 || decode == nullptr)
	{
		cerr << "Invalid argument\n";
		return INVALAV;
	}
	olen = 0;
	current = _ct;//root
	do
	{
		if(code[process++] == '0') current=_nds[current].lchild;
		else current = _nds[current].rchild;
		if(_nds[current].lchild == 0)
		{//leaves
			decode[olen++] = _chars[current - 1];
			current = _ct;//root
			continue;
		}
	}while(process < ilen);
	//cout << "ilen " << ilen << endl;
	//cout << "process " << process << ", current " << current << endl;
	return OK;
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
