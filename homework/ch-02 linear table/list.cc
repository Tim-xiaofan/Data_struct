#include "list.h"
#include <iostream>
#include <cassert>
#include <climits>

namespace HOMEWORK_NS
{

using std::cout;
using std::endl;

list create_list(const std::vector<int> & il)
{
	list head = new node;
	list cur = head;
	for(const int& e: il)
	{
		cur->next = new node(e, nullptr);
		cur = cur->next;
	}
	return head;
}

void destroy_list(list& l)
{
	list tmp;
	while(l)
	{
		tmp = l;
		l = l->next;
		delete tmp;
	}
}

void print_list(const list& l, const char* info)
{
	std::cout << info;
	list p = l->next;
	while(p)
	{
		std::cout << p->data << " ";
		p = p->next;
	}
	std::cout << std::endl;
}

size_t count_list(const list& l)
{
	size_t len = 0;
	list p = l->next;
	while(p)
	{
		++len;
		p = p->next;
	}
	return len;
}

void assert_list(const list& l, const std::vector<int>& il)
{
	assert(il.size() == count_list(l));
	auto it = il.begin();
	list p = l->next;
	while(p)
	{
		assert(p->data == *it);
		++it;
		p = p->next;
	}
}

bool equal_list(const list& A, const list& B)
{
	list pa = A->next;
	list pb = B->next;
	while(pa && pb)
	{
		if(pa->data != pb->data)
		{
			return false;
		}
		pa = pa->next;
		pb = pb->next;
	}

	return !pa && !pb;
}

static void list_remove_and_next(node* &p)
{
	list tmp = p;
	p = p->next;
	delete tmp;
}

list reuse_delete_mix_list(list& A, list& B)
{
	list pa = A->next;
	list pb = B->next;
	list C = A;
	list pc = C;
	while(pa && pb)
	{
		if(pa->data > pb->data)
		{
			list_remove_and_next(pb);
		}
		else if(pa->data < pb->data)
		{
			list_remove_and_next(pa);
		}
		else
		{
			pc->next = pa;
			pc = pc->next;

			list_remove_and_next(pb);
			pa = pa->next;
		}
	}
	pc->next = nullptr;
	while(pa)
	{
		list_remove_and_next(pa);
	}
	delete B;
	return C;
}


list reuse_delete_difference_list(list& A, const list& B)
{
	list pa = A->next;
	list pre = A;
	list pb = B->next;

	while(pa && pb)
	{
		if(pa->data < pb->data)
		{
			pre = pa;
			pa = pa->next;
		}
		else if(pb->data < pa->data)
		{
			pb = pb->next;
		}
		else
		{
			list tmp = pa;
			pre->next = pa->next;
			pa = pa->next;
			delete tmp;
			
			pb = pb->next;
		}
	}
	return A;
}

void reuse_neg_pos_partition_list(list&A, list& B)
{
	B = new node(0, nullptr);
	list pb = B;
	list pa = A;
	list cur = A->next;
	while(cur)
	{
		if(cur->data < 0)
		{
			pa->next = cur;
			pa = pa->next;
		}
		else
		{
			pb->next = cur;
			pb = pb->next;
		}
		cur = cur->next;
	}
	//添加终止标志nullptr
	if(pa) pa->next = nullptr;
	if(pb) pb->next = nullptr;
}


int max(const list& l)
{
	int ret = INT_MIN;
	list p = l->next;
	while(p)
	{
		if(p->data > ret)
		{
			ret = p->data;
		}
		p = p->next;
	}
	return ret;
}

list reverse_list(list& l)
{
	if(l->next && l->next->next)
	{
		list p = l->next->next;
		l->next->next = nullptr;
		while(p)
		{
			list q = p; // 摘取
			p = p->next;
			q->next = l->next;//链接
			l->next = q;
		}
	}
	return l;
}

list delete_min_max(list& l, int mink, int maxk)
{
	assert(mink <= maxk);
	list p =  l->next;
	list pre = l;
	while(p && p->data <= mink)
	{
		pre = p;
		p = p->next;
	}
	if(p)
	{
		list q = p;
		while(q && q->data < maxk)
		{
			q = q->next;
		}
		pre->next = q;
		while(p != q && p)
		{
			list tmp = p;
			p = p->next;
			delete tmp;
		}
	}
	return l;
}

}
