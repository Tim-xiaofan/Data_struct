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

static void simpleSelectionSort(std::vector<int>& a)
{
	for(size_t i = 0; i < a.size(); ++i)
	{
		int min = a[i];
		size_t minIndex = i;
		for(size_t j = i+1; j < a.size(); ++j)
		{
			if(a[j] <  min)
			{
				min = a[j];
				minIndex = j;
			}
		}
		if(minIndex != i)
		{
			std::swap(a[i], a[minIndex]);
		}
	}
}

int main(void)
{
	{//
		std::vector<int> a = {49,38,65,97,76,13,27,49,55,4};
		simpleSelectionSort(a);
		assert(a == std::vector<int>({4,13,27,38,49,49,55,65,76,97}));
	}
	{// empty
		std::vector<int> a;
		simpleSelectionSort(a);
		assert(a == std::vector<int>({}));
	}
	{// one
		std::vector<int> a = {1};
		simpleSelectionSort(a);
		assert(a == std::vector<int>({1}));
	}
	{// two
		std::vector<int> a = {2,1};
		simpleSelectionSort(a);
		assert(a == std::vector<int>({1, 2}));
	}
	{// three
		std::vector<int> a = {2,1,0};
		simpleSelectionSort(a);
		assert(a == std::vector<int>({0, 1, 2}));
	}
	{
		std::vector<int> a = {10, 7, 8, 9, 1, 5 };
		simpleSelectionSort(a);
		assert(a == std::vector<int>({1,5,7,8,9,10}));
	}
	std::cout << "All tests passed\n";
	return 0;
}
