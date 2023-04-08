#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <iterator>
#include "list.h"

using std::cout;
using std::endl;
using std::vector;
using std::initializer_list;

int main(void)
{
	using namespace HOMEWORK_NS;
	{//normal
		list A = create_list({-1, 4, 9, -10, 11, 22, -34});
		print_list(A, "original A: ");
		reverse_list(A);
		print_list(A, "reversed A: ");
		assert_list(A, {-34, 22, 11, -10, 9, 4, -1});
		destroy_list(A);
	}

	{// one
		cout << endl;
		list A = create_list({1});
		print_list(A, "original A: ");
		reverse_list(A);
		print_list(A, "reversed A: ");
		assert_list(A, {1});
		destroy_list(A);
	}

	{//empty
		cout << endl;
		list A = create_list({});
		print_list(A, "original A: ");
		reverse_list(A);
		print_list(A, "reversed A: ");
		assert_list(A, {});
		destroy_list(A);

	}

	{//double reverse
		list A = create_list({-1, 4, 9, -10, 11, 22, -34});
		print_list(A, "original A: ");
		reverse_list(A);
		reverse_list(A);
		print_list(A, "reversed A: ");
		assert_list(A, {-1, 4, 9, -10, 11, 22, -34});
		destroy_list(A);
	}
}
