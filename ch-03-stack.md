### ch-03 栈
![](./image/mind/03%E6%A0%88%E8%84%91%E5%9B%BE.png)
```c
struct s_stack
{//顺序栈
     elem_t * base;
     elem_t * top;
     int size;
};
typedef struct s_stack stack;
```
#### 1. 进栈
```c
*s.top = e;
s.top++;
```
#### 2. 出栈
```c
--s.top;
e = *s.top;
```
#### 3. 括号匹配
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
		if(is_right(cur)) // 右括号:消除
		{/** check if matches top one*/
			stack.pop(top);
			if(top != get_left(cur))/** not matched*/
			  return false; 
		}
		else/** 左括号:just push into stcak*/
		  stack.push(cur);
	}
	return stack.is_empty();
}
```
#### 4. 进制转换
```c++
template <typename T>//must be  an integer
std::string base_conversion<T>::
conversion(T t) const
{//短除法
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
		stack.push(elements[remainder]);//余数入栈
		t = quotient;
	}
	int len = stack.length();
	for(i = 0; i < len; i++)
	{
		stack.pop(ch);
		result.push_back(ch);
	}
	return result;
}
```

#### 5. 卡特兰数-栈的出栈序列
$$N = C^{n}_{2n} - C^{n-1}_{2n} = \frac{1}{n + 1}C^{n}_{2n}$$