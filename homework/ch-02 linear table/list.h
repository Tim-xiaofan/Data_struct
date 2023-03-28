#ifndef _HOMEWORK_LIST_H_
#define _HOMEWORK_LIST_H_
#include <initializer_list>
#include <iostream>

namespace HOMEWORK_NS
{

struct node
{
	int data;
	node* next;
	node(int d = 0, node* n = nullptr)
		:data(d),
		next(n)
	{}
};

using list = node*;

list create_list(const std::initializer_list<int> & il)
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

}

#endif
