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

template<typename C>
void borderCheck(const C& c, int pos)
{
	if(!(pos >= 0 && pos < static_cast<int>(c.size())))
	{
		throw std::out_of_range(std::string("pos=") + std::to_string(pos) + ", c.size()=" + std::to_string(c.size()));
	}
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
			throw std::out_of_range(std::string("pos=") + std::to_string(pos) + ", children.size()=" + std::to_string(children.size()));
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

	T& atKeys(int index)
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

	BTreeNode* getLSibling(int& i)
	{
		if(!parent) return nullptr;	
		auto it = std::find(parent->children.begin(), parent->children.end(), this);
		assert(it != parent->children.end());
		if(it != parent->children.begin())
		{
			--it;
			i = std::distance(parent->children.begin(), it);
			return *it;
		}
		return nullptr;
	}

	BTreeNode* getRSibling(int& i)
	{
		if(!parent) return nullptr;	
		auto it = std::find(parent->children.begin(), parent->children.end(), this);
		assert(it != parent->children.end());
		if(it + 1 != parent->children.end())
		{
			++it;
			i = std::distance(parent->children.begin(), it);
			return *it;
		}
		return nullptr;
	}
	
	void eraseChild(int pos)
	{
		borderCheck(children, pos);
		children.erase(children.begin() + pos);
	}

	void eraseKey(int pos)
	{
		borderCheck(keys, pos);
		keys.erase(keys.begin() + pos);
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
		Result erase(const T& value);

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
		Result eraseUtil(NodePtr n, int i);

		static void display(const NodePtr node, int level = 0);
		static void copy(NodePtr dst, const NodePtr src);
		static bool same(const NodePtr a, const NodePtr b);
		static bool isNonTerminalNode(const NodePtr n);
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

template<typename T, int m> typename BTree<T, m>::Result BTree<T, m>::
erase(const T& value)
{
	auto ret = search(value);
	if(!ret.tag)
	{
		return ret;
	}
	else
	{
		assert(value == ret.n->atKeys(ret.i));
		return eraseUtil(ret.n, ret.i);
	}
}

template<typename T, int m> typename BTree<T, m>::Result BTree<T, m>::
eraseUtil(NodePtr n, int i)
{
	if(isNonTerminalNode(n))
	{// non terminal node
		std::cout << "non-terminal node\n";
		// find minimum key in lchild
		NodePtr lchild = n->children[i];
		if(lchild)
		{
			while(lchild->atChildren(0))
			{
				lchild = lchild->atChildren(0);
			}
			//relace with min
			n->atKeys(i) = lchild->atKeys(0);
			//erase min
			n = lchild;
			i = 0;
		}
	}
	while(n)
	{
		std::cout << "\n\n";
		std::cout << n->atKeys(i) << " should erase at("<< i << ") in: " << n->keys << std::endl;
		n->eraseKey(i);
		assert(std::ceil(m*1.0/2) - 1 == 1);
		if(n->keysSize() >= std::ceil(1.0*m/2) - 1)
		{
			n->eraseChild(i);
			std::cout << "finished\n";
			return {true, n, i};//finished
		}
		NodePtr lSibling, rSibling;
		int lIndex = -1, rIndex = -1;
		if((lSibling = n->getLSibling(lIndex)) && lSibling->keysSize() >= std::ceil(m*1.0/2))
		{//case 1: borrow from left sibling
			std::cout << "borrow from left sibling:" << lSibling->keys <<std::endl;
			assert(lSibling == n->parent->atChildren(lIndex));
			T max = lSibling->keys.back();;
			lSibling->eraseChild(lSibling->keysSize());
			lSibling->keys.pop_back();
			n->insertKey(0, n->parent->keys[lIndex]);
			n->parent->keys[lIndex] = max;
			return {true, n, i};
		}
		else if((rSibling = n->getRSibling(rIndex)) && rSibling->keysSize() >= std::ceil(m*1.0/2))
		{//case 2: borrow from right sibling
			std::cout << "borrow from right sibling" << rSibling->keys << std::endl;
			assert(rSibling == n->parent->atChildren(rIndex));
			T min = rSibling->keys.front();;
			rSibling->eraseChild(0);
			rSibling->eraseKey(0);
			n->keys.push_back(n->parent->keys[rIndex-1]);
			n->parent->keys[rIndex-1] = min;
			return {true, n, i};
		}
		else if(lSibling)
		{//case 3: join in left sibling
			std::cout << "join in left sibling: " << lSibling->keys << std::endl;
			std::cout << "k: " << n->parent->keys[lIndex] << std::endl;;
			std::cout << "remaining: " << n->keys << std::endl;
			lSibling->keys.push_back(n->parent->keys[lIndex]);
			lSibling->children.push_back(nullptr);
			for(const T& k: n->keys)
			{
				lSibling->keys.push_back(k);
			}
			for(NodePtr c: n->children)
			{
				if(c)
					std::cout << "join: " << c->keys << std::endl;
				lSibling->children.push_back(c);
			}
			NodePtr tmp = n;
			n = n->parent;
			i = lIndex;
			assert(n->atChildren(lIndex+1) == tmp);
			n->atChildren(lIndex+1) = nullptr;
			delete tmp;
		}
		else if(rSibling)
		{//case 4: join in right sibling
			std::cout << "join in right sibling: " << rSibling->keys << std::endl;
			std::cout << "k: " << n->parent->keys[rIndex-1] << std::endl;;
			std::cout << "remaining: " << n->keys << std::endl;
			rSibling->insertKey(0, n->parent->keys[rIndex-1]);
			rSibling->insertChild(0, nullptr);
			for(const T& k: n->keys)
			{
				rSibling->insertKey(0, k);
			}
			for(size_t j = 0; j < n->children.size(); ++j)
			{
				if(n->children[j])
					std::cout << "join: " << n->children[j]->keys << std::endl;
				rSibling->insertChild(i, n->children[j]);
			}
			NodePtr tmp = n;
			n = n->parent;
			i = rIndex-1;
			assert(n->atChildren(rIndex-1) == tmp);
			n->atChildren(rIndex-1) = nullptr;
			delete tmp;
		}
		else
		{//root
			if(!n->keys.size())
			{
				for(auto c: n->children)
				  root_ = c;
				delete n;
			}
			else
			{
				n->eraseChild(i);
			}
			break;
		}
	}//while
	return {false, nullptr, -1};
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

template<typename T, int m>
bool BTree<T, m>::isNonTerminalNode(const NodePtr n)
{
	if(!n) return false;
	for(const NodePtr child: n->children)
	{
		if(child) return true;
	}
	return false;
}


	
#endif
