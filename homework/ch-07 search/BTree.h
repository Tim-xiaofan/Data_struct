#ifndef _BTREE_H_
#define _BTREE_H_
#include <vector>
#include <utility>
#include <limits>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	for (size_t i = 0; i < vec.size(); ++i) {
		os << vec[i];
		if (i != vec.size() - 1) {
			os << ", ";
		}
	}
	os << "]";
	return os;
}

template<typename T>
struct BTreeNode
{
	struct BTreeNode *parent;
	std::vector<T> keys;
	std::vector<BTreeNode*> children;

	BTreeNode()
		:parent(nullptr) {}

	void insertKey(int pos, const T& value)
	{
		if(pos < 0 || pos > static_cast<int>(keys.size()))
		{
			throw std::out_of_range(std::string("pos=") + std::to_string(pos) + ", keys.size()=" + std::to_string(keys.size()));
		}
		BTreeNode<int> n;
		auto it = keys.begin();
		std::advance(it, pos);
		keys.insert(it, value);
	}

	void insertChild(int pos, BTreeNode* child)
	{
		if(pos < 0 || pos > static_cast<int>(children.size()))
		{
			throw std::out_of_range(std::string("pos=") + std::to_string(pos) + ", keys.size()=" + std::to_string(keys.size()));
		}
		auto it = children.begin();
		std::advance(it, pos);
		children.insert(it, child);
	}

	int getKeyInsertIndex(const T& value)
	{
		int left = 0;
		int right = keys.size();

		while (left < right)
		{
			int mid = left + (right - left) / 2;

			if (keys[mid] < value)
			  left = mid + 1;
			else
			  right = mid;
		}

		return left;
	}

	std::pair<bool, int> findKey(const T& value)
	{
		int left = 0;
		int right = keys.size();

		while (left < right)
		{
			int mid = left + (right - left) / 2;

			if(keys[mid] == value)
			{
				return {true, mid};
			}
			else if (keys[mid] < value)
			{
				left = mid + 1;
			}
			else
			{
				right = mid;
			}
		}

		return {false, left};
	}

	BTreeNode*& atChildren(int index)
	{
		return children.at(index);
	}

	const T& atKeys(int index) const
	{
		return keys.at(index);
	}

	int keysSize() const
	{
		return static_cast<int>(keys.size());
	}

	BTreeNode* split(int mid)
	{
		assert(mid > 0);
		assert(mid < keysSize());
		
		BTreeNode* rchild = new BTreeNode();
		rchild->parent = parent;
		{
			auto it = keys.begin();
			std::advance(it, mid + 1);
			std::copy(it, keys.end(), std::back_inserter(rchild->keys));
			std::advance(it, -1);
			keys.erase(it, keys.end());
		}
		{
			auto it = children.begin();
			std::advance(it, mid + 1);
			std::copy(it, children.end(), std::back_inserter(rchild->children));
			children.erase(it, children.end());
		}

		return rchild;
	}

	bool same(const BTreeNode* rhs) const
	{
		if(keys != rhs->keys) return false;
		if(children.size() != rhs->children.size()) return false;
		for(size_t i = 0; i < children.size(); ++i)
		{
			if((children[i] == nullptr) != (rhs.children[i] == nullptr))
			{
				return false;
			}
		}
		for(size_t i = 0; i < children.size(); ++i)
		{
			if(children[i])
			{
				if(!children[i]->same(rhs->children[i]))
				{
					return false;
				}
			}
		}
		return true;
	}
};


template<typename T, int m>
class BTree
{
	public:
		static_assert(m > 1, "m must greater than 1");
		using NodeType = BTreeNode<T>;
		using NodePtr = NodeType*;

		struct Result
		{
			bool tag;
			NodePtr n;
			int i;
			Result(bool a=false, NodePtr b=nullptr, int c=-1)
				:tag(a), n(b), i(c){}
			bool operator==(const Result& rhs) const
			{
				return tag == rhs.tag && n == rhs.n && i == rhs.i;
			}

			void display() const
			{
				std::cout  << "Result(tag=" << tag << ", n=" << n << ", i=" << i << ")\n";
			}
		};

		BTree():root_(nullptr){}

		Result search(const T& value);
		Result insert(const T& value);

		void display() const
		{ display(root_, 0); std::cout << std::endl; }

		BTree& copy(BTree &rhs) const
		{
			if(root_)
			{
				rhs.root_ = new NodeType();
				copy(rhs.root_, root_);
			}
			return rhs;
		}

		bool same(const BTree& rhs)
		{
			return same(root_, rhs.root_);
		}

		//only for testing
		NodePtr& root()
		{ return root_; }

	private:
		NodePtr root_;
		struct BinaryNode
		{
			T data;
			BinaryNode* lchild;
			BinaryNode* rchild;
			BinaryNode(const T& d, BinaryNode* l=nullptr, BinaryNode* r=nullptr)
				:data(d), lchild(l), rchild(r) {}
		};
		Result insertUtil(T value, NodePtr n, int i);

		static void display(const NodePtr node, int level = 0);
		static void copy(NodePtr dst, const NodePtr src);
		static bool same(const NodePtr a, const NodePtr b);
};


template<typename T, int m> typename BTree<T, m>::Result BTree<T, m>::
search(const T& value)
{
	NodePtr n = root_;
	std::pair<bool, int> result = {false, 0};
	while(n)
	{
		result = n->findKey(value);
		if(result.first)
		{
			return {true, n, result.second};
		}
		else if(!n->atChildren(result.second))
		{
			return {false, n, result.second};
		}
		else
		{
			n = n->atChildren(result.second);
		}
	}
	return {false, n, result.second};
}


template<typename T, int m> typename BTree<T, m>::Result BTree<T, m>::
insert(const T& value)
{
	Result ret = search(value);
	if(ret.tag)
	{//if it exists
		ret.tag = false;
		return ret;
	}
	else
	{
		//std::cout << value << " does not exist, should insert into("<< ret.i << "): " << ret.n->keys << std::endl;
		return insertUtil(value, ret.n, ret.i);
	}
}

template<typename T, int m> typename BTree<T, m>::Result BTree<T, m>::
insertUtil(T value, NodePtr n, int i)
{
	bool finished = false;
	NodePtr rchild = nullptr;
	NodePtr lchild = nullptr;
	while(n && !finished)
	{
		std::cout << value << " should insert at("<< i << ") into: " << n->keys << std::endl;
		n->insertKey(i, value);
		n->insertChild(i + 1, rchild);
		if(n->keysSize() <= m -1)
		{
			finished = true;
		}
		else
		{//spilt n node
			int mid = (m - 1) / 2; 
			value = n->keys[mid];
			rchild = n->split(mid);
			lchild = n;

			// move mid value new node to parent
			n = n->parent;
			if(n)
			{
				i = n->getKeyInsertIndex(value);
			}
		}
	}

	if(!finished)
	{//empty tree or new root
		n = new NodeType();
		i = 0;
		n->insertKey(i, value);
		n->insertChild(i, lchild);
		n->insertChild(i + 1, rchild);
		root_ = n;
	}

	return Result(true, n, i);
}


template<typename T, int m>
void BTree<T, m>::display(const BTree<T, m>::NodePtr node, int level)
{
	if (node == nullptr)
	  return;

	for (int i = 0; i < level; ++i)
	  std::cout << "  ";
	std::cout << "|_";
	for (const auto& key : node->keys)
	  std::cout << key << " ";
	std::cout << std::endl;

	for (const auto& child : node->children)
	  display(child, level + 1);
}
		
template<typename T, int m>
void BTree<T, m>::copy(BTree<T, m>::NodePtr dst, const BTree<T, m>::NodePtr src)
{
	std::copy(src->keys.begin(), src->keys.end(), std::back_inserter(dst->keys));
	for (const auto& child : src->children)
	{
		if(!child)
		{
			dst->children.push_back(nullptr);
		}
		else
		{
			NodePtr p = new NodeType();
			dst->children.push_back(p);
			copy(p, child);
			p->parent = dst;
		}
	}
}

template<typename T, int m>
bool BTree<T, m>::same(const BTree<T, m>::NodePtr a, const BTree<T, m>::NodePtr b)
{
	if((a == nullptr) != (b == nullptr)) return false;
	if(a)
	{
		if(a->keys != b->keys) return false;
		if(a->children.size() != b->children.size()) return false;
		for (size_t i = 0; i < a->children.size(); ++i)
		{
			if(!same(a->children[i], b->children[i])) return false;
		}
	}
	return true;
}

#endif
