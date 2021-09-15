/** 20210915, zyj, GuangDong*/
#ifndef _HASHTABLE
#define _HASHTABLE
#include<iostream>
using std::cout;
using std::cerr;
using std::endl;

template <typename elem_t>
class hashtable
{
	private:
		enum{MAX_SIZE = 512};
		template<typename elem_t1>
		struct Node
		{
			elem_t e;
			bool existed;
			Node():existed(false){}
		};
		typedef Node<elem_t> node;
		
		int hashsize[MAX_SIZE] = {997, 173, 251, 337};
		node *_table;
		int _count;
		int _sizeindex;// hashsize[sizeindex]为当前容量
		
		static elem_t default_cmp(const elem_t & a, const elem_t & b) {return (a - b);}
		int hash(const elem_t & e);
		int collision(int i);
	public:
		enum{SUCCESS = 0, UNSUCCESS = 1, DUPLICATE = 2};
		
		hashtable():_table(nullptr), _count(0), _sizeindex(4){}
		
		template<typename cmp_t = elem_t(*)(const elem_t &, const elem_t &)>
		int search(const elem_t & e, const cmp_t & cmp = default_cmp);
};

template <typename elem_t>
template <typename cmp_t>
int hashtable<elem_t>::
search(const elem_t & e, const cmp_t & cmp)
{
	int c = 0, i = hash(e);
	
	while(_table[e].existed && 
				cmp(e, _table[i].e) != 0)
	{
		++c;
		i = collision(i);
	}
	
	if(cmp(e, _table[i].e) == 0)
	  return SUCCESS;
	else 
	  return UNSUCCESS;
}


template <typename elem_t>
int hashtable<elem_t>::
hash(const elem_t & e)
{
	return 0;
}

template <typename elem_t>
int hashtable<elem_t>::
collision(int i)
{
	return 0;
}
#endif
