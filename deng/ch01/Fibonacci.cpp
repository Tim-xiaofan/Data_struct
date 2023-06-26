#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

static std::int64_t fabonacci(int n)
{//O(2^n)
	return (n < 2) ? n : fabonacci(n-1) + fabonacci(n-2);
}

static std::int64_t fabonacci1(int n, std::int64_t& prev)
{//O(n), O(n)
	if(n == 0)
	{
		prev = 1;
		return 0;
	}
	else
	{
		std::int64_t prevPrev;
		prev = fabonacci1(n-1, prevPrev);
		return prevPrev + prev;
	}
}
static std::int64_t fabonacci1(int n)
{
	std::int64_t prev;
	return fabonacci1(n, prev);
}

static std::int64_t fabonacci2(int n)
{
	int prev = 0, prevPrev = 1;
	while(n-- > 0)
	{
		prev += prevPrev;
		prevPrev = prev-prevPrev;
	}
	return prev;
}

int main(void)
{
	assert(fabonacci(0) == 0);
	assert(fabonacci(1) == 1);
	assert(fabonacci(2) == 1);
	assert(fabonacci(3) == 2);
	assert(fabonacci(4) == 3);

	assert(fabonacci1(0) == 0);
	assert(fabonacci1(1) == 1);
	assert(fabonacci1(2) == 1);
	assert(fabonacci1(3) == 2);
	assert(fabonacci1(4) == 3);

	assert(fabonacci2(0) == 0);
	assert(fabonacci2(1) == 1);
	assert(fabonacci2(2) == 1);
	assert(fabonacci2(3) == 2);
	assert(fabonacci2(4) == 3);
	std::cout << "All tests passed\n";
	return 0;
}
