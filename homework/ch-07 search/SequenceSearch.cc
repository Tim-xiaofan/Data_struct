#include <iostream>
#include <vector>
#include <list>
#include <cassert>

template <typename InputIt, typename T>
InputIt sequenceSearch(InputIt fisrt, InputIt last, const T& key)
{
	for(; fisrt != last; ++fisrt)
	{
		if(*fisrt == key)
		{
			return fisrt;
		}
	}
	return last;
}

int main(void)
{
	{
		std::vector<int> table = {0, 1, 2};
		assert(sequenceSearch(table.begin(), table.end(), 0) != table.end());
		assert(sequenceSearch(table.begin(), table.end(), 3) == table.end());
	}

	{
		std::list<int> table = {0, 1, 2};
		assert(sequenceSearch(table.begin(), table.end(), 0) != table.end());
		assert(sequenceSearch(table.begin(), table.end(), 3) == table.end());
	}
	std::cout << "All test passed\n";
	return 0;
}
