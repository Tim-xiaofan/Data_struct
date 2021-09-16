/** 20210915, zyj, GuangDong*/
#include<iostream>
#include "sort.h"
#include "SqList.h"
using std::cout;
using std::endl;

void 
test_insert(void)
{
	const int size = 8;
	int A[size] = {38, 49, 65, 97, 76, 13, 27, 17};
	SqList<int> li(16);
	li.append_bulk(A, size);
	cout << "origin : ";
	li.show();

	insert_sort(li);
	cout << "sorted : ";
	li.show();
}

void 
test_binsert(void)
{
	const int size = 9;
	int A[size] = {38, 49, 65, 97, 76, 13, 27, 17, 99};
	SqList<int> li(16);
	li.append_bulk(A, size);
	cout << "origin : ";
	li.show();

	binsert_sort(li);
	cout << "sorted : ";
	li.show();
}

void test_2way(void)
{
	const int size = 9;
	int A[size] = {38, 49, 65, 97, 76, 13, 27, 17, 99};
	SqList<int> li(16);
	li.append_bulk(A, size);
	cout << "origin : ";
	li.show();

	twoway_insert_sort(li);
	cout << "sorted : ";
	li.show();
}

int main(int ac, char *av[])
{
	test_insert();
	cout << "---------\n";
	test_binsert();
	cout << "---------\n";
	test_2way();
	return 0;
}
