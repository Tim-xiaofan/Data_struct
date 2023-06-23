#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>

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

static void shellSortUtil(std::vector<int>& a, int d)
{
	for(int i = 0; i + d < static_cast<int>(a.size()); ++i)
	{// i-th sub list
		for(int j = i + d; j < static_cast<int>(a.size()); j+=d)
		{
			if(a[j] >= a[j-d]) continue;
			//find insert position in [i, j), step is d
			int value = a[j];
			int pos = j-d;
			for(; pos >= i; pos-=d)
			{
				if(value >= a[pos])
				{
					break;
				}
			}

			//move (pos, j)
			for(int k = j-d; k > pos; k-=d)
			{
				a[k+d] = a[k];
			}
			a[pos+d] = value;
		}
	}
}


static void shellSort(std::vector<int>& a, const std::vector<int> deltas)
{
	for(int d: deltas)
	{
		shellSortUtil(a, d);
	}
}


int main(void)
{
	//test shellSortUtil delta=[5, 3, 1]
	{
		std::vector<int> a = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
		shellSortUtil(a, 5);
		assert(a == std::vector<int>({13,27,49,55,4,49,38,65,97,76}));

		shellSortUtil(a, 3);
		assert(a == std::vector<int>({13,4,49,38,27,49,55,65,97,76}));
		
		shellSortUtil(a, 1);
		assert(a == std::vector<int>({4,13,27,38,49,49,55,65,76,97}));
	}
	
	// test shellSort
	{
		std::vector<int> a = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
		shellSort(a, {5, 3, 1});
		assert(a == std::vector<int>({4,13,27,38,49,49,55,65,76,97}));
	}
	{// empty
		std::vector<int> a;
		shellSort(a, {5, 3, 1});
		assert(a == std::vector<int>());
	}
	{// one
		std::vector<int> a = {1};
		shellSort(a, {5, 3, 1});
		assert(a == std::vector<int>({1}));
	}
	{// two
		std::vector<int> a = {2, 1};
		shellSort(a, {5, 3, 1});
		assert(a == std::vector<int>({1, 2}));
	}
	std::cout << "All tested passed\n";
	return 0;
}
