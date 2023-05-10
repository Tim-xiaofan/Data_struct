// 二叉树：二叉链表表示
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <iterator>
#include <unordered_map>
#include <exception>
#include <algorithm>
#include <stack>

using std::endl;
using std::cout;

template<typename T>
static std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
	return os;
}

template<typename T>
static std::ostream& operator<<(std::ostream& os, const std::unordered_map<T, size_t>& m)
{
	for(auto i: m)
	{
		os << "<" << i.first << "," << i.second << "> ";
	}
	return os;
}

template<typename T>
class BinaryTreeNode
{
	public:
		BinaryTreeNode();

		void createFromPreorderAndInorder(const std::vector<T>& preList,  const std::vector<T>& inList);

		void display(int level = 0) const;

		template<typename Unary>
		void preorderTraversal(Unary op) const;

		template<typename Unary>
		void preorderTraversalNotRecurion(Unary op) const;
		
		template<typename Unary>
		void inorderTraversal(Unary op) const;

		template<typename Unary>
		void inorderTraversalNotRecursion(Unary op) const;

		int numberOfLeaves(void) const;

		template<typename Unary>
		void dualorderTraversal(Unary op) const;

	private:
		T data_;
		BinaryTreeNode* lchild_;
		BinaryTreeNode* rchild_;

		using IterType = typename std::vector<T>::const_iterator;
		void  doCreateFromPreorderAndInorder(IterType preStart, IterType preEnd, IterType inStart, IterType inEnd);
};

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode()
		:lchild_(nullptr),
		rchild_(nullptr)
{
}

template<typename T>
void BinaryTreeNode<T>::createFromPreorderAndInorder(const std::vector<T>& preList, const std::vector<T>& inList)
{
	assert(!preList.empty());
	assert(preList.size() == inList.size());

	data_ = preList[0];
	//cout << "data_:" << data_ << endl;
	
	//find root in inorder list
	size_t index;
	for(index = 0; index < preList.size(); ++index)
	{
		if(inList[index] == data_)
		{
			break;
		}
	}
	assert(index != preList.size());
	//cout << "index:" << index << endl << endl;

	if(index > 0)
	{//create lchild if exists
		lchild_ = new BinaryTreeNode();
		lchild_->doCreateFromPreorderAndInorder(preList.begin() + 1, preList.begin() + 1 + index, inList.begin(), inList.begin() + index);
	}
	if(index + 1 < inList.size())
	{//create rchild if exists
		rchild_ = new BinaryTreeNode();
		rchild_->doCreateFromPreorderAndInorder(preList.begin() + 1 + index, preList.end(), inList.begin() + index + 1, inList.end());
	}
}

template<typename T>
void BinaryTreeNode<T>::doCreateFromPreorderAndInorder(IterType preStart, IterType preEnd, IterType inStart, IterType inEnd)
{
	data_ = *preStart;
	//cout << "data_: " << data_ << endl;
	//std::cout << "pre: " << std::vector<T>(preStart, preEnd) << endl;
	//std::cout << "in: " << std::vector<T>(inStart, inEnd) << endl << endl;

	auto index = std::find(inStart, inEnd, data_);
	assert(index != inEnd);
	ssize_t lchild_size = 0;
	if(index > inStart)
	{//create lchild if exists
		lchild_size = std::distance(inStart, index);
		//cout << "lchild_size: " << lchild_size << endl;
		lchild_ = new BinaryTreeNode();
		lchild_ ->doCreateFromPreorderAndInorder(preStart + 1, preStart + 1+ lchild_size, inStart, index);
	}
	if(index + 1 < inEnd)
	{//create rchild if exists
		rchild_ = new BinaryTreeNode();
		rchild_->doCreateFromPreorderAndInorder(preStart + lchild_size + 1, preEnd, index + 1, inEnd);
	}
}

template<typename T>
template<typename Unary>
void BinaryTreeNode<T>::preorderTraversal(Unary op) const
{
	op(data_);
	if(lchild_)
	{
		lchild_->preorderTraversal(op);
	}
	if(rchild_)
	{
		rchild_->preorderTraversal(op);
	}
}

template<typename T>
template<typename Unary>
void BinaryTreeNode<T>::preorderTraversalNotRecurion(Unary op) const
{
	const BinaryTreeNode<T>* p = this;
	std::stack<const BinaryTreeNode<T>*> s;
	while(p || !s.empty())
	{
		if(p)
		{
			while(p)
			{
				op(p->data_);
				s.push(p);
				p = p->lchild_;
			}
		}
		else
		{
			p = s.top();
			s.pop();
			p = p->rchild_;
		}
	}
}

template<typename T>
template<typename Unary>
void BinaryTreeNode<T>::inorderTraversal(Unary op) const
{
	if(lchild_)
	{
		lchild_->inorderTraversal(op);
	}
	op(data_);
	if(rchild_)
	{
		rchild_->inorderTraversal(op);
	}
}


template<typename T>
template<typename Unary>
void BinaryTreeNode<T>::inorderTraversalNotRecursion(Unary op) const
{
	const BinaryTreeNode<T>* p = this;
	std::stack<const BinaryTreeNode<T>*> s;
	while(p || !s.empty())
	{
		if(p)
		{
			while(p)
			{
				s.push(p);
				p = p->lchild_;
			}
		}
		else
		{
			p = s.top();
			s.pop();
			op(p->data_);
			p = p->rchild_;
		}
	}
}

template<typename T>
void BinaryTreeNode<T>::display(int level) const
{
	for (int i = 0; i < level; ++i) {
		std::cout << "   ";
	}
	std::cout << "|_" << data_ << std::endl;
	if (lchild_ != nullptr) {
		lchild_->display(level + 1);
	}
	if (rchild_ != nullptr) {
		rchild_->display(level + 1);
	}
}

template<typename T>
int BinaryTreeNode<T>::numberOfLeaves(void) const
{
	if(!lchild_ && !rchild_)
	{
		return 1;
	}
	else
	{
		int count = 0;
		if(lchild_)
		{
			count += lchild_->numberOfLeaves();
		}
		if(rchild_)
		{
			count += rchild_->numberOfLeaves();
		}
		return count;
	}
}

template<typename T>
template<typename Unary>
void BinaryTreeNode<T>::dualorderTraversal(Unary op) const
{
	op(data_);
	if(!lchild_ && !rchild_)
	{
		return ;
	}
	else
	{
		if(lchild_)
		{
			lchild_->dualorderTraversal(op);
		}
		op(data_);
		if(rchild_)
		{
			rchild_->dualorderTraversal(op);
		}
	}
}

static void assertBinaryTreeNode(const std::vector<int>& pre, const std::vector<int>& in, const std::string& caseName, int numberOfLeaves, const std::vector<int>& dual)
{
	cout << "pre: " << pre << endl;
	cout << "in: " << in << endl;
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>();
	root->createFromPreorderAndInorder(pre, in);
	root->display();

	assert(root->numberOfLeaves() == numberOfLeaves);

	{
		std::vector<int> pre_results;
		root->preorderTraversal([&pre_results](int i) {pre_results.push_back(i); });
		cout << "pre_results: " << pre_results << endl;
		assert(pre_results == pre);
	}

	{
		std::vector<int> pre_results;
		root->preorderTraversalNotRecurion([&pre_results](int i) {pre_results.push_back(i); });
		cout << "pre_results: " << pre_results << endl;
		assert(pre_results == pre);
	}

	{
		std::vector<int> in_results;
		root->inorderTraversal([&in_results](int i) {in_results.push_back(i); });
		cout << "in_results: " << in_results << endl;
		assert(in_results == in);
	}

	{
		std::vector<int> in_results;
		root->inorderTraversalNotRecursion([&in_results](int i) {in_results.push_back(i); });
		cout << "in_results: " << in_results << endl;
		assert(in_results == in);
	}

	{
		std::vector<int> dual_results;
		root->dualorderTraversal([&dual_results](int i) {dual_results.push_back(i); });
		cout << "dual_results: " << dual_results << endl;
		assert(dual_results == dual);
	}

	cout << caseName << " passed\n\n";
}

int main(void)
{
	{//case 1: full
		std::vector<int> pre= {1,2,4,5,3,6,7};
		std::vector<int> in= {4,2,5,1,6,3,7};
		assertBinaryTreeNode(pre, in, "case1", 4, {1,2,4,2,5,1,3,6,3,7});
	}

	{// case2: not full
		std::vector<int> pre= {1,2,4,3,6,7};
		std::vector<int> in= {4,2,1,6,3,7};
		assertBinaryTreeNode(pre, in, "case2", 3, {1,2,4,2,1,3,6,3,7});
	}

	{// case 3: one node
		std::vector<int> pre= {1};
		std::vector<int> in= {1};
		assertBinaryTreeNode(pre, in, "case3", 1, {1});
	}

	{//case 4: only lchild
		std::vector<int> pre= {1, 2, 3};
		std::vector<int> in= {3, 2, 1};
		assertBinaryTreeNode(pre, in, "case4", 1, {1,2,3,2,1});
	}

	{//case 5: only rchild
		std::vector<int> pre= {1, 2, 3, 4};
		std::vector<int> in= {1, 2, 3, 4};
		assertBinaryTreeNode(pre, in, "case5", 1, {1,1,2,2,3,3,4});
	}

	cout << "All test passed\n";
	return 0;
}
