/** 20210727 9:40, zyj, GuangDong*/
//test.c -- test n-queens
#include <iostream>
#include <iomanip>
#include <cstring>
#include "n_queens.h"

using std::cout;
using std::cin;
using std::endl;

int main(int ac, char * av[])
{
	int n;
	cout << "n : ";
	cin >> n;
	cout << "ct = " << n_queens(n) << endl;
	return 0;
}
