/** 20210727 9:35, zyj, GuangDong*/
//n_queens.cpp
#include "n_queens.h"
#include "sqstack.h"
#include <cstring>

using std::cout;
using std::cerr;
using std::endl;

struct position
{
	int i, j;
	bool operator==(const position & pos) const {return i == pos.i && j == pos.j;}
	friend std::ostream & operator<<(std::ostream & os, const position & pos);
};

std::ostream & operator<<(std::ostream & os, const position & pos)
{
	os << "(" << pos.i << "," << pos.j << ")";
	return os;
}

static void 
n_queens(int n, int i, sqstack<position> & s, int & ct);

static bool 
is_valid(int n, const position & pos, const sqstack<position> & s);

static void
show(int n, const sqstack<position> & s);

int n_queens(int n)
{
	int ct = 0;
	sqstack<position> s(n + 1);
	n_queens(n, 0, s, ct);
	return ct;
}

static void 
n_queens(int n, int i, sqstack<position> & s, int & ct)
{
	//static int index = 0;
	int j;
	position pos, tmp;
	if(i >= n) 
	{
		//cout << "************"<<++index<<"**************\n";
		//show(n, s);
		//cout << "******************************\n";
		ct++;
	}
	else
	{
		pos.i = i;
		//current row
		for(j = 0; j < n; ++j)
		{
			pos.j = j;
			if(is_valid(n, pos, s))
			{
				s.push(pos);
				n_queens(n, i + 1, s, ct);
				s.pop(tmp);
			}
		}
	}
}

static bool 
is_valid(int n, const position & pos, const sqstack<position> & s)
{
	int i, len, j;
	position tmp;
	//row check
	//col check
	len = s.length();
	for(i = 0; i < len; ++i)
	  if(s[i].j == pos.j) return false;
	//triangle check
	for(i = 0; i < len; ++i)
	{
		//left-up
		for(j = 1; pos.i - j >= 0 && pos.j - j >= 0; ++j)
		{
		  tmp.i = pos.i - j;
		  tmp.j = pos.j - j;
		  if(tmp == s[i]) return false;
		}
		//rigth-up
		for(j = 1; pos.i - j >= 0 && pos.j + j < n; ++j)
		{
		  tmp.i = pos.i - j;
		  tmp.j = pos.j + j;
		  if(tmp == s[i]) return false;
		}
	}
	return true;
}

static void
show(int n, const sqstack<position> & s)
{
	int i, j;
	char * mat = new char[n * n];
	memset(mat, '0', n * n);

	for(i = 0; i < s.length(); ++i)
	  mat[s[i].i * n + s[i].j] = '1';
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < n; ++j)
		  cout << mat[i * n + j] << " ";
		cout << endl;
	}
}
