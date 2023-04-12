#ifndef _DERINGQUEUE_H_
#define _DERINGQUEUE_H_

namespace HOMEWORK_NS
{

template<typename T>
class DeRingQueue
{
	public:
		DeRingQueue(int n);
		bool empty() const; 
		bool full() const; 
		bool backEnqueue(const T& e);
		bool frontEnqueue(const T& e);
		bool frontDequeue(T& e);
		bool backDequeue(T& e);
		int size() const;
		int front() const { return front_; }
		int rear() const { return rear_; }

	private:
		int front_;
		int rear_;
		int capacity_;
		T* data_;
};

template<typename T>
DeRingQueue<T>::DeRingQueue(int n)
		:front_(0),
		rear_(0),
		capacity_(n + 1)
{
	data_ = new T[capacity_];
}

template<typename T>
bool DeRingQueue<T>::empty(void) const
{
	return front_ == rear_;
}

template<typename T>
bool DeRingQueue<T>::full(void) const
{
	return (rear_ + 1) % capacity_ == front_;
}

template<typename T>
bool DeRingQueue<T>::backEnqueue(const T& e)
{
	if(!full())
	{
		data_[rear_] = e; 
		rear_ = (rear_ + 1) % capacity_;
		return true;
	}
	return false;
}

template<typename T>
bool DeRingQueue<T>::frontEnqueue(const T& e)
{
	if(!full())
	{
		//注意 ：c++中 -1 % 10 = 1
		front_ = (front_ - 1 + capacity_) % capacity_;
		data_[front_] = e; 
		return true;
	}
	return false;
}

template<typename T>
bool DeRingQueue<T>::frontDequeue(T& e)
{
	if(!empty())
	{
		e = data_[front_];
		front_ = (front_ + 1) % capacity_;
		return true;
	}
	return false;
}

template<typename T>
bool DeRingQueue<T>::backDequeue(T& e)
{
	if(!empty())
	{
		rear_ = (rear_ - 1 + capacity_) % capacity_;
		e = data_[rear_];
		return true;
	}
	return false;
}

template<typename T>
int DeRingQueue<T>::size() const
{
	return (rear_ - front_ + capacity_) % capacity_;
}

}

#endif
