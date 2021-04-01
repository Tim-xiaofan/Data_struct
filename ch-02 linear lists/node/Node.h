/* 20210329 20:13, zyj, GuangDong*/
//DuList.h
#include <iostream>
#include <iterator>
#ifndef NODE_H
#define NODE_H

template <typename Item>
class Node
{
	public:
		typedef Item item_type;
		Item _i;
		Node *_next;
	public:
		Node():_next(nullptr){}
		explicit Node(const Item &i):_i(i), _next(nullptr){}
		Node(const Node &nd):_i(nd._i), _next(nd._next){}
		Node & operator=(const Node & node) = default;
		~Node(){};/** no new, so no delete*/
};


template <typename Item>
class DuNode
{
	public:
		typedef Item item_type;
		Item _i;
		DuNode *_next, *_prior;
	public:
		DuNode(): _i(), _next(nullptr), _prior(nullptr){}
		explicit DuNode(const Item &i): _i(i), _next(nullptr), _prior(nullptr){}
		DuNode(const DuNode &nd):_i(nd._i), _next(nd._next), _prior(nd._prior){}
		DuNode & operator=(const DuNode & nd) = default;
		~DuNode(){};/** no new, so no delete*/
};

#endif
