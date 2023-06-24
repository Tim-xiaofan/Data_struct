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

static void mergeSort(std::vector<int>& a)
{
	int n = a.size();
	//std::cout << "a: " << a << std::endl;
	std::vector<int> b(n);
	for(int delta = 1; delta < n; delta+=delta)
	{
		for(int i = 0; i < n; i += 2 *delta)
		{
			int start1 = i;
			int end1 = std::min(start1 + delta, n);
			int start2  = end1;
			int end2 = std::min(start2 + delta, n);
			int k = start1;
			//std::cout << std::vector<int>(a.begin() + start1, a.begin() + end1);
			//std::cout << std::vector<int>(a.begin() + start2, a.begin() + end2) << std::endl;

			//merge
			while(start1 < end1 && start2 < end2)
			{
				b[k++] = (a[start1] < a[start2])?a[start1++]:a[start2++];
			}
			while(start1 < end1)
			{
				b[k++] = a[start1++];
			}
			while(start2 < end2)
			{
				b[k++] = a[start2++];
			}
		}
		a.swap(b);
		//std::cout << "delta = " << delta <<  ": " << a << "\n\n";
	}
}

int main(void)
{
	{//
		std::vector<int> a = {49,38,65,97,76,13,27};
		mergeSort(a);
		assert(a == std::vector<int>({13,27,38,49,65,76,97}));
	}
	{//
		std::vector<int> a = {49,38,65,97,76,13,27,49,55,4};
		mergeSort(a);
		assert(a == std::vector<int>({4,13,27,38,49,49,55,65,76,97}));
	}
	{// empty
		std::vector<int> a;
		mergeSort(a);
		assert(a == std::vector<int>({}));
	}
	{// one
		std::vector<int> a = {1};
		mergeSort(a);
		assert(a == std::vector<int>({1}));
	}
	{// two
		std::vector<int> a = {2,1};
		mergeSort(a);
		assert(a == std::vector<int>({1, 2}));
	}
	{// three
		std::vector<int> a = {2,1,0};
		mergeSort(a);
		assert(a == std::vector<int>({0, 1, 2}));
	}
	{
		std::vector<int> a = {10, 7, 8, 9, 1, 5 };
		mergeSort(a);
		assert(a == std::vector<int>({1,5,7,8,9,10}));
	}
	std::cout << "All tests passed\n";
	return 0;
}
