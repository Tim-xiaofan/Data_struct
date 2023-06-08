#include <iostream>
#include <vector>
#include <list>
#include <cassert>


template<typename ForwardIt, typename T>
bool binarySearch(ForwardIt first, ForwardIt last, const T& value)
{
	typename std::iterator_traits<ForwardIt>::difference_type d, step;
    d = std::distance(first, last);
	while(d > 0)
	{
		step = d / 2;
		ForwardIt cur = first;
		std::advance(cur, step);
		if(value == *cur) // found
		{
			return true;
		}
		else if(value > *cur) // right
		{
			first = ++cur;
			d -= step + 1;
		}
		else //left
		{
			d = step;
		}
	}
	return (first != last) && (value == *first);
}

int main(void)
{
	{// empty
		std::vector<int> table = {};
		assert(binarySearch(table.begin(), table.end(), 0) == false);

		std::list<int> table1 = {};
		assert(binarySearch(table1.begin(), table1.end(), 0) == false);
	}
	{// 1
		std::vector<int> table = {0};
		assert(binarySearch(table.begin(), table.end(), 0) == true);
		assert(binarySearch(table.begin(), table.end(), 1) == false);

		std::list<int> table1 = {1};
		assert(binarySearch(table1.begin(), table1.end(), 1) == true);
		assert(binarySearch(table1.begin(), table1.end(), 0) == false);
	}
	{//2
		std::vector<int> table = {0, 1};
		assert(binarySearch(table.begin(), table.end(), 0) == true);
		assert(binarySearch(table.begin(), table.end(), 1) == true);
		assert(binarySearch(table.begin(), table.end(), 3) == false);

		std::list<int> table1 = {0, 1};
		assert(binarySearch(table1.begin(), table1.end(), 0) == true);
		assert(binarySearch(table1.begin(), table1.end(), 1) == true);
		assert(binarySearch(table1.begin(), table1.end(), 3) == false);
	}
	{// 3
		std::vector<int> table = {0, 1, 2};
		assert(binarySearch(table.begin(), table.end(), 0) == true);
		assert(binarySearch(table.begin(), table.end(), 1) == true);
		assert(binarySearch(table.begin(), table.end(), 2) == true);
		assert(binarySearch(table.begin(), table.end(), 3) == false);

		std::list<int> table1 = {0, 1, 2};
		assert(binarySearch(table1.begin(), table1.end(), 0) == true);
		assert(binarySearch(table1.begin(), table1.end(), 1) == true);
		assert(binarySearch(table1.begin(), table1.end(), 2) == true);
		assert(binarySearch(table1.begin(), table1.end(), 3) == false);
	}
	{//4
		std::vector<int> table = {0, 1, 2, 3};
		assert(binarySearch(table.begin(), table.end(), 0) == true);
		assert(binarySearch(table.begin(), table.end(), 1) == true);
		assert(binarySearch(table.begin(), table.end(), 2) == true);
		assert(binarySearch(table.begin(), table.end(), 3) == true);
		assert(binarySearch(table.begin(), table.end(), 4) == false);

		std::list<int> table1 = {0, 1, 2, 3};
		assert(binarySearch(table1.begin(), table1.end(), 0) == true);
		assert(binarySearch(table1.begin(), table1.end(), 1) == true);
		assert(binarySearch(table1.begin(), table1.end(), 2) == true);
		assert(binarySearch(table1.begin(), table1.end(), 3) == true);
		assert(binarySearch(table1.begin(), table1.end(), 4) == false);
	}
	std::cout << "All test passed\n";
	return 0;
}
