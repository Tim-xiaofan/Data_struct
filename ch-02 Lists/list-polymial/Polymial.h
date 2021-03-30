/** 20210330 20:54, zyj, GuangDong*/
//Polymial.h
#ifndef POLYMIAL_H
#define POLYMIAL_H
#include "../list-adt/List.h"

template<typename T1 = float, typename T2 = int>
struct Item
{
	T1 coef;
	T2 expn;
	Item(c = 0, e = 0):coef(c), expn(e){}
}

template<typename Item> 
class Polymial: private List<Item>
{
	public:
		Polymial(const Item *is, int ct);
		Polymial(const Polymial & P);
		~Polymial(){}
		puts(const Items *is, int ct);
		puts(const Items &i);
		Polymial operator=(const Polymial & P);
		Polymial operator+(const Polymial & p) const;
		Polymial operator-(const Polymial & p) const;
		Polymial operator*(const Polymial & p) const;
		const Item & get(int pos) const;
		Item & get(int pos);
}

#endif
