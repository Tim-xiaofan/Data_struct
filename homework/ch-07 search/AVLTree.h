#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <utility>


template<typename T>
struct AVLTreeNode
{
	using AVLTree = AVLTreeNode*;
	T data;
	int factor;
	AVLTree lchild;
	AVLTree rchild;


	AVLTreeNode():
		factor(0),
		lchild(nullptr),
		rchild(nullptr)
	{}

	AVLTreeNode(const T& d):
		data(d),
		factor(0),
		lchild(nullptr),
		rchild(nullptr)
	{}

	AVLTree addLchild(const T& d)
	{
		assert(!lchild);
		lchild = new AVLTreeNode(d);
		return lchild;
	}

	AVLTree addRchild(const T& d)
	{
		assert(!rchild);
		rchild = new AVLTreeNode(d);
		return rchild;
	}

	bool same(const AVLTree other) const
	{
		if(other->data != other->data) return false;
		if((lchild == nullptr) != (other->lchild == nullptr)) return false; 
		if((rchild == nullptr) != (other->rchild == nullptr)) return false; 

		if(lchild && other->lchild)
		{
			if(!lchild->same(other->lchild)) return false;
		}
		if(rchild && other->rchild)
		{
			return rchild->same(other->rchild);
		}
		else
		{
			return true;
		}
	}

	bool search(const T& value) const
	{//O(log(height))
		if(data == value) return true;
		if(value < data)
		{
			if(lchild)
			{
				if(lchild->search(value)) return true;
			}
		}
		else
		{
			if(rchild)
			{
				if(rchild->search(value)) return true;
			}
		}
		return false;
	}

	void display(int level = 0) const
	{
		for (int i = 0; i < level; ++i) {
			std::cout << "   ";
		}
		std::cout << "|_" << data << std::endl;
		if (lchild) {
			lchild->display(level + 1);
		}
		if (rchild) {
			rchild->display(level + 1);
		}
	}

	
};


template<typename T>
using AVLTree = AVLTreeNode<T>*;

template<typename T>
void rightRotate(AVLTree<T>& B)
{
	AVLTree<T> C = B->lchild; 
	B->lchild =  C->rchild;
	C->rchild = B;
	B = C;
}

template<typename T>
void leftRotate(AVLTree<T>& B)
{
	AVLTree<T> C = B->rchild;
	B->rchild = C->lchild;
	C->lchild = B;
	B = C;
}

#endif
