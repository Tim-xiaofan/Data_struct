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

}
