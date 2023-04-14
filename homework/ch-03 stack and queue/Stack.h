#ifndef _STACK_H_
#define _STACK_H_
#include <cstddef>
namespace HOMEWORK_NS
{

template<typename T>
class Stack
{
	public:
		Stack(size_t capacity);
		~Stack() { delete [] data_; }
		bool pop(T& e);
		bool push(const T& e);
		size_t size(void) const { return top_; };
		bool empty(void) const { return top_ == 0 ;}
		bool full(void) const { return top_ == capacity_; }
		T& top() { return data_[top - 1]; }
		const T& top() const { return data_[top - 1]; }
	private:
		size_t top_;
		size_t capacity_;
		T* data_;
};

template<typename T>
Stack<T>::Stack(size_t capacity)
		:top_(0),
		capacity_(capacity)
{
	data_ = new T[capacity];
}

template<typename T>
bool Stack<T>::pop(T& e)
{
	if(!empty())
	{
		e = data_[--top_];
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Stack<T>::push(const T& e)
{
	if(!full())
	{
		data_[top_++] = e;
		return true;
	}
	else
	{
		return false;
	}
}

}

#endif
