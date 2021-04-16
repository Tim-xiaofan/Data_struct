/** 20210415 12:45, zyj, GuangDong*/
// bitree.h -- binary tree
#ifndef BITREE_H
#define BITREE_H
#include <iostream>
using std::cout;
using std::endl;

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
	public:
		bitree():_root(nullptr), _ct(0){cout << "diy\n";};
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
		/** preorder and inorder creat*/
		bool preinorder_construct(const Data * pre, const Data *in, int ct){return preinorder_construct(_root, pre, in , ct);}
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

//template<typename Data>
//template<typename UnaryOperator>
//void bitree<Data>::
//test(const UnaryOperator & op) 
//{
//	char a = 'a';
//	op(a);
//}

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
		//cout << "after inster " << ds[i] << ":";
		//preorder_traverse();
		//cout << endl;
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
	if(pre == nullptr || in = nullptr || ct == 0)
	  return true;
	/** create root*/
	if(root == nullptr) root = new node;
	root->data = pre[0]; 

	/** look left and right*/
	int lct = 0, rct = ct, root_pos;
	for(root_pos = 0; root_pos < ct; ++root_pos)
	{
		++lct;
		--rct;
		if(in[root_pos] == root->data)
			break;
	}

	return false;
}
#endif
