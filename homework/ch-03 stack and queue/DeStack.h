#ifndef _DESTACK_H_
#define _DESTACK_H_

namespace HOMEWORK_NS
{
	template<typename T>
	struct DeStack
	{
		int top[2];
		int bot[2];		//栈顶和栈底指针
		T *data;			//栈数组
		int m;			//栈最大可容纳元素个数
	};

	template<typename T>
	void init(DeStack<T>& s, int m)
	{
		s.top[0] = -1;
		s.top[1] = m;
		s.m = m;
		s.data = new T[m];
	}

	template<typename T>
	bool full(const DeStack<T>& s)
	{
		return s.top[0] + 1 == s.top[1];
	}

	template<typename T>
	bool empty(const DeStack<T>& s) 
	{
		return s.top[0] == -1 && s.top[1] == s.m;
	}

	template<typename T>
	int size(const DeStack<T>& s)
	{
		return s.top[0] + 1 + s.m-s.top[1];
	}

	template<typename T>
	bool pushLeft(DeStack<T>& s, const T& e)
	{
		if(!full(s))
		{
			s.data[++s.top[0]] = e;
			return true;
		}
		return false;
	}

	template<typename T>
	bool popLeft(DeStack<T>& s, T& e)
	{
		if(s.top[0] > -1)
		{
			e = s.data[s.top[0]--];
			return true;
		}
		return false;
	}

	template<typename T>
	bool pushRight(DeStack<T>& s, const T& e)
	{
		if(!full(s))
		{
			s.data[--s.top[1]] = e;
			return true;
		}
		return false;
	}

	template<typename T>
	bool popRight(DeStack<T>& s, T& e)
	{
		if(s.top[1] < s.m)
		{
			e = s.data[s.top[1]++];
			return true;
		}
		return false;
	}
}

#endif
