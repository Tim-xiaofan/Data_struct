/** 20210911, zyj, GuangDong*/
#ifndef _BS_BITREE_H
#define _BS_BITREE_H

#include <iostream>
#include "sorted_bitree.h"

using std::cout;
using std::endl;
using std::string;

template <typename Data>
class bs_bitree : public sorted_bitree<Data>
{
	private:
		typedef sorted_bitree<Data> base;
		using base::_root;
		using base::_node_num;
	public:
		typedef typename base::node node;
		typedef typename base::edge edge;
	private:
		enum {LH = 1, EH = 0, RH = -1};
		void l_rotate(node * & p);
		void r_rotate(node * & p);
		template<typename cmp_t>
		bool insert_alv(node * & root, const Data & e, const cmp_t & cmp, bool & taller);
		void l_balance(node * & root);
		void r_balance(node * & root);
	public:
		bs_bitree():base(){}
		template<typename cmp_t = Data (*)(const Data &, const Data &)>
		bool insert_alv(const Data & e, const cmp_t & cmp = base::default_cmp); 
		/** 构造*/
		template<typename cmp_t = Data (*)(const Data &, const Data &)>
		int bs_construct(const Data * ds, int size, const cmp_t & cmp = base::default_cmp); 
};

/*
   对以*p为根(失衡)的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转
   处理之前的左子树的根结点
 */
template <typename Data>
void bs_bitree<Data>::
r_rotate(node * & p)
{
	node * lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

/*
   对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转
   处理之前的右子树的根结点
 */
template <typename Data>
void bs_bitree<Data>::
l_rotate(node * & p)
{
	node * rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}
		
template<typename Data>
template<typename cmp_t>
bool bs_bitree<Data>::
insert_alv(node * & root, const Data & e, const cmp_t & cmp, bool & taller)
{
	if(root == nullptr)
	{
		root = new node();
		root->data = e;
		_node_num++;
		taller = true;
		return true;
	}
	else
	{
		if(cmp(e, root->data) == 0) return false;//existed
		else if(cmp(e, root->data) < 0) // insert into lchild
		{
			if(!insert_alv(root->lchild, e, cmp, taller)) 
			  return false;//not inserted
			if(taller)//root's is taller
			{
				switch(root->bf)
				{
					case LH:// 原本左子树比右子树高，需要作左平衡处理
						l_balance(root);
						taller = false;
						break;
					case EH://原本左、右子树等高，现因左子树增高而使树增高
						root->bf = LH;
						break;
					case RH://原本右子树比左子树高，现左、右子树等高
						root->bf = EH;
						taller = false;
						break;
				}
			}
		}
		else//insert into rchild
		{
			if(!insert_alv(root->rchild, e, cmp, taller)) //not inserted
			  return false;
			if(taller)
			{
				switch(root->bf)
				{
					case LH:// 原本左子树比右子树高，现左、右子树等高
						root->bf = EH;
						taller = false;
						break;
					case EH:// 原本左、右子树等高，现因右子树增高而使树增高
						root->bf = RH;
						break;
					case RH:// 原本右子树比左子树高，需要作右平衡处理
						r_balance(root);
						taller = false;
						break;
				}
			}
		}
	}
	return true;
}

template<typename Data>
template<typename cmp_t>
bool bs_bitree<Data>::
insert_alv(const Data & e, const cmp_t & cmp)
{
	bool taller;
	return insert_alv(_root, e, cmp, taller);
}


template<typename Data>
void bs_bitree<Data>::
l_balance(node * & root)
{
	node * lc = root->lchild, *rd; 
	switch(lc->bf)
	{
		case LH: //LL
			root->bf = EH;
			lc->bf = EH;
			r_rotate(root);
			break;
		case RH: //LR
			rd = lc->rchild;// 指向*T的左孩子的右子树根
			switch(rd->bf)
			{
				case LH: 
					root->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					root->bf =EH;
					lc->bf = EH;
					break;
				case RH:
					root->bf = EH;
					lc->bf = LH;
					break;
			}
		    rd->bf = EH;
			l_rotate(root->lchild);
			r_rotate(root);
	}
}

template<typename Data>
void bs_bitree<Data>::
r_balance(node * & root)
{
	node * rc = root->rchild, *ld; 
	switch(rc->bf)
	{
		case RH: //RR
			root->bf = EH;
			rc->bf = EH;
			l_rotate(root);
			break;
		case LH: //RL
			ld = rc->lchild;// 指向*T的右孩子的左子树根
			switch(ld->bf)
			{
				case LH: 
					root->bf = EH;
					rc->bf = RH;
					break;
				case EH:
					root->bf =EH;
					rc->bf = EH;
					break;
				case RH:
					root->bf = LH;
					rc->bf = EH;
					break;
			}
			ld->bf = EH;
			r_rotate(root->rchild);
			l_rotate(root);
	}
}


/** 
  构造平衡二叉树
  return number of node
 */
template<typename Data>
template<typename cmp_t>
int bs_bitree<Data>::
bs_construct(const Data * ds, int size, const cmp_t & cmp)
{
	int i;

	for(i = 0; i < size; ++i)
	  insert_alv(ds[i], cmp);

	return _node_num;
}
#endif
