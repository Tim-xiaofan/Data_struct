#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

static void reverseArray(std::vector<int>& a, int low, int high)
{//递归版本
	if(low < high)
	{
		std::swap(a[low++], a[high--]);
		reverseArray(a, low, high);
	}
}

static void reverseArray(std::vector<int>& a)
{
	reverseArray(a, 0, a.size()-1);
}

static void reverseArray1(std::vector<int>& a)
{// non-recursion
	int low = 0;
	int high = a.size() - 1;
	while(low < high)
	{
		std::swap(a[low++], a[high--]);
	}
}


int main(void)
{
	{
		std::vector<int> v = {0,1,2,3};
		reverseArray(v);
		assert(v == std::vector<int>({3,2,1,0}));
	}
	{
		std::vector<int> v = {0,1,2,3};
		reverseArray1(v);
		assert(v == std::vector<int>({3,2,1,0}));
	}
	std::cout << "All tests passed\n";
	return 0;
}
