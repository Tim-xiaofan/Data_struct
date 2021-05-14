/** 20210514 12:49, zyj, GuangDong*/
// bithrtree.h -- binary thread tree
#ifndef BITHRTREE_H
#define BITHRTREE_H
#include <iostream>
#include "sqstack.h"
using std::cout;
using std::endl;

template<typename Data>
void show_ds(const Data * ds, int ct);

template <typename Data>
class bithrtree
{
	private:
		typedef enum {LINK, THREAD} pointer_tag;
		template <typename Data1>
		struct Node
		{
			Data1 data;
			Node *lchild, *rchild;
			pointer_tag ltag, rtag;
			Node():lchild(nullptr),rchild(nullptr),ltag(LINK),rtag(LINK){}
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
	public:
		bithrtree():_root(nullptr), _ct(0){}
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
};

/** root first*/
template<typename Data>
template<typename UnaryOperator>
void bithrtree<Data>::
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
void bithrtree<Data>::
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

//template<typename Data>
//template<typename UnaryOperator>
//void bithrtree<Data>::
//test(const UnaryOperator & op) 
//{
//	char a = 'a';
//	op(a);
//}

template<typename Data>
template<typename Cmp>
bool bithrtree<Data>:: 
cmp_construct(const Data * ds, int ct, const Cmp & cmp)
{
	/** TODO:check whethe threre are duplicated elements in the ds array*/
	int i;
	for(i = 0; i < ct; i++)
	{
		cmp_insert(_root, ds[i], cmp);
		//cout << "after inster " << ds[i] << ":";
		//preorder_traverse();
		//cout << endl;
	}

	return true;
}

template<typename Data>
template<typename Cmp>
void bithrtree<Data>:: 
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
bool bithrtree<Data>:: 
preinorder_construct(node * & root, const Data * pre, const Data *in, int ct)
{
	if(pre == nullptr || in == nullptr || ct <= 0)
	  return true;

	//cout << "pre:";
	//show_ds(pre, ct);
	//cout << "in:";
	//show_ds(in, ct);
	/** create root*/
	if(root == nullptr) root = new node;
	root->data = pre[0]; 
	//cout << "root data = " << root->data << endl;

	/** look left and right in inorder*/
	int lct = 0, rct = 0, root_pos;
	for(root_pos = 0; root_pos < ct; ++root_pos)
	  if(in[root_pos] == root->data)
		break;
	lct = root_pos;
	rct = ct - lct - 1;
	//cout << "lct = " << lct << endl;
	//cout << "rct = " << rct << endl;

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
void bithrtree<Data>::
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
#endif
