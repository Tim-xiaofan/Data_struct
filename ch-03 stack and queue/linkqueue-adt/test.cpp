/** 20210405 18:41, zyj, GuangDong*/
//test.cpp -- test linkqueue
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <iterator>

#include "linkqueue.h"

#define N 16

int main()
{
	using namespace std;
	int i;
	linkqueue<int> queue(N);
	for(i = 0; i < N; i++)
	  queue.enqueue(i);
	cout << "after enqueueing : \n";
	cout << "empty : " << std::boolalpha << queue.is_empty() << endl;
	cout << "full : " << std::boolalpha << queue.is_full() << endl;
	cout << "size : " << queue.size() << endl;
	cout << "length : " << queue.length() << endl;
	queue.show();


	for(i = 0; i < N; i++)
	  queue.dequeue(i);
	cout << "after dequeueing : \n";
	cout << "empty : " << std::boolalpha << queue.is_empty() << endl;
	cout << "full : " << std::boolalpha << queue.is_full() << endl;
	cout << "size : " << queue.size() << endl;
	cout << "length : " << queue.length() << endl;
	queue.show();
}
