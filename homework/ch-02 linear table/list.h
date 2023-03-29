#ifndef _HOMEWORK_LIST_H_
#define _HOMEWORK_LIST_H_

#include <vector>

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

list create_list(const std::vector<int> & il);
void print_list(const list& l);
void assert_list(const list& l, const std::vector<int>& v);

}

#endif
