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
void destroy_list(list& l);
void print_list(const list& l, const char* info = "list: ");
void assert_list(const list& l, const std::vector<int>& v);
bool equal_list(const list& A, const list& B);

//algorithm on list
list reuse_delete_mix_list(list& A, list& B);
list reuse_delete_difference_list(list& A, const list& B);
void reuse_neg_pos_partition_list(list&A, list& B);
int max(const list& l);
list reverse_list(list& l);

}

#endif
