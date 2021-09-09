/** 20210415 12:45, zyj, GuangDong*/
// bitree.h -- binary tree
#ifndef BITREE_H
#define BITREE_H
#include <iostream>
#include <string>

#include "sqstack.h"
#include "sqqueue.h"
using std::cout;
using std::endl;
using std::string;


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
			friend std::ostream & operator<<(std::ostream & os, const Node & nd)
			{
				os << "(addr=" << (void *)&nd << ", data=" << nd.data
					<< ", lchild=" << (void *)nd.lchild 
					<< ", rchild=" << (void *)nd.rchild << ")";
				return os;
			}
		};
	public:
		typedef Node<Data> node;
	private:
		node *_root;
		int _node_num;
	private:
		template<typename UnaryOperator>
		void preorder_traverse(node * root, const UnaryOperator & op) ;
		template<typename UnaryOperator>
		void inorder_traverse(node * root, const UnaryOperator & op) ;
		template<typename Cmp>
		void cmp_insert(node * & root, const Data & d, const Cmp & cmp);
		static void show(const Data & d){cout << d <<" ";}
		static Data default_cmp(const Data & a, const Data & b) {return (a - b);};
		bool preinorder_construct(node * & root, const Data * pre, const Data *in, int ct);
		template<typename UnaryOperator>
		void inorder_traversex(node * root, const UnaryOperator & op) ;
		void second_optimal(node * & T, const Data * table, float *sw, int low, int high);
        template<typename key_t, typename cmp_t>
        bool sorted_search(const node * root, const key_t & k, const cmp_t & cmp) const;
        template<typename key_t = Data, typename cmp_t>
        bool sorted_delete(node * & root, const key_t &k , const cmp_t & cmp);
        void sorted_delete(node * & p);
	public:
		bitree():_root(nullptr), _node_num(0){}
		//template<typename UnaryOperator>
		//void test(const UnaryOperator & op);
		/** root fisrt*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void preorder_traverse(const UnaryOperator & op = show);
		/** root second*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void inorder_traverse(const UnaryOperator & op = show);
		template<typename UnaryOperator = void(*)(const Data &)>
		void level_traverse(const UnaryOperator & op = show);
		
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
		
        /** preorder and inorder create*/
		bool preinorder_construct(const Data * pre, const Data *in, int ct){_node_num = ct;return preinorder_construct(_root, pre, in , ct);}
		/** root second, not recursion*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void inorder_traversex(const UnaryOperator & op = show){inorder_traversex(_root, op); cout << endl;}
		static int count(int n) {return fact(2 * n) / fact(n) /fact(n + 1);}
		/** 构造次优查找树的*/
		void second_optimal(const Data * table, float * w, int size);
        int get_levels(int *level) const;
        /** 无重复节点*/
        int get_level(const Data & d) const;
        /** 节点数量*/
        int node_num(void) const {return _node_num;}
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
void bitree<Data>:: 
sorted_construct(const Data * ds, int ct, const Cmp & cmp)
{
	int i;

	for(i = 0; i < ct; i++)
	  cmp_insert(_root, ds[i], cmp);
}

template<typename Data>
template<typename Cmp>
void bitree<Data>:: 
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
    _node_num = size;
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

template<typename Data>
template<typename UnaryOperator>
void bitree<Data>::
level_traverse(const UnaryOperator & op) 
{
    if(_root == nullptr) 
    {
        cout << endl;
        return;
    }
    sqqueue<const node *> queue(_node_num);
    const node * p;

    queue.enqueue(_root);//enqueue root node
    while(!queue.is_empty())
    {
        queue.dequeue(p);
        op(p->data);
        if(p->lchild) queue.enqueue(p->lchild);
        if(p->rchild) queue.enqueue(p->rchild);
    }
    cout << endl;
}


/** 
 * 获取所有节点所在层次
 * return       number of node
 * */
template<typename Data>
int bitree<Data>::
get_levels(int * levels) const
{
    int level = 0, i = 0;;
    if(_root == nullptr) 
    {
        cout << endl;
        return 0;
    }
    sqqueue<const node *> queue(_node_num);
    const node * p;

    queue.enqueue(_root);//enqueue root node
    queue.enqueue(nullptr);// tag of level end
    ++level;
    while(i < _node_num)
    {
        /** visit entire level*/
        do
        {
            queue.dequeue(p);
            if(p == nullptr)//reach end of current level
            {
                ++level;
                break;
            }
            levels[i++] = level;
            if(p->lchild) queue.enqueue(p->lchild);
            if(p->rchild) queue.enqueue(p->rchild);
        }while(1);
        queue.enqueue(nullptr);
    }
    return _node_num;
    //cout << endl;
}


template<typename Data>
template<typename UnaryOperator>
void bitree<Data>::
preorder_traverse(const UnaryOperator & op)
{
    preorder_traverse(_root, op); 
    cout << endl;
}

template<typename Data>
template<typename UnaryOperator>
void bitree<Data>::
inorder_traverse(const UnaryOperator & op)
{
    inorder_traverse(_root, op); 
    cout << endl;
}

/** 
 * 获取节点d所在层次
 * return       0 for not found, > 0 for level of node d
 * */
template<typename Data>
int bitree<Data>::
get_level(const Data & d) const
{
    int level = 0, i = 0;;
    if(_root == nullptr) 
    {
        cout << endl;
        return 0;
    }
    sqqueue<const node *> queue(_node_num);
    const node * p;

    queue.enqueue(_root);//enqueue root node
    queue.enqueue(nullptr);// tag of level end
    ++level;
    //cout << "root->data : " << _root->data << endl;
    while(i < _node_num)
    {
        /** visit entire level*/
        do
        {
            queue.dequeue(p);
            if(p == nullptr)//reach end of current level
            {
                ++level;
                break;
            }
            //cout << "p->data : " << p->data << endl;
            //cout << "level : " << level << endl;
            if(p->data == d) return level;
            if(p->lchild) queue.enqueue(p->lchild);
            if(p->rchild) queue.enqueue(p->rchild);
        }while(1);
        queue.enqueue(nullptr);
    }
    return 0;
    //cout << endl;
}

template<typename Data>
template<typename Cmp>
bool bitree<Data>::
sorted_insert(const Data & d, const Cmp & cmp)
{
	int old = _node_num;
	cmp_insert(_root, d, cmp);
	return (old != _node_num);
}

template<typename Data>
template<typename key_t, typename cmp_t>
bool bitree<Data>::
sorted_search(const key_t & key, const cmp_t & cmp) const
{
    return sorted_search(_root, key, cmp);
}
        
template<typename Data>
template<typename key_t, typename cmp_t>
bool bitree<Data>::
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
bool bitree<Data>:: 
sorted_delete(const key_t &k, const cmp_t & cmp)
{
    return sorted_delete(_root, k, cmp);
}

template<typename Data>
template<typename key_t, typename cmp_t>
bool bitree<Data>:: 
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

/** sorted bitree：delete node p*/
template<typename Data>
void bitree<Data>::
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
    --_node_num;
}

#endif
