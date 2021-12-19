/** 20210918, zyj, GuangDong*/
#include<iostream>
#include "quick_sort.h"
#include "SqList.h"
using std::cout;
using std::endl;

void test_bubble(void)
{
	const int size = 8;
	int A[size] = {38, 49, 65, 97, 76, 13, 27, 17};
	SqList<int> li(16);
	li.append_bulk(A, size);
	cout << "origin : ";
	li.show();

	bubble_sort(li);
	cout << "sorted : ";
	li.show();
}

void test_qsort(void)
{
	const int size = 8;
	int A[size] = {49, 38, 65, 97, 76, 13, 27, 17};
	SqList<int> li(16);
	li.append_bulk(A, size);
	cout << "origin : ";
	li.show();

	//cout << "low : " << quick_partition(li, 0, size - 1) << endl;
	//cout << "partition: ";
	//li.show();

	quick_sort(li);
	cout << "sorted : ";
	li.show();
}

int main(int ac, char *av[])
{
	test_bubble();
	//test_qsort();
	return 0;
}
