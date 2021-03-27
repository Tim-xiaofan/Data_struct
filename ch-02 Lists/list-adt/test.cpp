/** 20210323 22:37, zyj, GuangDong*/
//test.c -- test list.h
#include <iostream>
#include <cstdio>
#include <string>
#include <List.h>
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
void show(const List<int> &);

int main()
{
	using namespace std;
	int i;
	string s;
	List<int> li(SIZE);
	List<string> ls(SIZE);

	li.append_bulk(A, 4);
	fprintf(stdout, "li(%d) : ", li.length());
	li.show();
	ls.append_bulk(B, 7);	
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
	List<string>::const_iterator it;
	for(it = ls.begin(); it != ls.end(); it++)
	  cout << *it << " ";
	cout << "\n";

	show(li);
	cout << "------- iterator -------" << endl << endl;
	li.show();
}

void show(const List<int> &li)
{
	List<int>::const_iterator it;
	for(it = li.begin(); it != li.end(); it++)
	  std::cout << *it << " ";
	std::cout << "\n";
}

