/** 20210907 12:40, zyj, GuangDong*/
//test.c -- test static_search.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include "static_search.h"
#include "SqList.h"

#define SQLIST 1

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#ifdef SQLIST
#define N 16
static void 
test_sqlist(void)
{
    SqList<int> list(N);
    int i, tar;

    srand(time(nullptr));
    for(i = 0; i < N; ++i)
      list.append(rand() % 100);
    list.show("list : ");
    while(1)
    {
        cout << "target (q to quit) : ";
        if(!(cin >> tar)) break; 
        cout << "result : "<< sq_search(list, tar, find<int>) << endl;
    }
}
#endif

int main(int ac, char * av[])
{
#ifdef SQLIST
    test_sqlist();
#endif
    cout << "done." << endl;
	return 0;
}
