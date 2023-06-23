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

static void straightInsertionSort(std::vector<int>& a)
{
	for(int i = 1; i < static_cast<int>(a.size()); ++i)
	{
		if(a[i] >= a[i-1]) continue;
		
		//find insert position in [0, i)
		int value = a[i];
		int pos;//[-1, i)
		for(pos = i-1; pos >= 0; --pos)
		{
			if(value >= a[pos])
			{
				break;
			}
		}

		//move (pos, i)
		for(int j = i-1; j > pos; --j)
		{
			a[j + 1] = a[j];
		}
		a[pos + 1] = value;
	}
}

int main(void)
{
	{//empty
		std::vector<int> a;
		std::vector<int> expected;
		straightInsertionSort(a);
		assert(a == expected);
	}
	{// one
		std::vector<int> a = {0};
		std::vector<int> expected = {0};
		straightInsertionSort(a);
		assert(a == expected);
	}
	{// two
		std::vector<int> a = {2, 1};
		std::vector<int> expected = {1, 2};
		straightInsertionSort(a);
		assert(a == expected);
	}
	{// three
		std::vector<int> expected = {1, 2, 3};
		{
			std::vector<int> a = {2, 3, 1};
			straightInsertionSort(a);
			assert(a == expected);
		}
		{
			std::vector<int> a = {1, 3, 2};
			straightInsertionSort(a);
			assert(a == expected);
		}
		{
			std::vector<int> a = {3, 2, 1};
			straightInsertionSort(a);
			assert(a == expected);
		}
	}
	{
		std::vector<int> a = {49, 38, 65, 97, 76, 13, 27, 49};
		std::vector<int> expected = {13, 27, 38, 49, 49, 65, 76, 97};
		straightInsertionSort(a);
		assert(a == expected);
	}

	std::cout << "All tested passed\n";
	return 0;
}
