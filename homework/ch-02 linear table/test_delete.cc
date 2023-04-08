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
	{//mink and maxk in list
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 4, 22);
		print_list(A, "delete(4, 22) A: ");
		assert_list(A, {1, 4, 22, 34});
		destroy_list(A);
	}

	{// only mink in list
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 4, 23);
		print_list(A, "delete(4, 23) A: ");
		assert_list(A, {1, 4, 34});
		destroy_list(A);
	}

	{// only maxk in list
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 3, 22);
		print_list(A, "delete(3, 22) A: ");
		assert_list(A, {1, 22, 34});
		destroy_list(A);
	}

	{//both not in list
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 3, 23);
		print_list(A, "delete(3, 23) A: ");
		assert_list(A, {1, 34});
		destroy_list(A);
	}

	{// mink out of range
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 0, 23);
		print_list(A, "delete(0, 23) A: ");
		assert_list(A, {34});
		destroy_list(A);
	}

	{// maxk out of range
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 4, 35);
		print_list(A, "delete(4, 35) A: ");
		assert_list(A, {1, 4});
		destroy_list(A);
	}

	{// both out of range
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 0, 35);
		print_list(A, "delete(0, 35) A: ");
		assert_list(A, {});
		destroy_list(A);
	}

	{//empty
		cout << endl;
		list A = create_list({});
		print_list(A, "original A: ");
		delete_min_max(A, 0, 35);
		print_list(A, "delete(0, 35) A: ");
		assert_list(A, {});
		destroy_list(A);
	}

	{// mink = maxk
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		print_list(A, "original A: ");
		delete_min_max(A, 4, 4);
		print_list(A, "delete(4, 4) A: ");
		assert_list(A, {1, 4, 9, 10, 11, 22, 34});
		destroy_list(A);
	}
}
