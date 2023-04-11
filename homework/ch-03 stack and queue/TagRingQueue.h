#ifndef _TAGRINGQUEUE_H_
#define _TAGRINGQUEUE_H_

namespace HOMEWORK_NS
{

template<typename T>
class TagRingQueue
{
	public:
		TagRingQueue(int n);
		bool empty() const; 
		bool full() const; 
		bool enqueue(const T& e);
		bool dequeue(T& e);
		int size() const;
		int front() const { return front_; }
		int rear() const { return rear_; }
		int tag() const {return tag_; }

	private:
		int front_;
		int rear_;
		int tag_;
		int capacity_;
		T* data_;
};

template<typename T>
TagRingQueue<T>::TagRingQueue(int n)
		:front_(0),
		rear_(0),
		tag_(0),
		capacity_(n)
{
	data_ = new T[n];
}

template<typename T>
bool TagRingQueue<T>::empty(void) const
{
	return tag_ == 0 && front_ == rear_;
}

template<typename T>
bool TagRingQueue<T>::full(void) const
{
	return tag_ == 1 && front_ == rear_;
}

template<typename T>
bool TagRingQueue<T>::enqueue(const T& e)
{
	if(!full())
	{
		data_[rear_] = e; 
		rear_ = (rear_ + 1) % capacity_;
		if(!tag_) tag_ = 1;
		return true;
	}
	return false;
}

template<typename T>
bool TagRingQueue<T>::dequeue(T& e)
{
	if(!empty())
	{
		e = data_[front_];
		front_ = (front_ + 1) % capacity_;
		if(rear_ == front_) tag_ = 0;
		return true;
	}
	return false;
}

template<typename T>
int TagRingQueue<T>::size() const
{
	if(empty())
	{
		return 0;
	}
	else if(full())
	{
		return capacity_;
	}
	else
	{
		return (rear_ - front_ + capacity_) % capacity_;
	}
}

}

#endif
