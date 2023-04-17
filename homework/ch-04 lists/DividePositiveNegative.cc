#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template<typename BiIter>
void dividePositiveNegative(BiIter fisrt, BiIter last)
{
	if(fisrt != last)
	{
		BiIter pa=fisrt;
		BiIter pb=last-1;
		while(pa != pb)
		{
			while(pa != pb && *pa < 0)
			{
				++pa;
			}
			while(pa != pb && *pb > 0)
			{
				--pb;
			}
			std::swap(*pa, *pb);
		}
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
	return os;
}

int main(void)
{
	{
		std::vector<int> v{};
		dividePositiveNegative(v.begin(), v.end());
		assert(v.empty());
	}

	{
		std::vector<int> v{1, 2, 3, 4};
		dividePositiveNegative(v.begin(), v.end());
		assert(std::is_sorted(v.begin(), v.end()));
	}

	{
		std::vector<int> v{-4, -3, -2, -1};
		dividePositiveNegative(v.begin(), v.end());
		assert(std::is_sorted(v.begin(), v.end()));
	}
	{
		std::vector<int> v{-1, 2, -3, 4, -5};
		dividePositiveNegative(v.begin(), v.end());
		std::vector<int> expected{-1,-5, -3, 4, 2};
		assert(v == expected);
	}
	{
		std::vector<int> v{1, 2, 3, -1, -2, -3};
		dividePositiveNegative(v.begin(), v.end());
		std::vector<int> expected{-3, -2, -1, 3, 2, 1};
		assert(v == expected);
	}
	{
		std::vector<int> v{-1, -2, -3, 1, 2, 3};
		dividePositiveNegative(v.begin(), v.end());
		std::vector<int> expected{-1, -2, -3, 1, 2, 3};
		assert(v == expected);
	}
	return 0;
}
