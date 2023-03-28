#include <iostream>
#include "list.h"

using std::cout;
using std::endl;

namespace HOMEWORK_NS
{

//将两个递增的有序链表合并为一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间, 不另外占用其它的存储空间。表中不允许有重复的数据。
static list merge_list_unique(list A, list B)
{
	list pa = A->next;
	list pb = B->next;
	list C = A;
	list pc = C;
	while(pa && pb)
	{
		if(pa->data < pb->data)
		{
			pc->next = pa;
			pa = pa->next;
		}
		else if(pa->data > pb->data)
		{
			pc->next = pb;
			pb = pb->next;
		}
		else
		{
			pc->next = pa;
			pa = pa->next;
			list tmp = pb;
			pb = pb->next;
			delete tmp;
		}
		pc = pc->next;
	}

	while(pa)
	{
		pc = pa;
		pa = pa->next;
	}

	while(pb)
	{
		pc = pb;
		pb = pb->next;
	}
	delete B;
	return C;
}

}

int main(void)
{
	using namespace HOMEWORK_NS;
	{
		list l = create_list({0, 1, 2, 3, 4, 5});
		std::cout << "l: ";
		print_list(l);
		list l1 = create_list({});
		std::cout << "l1: ";
		print_list(l1);
		list l2 = create_list({0});
		std::cout << "l2: ";
		print_list(l2);
		list l3 = create_list({0,1});
		std::cout << "l3: ";
		print_list(l3);
	}

	{
		list A = create_list({0, 4, 9, 10, 11, 34});
		list B = create_list({1, 3, 7, 9, 23});
		cout << "A: ";
		print_list(A);
		cout << "B: ";
		print_list(B);
		list C = merge_list_unique(A, B);
		cout << "C: ";
		print_list(C);
	}
	return 0;
}
