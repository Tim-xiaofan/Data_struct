#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <iterator>
#include "list.h"

using std::cout;
using std::endl;
using std::vector;
using std::initializer_list;

namespace HOMEWORK_NS
{

//将两个递增的有序链表合并为一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间, 不另外占用其它的存储空间。表中不允许有重复的数据。
static list unique_merge_list(list A, list B)
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
		pc->next = pa;
		pa = pa->next;
		pc = pc->next;
	}

	while(pb)
	{
		pc->next = pb;
		pb = pb->next;
		pc = pc->next;
	}
	delete B;
	return C;
}

// 将两个非递减的有序链表合并为一个非递增的有序链表。要求结果链表仍使用原来两个链表的存储空间, 不另外占用其它的存储空间。表中允许有重复的数据
static list reverse_merge_list(list A, list B)
{
	list pa = A->next;
	list pb = B->next;
	list C = A;
	C->next = nullptr;
	list q;

	while(pa && pb)
	{
		//摘取
		if(pa->data <= pb->data)
		{
			q = pa;
			pa = pa->next;
		}
		else
		{
			q = pb;
			pb = pb->next;
		}
		//插入
		q->next = C->next;
		C->next = q;
	}

	while(pa)
	{
		q = pa;
		pa = pa->next;
		q->next = C->next;
		C->next = q;
	}

	while(pb)
	{
		q = pb;
		pb = pb->next;
		q->next = C->next;
		C->next = q;
	}

	delete B;
	return C;
}

std::ostream& operator<<(std::ostream& os, std::vector<int> v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	return os;
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
		cout << endl;
		initializer_list<int> il1 = {0, 4, 9, 10, 11, 34}; 
		initializer_list<int> il2 = {1, 3, 7, 9, 23}; 
		list A = create_list(il1);
		list B = create_list(il2);
		cout << "A: ";
		print_list(A);
		cout << "B: ";
		print_list(B);
		list C = unique_merge_list(A, B);
		cout << "C: ";
		print_list(C);
		std::vector<int> v;
		std::merge(il1.begin(), il1.end(), il2.begin(), il2.end(), std::back_inserter(v));
		auto it = std::unique(v.begin(), v.end());
		v.erase(it, v.end());
		cout << "v: " << v << endl;
		assert_list(C, v);
	}

	{
		cout << endl;
		initializer_list<int> il1 = {0, 1, 4, 4, 9, 10, 11, 22, 22, 34};
		initializer_list<int> il2 = {1, 3, 7, 9, 22, 23};
		list A = create_list(il1);
		list B = create_list(il2);
		cout << "A: ";
		print_list(A);
		cout << "B: ";
		print_list(B);
		list C = reverse_merge_list(A, B);
		cout << "C: ";
		print_list(C);
		std::vector<int> v; 
		std::merge(il1.begin(), il1.end(), il2.begin(), il2.end(), std::back_inserter(v));
		std::reverse(v.begin(), v.end());
		cout << "v: " << v << endl;
		assert_list(C, v);
	}
	return 0;
}
