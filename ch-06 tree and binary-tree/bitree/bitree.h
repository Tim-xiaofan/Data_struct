/** 20210415 12:45, zyj, GuangDong*/
// bitree.h -- binary tree
#ifndef BITREE_H
#define BITREE_H
#include <iostream>
#include "sqstack.h"
using std::cout;
using std::endl;


template<typename Data>
void show_ds(const Data * ds, int ct);

static inline int fact(int n)
{
	int i, ret = 1;
	for(i = 1; i <= n; ++i)
	  ret *= i;
	return ret;
}

template <typename Data>
class bitree
{
	private:
		template <typename Data1>
		struct Node
		{
			Data1 data;
			Node *lchild, *rchild;
			Node():lchild(nullptr), rchild(nullptr){}
		};
	public:
		typedef Node<Data> node;
	private:
		node *_root;
		int _ct;
	private:
		template<typename UnaryOperator>
		void preorder_traverse(node * root, const UnaryOperator & op);
		template<typename UnaryOperator>
		void inorder_traverse(node * root, const UnaryOperator & op);
		template<typename Cmp>
		void cmp_insert(node * & root, const Data & d, const Cmp & cmp);
		static int less(const Data & d1, const Data & d2){return d1 - d2;}
		static void show(const Data & d){cout << d <<" ";}
		bool preinorder_construct(node * & root, const Data * pre, const Data *in, int ct);
		template<typename UnaryOperator>
		void inorder_traversex(node * root, const UnaryOperator & op);
		void second_optimal(node * & T, const Data * table, float *sw, int low, int high);
	public:
		bitree():_root(nullptr), _ct(0){}
		//template<typename UnaryOperator>
		//void test(const UnaryOperator & op);
		/** root fisrt*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void preorder_traverse(const UnaryOperator & op = show){preorder_traverse(_root, op); cout << endl;}
		/** root second*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void inorder_traverse(const UnaryOperator & op = show){inorder_traverse(_root, op); cout << endl;}
		/** cmp construct*/
		template<typename Cmp = int(*)(const Data &, const Data&)>
		bool cmp_construct(const Data * ds, int ct, const Cmp & cmp = less);
		/** preorder and inorder create*/
		bool preinorder_construct(const Data * pre, const Data *in, int ct){return preinorder_construct(_root, pre, in , ct);}
		/** root second, not recursion*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void inorder_traversex(const UnaryOperator & op = show){inorder_traversex(_root, op); cout << endl;}
		static int count(int n) {return fact(2 * n) / fact(n) /fact(n + 1);}
		/** 构造次优查找树的*/
		void second_optimal(const Data * table, float * w, int size);
};

/** root first*/
template<typename Data>
template<typename UnaryOperator>
void bitree<Data>::
preorder_traverse(node *root, const UnaryOperator & op)
{
	if(root)
	{
		op(root->data);
		/** traverse left child*/
		preorder_traverse(root->lchild, op);
		/** traverse right child*/
		preorder_traverse(root->rchild, op);
	}
}

/** root second*/
template<typename Data>
template<typename UnaryOperator>
void bitree<Data>::
inorder_traverse(node *root, const UnaryOperator & op)
{
	if(root)
	{
		/** traverse left child*/
		inorder_traverse(root->lchild, op);
		op(root->data);
		/** traverse right child*/
		inorder_traverse(root->rchild, op);
	}
}


template<typename Data>
template<typename Cmp>
bool bitree<Data>:: 
cmp_construct(const Data * ds, int ct, const Cmp & cmp)
{
	/** TODO:check whethe threre are duplicated elements in the ds array*/
	int i;
	for(i = 0; i < ct; i++)
	{
		cmp_insert(_root, ds[i], cmp);
	}

	return true;
}

template<typename Data>
template<typename Cmp>
void bitree<Data>:: 
cmp_insert(node * & root, const Data & d, const Cmp & cmp)
{
	if(root == nullptr)
	{ 
		root = new node;
		root->data = d;
		//cout << endl;
		return;
	}
	int ret = cmp(d, root->data);
	if(ret < 0)
	  cmp_insert(root->lchild, d, cmp);
	else if(ret > 0)
	  cmp_insert(root->rchild, d, cmp);
	else cout << "duplicated elements " << d << endl;
}

template<typename Data>
bool bitree<Data>:: 
preinorder_construct(node * & root, const Data * pre, const Data *in, int ct)
{
	if(pre == nullptr || in == nullptr || ct <= 0)
	  return false;

	/** create root from preorder*/
	if(root == nullptr) root = new node;
	root->data = pre[0]; 

	/** look left and right in inorder*/
	int lct = 0, rct = 0, root_pos;
	for(root_pos = 0; root_pos < ct; ++root_pos)
	  if(in[root_pos] == root->data)
		break;
	lct = root_pos;
	rct = ct - lct - 1;

	/** create lchild*/
	preinorder_construct(root->lchild, &pre[1], in, lct);
	/** create rchild*/
	preinorder_construct(root->rchild, &pre[1 + lct], &in[lct + 1], rct);
	return true;
}

template<typename Data>
void show_ds(const Data * ds, int ct)
{
	int i;
	for(i = 0; i < ct; ++i)
	  cout << ds[i] << " ";
	cout << endl;
}

/** root second, not recursion*/
template<typename Data>
template<typename UnaryOperator>
void bitree<Data>::
inorder_traversex(node *root, const UnaryOperator & op)
{
	sqstack<node *> stack(32);
	node * pn = root;
	while(!stack.is_empty() || pn)
	{
		if(pn)
		{
			stack.push(pn);
			pn = pn->lchild;
		}
		else
		{
			stack.pop(pn);
			op(pn->data);
			pn = pn->rchild;
		}
	}
}


template<typename Data>
void bitree<Data>::
second_optimal(const Data * table, float * w, int size)
{
	if(size == 0) return;
	int i;
	float *sw = new float[size];

	sw[0] = w[0];
	for(i = 1; i < size; ++i)
	  sw[i] = sw[i -1] + w[i];

	second_optimal(_root, table, sw, 0, size - 1);
}

template<typename T>
T abs(const T & t)
{
	if(t < 0) return (0 - t);
	return t;
}

template<typename Data>
void bitree<Data>::
second_optimal(node * & T, const Data * table,  float * sw, int low, int high)
{
	int i = low, j;
	float dw, min = abs(sw[high] - sw[low]);
	if(low == 0)  dw = sw[high] + 0;
	else  dw = sw[high] + sw[low -1];

	//min(Pi), i is current root
	cout << "\n-----------------------------------" << endl;
	cout << "low = " << low << ", high = " << high << endl;
	cout << table[low] << " ";
	for(j = low + 1; j <= high; ++j)
	{
		cout << table[j] << " ";
	  if(abs(dw - sw[j] - sw[j - 1]) < min)
	  {
		  min = abs(dw - sw[j] - sw[j -1]);
		  i = j;
	  }
	}
	cout << endl;
	T = new node();
	T->data = table[i];
	cout << "min = " << min << endl;
	cout << "i = " << i << endl;
	if(i != low)//create left child
	  second_optimal(T->lchild, table, sw, low, i - 1);
	if(i != high)//create right child
	  second_optimal(T->rchild, table, sw, i + 1, high);
}

#endif
