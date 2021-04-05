# 数据结构 严蔚敏 吴伟民
# 说明
（1）源码：C++11及以上<br>
（2）编译运行环境：理论上支持C++11及以上即可<br>
（3）笔者环境：Linux、g++、make。<br>
（4）ADT命名：***-adt存放的是对应抽象数据类型的定义和实现，例如sqlist-adt就是顺序表的顺序存储结构实现。<br>
（5）书中算法（不包括习题）命名：以算法命名，例如base-conversion存放的是进制转换的实现<br>
# 使用（Linux）:
>> * 获取<br>
>> ``` shell git clone git@github.com:Tim-xiaofan/Data_struct.git<br> ```
>> * 使用sqlist : <br>
>> ```C++
>> #include "/Data_struct/ch-02 linear lists/sqlist-adt/SqList.h"
>> ```
>> * 使用其他实现替换上面的路径即可
>> * 注意不能改变项目目录结构
# 目录
Table of contents
=================

<!--ts-->
   * [ch 03 stack and queue](#ch-03-stack-and-queue)
      * [stack adt](#stack-adt)
      * [base conversion](#base-conversion)
      * [bracket matching](#bracket-matching)
      * [maze path](#maze-path)
      * [evaluate expression](#evaluate-expression)
      * [hanoi tower](#hanoi-tower)
<!--te-->


Installation
============
# 遇到什么问题欢迎在[Issues](https://github.com/Tim-xiaofan/Data_struct/issues)中提出
ch 03 stack and queue
============
stack ADT
===========
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
base conversion
============
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

bracket matching
============
##### 算法描述(书)
由此，在算法中设置一个栈，每读入一个括号，若是右括号，则或者使置于栈顶的最急迫的期待得以消解，或者是不合法的情况;若是左括号，则作为—个新的更急迫的期待压入栈中，自然使原有的在栈中的所有未消解的期待的急迫性都降了一级。另外，在算法的开始和结束时，栈都应该是空的。
##### c++实现（未OJ）
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
maze path
============
##### 算法描述(书)
> 设定当前位置的初值为入口位置; <br>
> do (<br>
> 若当前位置可通，// 纳入路径<br>
> 则{ 将当前位置插入栈顶;// 求得路径存放在栈中<br>
>> 若该位置是出口位置，则结束;<br>
>> 否则切换当前位置的东邻方块为新的当前位置;<br>
> }<br>
> 否则，<br>
>> 若栈不空且栈顶位置尚有其他方向未经探索，<br>
>> 则设定新的当前位置为沿顺时针方向旋转找到的栈顶位置的下一相邻块;若栈不空但栈顶位置的四周均不可通，<br>
>> 则{ 删去栈顶位置;// 从路径中删去该通道块<br>
>> 若栈不空 ，则重新测试新的栈顶位置，<br>
>> 直至找到一个可通的相邻块或出栈至栈空;<br>
> }while（栈不空）;<br>
##### c++实现（未OJ）
```c++
template<typename Maze>
bool maze_path(Maze & maze)
{
	typedef typename Maze::room_type room;
	int rows, cols, loop = 0;
	room start, end, cur, next, top;

	/** check start and end*/
	start = maze.start();
	end = maze.end();
	if(!start.is_room() || !end.is_room())
	{
		std::cout << "invalid start or end\n";
		return false;
	}

	/** init stack*/
	rows = maze.rows();
	cols = maze.cols();
	sqstack<room> path(rows * cols);

	cur = start;
	do
	{
		++loop;
		if(maze.is_room(cur))/** room*/
		{
			if(!path.push(cur))
			{
				//std::cout << "path is full\n";
				return false;
			}
			maze.in_path(cur, true);/** marked*/
			if(cur == end)
			{
				std::cout << "got a path : ";
				path.show();
				return true;
			}
			//std::cout << cur << " is room\n";
			maze.get_next(cur, next);
			cur = next;
			//std::cout << next << " is next\n";
		}
		else
		{
			//std::cout << cur << " is not room\n";
			
			if(path.get_top(top)&&maze.has_other(top))/** there are other direction to explore*/
			{
				//std::cout << "there are other direction in top : "<< top << "\n";
				maze.get_next(top, next);
				cur =next;
				//std::cout << next << " is next\n";
			}
			else
			{/** there are not other direction to explore in top */
				//path.get_top(top);
				while(path.get_top(top)&&!maze.has_other(top))
				{
					maze.reset_status(top);
					path.pop(top);
					//std::cout << "no other, pop : " << top << std::endl;
					//path.get_top(top);
				}
				if(!path.is_empty()) 
				{/** found one that has other direction to explore*/
					path.get_top(top);
					//std::cout << "found one in stack"<< top <<"\n";
					maze.get_next(top, next);
					cur =next;
					//std::cout << next << " is next\n";
				}
			}
		}
		//std::cout << "current path : ";
		//path.show();
		//std::cout << "current maze : \n";
		//maze.show();
		//std::cout << "\n";
	}while(!path.is_empty());
	std::cout << "no path found : " << loop <<"\n";
	return false;
}
```
evaluate expression
============
##### 算法描述（书）
（1）首先置操作数栈为空栈，表达式起始符"#"为运算符栈的栈底元素;<br>
（2）依次读入表达式中每个字符，若是操作数则进 OPND 栈，若是运算符则和 OPTR 栈的栈顶运算符比较优先权后作相应操作，直至整个表达式求值完毕（即 OPTR栈的栈顶元素和当前读入的字符均为"#"）。<br>
##### c++实现（未OJ）
```c++
template<typename Expression, typename Operand>
bool evaluate_expression(const Expression & expr, Operand & result)
{
	if(!expr.is_valid())
		return false;

	typedef typename Expression::item_type item;

	int count = expr.count(), i;
	sqstack<item> optr(count);
	optr.push(Expression::delimiter);
	sqstack<item> opnd(count);
	item a, b, theta, top;

	for(i = 0; i < count; i++)
	{
		std::cout << "#0---------------\n";
		std::cout << "cur = " << expr[i] << std::endl;
		if((expr[i]).type() == Expression::OPND)/** It's operand*/
		  opnd.push(expr[i]);
		else/** It's operator*/
		{
			optr.get_top(top);
			switch(Expression::precede(top, expr[i]))
			{
				case Expression::LOW: /** top < current*/
					optr.push(expr[i]);
					break;
				case Expression::EQUAL: /** rm bracket*/
					optr.pop(theta);
					break;
				case Expression::HIGH:/** top > current*/
					if(!opnd.pop(b) || !opnd.pop(a))
					  return false;
					optr.pop(theta);
					/** get result and push result inito operator stack*/
					opnd.push(Expression::operator_theta(theta, a, b));
					--i;
					//optr.push(expr[i]);
					break;
				case Expression::UNKNOWN:/** incomparable*/
					return false;/** error*/
			}
		}
		opnd.show();
		optr.show();
		std::cout << "#1---------------\n";
	}
	opnd.get_top(result);
	return true;
}
```
hanoi tower
============
##### 算法描述（书）
如何实现移动圆盘的操作呢?<br>
当 n=1 时，问题比较简单，只要将编号为1 的圆盘从塔座 X直接移至塔座 乙 上即可∶<br>
当 n>1 时，需利用塔座 Y 作辅助塔座，若能设法将压在<br>
编号为 n 的圆盘之上的n—1 个圆盘从塔座 X（依照上述法则）移至塔座 Y 上，则可先将编号为n 的圆盘从塔座X移至塔座Z上，然后再将塔座 Y 上的 n—1个圆盘（依照上述法则）移至塔座Z上。而如何将n—1个圆盘从一个塔座移至另一个塔座的问题是一个和原问题具有相同特征属性的问题，只是问题的规模小1，因此可以用同样的方法求解。<br>
##### c++实现（未OJ）
```c++
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
```
