# 数据结构 严蔚敏 吴伟民
# 说明
（1）源码：C++11及以上<br>
（2）编译运行环境：理论上支持C++11及以上即可<br>
（3）笔者环境：Linux、g++、make。<br>
（4）ADT命名：***-adt存放的是对应抽象数据类型的定义和实现，例如sqlist-adt就是顺序表的顺序存储结构实现。<br>
（5）书中算法（不包括习题）命名：以算法命名，例如base-conversion存放的是进制转换的实现<br>
# 使用（Linux）:
>> * 获取<br>
>> ``` shell 
>> git clone git@github.com:Tim-xiaofan/Data_struct.git
>> ```
>> * 设置环境变量(非永久)<br>
>> ```shell
>> cd /path/Data_struct
>> source sourcefile
>> ```
>> * 使用sqlist : <br>
>> ```C++
>> #include "SqList.h"
>> ```
>> * 使用其他ADT依次类推
>> * 注意不能改变项目目录结构

Table of contents
=================

<!--ts-->
   * [ch-03 stack and queue](#ch-03-stack-and-queue)
      * [stack adt](#stack-adt)
      	* [base conversion](#base-conversion)（ 进制转换）
      	* [bracket matching](#bracket-matching)（括号匹配）
      	* [maze path](#maze-path)（迷宫求解）
      	* [evaluate expression](#evaluate-expression)（表达式求值）
      	* [hanoi tower](#hanoi-tower)（汉诺塔）
   * [ch-05 array and generalized-table](#ch-05-array-and-generalized-table)
      * [array adt](#array-adt)
      * [symmetric matrix adt](#symmetric-matrix-adt )（对称矩阵）
      * [triangular matrix adt](#triangular-matrix-adt)（三角矩阵）
      * [sparse matrix adt](#sparse-matrix-adt)（稀疏矩阵）
      	* [transpose one](#transpose-one)（稀疏矩阵的转置算法一）
      	* [transpose two](#transpose-two)（稀疏矩阵的转置算法二）
      	* [multi smatrix](#multi-smatrix)（稀疏矩阵的乘法）
   * [ch-06 tree and binary-tree](#ch-06-tree-and-binary-tree)
      * [bit tree](#bit-tree)
      	* [preinorder construct](#preinorder-construct)（先序-中序构造二叉树）
      	* [inorder traversex](#inorder-traversex)(中序-非递归遍历二叉树)
      * [bit thread tree](#bit-thread-tree)
      	* [in threading](#in-threading)（中序-线索化二叉树）
      	* [inorder thrtraverse](#inorder-thrtraverse)（中序-遍历线索二叉树）
<!--te-->
# 遇到什么问题欢迎在[Issues](https://github.com/Tim-xiaofan/Data_struct/issues)中提出
ch 03 stack and queue
============
stack ADT
===========
#### [实现一、采用的存储结构为顺序存储结构](https://github.com/Tim-xiaofan/Data_struct/blob/3db2295b3607cd276ac7eab763b57425fa126d91/ch-03%20stack%20and%20queue/sqstack-adt/sqstack.h)
```c++
#ifndef SQSTACK_H
#define SQSTACK_H
#include <iostream>
#include "SqList.h"

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
##### [c++实现](https://github.com/Tim-xiaofan/Data_struct/blob/9520abde744f3efe3d2092c6007862a70689ccdc/ch-03%20stack%20and%20queue/base-conversion/base_conversion.h#L52)
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
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/9418349b2c18d6c7ca961db596d942d1e988cbb0/ch-03%20stack%20and%20queue/bracket-matching/bracket_match.h#L69)
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
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/9418349b2c18d6c7ca961db596d942d1e988cbb0/ch-03%20stack%20and%20queue/maze-path/maze_path.cpp#L275)
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
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/9418349b2c18d6c7ca961db596d942d1e988cbb0/ch-03%20stack%20and%20queue/evaluate-expression/evaluate_expression.cpp#L179)
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
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/9418349b2c18d6c7ca961db596d942d1e988cbb0/ch-03%20stack%20and%20queue/hanio/hanoi.cpp#L17)
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
ch-05 array and generalized-table
============
array ADT
===========
#### [实现](https://github.com/Tim-xiaofan/Data_struct/blob/820600a3289c6c146573da9cbd9caf0b17875d90/ch-05%20array%20and%20generalized-table/array-adt/array.h#L12)
```C++
template<typename T, int dim = 1>
class array
{
	private:
		enum{MAX_DIM = 8};
		T * _base;
		int *_bounds, *_constant, _elemtot;
	private:
		bool construct(int b1 , va_list & ap);
		/** Map n-dimensional to one-dimensional*/
		bool locate(va_list & ap, int & off)const;
	public:
		array():_base(nullptr),_bounds(nullptr),_constant(nullptr),_elemtot(0){}
		~array(){delete [] _base; delete[]_constant; delete[]_bounds;}
		static array * instance(int b1, ...);
		/** get value at (i, j, ...)*/
		bool value(T & t, ...) const;
		/** set value at (i, j, ...)*/
		bool set_value(const T & t, ...);
		void show_constant(void)const;
		void show_bounds(void)const;
		/** get dimensin length*/
		int get_bound(int mdim)const;
		/** initialize values from ts*/
		array & set_values(T * ts, int n);
};
```
symmetric-matrix ADT
===========
#### [实现](https://github.com/Tim-xiaofan/Data_struct/blob/820600a3289c6c146573da9cbd9caf0b17875d90/ch-05%20array%20and%20generalized-table/symmetric-matrix-adt/symmetric_matrix.h#L10)
```C++
template<typename Item>
class symmetric_matrix
{
	private:
		Item * _base;
		int _size, _n;
		/** Map two-dimensional to one-dimensional*/
		static int map(int i, int j);
	public:
		~symmetric_matrix(){delete [] _base;}
		symmetric_matrix(int n){_size = (n + 1) *n / 2; _base = new Item[_size];  _n = n;}
		/** get value at (i, j, ...)*/
		Item & at(int i, int j){return _base[map(i, j)]; }
		const Item & at(int i, int j) const{return _base[map(i, j)];}
		void set_values(const Item * is, int ct);
		void show(void)const;
};
```
triangular-matrix ADT
===========
#### [实现](https://github.com/Tim-xiaofan/Data_struct/blob/820600a3289c6c146573da9cbd9caf0b17875d90/ch-05%20array%20and%20generalized-table/triangular-matrix-adt/triangular_matrix.h#L10)
```C++
template<typename Item>
class triangular_matrix
{
	private:
		Item * _base, _c;
		int _size, _n, _type;
		int map(int i, int j) const;
	public:
		enum{UP = 0, DOWN = 1};
		~triangular_matrix(){delete [] _base;}
		triangular_matrix(int n, int type = DOWN, const Item & c = 0);
		Item & at(int i, int j);
		/** get value at (i, j)*/
		const Item & at(int i, int j) const;
		void set_values(const Item * is, int ct);
		void show(void)const;
		int type(void)const{return type;}
		bool type(int new_type);
};
```
sparse-matrix ADT
===========
#### [实现一](https://github.com/Tim-xiaofan/Data_struct/blob/820600a3289c6c146573da9cbd9caf0b17875d90/ch-05%20array%20and%20generalized-table/sparse-matrix-adt/sparse_matrix.h#L32)
```C++
template<typename T>/** value type*/
class sparse_matrix : public SqList<triple<T>>
{
	private:
		typedef SqList<triple<T>> base;
	protected:
		typedef triple<T> item;
	private:
		enum {MAX_SIZE = 12500};
		int _m, _n, _tu;/** rows, cols and non-zero elements count*/
	public:
		sparse_matrix(const array<T, 2> & a2, int tu);
		sparse_matrix(int m, int n, int tu)
			:base(tu), _m(m), _n(n), _tu(tu){}
		int tu(void)const{return _tu;}
		static int count_tu(const array<T, 2> & a2);
		void show(void)const;
		/** matrix transpose algorithm*/
		bool transpose(sparse_matrix & N)const;
		bool transposex(sparse_matrix & N)const;
		item & operator[](int pos){return base::operator[](pos);} 
		const item & operator[](int pos)const{return base::operator[](pos);} 
		/** get number of non-zero elements in each column*/
		int get_num(int * num)const;
		/** get postion first non-zero elements in each column*/
		int get_cpot(int * cpot, const int * num)const;
		/** get matrix's rows*/
		int rows(void)const{return _m;}
		int cols(void)const{return _n;}
};
```
#### [实现二 行逻辑](https://github.com/Tim-xiaofan/Data_struct/blob/820600a3289c6c146573da9cbd9caf0b17875d90/ch-05%20array%20and%20generalized-table/sparse-matrix-adt/rlsparse_matrix.h#L13)
```C++
template<typename T>/** value type*/
class rlsparse_matrix : public sparse_matrix<T>
{
	private:
		typedef sparse_matrix<T> base;
		typedef typename base::item item;
	public:
		typedef T value_type;
	private:
		int * _rpos;
	public:
		~rlsparse_matrix(){delete [] _rpos;};
		rlsparse_matrix(const array<T, 2> & a2, int tu);
		/** FIXME: need to handle new exception*/
		rlsparse_matrix(int m, int n, int tu):base(m, n, tu){_rpos = new int[m];}
		void show_rpos(void)const;
		/** get the position of the row's first element*/
		int row_first(int row)const{return _rpos[row];
		/** get (the position of the row's one last element +1)*/
		int row_last(int row)const;
};
```
transpose one
===========
##### 算法描述（书）
按照 b.data中三元组的次序依次在 a.data 中找到相应的三元组进行转置。换句话说，按照矩阵 M 的列序来进行转置。为了找到 M 的每—列中所有的非零元素，需要对其三元组表 a.data 从第—行起整个扫描—遍，由于a.data是以M的行序为主序来存放每个非零元的，由此得到的恰是 b.data 应有的顺序。<br>
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/bcfcc4aea617872ce3e08018d65ee4d824dd2450/ch-05%20array%20and%20generalized-table/sparse-matrix-adt/sparse_matrix.h#L115)
```c++
/** M(m x n) --> N(n x m)
  * time:O(M.nu * tu)
 **/
template<typename T>
bool sparse_matrix<T>:: 
transpose(sparse_matrix & N)const
{
	/** TODO: to suport that target matrix is matrix self*/
	if(N._m != _n || N._n != _m || N._tu < _tu || &N == this)
	  return false;

	/** get a col in M*/
	int col, pos, pos1 = 0;
	for(col = 0; col < _n; ++col)
	  for(pos = 0; pos < _tu; ++pos)
		if(base::operator[](pos).j == col)
		{
			N[pos1].i = base::operator[](pos).j;
			N[pos1].j = base::operator[](pos).i;
			N[pos1].e = base::operator[](pos).e;
			++pos1;
		}
	return true;
}
```
transpose two
===========
##### 算法描述（书）
按照 a.data 中三元组的次序进行转置，并将转置后的三元组置入b中恰当的位置。如果能预先确定矩阵M中每一列（即T中每一行）的第一个非零元在b.data 中应有的位置，那么在对a.data中的三元组依次作转置时，便可直接放到 b.data 中恰当的位置上去。为了确定这些位置，在转置前，应先求得M的每一列中非零元的个数，进而求得每一列的第一个非零元在b.data中应有的位置。<br>
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/bcfcc4aea617872ce3e08018d65ee4d824dd2450/ch-05%20array%20and%20generalized-table/sparse-matrix-adt/sparse_matrix.h#L140)
```c++
/** M(m x n) --> N(n x m)
  * time:O(2 * n + tu)
 **/
template<typename T>
bool sparse_matrix<T>:: 
transposex(sparse_matrix & N)const
{
	/** TODO: to suport that target matrix is matrix self*/
	if(N._m != _n || N._n != _m || N._tu < _tu || &N == this)
	{
		std::cerr << "invalid target matrix\n";
		return false;
	}

	/** FIXME: need to catch the exception of new operator*/
	int *num = new int[_n], *cpot = new int[_n];
	if(get_num(num) == -1 || get_cpot(cpot, num) == -1)
	{
		std::cerr << "cannot get num or cpot\n";
		return false;
	}

	int pos, pos1, col;
	for(pos = 0; pos < _tu; ++pos)
	{
		col = base::operator[](pos).j;
		pos1 = cpot[col];
		N[pos1].i = base::operator[](pos).j; 
		N[pos1].j = base::operator[](pos).i; 
		N[pos1].e = base::operator[](pos).e;
		cpot[col]+=1;
	}
	delete num;
	delete cpot;
	return true;
}
```
multi-smatrix
===========
##### 算法描述（书）
稀疏矩阵相乘的基本操作是∶对于M中每个元素 M.data[p]（p=1，2，…，M. tu），找到N中所有满足条件 M.data[p].j=N.data[q].i的元素 N.data[q]，求得M.data[p].v和N.data[q].v的乘积，而从式（5-6）得知，乘积矩阵Q中每个元素的值是个累计和，这个乘积M.data[p].v×N.data[q].v只是Q[i][j]中的一部分。为便于操作，应对每个元素设一累计和的变量，其初值为零，然后扫描数组M，求得相应元素的乘积并累加到适当的求累计和的变量上。
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/820600a3289c6c146573da9cbd9caf0b17875d90/ch-05%20array%20and%20generalized-table/multi-smatrix/multi_smatrix.cpp#L84)
```c++
/** time: O(m1 * n2 + tu1 * tu2 / m2)*/
template<typename SMatrix, typename Array>
bool muti_smatrix(const SMatrix & M, const SMatrix & N, Array & a2)
{
	int m1, n1, m2, n2, mrow, nrow, *ctemp;
	m1 = M.rows();
	n1 = M.cols();
	m2 = N.rows();
	n2 = N.cols();

	if(n1 != m2)
	  return false;
	if(M.tu() * N.tu() == 0)
	  return true;

	ctemp = new int[n2];
	for(mrow = 0; mrow < m1; ++mrow)
	{
		int mfirst, mlast, nfirst, nlast, mpos, npos, ccol;

		/** initialize ctemp*/
		for(ccol = 0; ccol < n2; ++ccol)
		  ctemp[ccol] = 0;
		mfirst = M.row_first(mrow);
		mlast = M.row_last(mrow);
		std::cout << "-----------start-----------\n";
		for(mpos = mfirst; mpos < mlast; ++mpos)
		{
			nrow = M[mpos].j;/** get row of corresponding in N*/
			nfirst = N.row_first(nrow);
			nlast = N.row_last(nrow);
			//std::cout << "N : [" << nfirst << ", "<< nlast << ")\n";
			for(npos = nfirst; npos < nlast; ++npos)
			{
				std::cout << "{" << M[mpos] << " * " << N[npos] << "} "; 
				ctemp[N[npos].j]+= M[mpos].e * N[npos].e;
			}
			std::cout << "\n";
		}/** get non-zero elemets of Q's mrow-th row*/
		for(ccol = 0; ccol < n2; ++ccol)
		{
			//std::cout << triple<int>(mrow, ccol, ctemp[ccol]) << " ";
			a2.set_value(ctemp[ccol], mrow, ccol);
		}
		a2_show(a2);
		std::cout << "\n-----------end-----------\n\n";
	}
	delete [] ctemp;
	return true;
}
```
ch-06 tree and binary-tree
============
bit tree
===========
preinorder construct
===========
##### 算法描述（网络）
先序-中序构造二叉树：<br>
[构造二叉树](https://lucifer.ren/blog/2020/02/08/%E6%9E%84%E9%80%A0%E4%BA%8C%E5%8F%89%E6%A0%91%E4%B8%93%E9%A2%98/)
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/6f40d2758ab7a0647d3de67c238eed47be453633/ch-06%20tree%20and%20binary-tree/bitree/bitree.h#L141)
```c++
template<typename Data>
bool bitree<Data>:: 
preinorder_construct(node * & root, const Data * pre, const Data *in, int ct)
{
	if(pre == nullptr || in == nullptr || ct <= 0)
	  return true;

	//cout << "pre:";
	//show_ds(pre, ct);
	//cout << "in:";
	//show_ds(in, ct);
	/** create root*/
	if(root == nullptr) root = new node;
	root->data = pre[0]; 
	//cout << "root data = " << root->data << endl;

	/** look left and right in inorder*/
	int lct = 0, rct = 0, root_pos;
	for(root_pos = 0; root_pos < ct; ++root_pos)
	  if(in[root_pos] == root->data)
		break;
	lct = root_pos;
	rct = ct - lct - 1;
	//cout << "lct = " << lct << endl;
	//cout << "rct = " << rct << endl;

	/** create lchild*/
	preinorder_construct(root->lchild, &pre[1], in, lct);
	/** create rchild*/
	preinorder_construct(root->rchild, &pre[1 + lct], &in[lct + 1], rct);
	return true;
}
```
inorder traversex
===========
##### 算法描述(书）
中序-非递归遍历二叉树：<br>
1)当前节点非空，入栈，并更新当前节点为其左子树（根节点）。<br>
2)当前节点为空，出栈并访问。<br>
3)重复（1）（2）直到P为NULL并且栈为空, 则遍历结束。<br>
##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/3f7bd1d03ec2b59dfda17c85b53f7f649fb32117/ch-06%20tree%20and%20binary-tree/bitree/bitree.h#L184)
```c++
/** root second, not recursion*/
template<typename Data>
template<typename UnaryOperator>
void bitree<Data>::
inorder_traversex(node *root, const UnaryOperator & op)
{
	sqstack<node *> stack(32);
	node * pn = root;
	while(!stack.is_empty() || pn)
	{
		if(pn)
		{
			stack.push(pn);
			pn = pn->lchild;
		}
		else
		{
			stack.pop(pn);
			op(pn->data);
			pn = pn->rchild;
		}
	}
}
```
bit thread tree
===========
in threading
===========
##### 算法描述（书）
线索换二叉树（二叉树已建立）：<br>
（1）根据中序遍历的规律可知，结点的后继应是遍历其右子树时访问的第一个结点，即右子树中最左下的结点。<br>
（2）那么，又如何进行二叉树的线索化呢?由于线索化的实质是将二叉链表中的空指针改为指向前驱或后继的线索.而前驱或后维的信息只有在遍历时才能得到，因此线索化的过程即为在遍历的过程中修改空指针的过程。<br>
 (3)为了记下遍历过程中访向结点的先后关系，附设一个指针pre始终指向刚刚访问过的结点，若指针p指向当前访问的结点，则指向它的前驱.<br>
 (4)为方便起见，仿照线性表的存储结构，在二叉树的线索链表上也添加一个头结点，并令其lchild域的指针指向二叉树的根结点，其rchild 域的指针指向中序遍历时访问的最后一个结点;反之，令二叉树中序序列中的第一个结点的lchild域指针和最后—个结点rchild域的指针均指向头结点<br>
 ![](https://github.com/Tim-xiaofan/Data_struct/blob/684ec0dcf12005242a8fd92e10066331b2560f80/image/%E4%B8%AD%E5%BA%8F-%E7%BA%BF%E7%B4%A2%E5%8C%96%E4%BA%8C%E5%8F%89%E6%A0%91.PNG) 
##### 结点结构
|lchild| ltag | data | rtag | rchild|
|-----|------|------|------|-----

ltag ：0--lchild域指示结点的左孩子； 1--lchild-域指示结点的前驱<br>
rtag ：0--rchild域指示结点的右孩子； 1--rchild-域指示结点的后继<br>
#### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/3f7bd1d03ec2b59dfda17c85b53f7f649fb32117/ch-06%20tree%20and%20binary-tree/bithrtree/bithrtree.h#L228)
```c++
template<typename Data>
void bithrtree<Data>::in_threading(node * & pre, node * p)
{
	if(p)
	{
		in_threading(pre, p->lchild);/** threading left child*/

		/** set empty pointer*/
		if(!p->lchild)
		{
			p->ltag = THREAD;
			p->lchild = pre; /** precursor:last node in left child*/
		}
		if(!pre->rchild)
		{
			pre->rtag = THREAD;
			pre->rchild = p;/** successor*/
		}

		/** update pre*/
		pre = p;
		in_threading(pre, p->rchild);/** threading right child*/
	}
}
```
inorder thrtraverse
===========
##### 算法描述（书）

##### [c++实现（未OJ）](https://github.com/Tim-xiaofan/Data_struct/blob/3f7bd1d03ec2b59dfda17c85b53f7f649fb32117/ch-06%20tree%20and%20binary-tree/bithrtree/bithrtree.h#L323)
```c++
template <typename Data>
template<typename UnaryOperator>
void bithrtree<Data>::
inorder_thrtraverse(const UnaryOperator & op)
{
	node * p = _thrt->lchild;//pointer to root node
	while(p != _thrt)
	{
		while(p->ltag == LINK)
		{
#ifdef DEBUG
			cout << "(" << p << " : " << *p << ")";
#endif
			p = p->lchild;
		}
		op(p->data);
		while(p->rtag == THREAD && p->rchild != _thrt)
		{
#ifdef DEBUG
			cout << "(" << p << " : " << *p << ")";
#endif
			p = p->rchild;
			op(p->data);
		}
		p = p->rchild;
	}
	cout << endl;
}
```
