/** 20210405 15:56, zyj, GuangDong*/
//hanio.cpp -- hanio problem
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "sqstack.h"

template <typename Tower>
bool move(Tower & a, int no, Tower & b)
{
	typename Tower::value_type tmp;
	return a.pop(tmp) && b.push(tmp) && tmp == no;
}

template <typename Tower>
void hanoi(int n, Tower & x, Tower & y, Tower & z, int & mv_ct)
{
	//std::cout << "----------------\n";
	//std::cout << "ct : " << mv_ct << std::endl;
	//std::cout << "x : ";x.show();
	//std::cout << "y : ";y.show();
	//std::cout << "z : ";z.show();
	//std::cout << "\n----------------\n";

	if(n == 1)
	{
		move(x, 1, z);
		mv_ct++;
		std::cout << mv_ct << ", " << "moving \"1\" "<< x.name() << "-->" << z.name() <<"\n";
	}
	else
	{
		/** move the discs numbered from 1 to n-1 on x to y, and z as auxiliary tower*/
		hanoi(n-1, x, z, y, mv_ct); 
		/** move the discs numbered n on x to z*/
		move(x, n, z);
		mv_ct++;
		std::cout << mv_ct << ", " << "moving \""<< n << "\" "<< x.name() << "-->" << z.name() <<"\n";
		/** move the discs numbered from 1 to n-1 on y to z, and x as auxiliary tower*/
		hanoi(n-1, y, x, z, mv_ct); 
	}
}

template<typename T>
class tower : public sqstack<T>
{
	private:
		std::string _name;/** help to trace*/
	public:
		tower(int size = 16, const std::string & name = "NULL")
			:sqstack<T>(size), _name(name){}
		const std::string & name(void) const{return _name;}
};

int main()
{
	using namespace std;
	/** create x, y, x*/
	int n, i, ct = 0;
	cout << "enter n : ";
	cin >> n;
	tower<int> x(n, "X"), y(n, "Y"), z(n, "Z");
	for(i = 0; i < n; i++)
	  x.push(n - i);
	//cout << "x :" ;x.show();
	hanoi(n, x, y, z, ct);
	cout << "z :" ;z.show();
	cout << ct << endl;
}
