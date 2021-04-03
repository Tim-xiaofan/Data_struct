# 数据结构 严蔚敏 吴伟民
# 说明
（1）源码：C++11及以上<br>
（2）编译运行环境：理论上支持C++11及以上即可<br>
（3）笔者环境：Linux、g++、make。<br>
（4）ADT命名：***-adt存放的是对应抽象数据类型的定义和实现，例如sqlist-adt就是顺序表的顺序存储结构实现。<br>
（5）书中算法（不包括习题）命名：以算法命名，例如base-conversion存放的是进制转换的实现<br>
（6）why C++ not C?：<br>
>> * ADT设计是以面向对象设计的，虽然面向对象与语言无关，但是使用C语言进行面向对象设计对笔者这种菜鸡难度过大，而C++从语言层面提供了支持<br>
>> * ADT要求多形数据类型（polymorphic data type）。例如一个顺序表的ADT，其中的数据项可以是任意类型(char, int, float, struct, pointer), 使用C语言实现对笔者这种菜鸡难度过大, 而C++模板（Generic Programming）对此进行了支持。<br>
>> * 书中的typedef int ElemType使用环境是类C的伪代码：也就是实际实现时，单纯把int替换成long、char、short可能相关的你的 Stack ADT依然能用，但是换成strut book可能就要修改ADT了。而c++的重载可以满足不修改ADT的期望<br>
>> * 笔者自身感受（个人）：后面的章节发现之前的ADT不能开箱即用，会有巨大挫败感。<br>
# 使用（Linux）:
>> * 获取<br>
>> ``` shell git clone git@github.com:Tim-xiaofan/Data_struct.git<br> ```
>> * 使用sqlist : <br>
>> ```C++
>> #include "/Data_struct/ch-02 linear lists/sqlist-adt/SqList.h"
>> ```
>> * 使用其他实现替换上面的路径即可
>> * 注意不能改变项目目录结构
# 遇到什么问题欢迎在[Issues](https://github.com/Tim-xiaofan/Data_struct/issues)中提出
## 第三章 栈和队列
### Stack ADT
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
##### 算法描述（书）
![](https://github.com/Tim-xiaofan/Data_struct/blob/06a1118a4498ddfb7edd67e53bd5967f1ef06e4d/ch-03%20stack%20and%20queue/base-conversion/base_conversion.png) 
##### c++实现
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

### 括号匹配
##### 算法描述(书)
由此，在算法中设置一个栈，每读入一个括号，若是右括号，则或者使置于栈顶的最急迫的期待得以消解，或者是不合法的情况;若是左括号，则作为—个新的更急迫的期待压入栈中，自然使原有的在栈中的所有未消解的期待的急迫性都降了一级。另外，在算法的开始和结束时，栈都应该是空的。
##### c++实现
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
