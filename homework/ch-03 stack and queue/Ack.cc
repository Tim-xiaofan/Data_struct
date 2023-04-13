#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::string;

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<unsigned>>& matrix)
{
	for(const auto& v: matrix)
	{
		for(const auto i: v)
		{
			os << i << " ";
		}
		os << endl;
	}
	return os;
}

// 阿克曼函数
long Ack(unsigned m, unsigned n)
{
	if(m == 0)
	{
		return n + 1;
	}
	else if(n == 0)
	{
		return Ack(m - 1, 1);
	}
	else
	{
		return Ack(m-1, Ack(m, n - 1));
	}
}

long AckStack(unsigned m, unsigned n)
{
	std::stack<unsigned> s;
    s.push(m);
    while (!s.empty())
    {
        m = s.top();
        s.pop();
        if (m == 0)
        {
            n += 1;
        }
        else if (n == 0)
        {
            s.push(m-1);
            n = 1;
        }
        else
        {
            s.push(m-1);
            s.push(m);
            n -= 1;
        }
    }
    return n;
}

int main(void)
{
	assert(Ack(0, 0) == 1);
	assert(Ack(2, 1) == 5);
	assert(AckStack(0, 0) == 1);
    assert(AckStack(0, 1) == 2);
    assert(AckStack(1, 1) == 3);
	assert(AckStack(2, 1) == 5);
    assert(AckStack(2, 2) == 7);
    assert(AckStack(3, 3) == 29);
    assert(AckStack(3, 4) == 125);
    assert(AckStack(4, 0) == 13);
    assert(AckStack(4, 1) == 65533);  // this test may take a long time to complete
    assert(AckStack(4, 2) == 65535);  // this test may take a long time to complete
    assert(AckStack(4, 3) == 65539);  // this test may take a long time to complete
	return 0;
}
