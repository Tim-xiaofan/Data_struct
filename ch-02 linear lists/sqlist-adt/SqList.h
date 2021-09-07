/* 20210323 22:25, zyj, GuangDong*/
//SqList.h
#ifndef _SQLIST_H
#define _SQLIST_H
#include <iostream>
#include <iterator>
#include <cstring> /** memset*/
#include <string>

//
//template <typename Item>
//class Node
//{
//	public:
//		typedef Item item_type;
//		Item _i;
//		Node *_next;
//	public:
//		Node():_next(nullptr){}
//		explicit Node(const Item &i):_i(i), _next(nullptr){}
//		Node(const Node &nd):_i(nd._i), _next(nd._next){}
//		Node & operator=(const Node & node) = default;
//		~Node(){};
//};


template<typename Item>
class SqList
{
	private:
		template<typename Item1>
		class iterator : public std::iterator<std::input_iterator_tag, Item1>
		{
			private:
				Item1 * _pi;
			public:
				iterator(Item1 * pi = nullptr) : _pi(pi) {}
				virtual const Item1 & operator*() const{ return *_pi;}
				iterator & operator++(){++_pi; return *this;};
				iterator operator++(int){iterator tmp = *this; _pi++; return tmp;}
				iterator & operator=(Item *pi){_pi = pi; return *this;}
				iterator & operator=(const iterator & it){_pi = it._pi; return *this;}
				bool operator==(const iterator & it) const {return (_pi == it._pi);}
				bool operator!=(const iterator & it) const {return (_pi != it._pi);}
		};
		/** data*/
	private:
		enum {DEFAULT_SIZE = 16};
		int _size, _length;
		Item *_items;

		/** methods*/
	public:
		/** types*/
		typedef iterator<Item> input_iterator;
        typedef input_iterator const_iterator;
		typedef Item item_type;
        typedef Item elem_type;

		/** constructor and assignment operator*/
		explicit SqList(int size = DEFAULT_SIZE):_size(size), _length(0)
    {_items = new Item[size + 1];}
		SqList(const SqList & l);
		SqList(const Item *is, int n);
		SqList & operator=(const SqList &) = delete;
		~SqList(){delete [] _items;}

		/** interface*/
		int length(void) const {return _length;}
		int size(void) const {return _size;}
		bool get_n(int pos, Item &i) const ;
		bool del_n(int pos, Item &i);
		bool insert_n(int pos, const Item & i);
		bool append(const Item & i);
		bool append_bulk(const Item *is, int n);
		void show(const std::string & info = "") const;
		int search(const Item & i) const;
		bool is_full(void) const {return (_length == _size);}
		bool is_empty(void) const {return (_length == 0);}
		void clear(void){ _length = 0;}

		/** operators*/
		const Item & operator[](int pos) const { return _items[pos];}
		Item & operator[](int pos) { return _items[pos];}

		/** iterator methods*/
		input_iterator begin(void) const {return &_items[0];}
		input_iterator end(void) const {return &_items[_length];}
	private:
		bool out_bound(int pos)const{ return (pos < 0 || pos >= _length);}
};

/** */
template <typename Item>
SqList<Item>::
SqList(const Item *is, int n):SqList(2 * n)
{
	append_bulk(is, n);
}

template <typename Item>
SqList<Item>::
SqList(const SqList & l):SqList(l._size)
{
	_length = l._length;
	input_iterator it;
	for(it = l.begin(); it != l.end(); ++it)
	  append(*it);
}

/** 
 * time: O(1)
 * add an item at list tail
 **/
template <typename Item>
bool SqList<Item>::
append(const Item & i)
{
	if(is_full())
	{
		fprintf(stderr, "list is full\n");
		return false;
	}
	_items[_length++] = i; 
	return true;
}

template <typename Item>
bool SqList<Item>::
append_bulk(const Item *is,  int n)
{
	int pos;

	if(n > (_size - _length))
	{
		fprintf(stderr, "no enough space.\n");
		return false;
	}

	for(pos = 0; pos < n; pos++)
	  append(is[pos]);
	return true;
}

/** 
 * time : O(1) -- random access
 * get nth item of list, with boundary check
 **/
template <typename Item>
bool SqList<Item>::
get_n(int pos, Item & i) const
{
	if(is_empty())
	  return false;
	if(out_bound(pos))
	{
		//fprintf(stderr, "SqList::get_n:ERROR:out of boundary\n");
		return false;
	}

	i = _items[pos];
	return true;
}

/** 
 * time : O(n)
 * delete nth item of list
 **/
template <typename Item>
bool SqList<Item>::
del_n(int pos, Item &i)
{
	int j;

	if(out_bound(pos))
	{
		//fprintf(stderr, "SqList::del_n:ERROR : out of boundary\n");
		return false;
	}
	i = _items[pos];
	for(j = pos + 1; j < _length; j++)
	  _items[j - 1] = _items[j];
	_length--;
	return true;
}

/** 
 * time : O(n)
 * insert an item at nth
 **/
template <typename Item>
bool SqList<Item>::
insert_n(int pos, const Item &i)
{
	int j;

	if(is_full())
	{
		//fprintf(stderr, "SqList::insert_n:ERROR : list is full\n");
		return false;
	}

	if(pos < 0)
	{
		//fprintf(stderr, "SqList::insert:ERROR : out of boundary\n");
		return false;
	}

	/** just add to tail*/
	if(pos > _length) pos = _length;

	/** move*/
	for(j = _length - 1; j >= pos; --j)
	  _items[j + 1] = _items[j];

	_items[pos] = i;
	_length++;
	return true;
}

/** 
 * time: O(n)
 * @return -1 indicates item is not in list , or return index*/
template <typename Item>
int SqList<Item>::
search(const Item &i) const
{
	int pos;
	bool found;

	found = false;
	for(pos = 0; pos < _length; ++pos)
	  if(_items[pos] == i)
	  {
		  found = true;
		  break;
	  }

	if(found) return pos;
	else return -1;
}

template <typename Item>
void SqList<Item>::
show(const std::string & info)const
{
	int pos;
    
    std::cout << info;
	if(is_empty())
	{
		//printf("EMPTY LIST!\n");
		return;
	}

	for(pos = 0; pos < _length; pos++)
	  std::cout << _items[pos] << " ";
	std::cout << "\n";
}
#endif
