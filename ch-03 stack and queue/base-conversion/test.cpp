/** 20210323 22:37, zyj, GuangDong*/
//test.c -- test list.h
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <iterator>

#include "base_conversion.h"

#define SIZE 16

int main()
{
	using namespace std;
	int i = 1569;
	base_conversion<int> bc;

	cout << "original : \n";
	cout << bc.mode() << " : " << bc.mode2str() << endl;
	std::cout << "expected : 0x" << hex << i << endl;
	std::cout << "result : 0x" << bc.conversion(i) << endl;
	//bc.conversion(i);
	
	bc.mode(base_conversion<int>::DEC2BIN);
	cout << "after setting : \n";
	cout << bc.mode() << " : " << bc.mode2str() << endl;
	std::cout << "expected : 0x" << hex << i << endl;
	std::cout << "result : 0x" << bc.conversion(i) << endl;
}
