/** 20210323 22:37, zyj, GuangDong*/
//test.c -- test list.h
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <iterator>

#include "sqstack.h"

#define SIZE 16

static int A[4] = {3,5,8,11};
static std::string B[7]= {
	"Sunday", 
	"Monday", 
	"Tuesday",
	"Wednesday", 
	"Thursday", 
	"Friday", 
	"Saturday"};

template<typename List>
void show(const List &l, const std::string & info);

int main()
{
	using namespace std;

	int i;

	sqstack<int> sti(A, 4);
	sqstack<string> sts(B, 7);

	cout << "sti(" << sti.length() << ") : ";
	sti.show();
	cout << "sts(" << sts.length() << ") : ";
	sts.show();

	while(sti.pop(i))
	  cout << "pop : " << i << endl;
	cout << "after popping, sti(" << sti.length() << ") : ";
	sti.show();

	srand(time(NULL));
	i = 0;
	while(sti.push(1 + rand() % 512) && (++i) < 16);
	cout << "after pushing, sti(" << sti.length() << ") : ";
	sti.show();
}

template<typename List>
void show(const List &l, const std::string & info)
{
	std::cout << info;
	std::ostream_iterator<typename List::item_type, char> out(std::cout, " ");
	std::copy(l.begin(), l.end(), out);
	std::cout << "\n";
}

