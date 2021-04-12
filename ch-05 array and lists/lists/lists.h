/** 20210412 20:23, zyj, GuangDong*/
#ifndef LISTS_H
#define LISTS_H
#include <cstdarg>
template <typename Atom>
class htlists
{
	private:
		template<typename Atom1>
		struct Node
		{
			typedef enum{ATOM = 0, LIST = 0} elem_type;
			elem_type tag;
			union 
			{
				Atom1 atom;
				struct {Node *hp, *tp;} ptr;
			};
		};
		typedef Node<Atom> node;
	private:
		node *_lists;
		int length;
	private:
		int depth(node * lists) const;
	public:
		typedef node htnode;
	public:
		/** TODO: how to create a lists*/
		htlists():_lists(nullptr){}
		htlists(int ct, ...);
		int depth(void) const{return depth(_lists);}
};

template <typename Atom>
class llists
{
	private:
		template<typename Atom1>
		struct Node
		{
			typedef enum{ATOM = 0, LIST = 0} elem_type;
			elem_type tag;
			union 
			{
				Atom1 atom;
				Node *hp;
			};
			Node * tp;
		};
	private:
		typedef Node<Atom> node;
		node *_lists;
};

template <typename Coef>
class mplist
{
	private:
		template<typename Coef1>
		struct mpnode
		{
			union
			{
				Coef1 coef;
				mpnode *hp;
			};
			int exp;
			mpnode * tp;
		};
	private:
		typedef mpnode<Coef> node;
		node *_lists;
};


/** htlists methods*/
template<typename Atom>
htlists<Atom>::
htlists(int ct, ...)
{
	va_list ap;
	htnode *e;
	int i;
	va_start(ap, ct);
	for(i = 0; i < ct; ++i)
	{
		e = va_arg(ap, int);
	}
}

template<typename Atom>
int htlists<Atom>::
depth(node * lists) const
{
	int max, dep;
	node *p;
	if(!lists) return 1;/** depth of empty lists is 1*/
	if(lists->tag == node::ATOM) return 0;/** depth of atom is 0*/

	for(max = 0, p = lists; p; p = p->ptr.tp)
	{
		dep = depth(p->ptr.hp);
		if(max < dep) max = dep;
	}
	return max + 1;
}
#endif
