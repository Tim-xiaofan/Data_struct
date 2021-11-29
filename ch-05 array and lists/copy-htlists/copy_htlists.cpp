/**20210412 08:50, zyj, GuaangDong */
// copy_htlists.cpp -- copy head-tail lists
#include <iostream>
#include "lists.h"

using std::cout;
using std::endl;

template<typename Atom>
void copy_htlists(htlists<Atom> & ldst, const htlists<Atom> & lsrc)
{
	//typedef typename htlists<Atom>::htnode node;
	typedef typename htlists<Atom>::phtnode pnode;
	pnode & pdst  = ldst.get_head();
	const pnode & psrc = lsrc.get_head();
	copy_htlists(pdst, psrc);
}

template<typename Node>
void copy_htlists(Node* & pdst, const Node* const & psrc)
{
	if(psrc == nullptr)
	{/** src is empty list */
		pdst = nullptr;
	}
	else
	{
		pdst = new Node;
		pdst->tag = psrc->tag;
		if(psrc->tag == Node::ATOM)
		{
			pdst->atom = psrc->atom;
		}
		else
		{
			/** copy list head*/
			copy_htlists(pdst->ptr.hp, psrc->ptr.hp);
			/** copy list tail*/
			copy_htlists(pdst->ptr.tp, psrc->ptr.tp);
		}
	}
}

int main(int ac, char *av[])
{
	htlists<char> la, lb;
	copy_htlists(la, lb);
	return 0;
}
