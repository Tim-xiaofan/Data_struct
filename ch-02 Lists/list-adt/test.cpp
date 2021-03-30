/** 20210323 22:37, zyj, GuangDong*/
//test.c -- test list.h
#include <iostream>
#include <cstdio>
#include <string>
#include <List.h>
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

template<typename T>
void show(const List<T> &l, const std::string & info);

int main()
{
	using namespace std;
	int i;
	string s;
	List<int> li(SIZE);
	List<string> ls(B, 7);

	li.append_bulk(A, 4);
	fprintf(stdout, "li(%d) : ", li.length());
	li.show();
	//ls.append_bulk(B, 7);	
	fprintf(stdout, "ls(%d) : ", ls.length());
	ls.show();

	li.set_cursor(0);
	fprintf(stdout, "current pos : %d\n", li.current());
	ls.set_cursor(5);
	fprintf(stdout, "current pos : %d\n", ls.current());
	ls.reset_cursor();
	fprintf(stdout, "current pos : %d\n", ls.current());

	while(li.get_next(i))
	  fprintf(stdout, "%d ", i);
	fprintf(stdout, "\n");
	while(ls.get_next(s))
	  fprintf(stdout, "%s ", s.c_str());
	fprintf(stdout, "\n");

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
	List<string>::input_iterator it;
	for(it = ls.begin(); it != ls.end(); it++)
	  cout << *it << " ";
	cout << "\n";
	List<string>::fwd_iterator fit = ls.begin();
	*fit = B[6];
	
	List<int>::fwd_iterator it1;
	for(it1 = li.begin(); it1 != li.end(); it1++)
	   (*it1) = 5;

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

	List<string> ls1 = ls, ls2;
	show(ls1, "ls1 : ");
	ls1.clear();
	cout << "after clearing, ls1(" << ls1.length() << ") : ";
	ls1.show();
}

template<typename T>
void show(const List<T> &l, const std::string & info)
{
	std::cout << info;
	std::ostream_iterator<T, char> out(std::cout, " ");
	std::copy(l.begin(), l.end(), out);
	std::cout << "\n";
}
