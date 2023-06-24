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

static void heapAdjust(std::vector<int>& a, int n, int i)
{//max heap[i,..,n]
	//a[i] destroy the heap
	int max = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if(left < n && a[left] > a[max])
	{
		max = left;
	}
	if(right < n && a[right] > a[max])
	{
		max = right;
	}
	if(i != max)
	{
		std::swap(a[i], a[max]);
		heapAdjust(a, n, max);
	}
}

static void heapSort(std::vector<int>& a)
{
	int n = a.size();
	//build a max head
	for(int i = n/2-1; i>=0; --i)
	{
		heapAdjust(a, n, i);
	}

	for(int i = n-1; i > 0; --i)
	{
		std::swap(a[0], a[i]);
		heapAdjust(a, i, 0);
	}
}

int main(void)
{
	{//
		std::vector<int> a = {49,38,65,97,76,13,27,49,55,4};
		heapSort(a);
		assert(a == std::vector<int>({4,13,27,38,49,49,55,65,76,97}));
	}
	{// empty
		std::vector<int> a;
		heapSort(a);
		assert(a == std::vector<int>({}));
	}
	{// one
		std::vector<int> a = {1};
		heapSort(a);
		assert(a == std::vector<int>({1}));
	}
	{// two
		std::vector<int> a = {2,1};
		heapSort(a);
		assert(a == std::vector<int>({1, 2}));
	}
	{// three
		std::vector<int> a = {2,1,0};
		heapSort(a);
		assert(a == std::vector<int>({0, 1, 2}));
	}
	{
		std::vector<int> a = {10, 7, 8, 9, 1, 5 };
		heapSort(a);
		assert(a == std::vector<int>({1,5,7,8,9,10}));
	}
	std::cout << "All tests passed\n";
	return 0;
}
