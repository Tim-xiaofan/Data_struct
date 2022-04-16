# ch-06 二叉树和树
![](./image/mind/06%E4%BA%8C%E5%8F%89%E6%A0%91%E8%84%91%E5%9B%BE.png)

## 6.1 二叉树
### 1. 存储结构
```c
struct binode
{
    elem_t data;
    struct binode * lchild, * rchild;
};
typedef struct binode * bitree;
```
### 2. 先序遍历
先序遍历二叉树的操作定义为∶若二叉树为空，则空操作;否则\
（1）访问根结点;\
（2）先序遍历左子树;\
（3）先序遍历右子树.
```c
void preorder_traverse(bitree t)
{//线序遍历二叉树,递归实现
    if(!t) return;
    visit(t->data);
    preorder_traverse(t->lchild);
    preorder_traverse(t->rchild);
}
```
### 3. 中序遍历
中序遍历二叉树的操作定义为∶若二叉树为空，则空操作;否则\
（1）中序遍历左子树;\
（2）访问根结点;\
（3）中序遍历右子树。
```c
/**
 * 非递归实现
 * 1)当前节点非空，入栈，并更新当前节点为其左子树的根节点。
 * 2)当前节点为空，出栈并访问, 并更新当前节点为其右子树的根节点。
 * 3)重复（1）（2）直到P为NULL并且栈为空则遍历结束。
*/
void inorder_traverse(bitree t)
{
	stack s;
	bitree p = T;
	while(p || !s.empty())
	{
		if(p)
		{
			s.push(p);
			p = p->lchid;
		}
		else
		{
			s.pop(p);
			visit(p->data);
			p = p->rlchid;
		}
	}
}
```
### 4. 哈夫曼树
huffman树只有0度和2度节点,正则二叉树(严格二叉树), 由$ n_0 = n_2 + 1 $ 和 $n = n_0 + 0 + n_2$得 $n = 2n_0 - 1$
```c++
template <typename Data>
huffman_tree<Data>::
huffman_tree(Data * chars, float * weigths, int n)
{
	int i, j, s1, s2;//smalls

	_ct = 2 * n - 1;//huffman树只有0度和2度节点,正则二叉树(严格二叉树)
	_n = n;
	_nds = new node[_ct + 1];// 0 is unused
	_codes = new char*[n];
	_chars = new Data[n + 1];

	memcpy(_chars, chars, sizeof(Data) * n);
	_chars[n] = '\0';

	/** initiate node array*/
	for(i = 1, j = 0; i <= n && j < n; ++i, ++j)
	{//leaves
		_nds[i].weigth = weigths[j];
		_nds[i].parent = 0;
		_nds[i].lchild = 0;
		_nds[i].rchild = 0;
	}
	for(i = n + 1; i <= _ct; ++i)
	{//non-leaves
		_nds[i].weigth = 0;
		_nds[i].parent = 0;
		_nds[i].lchild = 0;
		_nds[i].rchild = 0;
	}
	
	/** construct the tree*/
	for(i = n + 1; i <= _ct; ++i)
	{
        //select the fisrt smallest and second smallest
		select_2s(i - 1, s1, s2);
		_nds[i].lchild = s1;
		_nds[i].rchild = s2;
		_nds[i].weigth = _nds[s1].weigth + _nds[s2].weigth;
		_nds[s1].parent = i;
		_nds[s2].parent = i;
	}

	/** get code for each character : from leaves to root*/
	char * cd = new char[n];
	int start, parent, current;
	cd[n -1] = '\0';
	for(i = 1; i <= n; ++i)
	{
		start =  n - 1;
		for(current = i, parent = _nds[current].parent;
					parent != 0; 
					current = parent, 
                    parent = _nds[current].parent)
		{
			/** from left 0, from right 1*/
			if(_nds[parent].lchild == current) cd[--start] = '0';
			else cd[--start] = '1';
		}
        //malloc memory according to real encode-len
		_codes[i - 1] = new char[n - start];
		strcpy(_codes[i - 1], &cd[start]);
	}
	delete [] cd;
}
```

## 6.2 树
### 1. 存储结构
```c
struct csnode
{
    elem_t data;
    struct csnode * firstchild;//第一个孩子
    struct csnode * nextsibling;//下一个兄弟节点
};
```
### 2. 先根遍历
先访问树的根结点，然后依次先根遍历根的每棵子树
### 3. 后根遍历
先依次后根遍历每棵子树，然后访问根结点

## 6.3 森林
每颗树根节点的访问时机
### 1. 先序遍历
若森林非空，则可按下述规则遍历之∶\
（1）访问森林中第一棵树的根结点;\
（2）先序遍历第一棵树中根结点的子树森林;\
（3）先序遍历除去第一棵树之后剩余的树构成的森林。
### 2. 中序遍历
若森林非空，则可按下述规则遍历之∶\
（1）中序遍历森林中第一棵树的根结点的子树森林;\
（2）访问第一棵树的根结点;\
（3）中序遍历除去第一棵树之后剩余的树构成的森林。

## 6.3 树的计数
二叉树:
$$b_n = C^{n}_{2n} - C^{n-1}_{2n} = \frac{1}{n + 1}C^{n}_{2n}$$
树:
$$t_n = b_{n-1}$$
其中:
$$C^m_n = \frac{n!}{m!(n-m)!}$$