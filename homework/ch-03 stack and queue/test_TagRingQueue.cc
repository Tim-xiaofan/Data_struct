#include "TagRingQueue.h"
#include <iostream>
#include <cassert>

using std::endl;
using std::cout;

int main(void)
{
	using namespace HOMEWORK_NS;
	const int N = 10;

	{
		TagRingQueue<int> q(N);
		assert(q.empty());
		assert(!q.full());
		assert(!q.size());

		int i = 0;
		while(q.enqueue(i))
		{
			++i;
			assert(q.size() == i);
		}
		assert(q.size() == N);

		int j = 0;
		i = 0;
		while(q.dequeue(j))
		{
			assert(i == j);
			++i;
			assert(q.size() == (N - i));
		}
		assert(!q.size());
	}

	cout << "All passed\n";

	return 0;
}
