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
#define N 16
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
#define N 16
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
template <typename T>
void show_array(const T * a, int size)
{
    int i;
    for(i = 0; i < size; ++i)
      cout << a[i] << " ";
    cout << endl;
}

static void
test_so(char *table, float *w, int size)
{
	bitree<char> tree;
    int * levels = new int[size], ret, i;
    float PH = 0;
    /** 从有序序列和对应权值构建次优查找树*/
	tree.second_optimal(table, w, size);
    cout << "preorder_traverse : ";
	tree.preorder_traverse();
    cout << "inorder_traverse  : ";
	tree.inorder_traverse();
    cout << "level_traverse    : ";
	tree.level_traverse();
    cout << "levels            : ";
    ret = tree.get_levels(levels);
    show_array(levels, ret);
    cout << "table             : ";
    show_array(table, size);
    cout << "w                 : ";
    show_array(w, size);
    cout << "levels            : ";
    for(i = 0; i < size; ++i)
      cout <<tree.get_level(table[i]) << " ";
    cout << endl;

    /** PH calculation*/
    for(i = 0; i < size; ++i)
      PH += tree.get_level(table[i]) * w[i];
    cout << "PH                : " << PH << endl;
    cout << "edges :";
    bitree<char>::edge edges[64];
    ret = tree.get_edges(edges, 64);
    for(int i = 0; i < ret; ++i)
      cout << ""<<edges[i] << " ";
    cout << endl;
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
	char table[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
	float w[9] = {1, 1, 2, 5, 3, 4, 4, 3, 5};
	//float w1[5] = {1, 30, 2, 29, 3};
    test_so(table, w, 9);
    //test_so(table, w1, 5);
#endif
    cout << "done." << endl;
	return 0;
}
