/* 20210329 20:13, zyj, GuangDong*/
//DuList.h
#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>

template<typename Node>
class forward_iterator;

template<typename Node>
class iterator : public std::iterator<std::input_iterator_tag, Node>
{
	protected:
		Node * _pn;
	public:
		iterator(Node * pn = nullptr) : _pn(pn) {}
		virtual const typename Node::item_type & 
			operator*() const  { return _pn->_i;}
		//virtual typename Node::item_type & 
		//	operator*()  { return _pn->_i;}
		iterator & operator++(){_pn = _pn->_next; return *this;};
		iterator operator++(int){iterator tmp; _pn =_pn->_next; return tmp;}
		iterator & operator=(Node *pn){_pn = pn; return *this;}
		iterator & operator=(const iterator &) = default;
		iterator & operator=(const forward_iterator<Node> & it) {_pn = it._pn; return *this;};
		bool operator==(const iterator & it) const {return (_pn == it._pn);}
		bool operator!=(const iterator & it) const {return (_pn != it._pn);}
		bool operator!=(const forward_iterator<Node> & it) const {return (_pn != it._pn);}
};

template<typename Node>
class forward_iterator :  public std::iterator<std::forward_iterator_tag, Node>
{
	private:
		Node * _pn;
	public:
		forward_iterator(Node * pn = nullptr) : _pn(pn) {}
		typename Node::item_type & 
			operator*() { return _pn->_i;}
		forward_iterator & operator++(){_pn = _pn->_next; return *this;};
		forward_iterator operator++(int){forward_iterator tmp; _pn =_pn->_next; return tmp;}
		forward_iterator & operator=(Node *pn){_pn = pn; return *this;}
		forward_iterator & operator=(const forward_iterator &) = default;
		forward_iterator & operator=(iterator<Node> & it){ _pn = it->_pn; return *this;}
		bool operator==(const forward_iterator & it) const {return (_pn == it._pn);}
		bool operator!=(const forward_iterator & it) const {return (_pn != it._pn);}
		friend class iterator<Node>;
};


template<typename Node>
class bidirectional_itrator : public iterator<Node> 
{
	private:
		typedef  iterator<Node> base;
	public:
		bidirectional_itrator(Node * pn = nullptr) : base(pn){}
		bidirectional_itrator & operator=(Node *pn){ return base::operator=(pn);}
		typename Node::item_type & 
			operator*() { return base::_pn->_i;}
		bidirectional_itrator & operator++(){return base::operator++();}
		bidirectional_itrator & operator++(int){return base::operator++(0);}
		/** pre decrement operator*/
		bidirectional_itrator & 
			operator--(){base::_pn = base::_pn->_prior; return *this;};
		/** post decrement operator*/
		bidirectional_itrator 
			operator--(int){bidirectional_itrator tmp; base::_pn = base::_pn->_prior; return tmp;}
};

#endif
