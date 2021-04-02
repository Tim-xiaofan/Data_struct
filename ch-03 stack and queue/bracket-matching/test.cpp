/** 20210402 21:00, zyj, GuangDong*/
//test.c -- test bracket matching algorithm
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <iterator>

#include "bracket_match.h"

#define N 3
#define M 12

static const pair ps[N] = 
{
	{'(', ')'},
	{'[', ']'},
	{'{', '}'}
};

static const std::string tests[M]
{
	"",
	"()",
	"[]",
	"{}",
	"(",
	")",
	"[",
	"]",
	"{",
	"}",
	"{()}",
	"[{)}]"
};

int main()
{
	using namespace std;

	int i;
	bracket_match bm(ps, N);
	bm.show();

	for(i = 0; i < M; i++)
	  cout << '"'<< tests[i] << '"'<<  " is matched :"
		  << std::boolalpha <<bm.match(tests[i]) << endl;
}
