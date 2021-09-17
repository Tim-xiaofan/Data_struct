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

void test_shell(void)
{
	const int size = 10, t = 3;
	int A[size] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
	int dlta[t] = {5, 3, 1};
	SqList<int> li(16);
	li.append_bulk(A, size);
	cout << "origin : ";
	li.show();

	shell_sort(li, dlta, t);
	cout << "sorted : ";
	li.show();
}

int main(int ac, char *av[])
{
	//test_insert();
	//cout << "---------\n";
	//test_binsert();
	//cout << "---------\n";
	//test_2way();
	cout << "---------\n";
	test_shell();
	return 0;
}
