/** 20210415 12:45, zyj, GuangDong*/
// bitree.h -- binary tree
#ifndef _SORTED_BITREE_H_
#define _SORTED_BITREE_H
#include <iostream>
#include <string>
#include "sqstack.h"
#include "sqqueue.h"
#include "bitree.h"

#ifndef MAX_NUM_NODE 
#define MAX_NUM_NODE 128
#endif

using std::cout;
using std::endl;
using std::string;

template <typename Data>
class sorted_bitree : public bitree<Data>
{
	private:
		typedef bitree<Data> base;
	public:
		typedef typename base::node node;
		typedef typename base::edge edge;
	protected:
		using base::_root;
		using base::_node_num;
		template<typename Cmp>
		void cmp_insert(node * & root, const Data & d, const Cmp & cmp);
		template<typename key_t, typename cmp_t>
        bool sorted_search(const node * root, const key_t & k, const cmp_t & cmp) const;
		static Data default_cmp(const Data & a, const Data & b) {return (a - b);};
		template<typename key_t, typename cmp_t>
		bool sorted_delete(node * & root, const key_t &k , const cmp_t & cmp);
        void sorted_delete(node * & p);
		//node * & root(void) {return base::_root;}
	public:
		sorted_bitree():base(){}
		/** 构造二叉排序树:重复节点直接舍弃*/
		template<typename Cmp = Data(*)(const Data &, const Data &)>
		void sorted_construct(const Data * ds, int ct, const Cmp & cmp = default_cmp);
		/** 在排序二叉树插入新的节点 */
		template<typename Cmp = Data(*)(const Data &, const Data &)>
		bool sorted_insert(const Data & d, const Cmp & cmp = default_cmp);
        /** 在排序二叉树搜寻key为k的节点*/
        template<typename key_t = Data, typename cmp_t = Data(*)(const Data &, const Data &)>
        bool sorted_search(const key_t & k, const cmp_t & cmp = default_cmp) const;
        /** 排序二叉树：删除key为k的节点*/
        template<typename key_t = Data, typename cmp_t = Data(*)(const Data &, const Data &)>
        bool sorted_delete(const key_t &k , const cmp_t & cmp = default_cmp);
};

template<typename Data>
template<typename Cmp>
void sorted_bitree<Data>::
cmp_insert(node * & root, const Data & d, const Cmp & cmp)
{
	if(root == nullptr)
	{
		_node_num ++;//really inserted
		root = new node;
		root->data = d;
		//cout << endl;
		return ;
	}
	Data ret = cmp(d, root->data);
	if(ret < 0)//insert into lchild
	{
		cmp_insert(root->lchild, d, cmp);
	}
	else if(ret > 0)
	{
		cmp_insert(root->rchild, d, cmp);//insert into rchild
	}
	else
	{
		cout << "duplicated element : " << d << endl;
	}
}

template<typename Data>
template<typename Cmp>
void sorted_bitree<Data>::
sorted_construct(const Data * ds, int ct, const Cmp & cmp)
{
	int i;

	for(i = 0; i < ct; i++)
	  cmp_insert(base::_root, ds[i], cmp);
}

template<typename Data>
template<typename Cmp>
bool sorted_bitree<Data>::
sorted_insert(const Data & d, const Cmp & cmp)
{
	int old = base::_node_num;
	cmp_insert(base::_root, d, cmp);
	return (old != base::_node_num);
}

template<typename Data>
template<typename key_t, typename cmp_t>
bool sorted_bitree<Data>::
sorted_search(const key_t & key, const cmp_t & cmp) const
{
    return sorted_search(base::_root, key, cmp);
}

template<typename Data>
template<typename key_t, typename cmp_t>
bool sorted_bitree<Data>::
sorted_search(const node * root, const key_t & key, const cmp_t & cmp) const
{
    if(root)
    {
        if(cmp(root->data, key) == 0)//root
        {
            return true;
        }

        if(root->lchild)//lchild
        {
            if(sorted_search(root->lchild, key, cmp))
              return true;
        }

        if(root->rchild)//rchild
        {
            if(sorted_search(root->rchild, key, cmp))
              return true;
        }
    }
    return false;;
}

template<typename Data>
template<typename key_t, typename cmp_t>
bool sorted_bitree<Data>::
sorted_delete(const key_t &k, const cmp_t & cmp)
{
    return sorted_delete(base::_root, k, cmp);
}

template<typename Data>
template<typename key_t, typename cmp_t>
bool sorted_bitree<Data>::
sorted_delete(node * & root, const key_t &k, const cmp_t & cmp)
{
    if(root)
    {
		//cout << "root = " << *root << endl;
        if(cmp(k, root->data) == 0)
        {
            sorted_delete(root);
            return true;
        }
        else if(cmp(k, root->data) < 0)
          return sorted_delete(root->lchild, k, cmp);
        else
          return sorted_delete(root->rchild, k, cmp);
    }
    return false;
}

/** sorted sorted_bitree：delete node p*/
template<typename Data>
void sorted_bitree<Data>::
sorted_delete(node * & p)
{
    node * q, *s;
    if(!p) return;
	//cout << "delete p = " << *p << endl;

	if(!p->lchild)//empty lchild
    {
        q = p;
        p = p->rchild;
        delete q;
    }
    else if(!p->rchild)// empty rchild
    {
        q = p;
        p = p->lchild;
        delete q;
    }
    else
    {
        /** 寻找前驱s*/
        q = p;
        s = p->lchild;
        while(s->rchild)
        {
             q = s;
             s = s->rchild;
        }
		//cout << "q = " << *q << endl;
		//cout << "s = " << *s << endl;
        p->data = s->data;//s替换p
        if(q != p) q->rchild = s->lchild;
        else q->lchild = s->lchild;//旋转
        delete s;
    }
    --base::_node_num;
}
#endif
