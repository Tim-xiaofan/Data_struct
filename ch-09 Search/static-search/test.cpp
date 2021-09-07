/** 20210907 12:40, zyj, GuangDong*/
//test.c -- test static_search.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include "static_search.h"
#include "SqList.h"
#include "bitree.h"

#define N 16

//#define LTABLE 1
//#define BIN 1
#define SECOND_OPTIMAL 1

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#ifdef LTABLE
static void 
test_linear(void)
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

#ifdef BIN
static void 
test_bin(void)
{
    SqList<int> list(N);
    int i, tar;

    srand(time(nullptr));
    for(i = 0; i < N; ++i)
      list.append(i);
    list.show("list : ");
    while(1)
    {
        cout << "target (q to quit) : ";
        if(!(cin >> tar)) break; 
        cout << "result : "<< bin_search(list, tar, cmp<int>) << endl;
    }
}
#endif

#ifdef SECOND_OPTIMAL
static void
test_so(void)
{
	bitree<char> tree;
	char table[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
	float w[9] = {1, 1, 2, 5, 3, 4, 4, 3, 5};
	tree.second_optimal(table, w, 9);
	cout << "preorder : ";
	tree.preorder_traverse();
	cout << "inorder : ";
	tree.inorder_traverse();
}
#endif

int main(int ac, char * av[])
{
#ifdef LTABLE
    test_linear();
#endif
#ifdef BIN
    test_bin();
#endif
#ifdef SECOND_OPTIMAL
    test_so();
#endif
    cout << "done." << endl;
	return 0;
}
