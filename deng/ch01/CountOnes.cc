#include <iostream>
#include <cassert>

int countOnes(unsigned int n)
{//O(logn)
	int ones = 0;
	while(n > 0)
	{
		ones += (n&1);
		n>>=1;
	}
	return ones;
}

int countOnes1(unsigned int n)
{//O(1)
	int ones = 0;
	while(n>0)
	{
		++ones;
		n&=(n-1);//最右边的1置成0
	}
	return ones;
}

int main(void)
{
	unsigned int n = 441;//110111001
	assert(countOnes(n)== 6);
	assert(countOnes1(n)== 6);
	std::cout << "All tests passed\n";
	return 0;
}
