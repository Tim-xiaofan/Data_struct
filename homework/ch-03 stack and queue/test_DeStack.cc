#include "DeStack.h"
#include <iostream>
#include <cassert>

using std::endl;
using std::cout;

int main(void)
{
	using namespace HOMEWORK_NS;
	const int N = 10;

	{
		DeStack<int> s;
		init(s, N);
		assert(s.m  == N);
		assert(s.top[0] == -1);
		assert(s.top[1] == N);
		assert(empty(s));
		assert(!full(s));
		assert(size(s) == 0);
	}

	{//left
		DeStack<int> s;
		init(s, N);
		int i = 0;
		while(pushLeft(s, i))
		{
			++i;
		}
		assert(i == N);
		assert(size(s) == N);
		assert(!empty(s));
		assert(full(s));

		int j = 0;
		while(popLeft(s, j))
		{
			--i;
			assert(i == j);
		}
		assert(empty(s));
		assert(!full(s));
		assert(size(s) == 0);
	}

	{//right
		DeStack<int> s;
		init(s, N);
		int i = 0;
		while(pushRight(s, i))
		{
			++i;
		}
		assert(i == N);
		assert(size(s) == N);
		assert(!empty(s));
		assert(full(s));

		int j = 0;
		while(popRight(s, j))
		{
			--i;
			assert(i == j);
		}
		assert(empty(s));
		assert(!full(s));
		assert(size(s) == 0);

	}

	{//left and right
		DeStack<int> s;
		init(s, N);
		int i = 0;
		while(pushLeft(s, i) && pushRight(s, i * 2))
		{
			++i;
		}
		assert(size(s) == N);
		assert(!empty(s));
		assert(full(s));
		
		int j = 0;
		int backup = i;
		while(popRight(s, j))
		{
			--i;
			assert(i * 2 == j);
		}

		i = backup;
		while(popLeft(s, j))
		{
			--i;
			assert(i == j);
		}
	}

	cout << "All test passed\n";
	return 0;
}
