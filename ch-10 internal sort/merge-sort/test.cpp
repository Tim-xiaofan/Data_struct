/** 20210919, zyj, GuangDong*/
#include<iostream>
#include "merge_sort.h"
#include "SqList.h"
using std::cout;
using std::endl;

void test_merge(void)
{
	const int size = 8;
	int A[size] = {49, 38, 65, 97, 76, 13, 27, 49};
	SqList<int> li(16);
	li.append_bulk(A, size);
	cout << "origin : ";
	li.show();

	//cout << "low : " << quick_partition(li, 0, size - 1) << endl;
	//cout << "partition: ";
	//li.show();

	merge_sort(li);
	cout << "sorted : ";
	li.show();

}

int main(int ac, char *av[])
{
    test_merge();
	return 0;
}
