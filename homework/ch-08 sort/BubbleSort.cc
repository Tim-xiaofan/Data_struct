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

static void bubbleSort(std::vector<int>& a)
{
	for(size_t i = 0; i < a.size(); ++i)
	{
		bool swap = false;
		for(size_t j = 1; j < a.size()-i; ++j)
		{
			if(a[j-1] > a[j])
			{
				std::swap(a[j-1], a[j]);
				swap = true;
			}
		}
		if(!swap)
		{
			break;
		}
	}
}

int main(void)
{
	{//
		std::vector<int> a = {49,38,65,97,76,13,27,49,55,4};
		bubbleSort(a);
		assert(a == std::vector<int>({4,13,27,38,49,49,55,65,76,97}));
	}
	{// empty
		std::vector<int> a;
		bubbleSort(a);
		assert(a == std::vector<int>({}));
	}
	{// one
		std::vector<int> a = {1};
		bubbleSort(a);
		assert(a == std::vector<int>({1}));
	}
	{// two
		std::vector<int> a = {2,1};
		bubbleSort(a);
		assert(a == std::vector<int>({1, 2}));
	}
	{// three
		std::vector<int> a = {2,1,0};
		bubbleSort(a);
		assert(a == std::vector<int>({0, 1, 2}));
	}
	std::cout << "All tests passed\n";
	return 0;
}
