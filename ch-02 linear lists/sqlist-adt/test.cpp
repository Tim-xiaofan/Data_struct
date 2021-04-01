/** 20210323 22:37, zyj, GuangDong*/
//test.c -- test list.h
#include <iostream>
#include <cstdio>
#include <string>
#include <SqList.h>
#include <algorithm>
#include <iterator>
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
	string s;
	SqList<int> li(SIZE);
	fprintf(stdout, "li(%d, %d)\n", li.size(), li.length());
	SqList<string> ls(B, 7);

	li.append_bulk(A, 4);
	fprintf(stdout, "li(%d) : ", li.length());
	li.show();
	//ls.append_bulk(B, 7);	
	fprintf(stdout, "ls(%d) : ", ls.length());
	ls.show();

	for(i = -1; i <= ls.length(); i++)
	  if(ls.get_n(i, s)) 
		fprintf(stdout, "%s ", s.c_str());
	fprintf(stdout, "\n");

	cout << "enter the position to delete in list ls : ";
	cin >>  i;
	ls.del_n(i, s);
	cout << "after deleting, ls (" << ls.length()<< "): ";
	ls.show();

	cout << "enter the position to insert into list ls : ";
	cin >>  i;
	ls.insert_n(i, "test");
	cout << "after inserting, ls (" << ls.length()<< "): ";
	ls.show();
	
	cout << "enter the content to search in list ls : ";
	cin >>  s;
	cout << "result of searching " << s 
		<< " :  " << ls.search(s)<< endl;

	cout << "------- iterator -------" << endl;
	SqList<string>::input_iterator it;
	for(it = ls.begin(); it != ls.end(); it++)
	  cout << *it << " ";
	cout << "\n";

	cout << "------- iterator -------" << endl << endl;
	//li.show();

	/** STL algorithms*/
	cout << "------- STL algorithms -------" << endl;
	cout << "copy : \n";
	show(ls, "ls : ");
	show(li, "li : ");
	cout << "count_if : " << 
		count_if(ls.begin(), ls.end(),
					[](string s){return (s == "Saturday");});
	cout << endl;
	cout << "------- STL algorithms -------" << endl;

	SqList<string> ls1 = ls, ls2, ls3(ls);
	show(ls1, "ls1 : ");
	ls1.clear();
	cout << "after clearing, ls1(" << ls1.length() << ") : ";
	ls1.show();

	show(ls3, "ls3 : ");
}

template<typename List>
void show(const List &l, const std::string & info)
{
	std::cout << info;
	std::ostream_iterator<typename List::item_type, char> out(std::cout, " ");
	std::copy(l.begin(), l.end(), out);
	std::cout << "\n";
}

