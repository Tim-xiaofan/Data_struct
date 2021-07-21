/** 20210514 12:49, zyj, GuangDong*/
// bithrtree.h -- binary thread tree
#ifndef BITHRTREE_H
#define BITHRTREE_H
#include <iostream>
#include "sqstack.h"

//#define DEBUG 1 //TODO:need a logsystem

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
			friend std::ostream & operator<<(std::ostream & os, const Node & nd)
			{
				os << "data = " << nd.data
					<< ", lchild = " << nd.lchild
					<< ", ltag = " << nd.ltag
					<< ", rchild = " << nd.rchild
					<< ", rtag = " << nd.rtag;
				return os;
			}
		};
	public:
		typedef Node<Data> node;
	private:
		node *_root;
		node *_thrt;/** head bode of thread link*/
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
		/** inorder threading*/
		void in_threading(node * & pre, node * p);
	public:
		bithrtree():_root(nullptr), _thrt(nullptr), _ct(0){}
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
		/** inorder threading*/
		void inorder_threading(void);
		/** inorder_threading traverse*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void inorder_thrtraverse(const UnaryOperator & op = show);
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
#ifdef DEBUG
		//cout << root <<": ( "<< *root << "), ";
#else
		op(root->data);
#endif
		/** traverse right child*/
		inorder_traverse(root->rchild, op);
	}
}


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
	sqstack<node *> stack(215);
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

void indent(int ct)
{
	int i;
	for(i = 0; i < ct - 1; i++)
	  cout << "\t";
}

template<typename Data>
void bithrtree<Data>::in_threading(node * & pre, node * p)
{
	static int level = 0;
	++level;
#ifdef DEBUG
	indent(level);
	cout << "enter level-" << level;
	if(pre) cout << " : pre = " << pre->data;
	else cout << " : pre = " << "NULL";
	if(p)cout << ", p = " << p->data << "(" << p << ")" <<", p->lchild : " << p->lchild << ", p->rchild : " << p->rchild << endl;
	else cout << ", p = " << "NULL" << endl;
#endif

	if(p)
	{
#ifdef DEBUG
		indent(level);
		cout << "#1 level-" << level << " : pre = " << pre->data <<"(" << pre <<")" << ", p = " << p->data << "(lchild: " << p->lchild <<")" << endl;
#endif
		in_threading(pre, p->lchild);/** threading left child*/

		/** set empty pointer*/
		if(!p->lchild)
		{
			p->ltag = THREAD;
#ifdef DEBUG
			cout << "# level-" << level << " : ";
			cout << p << " : "<< pre << "<--" << p->lchild <<endl;
#endif
			p->lchild = pre; /** precursor:last node in left child*/
#ifdef DEBUG
			indent(level);
			cout << "# level-" << level << " : " << p->data << "'s precursor is " << pre->data << endl;
			
#endif
		}
		if(!pre->rchild)
		{
			pre->rtag = THREAD;
#ifdef DEBUG
			cout << "# level-" << level << " : ";
			cout << pre << ":" << pre->rchild << "-->" << p <<endl;
#endif
			pre->rchild = p;/** successor*/
#ifdef DEBUG
			indent(level);
			cout << "# level-" << level << " : " << pre->data << "'s successor is " << p->data << endl;
#endif
		}

		/** update pre*/
		pre = p;
#ifdef DEBUG
		indent(level);
		cout << "#2 level-" << level << " : pre = " << pre->data << "(" << pre <<")" << ", p = " << p->data << "(" << p << ")" << "(rchild : " << p->rchild <<")" << endl;
#endif
		in_threading(pre, p->rchild);/** threading right child*/
	}
#ifdef DEBUG
	indent(level);
	cout << "leave level-" << level;
	if(pre) cout << " : pre = " << pre->data;
	else cout << " : pre = " << "NULL";
	if(p)cout << ", p = " << p->data << ", p->lchild : " << p->lchild << ", p->rchild : " << p->rchild << endl;
	else cout << ", p = " << "NULL" << endl;
#endif
	level--;
}

template<typename Data>
void bithrtree<Data>::inorder_threading(void)
{
	if(_thrt != nullptr) return; /** avoid double threading*/
	/** TODO:need to catch exception*/
	_thrt = new node();
	/** create head node*/
	_thrt->ltag = LINK;
	_thrt->rtag = THREAD;
	_thrt->rchild = _thrt;
	if(!_root) _thrt->lchild = _thrt;/** pointer back*/
	else
	{
		node * pre = nullptr;
		_thrt->lchild = _root;
		pre = _thrt;
		in_threading(pre, _root);
		/** threading last node*/
		pre->ltag = THREAD;
		pre->rchild = _thrt;
		_thrt->rchild = pre;
	}
}


template <typename Data>
template<typename UnaryOperator>
void bithrtree<Data>::
inorder_thrtraverse(const UnaryOperator & op)
{
	node * p = _thrt->lchild;//pointer to root node
	while(p != _thrt)
	{
		while(p->ltag == LINK)
		{
#ifdef DEBUG
			cout << "(" << p << " : " << *p << ")";
#endif
			p = p->lchild;
		}
		op(p->data);
		while(p->rtag == THREAD && p->rchild != _thrt)
		{
#ifdef DEBUG
			cout << "(" << p << " : " << *p << ")";
#endif
			p = p->rchild;
			op(p->data);
		}
		p = p->rchild;
	}
	cout << endl;
}
#endif
