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
		list B = nullptr;
		reuse_neg_pos_partition_list(A, B);
		print_list(A, "A: ");
		print_list(B, "B: ");
		assert_list(A, {-1, -10, -34});
		assert_list(B, {4, 9, 11, 22});
		destroy_list(A);
		destroy_list(B);
	}

	{//all negative
		cout << endl;
		list A = create_list({-1, -4, -9, -10, -11, -22, -34});
		list B = nullptr;
		reuse_neg_pos_partition_list(A, B);
		print_list(A, "A: ");
		print_list(B, "B: ");
		assert_list(A, {-1, -4, -9, -10, -11, -22, -34});
		assert_list(B, {});
		destroy_list(A);
		destroy_list(B);
	}
	
	{//all positive
		cout << endl;
		list A = create_list({1, 4, 9, 10, 11, 22, 34});
		list B = nullptr;
		reuse_neg_pos_partition_list(A, B);
		print_list(A, "A: ");
		print_list(B, "B: ");
		assert_list(B, {1, 4, 9, 10, 11, 22, 34});
		assert_list(A, {});
		destroy_list(A);
		destroy_list(B);
	}

	{//empty
		cout << endl;
		list A = create_list({});
		list B = nullptr;
		reuse_neg_pos_partition_list(A, B);
		print_list(A, "A: ");
		print_list(B, "B: ");
		assert_list(B, {});
		assert_list(A, {});
		destroy_list(A);
		destroy_list(B);

	}
}
