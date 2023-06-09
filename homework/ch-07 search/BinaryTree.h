#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

template<typename T>
struct BinaryTreeNode;

template<typename T>
using BinaryTree = std::shared_ptr<BinaryTreeNode<T>>;

template<typename T>
struct BinaryTreeNode
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
