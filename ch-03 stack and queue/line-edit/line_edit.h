/** 20210403 11:54, zyj, GuangDong*/
#ifndef LINE_EDIT_H
#define LINE_EDIT_H
#include <iostream>
#include <string>
#include "../sqstack-adt/sqstack.h"

class line_edit
{
	private:
		char _bsapce;/** backspace*/
		char _bline;
	public:
		~line_edit(){}
		line_edit(char bspace = '#', char bline = '@'):
			_bsapce(bspace), _bline(bline){}
		std::string get_line(void) const;
};

std::string line_edit::
get_line(void) const
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::string;

	char ch, top;
	string result;
	sqstack<char> stack(128);
	int i, len;

	while((ch = cin.get()) != '\n')
	{
		//cout << "cur = " << ch << endl;
		if(ch == _bsapce) stack.pop(top);
		else if (ch == _bline) while(stack.pop(top));
		else stack.push(ch);
		//cout << "stack : " << endl;
		//stack.show();
	}

	len = stack.length();
	for(i = 0; i < len; i++)
	  result.push_back(stack[i]);
	return result;
}
#endif
