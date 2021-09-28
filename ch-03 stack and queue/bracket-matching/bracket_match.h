/** 20210402 20:54, zyj, GuangDong*/
#ifndef BRACKET_MATCH_H
#define BRACKET_MATCH_H
#include <iostream>
#include <string>
#include "sqstack.h"

struct pair
{
	char left, right;
	pair(char l = '0', char r = '0'):left(l), right(r){}
	pair & operator=(const pair &) = default;
};

std::ostream & operator<<(std::ostream & os, const pair p)
{
	os << "\"" <<p.left << " " << p.right << "\"";
	return os;
}

class bracket_match
{
	private:
		enum{MAX = 12};
		int _ct;
		pair _ps[MAX];
	private:
		/** auxiliary functions*/
		bool is_right(char half);
		char get_left(char half);
	public:
		~bracket_match(){};
		bracket_match(const pair * ps, int ct);
		bool match(const std::string & bkts);
		void show(void) const;
};

bracket_match::
bracket_match(const pair *ps, int ct)
{
	int i;

	_ct = ct;
	for(i = 0; i < ct; ++i)
	  _ps[i] = ps[i];
}

bool bracket_match::
is_right(char half)
{
	int i;
	for(i = 0; i < _ct; i++)
	  if(_ps[i].right == half) return true;
	return false;
}

/** @return '0' is failed, else successful*/
char bracket_match::
get_left(char half)
{
	int i;
	for(i = 0; i < _ct; i++)
	  if(_ps[i].right == half) return _ps[i].left;
	return '0';
}

/** check if the brackets are matched*/
bool bracket_match::
match(const std::string & bkts)
{
	int i, len;
	char top, cur;
	sqstack<char> stack(128);

	len = bkts.size();
	/** odd number brackets must be not matched*/
	if(len % 2 != 0) return false;
	for(i = 0; i < len; i++)
	{
		cur  = bkts[i];
		if(is_right(cur))//right
		{/** check if matches top one*/
			stack.pop(top);
			if(top != get_left(cur))/** not matched*/
			  return false; 
		}
		else/** left : just push into stcak*/
		  stack.push(cur);
	}
	return stack.is_empty();
}

void bracket_match::
show(void) const
{
	int i;
	for(i = 0; i < _ct; ++i)
	  std::cout << _ps[i] << " ";
	std::cout << std::endl;
}

#endif
