#include "Stack.h"
#include <iostream>
#include <cassert>

using std::endl;
using std::cout;

int main(void)
{
	using namespace HOMEWORK_NS;
	const int N = 10;

	{
		Stack<int> s(N);
		assert(!s.size());
		assert(s.empty());
		assert(!s.full());
	}

	{
		Stack<int> s(N);
		int i = 0;
		while(s.push(i))
		{
			++i;
		}
		assert(s.size() == N);
		assert(!s.empty());
		assert(s.full());

		int j = 0;
		while(s.pop(j))
		{
			--i;
			assert(i == j);
		}
		assert(!s.size());
		assert(s.empty());
		assert(!s.full());
	}
	cout << "All test passed\n";
	return 0;
}
