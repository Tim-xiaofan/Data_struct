/** 20210402 08:56, zyj, GuangDong*/
#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H
#include <iostream>
#include <string>
#include "sqstack.h"

template <typename T = int>
class base_conversion
{
	private:
		int _mode;
	public:
		enum {DEC2BIN = 2, DEC2OCT = 8, DEC2HEX = 16};
		base_conversion(int mode = DEC2HEX): _mode(mode){}
		bool mode(int mode);
		int mode(void)const{return _mode;}; 
		std::string mode2str(void)const; 
		std::string conversion(T t)const;
};

static const char elements[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

template <typename T>
bool base_conversion<T>::
mode(int mode)
{
	switch(mode)
	{
		case DEC2BIN:_mode = DEC2BIN;return true;
		case DEC2OCT:_mode = DEC2OCT;return true;
		case DEC2HEX:_mode = DEC2HEX;return true;
		default:std::cerr<< "unknown mode : " << mode << std::endl; return false;
	}
}

template <typename T>
std::string base_conversion<T>::
mode2str(void)const
{
	switch(_mode)
	{
		case DEC2BIN:return "DEC2BIN";
		case DEC2OCT:return "DEC2OCT";
		case DEC2HEX:return "DEC2HEX";
		default:return "UNKOWN";
	}
}

template <typename T>
std::string base_conversion<T>::
conversion(T t) const
{
	T quotient, remainder;
	sqstack<char> stack(16);
	std::string result;
	char ch;
	quotient = t;
	int i;

	while(t != 0)
	{
		quotient = t / _mode;
		remainder = t % _mode;
		//std::cout << "push : " << remainder << std::endl;
		//stack.push('0' + remainder);
		stack.push(elements[remainder]);//当前余数入栈
		t = quotient;
	}

	//stack.show();
	//std::cout << "length = " << stack.length() << std::endl;
	int len = stack.length();
	for(i = 0; i < len; i++)
	{
		stack.pop(ch);
		//std::cout << "pop : " << ch << std::endl;
		result.push_back(ch);
	}
	return result;
}
#endif
