## 第九章 查找<a id="9"></a>
>><!--ts-->
>>* <a href="#91">（1）试写出折半查找的递归算法</a><br>
>>* <a href="#92">（2）判别给定二叉树是否为二叉排序树</a><br>
>>* <a href="#93">（3）从小到大输出二叉排序树中所有数据值>=x的结点的数据</a><br>
>>* <a href="#94">（4）二叉排序树查找、插入</a><br>
>>* <a href="#95">（5）求平衡二叉树的高度</a><br>
>>* <a href="#96">（6）散列表中插入和删除关键字</a><br>
>><!--te-->
#### <a  href="#9">（1）试写出折半查找的递归算法。</a> <a id = "91"></a>
 [算法描述]
 
 ```c++
int bin_search(sqtable_t tab, int low, int high, key_t k)
{
    int mid = (low + high) / 2;
    if(low > high) return -1;//not found
    if(tab[mid] == k) return mid;
    else if( k < tab[mid]) return bin_search(tab, low, high - 1, k);
    else return bin_search(tab, low + 1, high, k);
}
```
#### <a  href="#9">（2）试写一个判别给定二叉树是否为二叉排序树的算法。</a><a id = "92"></a>
[题目分析] 根据二叉排序树中序遍历所得结点值为增序的性质，在遍历中将当前遍历结点与其前驱结点值比较，即可得出结论，为此设全局指针变量pre（初值为null）和全局变量flag，初值为true。若非二叉排序树，则置flag为false。
[算法描述]

```c++
bool is_bstree(bitree T, bitree & pre)
{//pre 目前的遍历到的最后一个节点
    if(T)
    {
        /** 中序遍历并判断左子树 */
        if(!is_bstree(T->lchild, pre)) return false;
        else
        {
            if(pre == nullptr) pre = T;//第一个被遍历的节点
            else
            {
                if(pre->data < T->data) pre = T;
                else {return false;}
            }
            return is_bstree(T->rchild, pre);//中序遍历并判断右子树
        }
    }
    return true;//空树
}
```

#### <a  href="#9">（3）已知二叉排序树采用二叉链表存储结构，根结点的指针为T，链结点的结构为（lchild,data,rchild），其中lchild，rchild分别指向该结点左、右孩子的指针，data域存放结点的数据信息。请写出递归算法，从小到大输出二叉排序树中所有数据值>=x的结点的数据。要求先找到第一个满足条件的结点后，再依次输出其他满足条件的结点。</a><a id = "93"></a>
[题目分析] 本题算法之一是如上题一样，中序遍历二叉树，在“访问根结点”处判断结点值是否≥x，如是则输出，并记住第一个≥x值结点的指针。这里给出另一个算法，利用二叉排序树的性质，如果根结点的值>=x,则除左分枝中可能有<x的结点外都应输出。所以从根结点开始查找，找到结点值<x的结点后，将其与双亲断开输出整棵二叉排序树。如果根结点的值<x,则沿右子树查找第一个≥x的结点，找到后，与上面同样处理。

```c++
/** @param  fisrt第一个满足条件的节点初值为nullptr*/
void bstree_be(bstree T, key_t x, bstree & first)
{
    if(T)
    {
        bstree_be(T->lchild, x, first);//中序遍历左子树
        if(T->data >= x) 
        {
            if(!first) first = T;
            cout << T->data;
        }
        bstree_be(T->rchild, x, first);//中序遍历右子树
}
```

#### <a  href="#9">（4）已知二叉树T的结点形式为（lchild,data,count,rchild），在树中查找值为X的结点，若找到，则记数（count）加1，否则，作为一个新结点插入树中，插入后仍为二叉排序树，写出其非递归算法。</a> <a id = "94"></a>
[算法描述]

```c++
bool bstree_search_count(bstree T, const key_t & k, 
        bstree parent, bstree & last)
{//last 最后一个访问的节
    if(!T) {last = parent; return false;}
    /** 找到节点并计数*/
    if(T->data == k){T->data++; return true; last = T;}
    else if(k < T->data) 
        return bstree_search_count(T->lchild, k, T, last);
    else
        return bstree_search_count(T->rchild, k, T, last);
}

void bstree_search_insert(bstree T, const key_t & k)
{
    bstree last = nullptr, newnode = nullptr;
    if(!btree_search_count(T, k, nullptr, last))
    {
        newnode = new bsnode(k, 0, nullptr, nullptr);
        if(!last) last = newnode;//被插结点为新的根结点
        else if(k < last->data) 
            last->lchild = newnode; //被插结点为左孩子
        else last->rchild = newnode;//被插结点为右孩子
    }
}
```

#### <a  href="#9">（5）假设一棵平衡二叉树的每个结点都标明了平衡因子b，试设计一个算法，求平衡二叉树的高度。</a><a id = "95"></a>
[题目分析] 因为二叉树各结点已标明了平衡因子b，故从根结点开始记树的层次。根结点的层次为1，每下一层，层次加1，直到层数最大的叶子结点，这就是平衡二叉树的高度。当结点的平衡因子b为0时，任选左右一分枝向下查找，若b不为0，则沿左（当b=1时）或右（当b=-1时）向下查找。
[算法描述]

```c++
int bbtree_height(bbtree T)
{
    if(T) return 0;
    if(T->bf >= 0) return (1 + bbtree_height(T->lchild));
    else return (1 + bbtree_height(T->rchild));
}
```


#### <a  href="#9">（6）分别写出在散列表中插入和删除关键字为K的一个记录的算法，设散列函数为H，解决冲突的方法为链地址法。</a><a id = "96"></a>
[算法描述]

```c++
struct hash_table
{
    int count, size;
    array<list<data_ t> > lists(size);
};

bool hash_insert(hash_table & tab, const key_t & k)
{
    hcode_t code = H(k);
    
    for(auto p = l.begin(); p != l.end(); ++p)
        if(p->data == k) {cerr << "duplicate\n"; return false;}
    l.append(k);
    return true;
}

bool hash_delete(hash_table & tab, const key_t & k)
{
    hcode_t code = H(k);
    list<data_t> & l = lists[code];
    for(auto p = l.begin(); p != l.end(); ++p)
        if(p->data == k) {l.erase(p); return true;}
    cerr << "not found\n"; return false;
}
```