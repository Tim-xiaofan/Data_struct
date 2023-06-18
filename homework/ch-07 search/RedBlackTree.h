#ifndef _REDBLACKTREE_H_
#define _REDBLACKTREE_H_

#include <utility>
#include <cassert>
#include <iostream>

template<typename T> class RedBlackTreeNode;
template<typename T> class RedBlackTree;

template<typename T>
using RedBlackTreeNodePtr = struct RedBlackTreeNode<T>*;

enum Color {RED, BLACK};

template<typename T>
struct RedBlackTreeNode
{
	RedBlackTreeNode():
		color(RED),
		parent(nullptr),
		lchild(nullptr),
		rchild(nullptr)
	{}

	RedBlackTreeNode(const T& d, Color c = RED):
		data(d),
		color(c),
		parent(nullptr),
		lchild(nullptr),
		rchild(nullptr)
	{}

	RedBlackTreeNodePtr<T> addLchild(const T& d, Color c = RED)
	{
		assert(!lchild);
		lchild = new RedBlackTreeNode(d, c);
		lchild->parent = this;
		return lchild;
	}

	RedBlackTreeNodePtr<T> addRchild(const T& d, Color c = RED)
	{
		assert(!rchild);
		rchild = new RedBlackTreeNode(d, c);
		rchild->parent = this;
		return rchild;
	}

	bool same(const RedBlackTreeNodePtr<T> other) const
	{
		if(data != other->data && color == other->color) return false;
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

	void display(int level = 0) const
	{
		if(level > 8) return;
		for (int i = 0; i < level; ++i) {
			std::cout << "   ";
		}
		std::cout << "|_<" << data << "," << color <<  ">\n";
		if (lchild) {
			lchild->display(level + 1);
		}
		if (rchild) {
			rchild->display(level + 1);
		}
	}

	T data;
	Color color;
	RedBlackTreeNodePtr<T> parent;
	RedBlackTreeNodePtr<T> lchild;
	RedBlackTreeNodePtr<T> rchild;
};

template<typename T>
class RedBlackTree
{
	public:
		RedBlackTree();

		std::pair<bool, RedBlackTreeNodePtr<T>> insert(const T& value);
		std::pair<bool, RedBlackTreeNodePtr<T>> search(const T& value)
		{
			RedBlackTreeNodePtr<T> f = nullptr;
			return search(root_, value, f);
		}
		bool isRedBlackTree(void) const
		{
			return isRedBlackTree(root_);
		}

		//Only for testing
		void rightRotate(RedBlackTreeNodePtr<T> n);
		void leftRotate(RedBlackTreeNodePtr<T> n);
		RedBlackTreeNodePtr<T>& root()
		{
			return root_;
		}

	private:
		RedBlackTreeNodePtr<T> root_;

		//https://zh.wikipedia.org/zh-cn/%E7%BA%A2%E9%BB%91%E6%A0%91
		void insert_case1(RedBlackTreeNodePtr<T> n);
		void insert_case2(RedBlackTreeNodePtr<T> n);
		void insert_case3(RedBlackTreeNodePtr<T> n);
		void insert_case4(RedBlackTreeNodePtr<T> n);
		void insert_case5(RedBlackTreeNodePtr<T> n);

		static int countBlackNodes(const RedBlackTreeNodePtr<T> t);
		
		static RedBlackTreeNodePtr<T> grandparent(RedBlackTreeNodePtr<T> n)
		{
			return n->parent->parent;
		}

		static RedBlackTreeNodePtr<T> uncle(RedBlackTreeNodePtr<T> n){
			if(n->parent == grandparent(n)->lchild)
			  return grandparent (n)->rchild;
			else
			  return grandparent (n)->lchild;
		}

		static bool isRedBlackTree(const RedBlackTreeNodePtr<T> t);
		static std::pair<bool, RedBlackTreeNodePtr<T>> search(RedBlackTreeNodePtr<T> t, const T& value, RedBlackTreeNodePtr<T> f);
};
	
template<typename T>
RedBlackTree<T>::RedBlackTree()
		:root_(nullptr)
{
}

template<typename T>
std::pair<bool, RedBlackTreeNodePtr<T>> RedBlackTree<T>::insert(const T& value)
{
	if(root_ == nullptr)
	{
		root_ = new RedBlackTreeNode<T>(value);
		insert_case1(root_);
		return {true, root_};
	}
	else
	{
		auto p = search(value);
		if(p.first)
		{// if it exists
			return {false, p.second};
		}
		else
		{
			auto parent = p.second;
			RedBlackTreeNodePtr<T> n = new RedBlackTreeNode<T>(value);
			n->parent = parent;
			assert(parent->data != value);
			if(value < parent->data)
			{
				assert(!parent->lchild);
				parent->lchild = n;
			}
			else
			{
				assert(!parent->rchild);
				parent->rchild = n;
			}
			insert_case1(n);
			return {true, n};
		}
	}
}

template<typename T>
void RedBlackTree<T>::rightRotate(RedBlackTreeNodePtr<T> n)
{
	RedBlackTreeNodePtr<int> parent_ = n->parent;
	if(!parent_)
	{
		return;
	}
	RedBlackTreeNodePtr<int> grandparent_ = grandparent(n);

	parent_->lchild = n->rchild;
	if(n->rchild)
	{
		n->rchild->parent = parent_;
	}
	n->rchild = parent_;
	parent_->parent = n;

	if(parent_ == root_)
	{
		root_ = n;
	}

	if(grandparent_)
	{
		if(grandparent_->lchild == parent_)
		{
			grandparent_->lchild = n;
		}
		else
		{
			grandparent_->rchild = n;
		}
	}
	n->parent = grandparent_;
}

template<typename T>
void RedBlackTree<T>::leftRotate(RedBlackTreeNodePtr<T> n)
{
	RedBlackTreeNodePtr<int> parent_ = n->parent;
	if(!parent_)
	{
		return;
	}
	RedBlackTreeNodePtr<int> grandparent_ = grandparent(n);

	parent_->rchild = n->lchild;
	if(n->lchild)
	{
		n->lchild->parent = parent_;
	}
	n->lchild = parent_;
	parent_->parent = n;

	if(parent_ == root_)
	{
		root_ = n;
	}
	
	if(grandparent_)
	{
		if(grandparent_->lchild == parent_)
		{
			grandparent_->lchild = n;
		}
		else
		{
			grandparent_->rchild = n;
		}
	}
	n->parent = grandparent_;
}

template<typename T>
void RedBlackTree<T>::insert_case1(RedBlackTreeNodePtr<T> n)
{
	if(!n->parent)
	{
		n->color = BLACK;
	}
	else
	{
		insert_case2(n);
	}
}

template<typename T>
void RedBlackTree<T>::insert_case2(RedBlackTreeNodePtr<T> n)
{
	if(n->parent->color == BLACK)
	{
		return;
	}
	else
	{
		insert_case3(n);
	}
}

template<typename T>
void RedBlackTree<T>::insert_case3(RedBlackTreeNodePtr<T> n)
{
	if(uncle(n) && uncle(n)->color == RED)
	{
		n->parent->color = BLACK;
		uncle(n)->color = BLACK;
		grandparent(n)->color = RED;
		insert_case1(grandparent(n));
	}
	else
	{
		insert_case4(n);
	}
}

template<typename T>
void RedBlackTree<T>::insert_case4(RedBlackTreeNodePtr<T> n)
{
	if(n == n->parent->rchild && n->parent == grandparent(n)->lchild)
	{
		leftRotate(n);
		n = n->lchild;
	}
	else if(n == n->parent->lchild && n->parent == grandparent(n)->rchild)
	{
		rightRotate(n);
		n = n->rchild;
	}
	insert_case5(n);
}

template<typename T>
void RedBlackTree<T>::insert_case5(RedBlackTreeNodePtr<T> n)
{
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if(n->parent->lchild == n && grandparent(n)->lchild == n->parent)
	{
		rightRotate(n->parent);
	}
	else
	{
		leftRotate(n->parent);
	}
}

template<typename T>
std::pair<bool, RedBlackTreeNodePtr<T>> RedBlackTree<T>::search(RedBlackTreeNodePtr<T> t, const T& value, RedBlackTreeNodePtr<T> f)
{
	if(!t)
	{
		return {false, f};
	}
	if(value < t->data)
	{
		return search(t->lchild, value, t);
	}
	else if(value > t->data)
	{
		return search(t->rchild, value, t);
	}
	else
	{
		return {true, t};
	}
}

template<typename T>
bool RedBlackTree<T>::isRedBlackTree(const RedBlackTreeNodePtr<T> t)
{
    // Base case: an empty tree or a nullptr is considered a valid Red-Black tree
    if (t == nullptr)
        return true;

    // Property 1: Every node is either red or black
    if (t->color != RED && t->color != BLACK)
        return false;

    // Property 3: A red node does not have a red child
    if (t->color == RED && (t->lchild != nullptr && t->lchild->color == RED))
	{
        return false;
	}
    if (t->color == RED && (t->rchild != nullptr && t->rchild->color == RED))
	{
        return false;
	}

    // Property 4: Every path from a given node to any of its descendant NIL nodes
    // goes through the same number of black nodes
    int leftBlackHeight = countBlackNodes(t->lchild);
    int rightBlackHeight = countBlackNodes(t->rchild);
    if (leftBlackHeight != rightBlackHeight)
	{
        return false;
	}

    // Recursively check the left and right subtrees
    return isRedBlackTree(t->lchild) && isRedBlackTree(t->rchild);
}

template<typename T>
int RedBlackTree<T>::countBlackNodes(const RedBlackTreeNodePtr<T> t)
{
    // Property 2: All NIL nodes are considered black
    if (t == nullptr)
        return 1;

    int leftBlackHeight = countBlackNodes(t->lchild);
    int rightBlackHeight = countBlackNodes(t->rchild);

    // Increment the black height if the current node is black
    int currentBlackHeight = (t->color == BLACK) ? 1 : 0;

    // Return the black height of the subtree rooted at the current node
    return currentBlackHeight + std::max(leftBlackHeight, rightBlackHeight);
}


#endif // _REDBLACKTREE_H_
