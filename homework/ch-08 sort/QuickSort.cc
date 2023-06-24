#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	for (size_t i = 0; i < vec.size(); ++i) {
		os << vec[i];
		if (i != vec.size() - 1) {
			os << ", ";
		}
	}
	os << "]";
	return os;
}

static int partition(std::vector<int>& a, int low, int high)
{
	int pivotkey = a[low];
	while(low < high)
	{
		while(high > low && a[high] >= pivotkey) --high;
		a[low] = a[high];
		while(low<high && a[low]<=pivotkey) ++low;
		a[high] = a[low];
	}
	a[low] = pivotkey;
	return low;
}

static void quickSortUtil(std::vector<int>& a, int low, int high)
{
	if(low < high)
	{
		int pivotIndex = partition(a, low, high);
		quickSortUtil(a, low, pivotIndex-1);
		quickSortUtil(a, pivotIndex+1, high);
	}
}

static void quickSort(std::vector<int>& a)
{
	quickSortUtil(a, 0, a.size() - 1);
}

int main(void)
{
	{//
		std::vector<int> a = {49,38,65,97,76,13,27,49,55,4};
		quickSort(a);
		assert(a == std::vector<int>({4,13,27,38,49,49,55,65,76,97}));
	}
	{// empty
		std::vector<int> a;
		quickSort(a);
		assert(a == std::vector<int>({}));
	}
	{// one
		std::vector<int> a = {1};
		quickSort(a);
		assert(a == std::vector<int>({1}));
	}
	{// two
		std::vector<int> a = {2,1};
		quickSort(a);
		assert(a == std::vector<int>({1, 2}));
	}
	{// three
		std::vector<int> a = {2,1,0};
		quickSort(a);
		assert(a == std::vector<int>({0, 1, 2}));
	}
	{
		std::vector<int> a = { 10, 7, 8, 9, 1, 5 };
		quickSort(a);
		assert(a == std::vector<int>({1,5,7,8,9,10}));
	}
	std::cout << "All tests passed\n";
	return 0;
}
