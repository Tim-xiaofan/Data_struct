#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

static std::int64_t power2(int n)
{//O(n)
	if(n==0)
	{
		return 1;
	}
	else
	{
		return 2 * power2(n-1);
	}
}

static inline std::int64_t sqr(int a) { return a * a; }

static std::int64_t power2A(int n)
{//O(logn)
	if(n== 0)
	{
		return 1;
	}
	else if(n&1)
	{
		return sqr(power2A(n>>1)) << 1;
	}
	else
	{
		return sqr(power2A(n>>1));
	}
}

int main(void)
{
	assert(power2(0) == 1);
	assert(power2A(0) == 1);
	assert(power2(1) == 2);
	assert(power2A(1) == 2);
	assert(power2(3) == 8);
	assert(power2A(3) == 8);
	assert(power2(4) == 16);
	assert(power2A(4) == 16);
	std::cout << "All tests passed\n";
	return 0;
}
