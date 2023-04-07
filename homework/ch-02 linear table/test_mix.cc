#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <cassert>
#include "list.h"

using std::cout;
using std::endl;
using std::vector;
using std::initializer_list;

namespace HOMEWORK_NS
{

std::ostream& operator<<(std::ostream& os, std::vector<int> v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	return os;
}

}

int main(void)
{
	using namespace HOMEWORK_NS;
	{
		initializer_list<int> il1 = {0, 1, 4, 9, 10, 11, 22, 34};
		initializer_list<int> il2 = {1, 3, 7, 9, 22, 23};
		list A = create_list(il1);
		list B = create_list(il2);
		list C = reuse_delete_mix_list(A, B);
		print_list(A, "A: ");
		print_list(C, "C: ");
		assert(equal_list(A, C));
		assert_list(C, {1, 9, 22});
		destroy_list(A);
	}

	{
		cout << endl;
		list A = create_list({1, 3, 5, 7, 9});
		list B = create_list({0, 2, 4, 6, 8});
		A = reuse_delete_mix_list(A, B);
		print_list(A, "A: ");
		assert_list(A, {});
		destroy_list(A);
	}

	{
		cout << endl;
		list A = create_list({});
		list B = create_list({});
		A = reuse_delete_mix_list(A, B);
		print_list(A, "A: ");
		assert_list(A, {});
		destroy_list(A);
	}

	return 0;
}
