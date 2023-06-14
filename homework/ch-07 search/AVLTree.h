#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <utility>
#include <stdexcept>

enum{LH=1, EH=0, RH=-1};

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

	AVLTreeNode(const T& d, int f=0):
		data(d),
		factor(f),
		lchild(nullptr),
		rchild(nullptr)
	{}

	AVLTree addLchild(const T& d, int f=0)
	{
		assert(!lchild);
		lchild = new AVLTreeNode(d, f);
		return lchild;
	}

	AVLTree addRchild(const T& d, int f=0)
	{
		assert(!rchild);
		rchild = new AVLTreeNode(d, f);
		return rchild;
	}

	bool same(const AVLTree other) const
	{
		if(data != other->data && factor == other->factor) return false;
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
		std::cout << "|_<" << data << "," << factor <<  ">\n";
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

template<typename T>
void leftBalance(AVLTree<T>& A)
{
	AVLTree<T>& B = A->lchild;
	AVLTree<T>& C = B->rchild;
	switch(B->factor)
	{
		case LH: //LL
			A->factor = EH;
			B->factor = EH;
			rightRotate(A);
			break;

		case RH: //LR
			switch (C->factor)
			{
				case LH:
					A->factor = RH;
					B->factor = EH;
					break;
				case EH:
					A->factor = EH;
					B->factor = EH;
					break;
				case RH:
					A->factor = EH;
					B->factor = LH;
					break;
			}
			C->factor = EH;
			leftRotate(B);
			rightRotate(A);
			break;

		default:
			throw std::logic_error("Must be LL or LR");
			break;
	}
}

template<typename T>
void rightBalance(AVLTree<T>& A)
{
	AVLTree<T>& B = A->rchild;
	AVLTree<T>& C = B->lchild;
	switch(B->factor)
	{
		case RH: //RR
			A->factor = EH;
			B->factor = EH;
			leftRotate(A);
			break;

		case LH: //RL
			switch (C->factor)
			{
				case LH:
					A->factor = EH;
					B->factor = RH;
					break;
				case EH:
					A->factor = EH;
					B->factor = EH;
					break;
				case RH:
					A->factor = LH;
					B->factor = EH;
					break;
			}
			C->factor = EH;
			rightRotate(B);
			leftRotate(A);
			break;

		default:
			throw std::logic_error("Must be RR or RL");
			break;
	}
}

template<typename T>
bool insert(AVLTree<T>& A, const T& value, bool& taller)
{
	if(!A)
	{
		A = new AVLTreeNode<T>(value, EH);
		taller = true;
		return true;
	}
	
	taller = false;
	if(value < A->data)
	{
		if(!insert(A->lchild, value, taller)) return false;
		if(taller)
		{
			switch(A->factor)
			{
				case LH:
					leftBalance(A);
					taller = false;
					break;
				case EH:
					A->factor = LH;
					taller = true;
					break;
				case RH:
					A->factor = EH;
					taller = false;
					break;
			}
		}
		return true;
	}
	else if(value > A->data)
	{
		if(!insert(A->rchild, value, taller)) return false;
		if(taller)
		{
			switch(A->factor)
			{
				case RH:
					rightBalance(A);
					taller = false;
					break;
				case EH:
					A->factor = RH;
					taller = true;
					break;
				case LH:
					A->factor = EH;
					taller = false;
					break;
			}
		}
		return true;
	}
	return false;
}

#endif
