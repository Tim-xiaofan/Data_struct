/** 20210330 20:54, zyj, GuangDong*/
//Polymial.h
#ifndef POLYMIAL_H
#define POLYMIAL_H
#include "../list-adt/List.h"
#include <iostream>
#include <cstdlib>

template<typename T1 = float, typename T2 = int>
struct Item
{
	T1 coef;
	T2 expn;
	Item(T1 c = 0, T2 e = 0):coef(c), expn(e){}
	Item & operator-(void){coef = -coef; return *this;};
	Item operator-(void)const{return Item(-coef, expn);};
	Item operator-(const Item & i) const;
	Item operator+(const Item & i) const;
	Item operator*(const Item & i) const{return Item(coef * i.coef, expn + i.expn);};
};

template<typename T1, typename T2>
Item<T1, T2> Item<T1, T2>::
operator-(const Item & i) const
{
	if(i.expn == expn)
	  return Item(coef - i.coef, expn);
	else
	{
		std::cerr << "operator- : not same expn, first is "
			<< expn <<" and second is "<< i.expn <<"\n";
		abort();
	}
}

template<typename T1, typename T2>
Item<T1, T2> Item<T1, T2>::
operator+(const Item & i) const
{
	if(i.expn == expn)
	  return Item(coef + i.coef, expn);
	else
	{
		std::cerr << "operator+ : not same expn, first is "
			<< expn <<" and second is "<< i.expn <<"\n";
		abort();
	}
}

template<typename T1, typename T2>
std::ostream & operator<<(std::ostream & os, const Item<T1, T2> & it)
{
	os << "<" << it.coef << "," << it.expn << ">";
	return os;
}

template<typename Item> 
class Polymial: private List<Item>
{
	private:
		typedef List<Item> base;
		enum {default_size = 16};
	private:
		bool append(const Item & i){return base::append(i);}
	public:
		typedef typename base::input_iterator input_iterator;
		typedef typename base::fwd_iterator fwd_iterator;
		Polymial(int size = default_size):base(size){}
		Polymial(const Item *is, int ct);
		Polymial(Polymial && P) :base((std::move(P))) 
		{
			//std::cout << "-------Polymial-------\n";
			std::cout << "Polymial : move constructor\n";
			//show();
			//std::cout << "-------Polymial-------\n";
		}
		Polymial(const Polymial & P) = delete;
		~Polymial(){/**std::cout << "~Polymial()\n";*/}
		Polymial & operator=(const Polymial & P);
		Polymial & operator=(Polymial && P);
		/** Polymial + Polymial*/
		Polymial operator+(const Polymial & P) const;
		/** Polymial - Polymial*/
		Polymial operator-(const Polymial & P) const;
		/** TODO:Polymial * Polymial*/
		Polymial operator*(const Polymial & P) const = delete;
		/** TODO:Polymial * item */
		Polymial operator*(const Item & i) const = delete;
		/** TODO:item * Polymial */
		friend operator*(const Item & i, const Polymial & P) const = delete;
		int length() const {return base::length();}
		int size() const {return base::size();}
		bool puts(const Item *is, int ct);
		bool put(const Item &i);
		bool get_n(int pos, Item & i) const;
		void show()const{base::show();}
		void clear(){base::clear();}
		/** */
		input_iterator begin(void) const {return base::begin();}
		input_iterator end(void) const {return base::end();}
		fwd_iterator begin(void)  {return base::begin();}
		fwd_iterator end(void)  {return base::end();}
};


template<typename Item>
Polymial<Item>::
Polymial(const Item *is, int ct):base::List(2 * ct)
{
	int j;
	for(j = 0; j < ct; j++)
	  put(is[j]);
}


/**
 * time:O(n)
 * normal assignment operator
 **/
template<typename Item>
Polymial<Item> & Polymial<Item>::
operator=(const Polymial & P)
{
	input_iterator it;
	/** self check*/
	if(this == & P) return *this;

	/** clear all items currently*/
	base::clear();
	for(it = P.begin(); it != P.end(); ++it)
	  base::append(*it);//O(1)
	return *this;
}


/**
 * time:O(1)
 * move assignment operator
 **/
template<typename Item>
Polymial<Item> & Polymial<Item>::
operator=(Polymial && P)
{
	base::operator=(std::move(P));
	std::cout << "Polymial : move assignment\n";
	return *this;
}

/**  time:O(n + n) **/
template<typename Item>
Polymial<Item> Polymial<Item>::
operator+(const Polymial & P) const
{
	Polymial<Item> sum(length() + P.length());
	input_iterator it1 = begin(), it2 = P.begin();

	while(it1 != end() && it2 != P.end())
	{
		  if((*it1).expn < (*it2).expn) 
		  {
			  sum.append(*it1);
			  ++it1;
		  }
		  else if((*it1).expn > (*it2).expn) 
		  {
			  sum.append(*it2);
			  ++it2;
		  }
		  else 
		  {/** same expn*/
			  if((*it1).coef + (*it2).coef != 0)
				sum.append(Item((*it1).coef + (*it2).coef, (*it1).expn));
			  ++it1;
			  ++it2;
		  }
	}

	/** handle remaining*/
	while(it1 != end() )
	{
		sum.append(*it1);
		++it1;
	}
	while(it2 != P.end() )
	{
		sum.append(*it2);
		++it2;
	}
	//std::cout << "sum ：";
	//sum.show();
	return (sum);
}

/**  time:O(n + n) **/
template<typename Item>
Polymial<Item> Polymial<Item>::
operator-(const Polymial & P) const
{
	Polymial<Item> sum(length() + P.length());
	input_iterator it1 = begin(), it2 = P.begin();

	while(it1 != end() && it2 != P.end())
	{
		  if((*it1).expn < (*it2).expn) 
		  {
			  sum.append(*it1);
			  ++it1;
		  }
		  else if((*it1).expn > (*it2).expn) 
		  {/** - */
			  sum.append(-(*it2));
			  ++it2;
		  }
		  else 
		  {/** same expn*/
			  if((*it1).coef - (*it2).coef != 0)
				sum.append(Item((*it1).coef - (*it2).coef, (*it1).expn));
			  ++it1;
			  ++it2;
		  }
	}

	/** handle remaining*/
	while(it1 != end() )
	{
		sum.append(*it1);
		++it1;
	}
	while(it2 != P.end() )
	{
		sum.append(-(*it2));
		++it2;
	}
	//std::cout << "sum ：";
	//sum.show();
	return (sum);
}


/** put item into list according expn and keep items in order
 *	time:O(n)
 **/
template<typename Item>
bool Polymial<Item>::
put(const Item & i)
{
	int pos;
	typename base::input_iterator it;
	pos = 0;
	for(it = base::begin(); it != base::end(); ++it)
	{
		if(i.expn > (*it).expn) 
		{
			//std::cout << i.expn << " > " << (*it).expn << std::endl;
			pos++;
		}
		else if(i.expn == (*it).expn) return false;
	}
	//std::cout << "pos = " << pos << std:: endl;
	return base::insert_n(pos, i);
}

#endif
