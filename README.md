# Data_struct 严蔚敏 吴伟民
## ch-03 stack and queue
### stack ADT
#### 实现一、采用的存储结构为顺序存储结构
```c++
#ifndef SQSTACK_H
#define SQSTACK_H
#include <iostream>
#include "../../ch-02 linear lists/sqlist-adt/SqList.h"

template <typename Item>
class sqstack : private SqList<Item>
{
	private:
		typedef SqList<Item> base; 
	private:
		enum {default_size = 512};
	public:
		~sqstack(){};
		sqstack(int size = default_size): base(size){};
		sqstack(const Item * is, int n): base(is, n){};
		sqstack(const sqstack & st): base(st){};
		sqstack & operator=(const sqstack &) = delete;
		/** read top item*/
		bool get_top(Item & i)const{return base::operator[](base::length()-1);};
		bool push(const Item & i){return base::append(i);}
		/** read top item and delete it*/
		bool pop(Item & i){return base::del_n(base::length()-1, i);}
		bool is_empty(void)const{return base::is_empty();};
		bool is_full(void)const{ return base::is_full();};
		void show(void)const{base::show();};
		int length(void)const{return base::length();}
		int size(void)const{return base::size();}
};
#endif
```
### 应用
#### 进制转换
```c++
template <typename T>//must be  an integer
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
		stack.push(elements[remainder]);
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
```
![](https://github.com/Tim-xiaofan/Data_struct/blob/06a1118a4498ddfb7edd67e53bd5967f1ef06e4d/ch-03%20stack%20and%20queue/base-conversion/base_conversion.png) 

### 括号匹配
```c++
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
		//std::cout << "cur = " << cur << std::endl;
		if(is_right(cur))
		{/** check if matches top one*/
			stack.pop(top);
			if(top != get_left(cur))/** not matched*/
			  return false; 
		}
		else/** just push into stcak*/
		  stack.push(cur);
		//std::cout << "stack : ";
		//stack.show();
	}
	return stack.is_empty();
}
```
```
