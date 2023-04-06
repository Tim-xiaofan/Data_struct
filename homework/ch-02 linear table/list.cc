#include "list.h"
#include <iostream>
#include <cassert>

namespace HOMEWORK_NS
{

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

void print_list(const list& l)
{
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
		}
	}
	while(pa)
	{
		list_remove_and_next(pa);
	}

	while(pb)
	{
		list_remove_and_next(pb);
	}

	delete B;
	return C;
}

}
