// 二叉树：线索二叉树
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
class ThreadedBinaryTreeNode
{
	public:
		ThreadedBinaryTreeNode();

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

		void inorderTraversalThreading()
		{
			ThreadedBinaryTreeNode* lastVisted = nullptr;
			inorderTraversalThreading(lastVisted);
		}
		
		template<typename Unary>
		void inorderTraversalThreaded(Unary op) const;

	private:
		T data_;
		ThreadedBinaryTreeNode* lchild_;
		ThreadedBinaryTreeNode* rchild_;
		bool lTag_;
		bool rTag_;

		using IterType = typename std::vector<T>::const_iterator;
		void  doCreateFromPreorderAndInorder(IterType preStart, IterType preEnd, IterType inStart, IterType inEnd);
		void inorderTraversalThreading(ThreadedBinaryTreeNode* & lastVisted);
};

template<typename T>
ThreadedBinaryTreeNode<T>::ThreadedBinaryTreeNode()
		:lchild_(nullptr),
		rchild_(nullptr),
		lTag_(false),
		rTag_(false)
{
}

template<typename T>
void ThreadedBinaryTreeNode<T>::createFromPreorderAndInorder(const std::vector<T>& preList, const std::vector<T>& inList)
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
		lchild_ = new ThreadedBinaryTreeNode();
		lchild_->doCreateFromPreorderAndInorder(preList.begin() + 1, preList.begin() + 1 + index, inList.begin(), inList.begin() + index);
	}
	if(index + 1 < inList.size())
	{//create rchild if exists
		rchild_ = new ThreadedBinaryTreeNode();
		rchild_->doCreateFromPreorderAndInorder(preList.begin() + 1 + index, preList.end(), inList.begin() + index + 1, inList.end());
	}
}

template<typename T>
void ThreadedBinaryTreeNode<T>::doCreateFromPreorderAndInorder(IterType preStart, IterType preEnd, IterType inStart, IterType inEnd)
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
		lchild_ = new ThreadedBinaryTreeNode();
		lchild_ ->doCreateFromPreorderAndInorder(preStart + 1, preStart + 1+ lchild_size, inStart, index);
	}
	if(index + 1 < inEnd)
	{//create rchild if exists
		rchild_ = new ThreadedBinaryTreeNode();
		rchild_->doCreateFromPreorderAndInorder(preStart + lchild_size + 1, preEnd, index + 1, inEnd);
	}
}

template<typename T>
template<typename Unary>
void ThreadedBinaryTreeNode<T>::preorderTraversal(Unary op) const
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
void ThreadedBinaryTreeNode<T>::preorderTraversalNotRecurion(Unary op) const
{
	const ThreadedBinaryTreeNode<T>* p = this;
	std::stack<const ThreadedBinaryTreeNode<T>*> s;
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
void ThreadedBinaryTreeNode<T>::inorderTraversal(Unary op) const
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
void ThreadedBinaryTreeNode<T>::inorderTraversalNotRecursion(Unary op) const
{
	const ThreadedBinaryTreeNode<T>* p = this;
	std::stack<const ThreadedBinaryTreeNode<T>*> s;
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
void ThreadedBinaryTreeNode<T>::inorderTraversalThreading(ThreadedBinaryTreeNode<T>* & lastVisted)
{
	if(lchild_)
	{
		lchild_->inorderTraversalThreading(lastVisted);
	}
	
	if(lastVisted != nullptr)
	{
		if(!lastVisted->rchild_)
		{
			lastVisted->rTag_ = true;
			lastVisted->rchild_ = this;
		}
		if(!lchild_)
		{
			lTag_ = true;
			lchild_ = lastVisted;
		}
	}
	lastVisted = this;

	if(rchild_)
	{
		rchild_->inorderTraversalThreading(lastVisted);
	}
}

template<typename T>
template<typename Unary>
void ThreadedBinaryTreeNode<T>::inorderTraversalThreaded(Unary op) const
{
	auto p = this;
	while(p)
	{
		while(p->lchild_ && !p->lTag_)
		{
			p = p->lchild_;
		}
		op(p->data_);
		while(p && p->rTag_)
		{
			p = p->rchild_;
			op(p->data_);
		}
		p = p->rchild_;
	}
}

template<typename T>
void ThreadedBinaryTreeNode<T>::display(int level) const
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

static void assertThreadedBinaryTreeNode(const std::vector<int>& pre, const std::vector<int>& in, const std::string& caseName)
{
	cout << "pre: " << pre << endl;
	cout << "in: " << in << endl;
	ThreadedBinaryTreeNode<int> *root = new ThreadedBinaryTreeNode<int>();
	root->createFromPreorderAndInorder(pre, in);
	root->display();
	
	
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
		root->inorderTraversalThreading();
		std::vector<int> in_results;
		root->inorderTraversalThreaded([&in_results](int i) {in_results.push_back(i); });
		cout << "in_results_threaded: " << in_results << endl;
		assert(in_results == in);
	}


	cout << caseName << " passed\n\n";
}

int main(void)
{
	{//case 1: full
		std::vector<int> pre= {1,2,4,5,3,6,7};
		std::vector<int> in= {4,2,5,1,6,3,7};
		assertThreadedBinaryTreeNode(pre, in, "case1");
	}

	{// case2: not full
		std::vector<int> pre= {1,2,4,3,6,7};
		std::vector<int> in= {4,2,1,6,3,7};
		assertThreadedBinaryTreeNode(pre, in, "case2");
	}

	{// case 3: one node
		std::vector<int> pre= {1};
		std::vector<int> in= {1};
		assertThreadedBinaryTreeNode(pre, in, "case3");
	}

	{//case 4: only lchild
		std::vector<int> pre= {1, 2, 3};
		std::vector<int> in= {3, 2, 1};
		assertThreadedBinaryTreeNode(pre, in, "case4");
	}

	{//case 5: only rchild
		std::vector<int> pre= {1, 2, 3, 4};
		std::vector<int> in= {1, 2, 3, 4};
		assertThreadedBinaryTreeNode(pre, in, "case5");
	}

	cout << "All test passed\n";
	return 0;
}
