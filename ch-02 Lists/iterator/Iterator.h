/* 20210329 20:13, zyj, GuangDong*/
//DuList.h
#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>

template<typename Node>
class iterator : public std::iterator<std::input_iterator_tag, Node>
{
	protected:
		Node * _pn;
	public:
		iterator(Node * pn = nullptr) : _pn(pn) {}
		virtual const typename Node::item_type & 
			operator*() const  { return _pn->_i;}
		iterator & operator++();
		iterator operator++(int);
		iterator & operator=(Node *pn){_pn = pn; return *this;}
		iterator & operator=(const iterator &) = default;
		bool operator==(const iterator & it) const {return (_pn == it._pn);}
		bool operator!=(const iterator & it) const {return (_pn != it._pn);}
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
