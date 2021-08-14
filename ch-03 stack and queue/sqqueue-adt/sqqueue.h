/** 20210405 18:38, zyj, GuangDong*/
#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include <iostream>
#include "SqList.h"

template <typename Item>
class sqqueue : private SqList<Item>
{
	private:
		typedef SqList<Item> base;
	private:
		enum{MAX_SIZE = 128};
		int _front, _rear, _size;
	public:
		sqqueue(int size = MAX_SIZE)
			:base(size),_front(0),_rear(0),_size(size){}
		/** status*/
		bool is_full(void)const{return _front == (_rear + 1) % _size;}
		bool is_empty(void)const{return _rear == _front;}
		int length(void)const{return (_rear - _front + _size) % _size;}
		int size(void)const{return _size;}
		/** operator*/
		bool enqueue(const Item & i);
		bool dequeue(Item & i);
		bool first(Item & i)const{i = base::operator[](_front); return true;}
		void show(void)const;
};

template<typename Item>
bool sqqueue<Item>::
enqueue(const Item & i)
{
	if(is_full()) 
	{
		//std::cout << "enqueue: is full\n";
		return false;
	}

	base::operator[](_rear) = i;
	//std::cout << "enqueue " << i << " at " << _rear << std::endl;
	_rear = (_rear + 1) % _size;
	//std::cout << "_front = " << _front << ", _rear = " << _rear << std::endl;
	return true;
}

template<typename Item>
bool sqqueue<Item>::
dequeue(Item & i)
{
	if(is_empty()) return false;

	i = base::operator[](_front);
	_front = (_front + 1) % _size;
	return true;
}

template<typename Item>
void sqqueue<Item>::
show(void)const
{
	int i;
	for(i = _front; i != _rear; i = (i+1)%_size)
	  std::cout << base::operator[](i) << " ";
	std::cout << "\n";
}
#endif
