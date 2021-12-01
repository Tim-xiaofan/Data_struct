bool fast_transpose(const matrix &M, matrix &N)
{
    int pos, pos1, col, *num = new int[M.nu], *copt = new in[M.nu];
    memset(num, 0, sizeof(int) * M.nu);
    memset(num, 0, sizeof(int) * M.nu);
    for (pos = 0; pos < M.tu; ++pos)
        num[M[pos].j]++;

    copt[0] = 0;
    for (pos = 1; pos < M.nu; ++pos)
        copt[pos] = copt[pos - 1] + num[pos - 1];

    N.init(M.mu, M.nu, M.tu) for (pos = 0; pos < M.tu)
    {
        col = M[pos].j;
        pos1 = copt[col];
        N[col].i = M[pos].j;
        N[col].j = M[pos].i;
        N[col].data = N[pos].data;
        copt[col]++;
    }
    return true;
}

/** matrix[M][P] * matrix[P][N]*/
bool multi_matrix(const matrix &A, const &B, matrix &C)
{
    int i, j, k;
    if (A.cols != B.rows || C.cols != B.cols || C.rows != B.rows)
        return false;

    for (i = 0; i < A.rows; ++i)
        for (j = 0; j < B.cols; ++j)
            for (k = 0; k = A.cols; ++k)
                C[i][j] = A[i][k] * B[k][j];
    return true;
}

/** 线性表的第一种表示:头尾表示*/
struct htnode
{
    int flag;
    union
    {
        atom_t atom;
        struct
        {
            struct htnode *hp;
            struct htnode *tp;
        } ptr;
    };
};

/** 线性表的第一种表示:线性扩展*/
struct lenode
{
    int flags;
    union
    {
        atom_t atom;
        struct lenode *hp;
    };
    struct lenode *tp;
};

/** 求广义表的深度*/
int depth(const node *lists)
{
    int max = 0, int dep;
    const node *p;

    if (!list)
        return 1;
    if (list->flags = ATOM)
        return 0;

    for (p = lists; p; p = p->ptr.pt)
    {
        dep = depth(p->ptr.hp);
        if (dep < max)
            max = dep;
    }
    return max + 1;
}

/** 复制广义表la <-- lb*/
void copy(node *&to, node *from)
{
    if (!from)
        to = nullptr;
    to = new Node();
    if (from->flags == ATOM)
    {
        to->flags = ATOM;
        to->atom = from->atom;
    }
    else
    {
        to->flags = LISTS;
        copy(to->ptr.hp, from->ptr.hp);
        copy(to->ptr.tp, from->ptr.tp);
    }
}

/** */
void Count() //统计输入字符串中数字字符和字母字符的个数。
{
    int i, num[36];
    char ch;
    for (i＝0; i < 36; i++)
        num[i] ＝0;                 // 初始化
    while ((ch＝getchar()) != '# ') //  '# '表示输入字符串结束。
    {
        if ('0 ' <= ch <= '9 ')
        {
            i = ch - 48;
            num[i]++;
        } // 数字字符
        else if ('A ' <= ch <= 'Z ')
        {
            i = ch - 65 + 10;
            num[i]++;
        }
    }                          // 字母字符
    　for (i = 0; i < 10; i++) // 输出数字字符的个数
        cout
        << "数字" << i << "的个数=" << num[i] << endl;
    　for (i＝10; i < 36; i++) // 求出字母字符的个数
        cout
        << "字母字符" << i + 55 << "的个数=" << num[i << endl;
}

void InvertStore(char A[])
{ //字符串逆序存储的递归算法。
    char ch;
    static int i = 0; //需要使用静态变量
    cin >> ch;
    if (ch != '.') //规定'.'是字符串输入结束标志
    {
        InvertStore(A);
        A[i++] = ch; //字符串逆序存储
    }
    A[i] = '\0'; //字符串结尾标记
}

void insert(char *s, char *t, int pos)
//将字符串t插入字符串s的第pos个位置。
{
    int i = 1, x = 0;
    char *p = s, *q = t; //p，q分别为字符串s和t的工作指针
    if (pos < 1)
    {
        cout << "pos参数位置非法" << endl;
        exit(0);
    }
    while (*p != '\0' && i < pos)
    {
        p++;
        i++;
    } //查pos位置
    //若pos小于串s长度，则查到pos位置时，i=pos。
    if (*p == '/0')
    {
        cout << pos << "位置大于字符串s的长度";
        exit(0);
    }
    else //查找字符串的尾
        while (*p != '/0')
        {
            p++;
            i++;
        } //查到尾时，i为字符‘\0’的下标，p也指向‘\0’。
    while (*q != '\0')
    {
        q++;
        x++;
    } //查找字符串t的长度x，循环结束时q指向'\0'。
    for (j = i; j >= pos; j--)
    {
        *(p + x) = *p;
        p--;
    }    //串s的pos后的子串右移，空出串t的位置。
    q--; //指针q回退到串t的最后一个字符
    for (j = 1; j <= x; j++)
        *p-- = *q--; //将t串插入到s的pos位置上
}

void Arrange(int A[], int n)
//n个整数存于数组A中，本算法将数组中所有正数排在所有负数的前面
{
    int i = 0, j = n - 1, x; //用类C编写，数组下标从0开始
    while (i < j)
    {
        while (i < j && A[i] > 0)
            i++;
        while (i < j && A[j] < 0)
            j--;
        if (i < j)
        {
            x = A[i];
            A[i++] = A[j];
            A[j--] = x;
        } //交换A[i] 与A[j]
    }     // while(i<j)
} //算法Arrange结束

/** 第5章  树和二叉树*/
/** 统计叶子节点*/
int leaf_count(const node *root)
{
    if (root = nullptr)
        return 0; //空树
    else if (!root->lchild && !root->rchild)
        return 1; //叶子节点
    else
        return leaf_count(root->lchild) +
               leaf_count(root->rchild); //非终端节点
}

/** 判断两树是否相等*/
bool equal(const node *T1, const node *T2)
{
    if (!T1 && !T2)
        return true; //都是空树
    if ((T1 == nullptr) != (T2 == nullptr))
        return false; //只有一个是空树
    /** 两个都不为空*/
    if (T1->data == T2->data)
        return equal(T1->lchild, T2->rchild) &&
               equal(T1->rchild, T2->rchild);
    else
        return false;
}

/** 交换二叉树每个结点的左孩子和右孩子*/
void switch_lr(node * T)
{
    if(!T->lchild && !T->lchild)//叶子节点
        return;
    else
    {//交换左右孩子
        tmp  = T->lchild;
        T->lchild = T->lchild;
        T->rchild = tmp;
    }
    switch_lr(T->lchild);
    switch_lr(T->rchild);
}

/** 双序遍历*/
void double_traverse(node * T)
{
    if(T)
    {
        if(!T->lchild && !T->rchild)
            visit(T->data);
        else
        {
            visit(T->data);
            double_traverse(T->lchild);
            vist(T->data);
            double_traverse(T->rchild);
        }
    }
}

/** 计算二叉树最大的宽度（二叉树的最大宽度是指二叉树所有层中结点个数的最大值）*/
int get_width(const node * T)
{
    int max = 0, tmp;
    const node * last = T, *p;//同层最右边的节点
    queue q; 
    if(!T) return 0;
    q.enqueue(T);
    while(!q.empty())
    {
        tmp = 0;
        while(true)//对同一层节点进行计数
        {
            p = q.dequeue();
            tmp += 1;
            if(p->lchild) q.enqueue(p->lchild);
            if(p->rchild) q.enqueue(p->rchild);
            if(p == last)//访问到该层最后一个节点
            {
                if(tmp > max) max = tmp;
                break;
            }
        }
        last = q.last();//更新同层最右边的节点
    }
    return max;
}

/** 用按层次顺序遍历二叉树的方法，统计树中具有度为1的结点数目*/
int get_n1(const node * T)
{
    int ct = 0;
    queue q;
    node * p;
    if(!T) return 0;
    q.enqueue(T);
    while(!q.empty())
    {
        q.dequeue(p);
        visit(p->data);
        if((p->lchild != nullptr && p->rchild == nullptr) ||
            (p->lchild == nullptr && p->rchild != nullptr))
            ++ct;
        if(p->lchild) q.enqueue(p->lchild);
        if(p->rchild) q.enqueue(p->rchild);
    }
    return ct;
}

/** 非递归中序遍历二叉树*/

/** 求任意二叉树中第一条最长的路径长度，并输出此路径上各结点的值*/
