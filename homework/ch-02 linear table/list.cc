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

}
