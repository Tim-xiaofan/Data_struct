/** 20210922, zyj, GuangDong*/
#ifndef _K_MERGE_H
#define _K_MERGE_H

template<typename T, int k = 5>
class k_merge
{
    public:
        typedef int loser_tree[k];//败者树是宪全二叉树且不含叶子，可采用顺序存储结构
        typedef T external[k + 1];//叶结点，只存放待归并记录的关键字
    private:
        loser_tree _ls;
        external _b;
        void create_loser_tree(const external & b);
        void adjust(int i);
    public:
};


/** 沿从叶子结点b[s]到根结点ls[0]的路径调整败者树*/
template<typename T, int k>
void k_merge<T, k>::
adjust(int s)
{
    /** ls[t]是b[s]的双亲结点*/
    int t = (s + k) / 2, tmp;

    while(t > 0)
    {
        /** s指示新的胜者 */
        if(_b[s] > _b[_ls[t]])
        {
            tmp = s;
            s = _ls[t];
            _ls[t] = s;
            t = t / 2;
        }
    }

    _ls[0] = s;
}

/**
  已知b[0]到b[k-1]为完全二叉树ls的叶子结点存有k个关键字，沿从叶子
  到根的k条路径将ls调整成为败者树。
  */
template<typename T, int k>
void k_merge<T, k>::
create_loser_tree(const external & b)
{
    int i;

    for(i = 0; i < k + 1; ++i)
      _b[i] = b[i];

    /** 设置ls中"败者"的初值*/
    for(i = 0; i < k; ++i)
      _ls[i] = k;

    /** 次从b[k-1], b[k-2],...,b[0]出发调*/
    for(i = k -1; i >= 0; --i) 
      adjust(_ls, i);
}
#endif
