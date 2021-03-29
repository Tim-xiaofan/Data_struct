/* 20210323 22:25, zyj, GuangDong*/
//List.h
#include <iostream>
#include <iterator>
#ifndef LIST_H
#define LIST_H

template<typename Node>
class iterator : public std::iterator<std::input_iterator_tag, Node>
{
	private:
		Node * _pn;
	public:
		iterator(Node * pn = nullptr) : _pn(pn) {}
		virtual const typename Node::item_type & 
			operator*() const  { return _pn->_i;}
		iterator & operator++();
		iterator operator++(int);
		iterator & operator=(Node *pn){_pn = pn; return *this;}
		iterator & operator=(const iterator & it){_pn = it._pn; return *this;}
		bool operator==(const iterator & it) const {return (_pn == it._pn);}
		bool operator!=(const iterator & it) const {return (_pn != it._pn);}
};

template <typename Item>
class Node
{
	public:
		typedef Item item_type;
		Item _i;
		Node *_next;
	public:
		Node():_next(nullptr){}
		explicit Node(const Item &i):_i(i), _next(nullptr){}
		Node(const Node &nd):_i(nd._i), _next(nd._next){}
		Node & operator=(const Node & node) = default;
		~Node(){};
};


template<typename Item>
class List
{
    /** data*/
    private:
		typedef Node<Item> node;
		enum {DEFAULT_SIZE = 16};
        int _size, _length, _current;
        node *_head, *_tail, *_cursor;
	
	/** methods*/
	public:
		/** types*/
		typedef iterator<node> input_iterator;
		typedef Item item_type;

		/** constructor and assignment operator*/
		explicit List(int size = DEFAULT_SIZE);
		List(const List & l);
		List(const Item *is, int n);
		List & operator=(const List &) = delete;
		~List();
		
		/** interface*/
		int length(void) const {return _length;}
		int size(void) const {return _size;}
		int current(void) const {return _current;}
		bool set_cursor(int pos);
		bool reset_cursor(void);
		bool get_n(int pos, Item &i) const ;
		bool get_next(Item &i);
		bool del_n(int pos, Item &i);
		bool insert_n(int pos, const Item & i);
		bool append(const Item & i);
		bool append_bulk(const Item *is, int n);
		void show(void) const;
		int search(const Item & i) const;
		bool is_full(void) const {return (_length == _size);}
		bool is_empty(void) const {return (_length == 0);}
		void clear(void);

		/** iterator methods*/
		input_iterator begin(void) const {return _head->_next;}
		input_iterator end(void) const {return _tail->_next;}
	private:
		node * locate_n(int pos);
		bool out_bound(int pos)const{ return (pos < 0 || pos >= _length);}
};

template <typename Node>
iterator<Node> & iterator<Node>::
operator++()/** ++i, pre increment operator*/
{
	_pn =  _pn->_next;
	return *this;
}

template <typename Node>
iterator<Node> iterator<Node>::
operator++(int)/** i++, post increment operator*/
{
	iterator tmp;
	_pn =  _pn->_next;
	return tmp;
}

template <typename Item> 
List<Item>::
List(int size) 
{
	_length = 0;
	_size = size;
	_current = -1;
	_head = new node();
	_tail = _head;
	_cursor = _head;
}

template <typename Item>
List<Item>::
List(const Item *is, int n):List(2 * n)
{
	append_bulk(is, n);
}

template <typename Item>
List<Item>::
List(const List & l):List(l._size)
{
	input_iterator it;
	for(it = l.begin(); it != l.end(); ++it)
	  append(*it);
}

template <typename Item>
List<Item>::
~List()
{
	node *p = _head, *tmp;
	/** free nodes*/
	while(p)
	{
		tmp = p;
		p = p->_next;
		delete tmp;
	}
}

/** clear all items in list*/
template <typename Item>
void List<Item>::
clear(void)
{
	node *p = _head->_next, *tmp;
	/** free nodes*/
	while(p)
	{
		tmp = p;
		p = p->_next;
		delete tmp;
	}
	_head->_next = nullptr;
	_tail = _head;
	_length = 0;
	_current = -1;
	_cursor = _head;
}

template <typename Item>
typename List<Item>::node * List<Item>::
locate_n(int pos)
{
	node *p;
	int j;

	p = _head;
	for(j = 0; j <= pos; j ++)
	  p = p->_next;

	return p;
}

/** 
 * O(n)
 * set cursor to specified position
 **/
template <typename Item>
bool List<Item>::
set_cursor(int pos)
{
	node *p;

	if(pos >= _length)
	  return false;

	p = locate_n(pos);
	_cursor = p;
	_current = pos;
	return true;
}

/**
 * time:O(1)
 * set cursor to head
 **/
template <typename Item>
bool List<Item>::
reset_cursor(void)
{
	return set_cursor(-1);
}

/** 
 * time: O(1)
 * add an item at list tail
 **/
template <typename Item>
bool List<Item>::
append(const Item & i)
{
	if(is_full())
	{
		fprintf(stderr, "list is full\n");
		return false;
	}

	node *tmp = new node(i);
	/** 0 --> 1*/
	if(is_empty())
	{
		_head->_next = tmp;
		_tail = tmp;
		_length++;
	}
	else
	{/** n --> n + 1*/
		_tail->_next = tmp;;
		_tail = tmp;
		_length++;
	}
	return true;
}

template <typename Item>
bool List<Item>::
append_bulk(const Item *is,  int n)
{
	int i;

	if(n > (_size - _length))
	{
		fprintf(stderr, "no enough space.\n");
		return false;
	}

	for(i = 0; i < n; i++)
		append(is[i]);
	return true;
}

/** 
 * time : O(1)
 * get next item of current position
 **/

template <typename Item>
bool List<Item>::
get_next(Item & i)
{
	if(_current == _length -1 )
	  return false;
	_cursor = _cursor->_next;
	_current++;
	i = _cursor->_i;
	return true;
}


/** 
 * time : O(n)
 * get nth item of list
 **/
template <typename Item>
bool List<Item>::
get_n(int pos, Item & i) const
{
	int j;
	node *p;

	if(is_empty())
		return false;
	if(out_bound(pos))
	{
		fprintf(stderr, "ERROR:out of boundary\n");
		return false;
	}

	p = _head->_next;
	for(j = 0; j < pos; j++)
	  p = p->_next;
	i = p->_i;

	return true;
}

/** 
 * time : O(n)
 * delete nth item of list
 **/
template <typename Item>
bool List<Item>::
del_n(int pos, Item &i)
{
	node *p, *tmp;
	int j;

	if(out_bound(pos))
	{
		fprintf(stderr, "ERROR : out of boundary\n");
		return false;
	}

	/** 1--> 0 */
	if(_length == 1)
	{
		i = _tail->_i;
		delete _tail;
		_tail = nullptr;
		_head->_next = _tail;
	}
	else
	{/** n --> n - 1*/
		/** locate to i-1*/
		p = _head;
		for(j = 0; j < pos; j++)
		  p = p->_next;

		/** = operator*/
		tmp = p->_next;
		i = tmp->_i;
		//fprintf(stdout, "rm item : ");
		//item_show(*e);
		//fprintf(stdout, "\n");

		/** adjust and free node*/
		p->_next = tmp->_next;
		delete tmp;
	}

	_length--;
	return true;
}

/** 
 * time : O(n)
 * insert an item at nth
 **/
template <typename Item>
bool List<Item>::
insert_n(int pos, const Item &i)
{
	node *tmp, *p;

	if(is_full())
	{
		fprintf(stderr, "ERROR : list is full\n");
		return false;
	}

	if(pos < 0)
	{
		fprintf(stderr, "ERROR : out of boundary\n");
		return false;
	}

	/** just add to tail*/
	if(pos > _length) pos = _length;

	tmp = new node(i);

	/** 0 --> 1*/
	if(is_empty())
	{
		_tail = tmp;
		_head->_next = _tail;
	}
	else
	{/** n --> n + 1*/
		/** locate pos - 1*/
		p = locate_n(pos - 1);
		tmp->_next = p->_next;
		p->_next = tmp;
	}
	_length++;
	return true;
}

/** 
  * time: O(n)
  * @return -1 indicates item is not in list , or return index*/
template <typename Item>
int List<Item>::
search(const Item &i) const
{
	int pos;
	bool found;
	node * p;

	found = false;
	pos = 0;
	p = _head;
	while((p = p->_next))
	{
	  if(i == p->_i)
	  {
		  found = true;
		  break;
	  }
	  pos++;
	}

	if(found) return pos;
	else return -1;
}

template <typename Item>
void List<Item>::
show(void)const
{
	node *p;

	if(is_empty())
	{
		printf("EMPTY LIST!\n");
		return;
	}

	p = _head->_next;
	while(p != NULL)
	{
		std::cout << p->_i << " ";
		p = p->_next;
	}
	printf("\n");
}
#endif
