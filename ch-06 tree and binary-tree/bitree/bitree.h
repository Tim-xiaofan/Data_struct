/** 20210415 12:45, zyj, GuangDong*/
// bitree.h -- binary tree
#ifndef BITREE_H
#define BITREE_H
#include <iostream>
#include <string>
#include <vector>
#include "sqstack.h"
#include "sqqueue.h"
#include "List.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

#ifndef MAX_NUM_NODE 
#define MAX_NUM_NODE 128
#endif


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
			int bf;//平衡因子
			Node *lchild, *rchild;
			Node():bf(0), lchild(nullptr), rchild(nullptr){}
			friend std::ostream & operator<<(std::ostream & os, 
                        const Node & nd)
			{
				os << "(addr=" << (void *)&nd << ", data=" << nd.data
					<< ", lchild=" << (void *)nd.lchild 
					<< ", rchild=" << (void *)nd.rchild << ")";
				return os;
			}
		};
        template<typename Data1>
        struct Edge
        {
            Data1 tail, head;
            Edge(const Data1 &t, const Data1 & h) : tail(t), head(h){}
            Edge(){}
            friend std::ostream & operator<<(std::ostream & os, 
                        const Edge & e)
            {
                os << e.tail << " " << e.head;
                return os;
            }
        };
	public:
		typedef Node<Data> node;
        typedef Edge<Data> edge;
	protected:
		node *_root;
		int _node_num;
	protected:
		static void show(const Data & d){cout << d <<" ";}
	private:
		template<typename UnaryOperator>
		void preorder_traverse(node * root, const UnaryOperator & op) ;
		template<typename UnaryOperator>
		void inorder_traverse(node * root, const UnaryOperator & op) ;
		static Data default_cmp(const Data & a, const Data & b) {
            return (a - b);};
		bool preinorder_construct(node * & root, const Data * pre,
                    const Data *in, int ct);
		template<typename UnaryOperator>
		void inorder_traversex(node * root, const UnaryOperator & op) ;
		void second_optimal(node * & T, const Data * table,
                    float *sw, int low, int high);
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
		
        /** preorder and inorder create*/
		bool preinorder_construct(const Data * pre, const Data *in, int ct)
        {
            _node_num = ct;
            return preinorder_construct(_root, pre, in , ct);
        }
		/** root second, not recursion*/
		template<typename UnaryOperator = void(*)(const Data &)>
		void inorder_traversex(const UnaryOperator & op = show)
        {
            inorder_traversex(_root, op); 
            cout << endl;
        }
		static int count(int n) {return fact(2 * n) / fact(n) /fact(n + 1);}
		/** 构造次优查找树的*/
		void second_optimal(const Data * table, float * w, int size);
        /** 输出所有节点的层次*/
        int get_levels(int *level) const;
        /** 无重复节点：输出节点D的层次*/
        int get_level(const Data & d) const;
        /** 节点数量*/
        int node_num(void) const {return _node_num;}
        /** 按层次输出边*/
        int get_edges(edge * E, int size) const;
		void show_edges(void) const;
        /** 最大路径*/
        int longest_path(vector<Data> & path) const;
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
	sqstack<node *> stack(_node_num);
	node * pn = root;
	while(!stack.is_empty() || pn)
	{
		if(pn)
		{//根指针进栈.遍历左子树
			stack.push(pn);
			pn = pn->lchild;
		}
		else
		{//根指针退栈.访问根结点，遍历右子树
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

        

/** return number of edge*/
template <typename Data>
int bitree<Data>::
get_edges(edge * E, int size) const
{
    int i = 0;
    if(size < _node_num -1)
      return 0;
    
    if(_root == nullptr) 
    {
        return 0;
    }
    sqqueue<const node *> queue(_node_num);
    const node * p;

    queue.enqueue(_root);//enqueue root node
    while(!queue.is_empty())
    {
        queue.dequeue(p);
        if(p->lchild) 
        {
            E[i++] = edge(p->data, p->lchild->data);
            queue.enqueue(p->lchild);
        }
        if(p->rchild) 
        {
            E[i++] = edge(p->data, p->rchild->data);
            queue.enqueue(p->rchild);
        }
    }
    return i;
}

template<typename Data>
void bitree<Data>::
show_edges(void) const
{
	edge E[MAX_NUM_NODE];
	int ret, i;

	ret = get_edges(E, MAX_NUM_NODE);
	cout << "edges : ";
	for(i = 0; i < ret; ++i)
	  cout << E[i] << "  ";
	cout << endl;
}

template<typename Data>
int bitree<Data>::
longest_path(vector<Data> & path) const
{
    sqstack<node *> stack(_node_num);
	node * p = _root;
    bool *rvisited = new bool[_node_num];
    
    if(!_root) return 0;
    
    for(int i = 0; i < _node_num; ++i) rvisited[i] = false;
	
    while(!stack.is_empty() || p)
	{
        while(p)
        {
            if(!stack.push(p))
              return -1;
            p = p->lchild;
        }
        if(rvisited[stack.length() -1])
        {
            stack.get_top(p);
            if(!p->lchild && !p->rchild) 
            {
                if(stack.length() > path.size())
                {
                    path.clear();
                    for(int i = 0; i < stack.length(); ++i)
                      path.push_back(stack[i]->data);
                }
                stack.pop(p);
            }
        }
        else
        {
            rvisited[stack.length() -1] = true;
            stack.get_top(p);
            p = p->rchild;
        }
	}
    delete [] rvisited;
    return 0;
}

#endif
