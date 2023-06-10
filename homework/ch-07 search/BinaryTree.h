#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <utility>

template<typename T>
struct BinaryTreeNode;

template<typename T>
using BinaryTree = std::shared_ptr<BinaryTreeNode<T>>;

template<typename T>
struct BinaryTreeNode : public std::enable_shared_from_this<BinaryTreeNode<T>>
{
	T data;
	std::shared_ptr<struct BinaryTreeNode> lchild;
	std::shared_ptr<struct BinaryTreeNode> rchild;
	BinaryTreeNode():
		lchild(nullptr),
		rchild(nullptr)
	{}

	BinaryTreeNode(const T& d):
		data(d),
		lchild(nullptr),
		rchild(nullptr)
	{}

	void addLchild(const T& d)
	{
		assert(!lchild);
		lchild = std::make_shared<BinaryTreeNode>(d);
	}

	void addRchild(const T& d)
	{
		assert(!rchild);
		rchild = std::make_shared<BinaryTreeNode>(d);
	}

	bool same(const BinaryTreeNode& other) const
	{
		if(other.data != other.data) return false;
		if((lchild == nullptr) != (other.lchild == nullptr)) return false; 
		if((rchild == nullptr) != (other.rchild == nullptr)) return false; 

		if(lchild && other.lchild)
		{
			if(!lchild->same(*other.lchild)) return false;
		}
		if(rchild && other.rchild)
		{
			return rchild->same(*other.rchild);
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

	//search in Binary Sort Tree
	std::pair<bool, std::shared_ptr<BinaryTreeNode<T>>> search(const T& value, const std::shared_ptr<BinaryTreeNode<T>>& f)
	{
		if(value == data)
		{
			return std::make_pair(true, this->shared_from_this());
		}
		else if(value < data && lchild)
		{
			return lchild->search(value, this->shared_from_this());
		}
		else if(value > data && rchild)
		{
			return rchild->search(value, this->shared_from_this());
		}
		return std::make_pair(false, this->shared_from_this());
	}

	//insert into Binary Sort Tree if it doese not exist
	std::pair<bool, BinaryTree<T>> insert(const T& value)
	{
		auto ret = search(value, nullptr);
		if(!ret.first)
		{
			if(value > ret.second->data)
			{
				ret.second->addRchild(value);
				return {true, ret.second->rchild};
			}
			else
			{
				ret.second->addLchild(value);
				return {true, ret.second->lchild};
			}
		}
		else
		{
			ret.first = false;
			return ret;
		}
	}
	
	void delete_(BinaryTree<T>& p)
	{
		if(!p->lchild && !p->rchild) //leaf node
		{
			p.reset();
		}
		else if(!p->rchild) // only left child
		{
			BinaryTree<T> q = p->lchild;
			p->data = q->data;
			p->lchild = q->lchild;
			p->rchild = q->rchild;
			q.reset();
		}
		else if(!p->lchild) // only right child
		{
			BinaryTree<T> q = p->rchild;
			p->data = q->data;
			p->lchild = q->lchild;
			p->rchild = q->rchild;
			q.reset();
		}
		else
		{
			//find predecessor of p
			BinaryTree<T> q = p;
			BinaryTree<T> s = p->lchild;
			while(s->rchild)
			{
				q = s;
				s = s->rchild;
			}
			//replace p with s
			p->data = s->data;
			if(q != p)
			{
				q->rchild = s->lchild;
			}
			else
			{
				q->lchild = s->lchild;
			}
			//delete s;
			s.reset();
		}
	}

	// delete if it exists
	bool delete_(const T& value)
	{
		auto ret = search(value, nullptr);
		if(!ret.first) return false;// not found

		delete_(ret.second);
		return true;
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



#endif
