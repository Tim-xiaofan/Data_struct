## 第10章 内部排序<a id="10"></a>
>><!--ts-->
>>* <a href="#101">10.1 概述</a><br>
>>* <a href="#102">10.2 插入排序</a><br>
>>   * <a href="#1021">10.2.1 直接插入排序</a><br>
>>   * <a href="#1022">10.2.2 其他插入排序</a><br>
>>   * <a href="#1023">10.2.3 希尔排序</a><br>
>>* <a href="#103">10.3 快速排序</a><br>
>>   * <a href="#1031">10.3.1 冒泡排序</a><br>
>>   * <a href="#1032">10.3.2 快速排序</a><br>
>>* <a href="#104">10.4 选择排序</a><br>
>>    * <a href="#1041">10.4.1 简单选择排序</a><br>
>>    * <a href="#1042">10.4.2 树形选择排序</a><br>
>>    * <a href="#1043">10.4.3 堆排序</a><br>
>>* <a href="#105">10.5 归并排序</a><br>
>>* <a href="#106">10.6 基数排序</a><br>
>>    * <a href="#1061">10.6.1 多关键字的排序</a><br>
>>    * <a href="#1062">10.6.2 链式基数排序</a><br>
>>* <a href="#107">10.7 各种内部排序方法的比较讨论</a><br>
>><!--te-->
### <a href="#10">10.1 概述<a> <a id="101"></a>
（1）为了查找方便，通常希望计算机中的表是按关键字有序的<br>
（2）排序方法是否稳定<br>
（3）内部排序：内存<br>
（3）外部排序：内存 + 外存<br>
（4）依据的不同原则： 插入排序、交换排序、选择排序，归并排序和计数排序<br>
（5）工作量：简单的排序方法$O(n^2)$，先进的排序$O(nlogn)$，基数数排序$O(d * n)$<br>
（6）操作：比较和移动<br>
### <a href="#10">10.2 插入排序<a> <a id="102"></a>
#### <a href="#10">10.2.1 直接插入排序<a> <a id="1021"></a>
<b>基本操作:</b> 将一个记录插入到已排好序的有序表中，从而得到一个新的、记录数增1的有序表

```c++
void insert_sort(sqtable & a)
{//O(n ** 2)
    int len = a.length(), i = 1, j, k;
    data_t tmp;
    /** 跳过有序子序列*/
    while (i < len && a[i] > a[i -1]) ++i;
    for(; i < len; ++i)
    {
        if(a[i] >= a[i - 1]) continue;//已经是正确位置
        for(j = 0; j < i - 1; ++j) //顺序查找a[i]插入0...i-1位置
          if(a[i] < a[j]) break;
        tmp = a[i];
        for(k = i - 1; k >= j; --k) a[k + 1] = a[k];//移动
        a[j] = tmp;//插入
    }
}
```
#### <a href="#10">10.2.2 其他插入排序<a> <a id="1022"></a>
<b>1.折半插入排序</b><br>
这个"查找"操作可利用"折半查找"来实现

```c++
int bin_locate(const sqtable & a const key_t & k, int start, int end)
{
    int l = start, h = end, mid;
    while(l <= h)
    {
        mid = (l + h) / 2;
        if(k < a[mid] ) h = mid - 1;//左半区
        else l = mid + 1;
    }
    return l + 1;
}
void binsert_sort(sqtable & a)
{//O(n ** 2)
    int len = a.length(), i = 1, j, k;
    data_t tmp;
    /** 跳过有序子序列*/
    while (i < len && a[i] > a[i -1]) ++i;
    for(; i < len; ++i)
    {
        if(a[i] >= a[i - 1]) continue;//已经是正确位置
        j = bin_locate(a, a[i], 0, i - 1);//折半查找a[i]插入0...i-1的位置
        tmp = a[i];
        for(k = i - 1; k >= j; --k) a[k + 1] = a[k];//移动
        a[j] = tmp;//插入
    }
}
```

<b>2.2-路插入排序</b><br>
（1）其目的是减少排序过程中移动记录的次数，但为此需要n个记录的辅助空间<br>
（2）时间复杂度仍是$O(n^2)$。<br>
（3）当table[0]是待排序记录中关键字最小或最大的记录时，2-路插入排序就完全失去它的优越性<br>
（4）移动记录的次数约为$\frac{n^2}{8}$<br>
<img src="./image/10-2二路插入排序.png" alt="10-2二路插入排序" width="400"><br>
<b>[算法描述]</b><br>
并将d[0]看成是在排好序的序列中处于中间位置的记录，然后从第2个记录起依次插入到d[0]之前或之后的有序序列中

```c++
void towway_insert(sqtable & tab)
{
    int len = tab.length() + 1, first = 0, last = 1, i, j ,k;
    data_t * d = new data_t[len + 1], tmp;
    d[0] = tab[0];

    for(i = 1; i < tab.length(); ++i)
    {
        tmp = tab[i];
        if(tmp < tab[0])//插入d[0]前面的子序列
        {
            if(first == 0)
            {
                first = len - 1;
                d[fisrt] = tmp;
            }
            else
            {
                /** 寻找插入位置*/
                for(j = len - 1; j >= first; --j)
                    if(tmp > d[j]) break;
                /** first...j序列左移*/
                for(k = fisrt; k <= j; ++k) d[k - 1] = d[k];
                d[j] = tmp; --first;
            }
        }
        else//插入d[0]后面的子序列
        {
            /** 寻找插入位置*/
            for(j = 0; j < last; ++j)
                if(tmp < d[j]) break;
            /** j...last序列右移*/
            for(k = last - 1; k >= j; --k) d[k + 1] = d[k];
            d[j] = tmp; ++last;
        }
    }
    /** 复制排序结果到原表*/
    for(i = 0, j = first; j != last; ++i, j = (j + 1) % len)
        tab[i] = d[j];
    delete [] d;
}
```

<b>3.表插入排序</b><br>
（1）若希望在排序过程中不移动记录，只有改变存储结构，进行表插入排序<br>
（2）以修改2n次指针值代替移动记录，排序过程中所需进行的关键字间的比较次数相同<br>
（3）时间复杂度仍是$O(n^2)$<br>
（4）结果只是求得一个有序链表，则只能对它进行顺序查找，不能进行随机查找<br>
（5）为了能实现有序表的折半查找，尚需对记录进行重新排列<br>
<img src="./image/10-3表插入排序.png" alt="10-3表插入排序" width="400"><br>
<b>[算法描述]</b><br>
它可以用一个数组来初始化，初始化用头元素和第一个元素组成一个循环链表，然后排序时从第二
个元素开始插入到这个循环链表中，当然只是修改每个元素的next域。使头结点的next域始终指示
最小的那个元素，然后依次向下：每一个元素的next域都指示比它稍大的那个元素。最大的元素的
next域指示头结点。这样形成一个循环链表。

#### <a href="#10">10.2.3 希尔排序<a> <a id="1023"></a>
（1）"缩小增量排序"（Diminishing Increment Sort），它也是一种属插入排序类的方法。<br>
（2）基本思想∶ 先将整个待排记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录"基本有序"时，再对全体记录进行一次直接插人排序。<br>
<img src="./image/10-5希尔排序.png" alt="10-5希尔排序" width="400"><br>
（3）特点∶子序列的构成不是简单地"逐段分割"，而是将相隔某个"增量"的记录组成一个子序列。<br>

```c++
int shell_sort(sqtable & tab, int * delta, int ct)
{
    if(delta[ct -1] != 1) return -1;
    for(int i = 0; i < ct; ++i)
        shell_insert(tab, delta[i]);//一趟增量为dlta[k]的插人排序
    return 0;
}

void shell_insert(sqtable & tab, int dk)
{
    for(int i = 0; i < tab.length(); ++i)//对每个子表进行插入排序
        shell_insert(tab, i, dk);
}

void shell_insert(sqtable & tab, int start, int dk)
{//直接插入排序
    data_t tmp; 
    int i, j, k;
    for(i = start + dk; i < tab.length(); i += dk)
    {
        if(tab[i] > tab[i - dk]) continue;//已经是正确位置
        tmp = tab[i];
        for(j = start; j < i; j+=dk)//顺序搜索tab[i]插入位置
            if(tmp < tab[j]) break;
        for(k = i - dk; k >= j; k-=dk)//右移
            tab[k + 1] = tab[k];
        tab[j] = tmp;//插入
    }
}
```

### <a href="#10">10.3 快速排序<a> <a id="103"></a>
一类藉助"交换"进行排序的方法
#### <a href="#10">10.3.1 起泡排序<a> <a id="1031"></a>
<b>[基本思路]</b><br>
（1）趟：若相邻两个元素逆序，则交换。最多$n-1$轮（逆序）<br>
（2）结束的条件应该是"在一趟排序过程中没有进行过交换记录的操作"<br>
（3）最差情况（逆序）：$\frac{n(n - 1)}{2}$，总的时间复杂度为$O(n^2)$。<br>

```c++
void bubble_sort(sqtable & a)
{
    int len = a.length();
    bool swapped;
    for(int i = 0; i < len - 1; ++i)
    {//第i轮排序, 最多n-1轮
        swapped = false;
        for(j = 0; j < len - 1 - i; ++j)
            if(a[i] > a[i + 1])
            { 
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        if(!swapped) break;//为发生交换
    }
}
```

#### <a href="#10">10.3.2 快速排序<a> <a id="1032"></a>
<b>[基本思想]</b><br>
它的基本思想是，通过一趟排序将待排记录分割成独立的两部分，其中一部分记录的关键字均比另一部分记录的关键字小，则可分别对这两部分记录继续进行排序，以达到整个序列有序<br>
<b>[具体做法]</b><br>
附设两个指针 low 和 high，它们的初值分别为 low 和 high，设枢轴记录的关键字为 pivotkey，则首先从 high 所指位置起向前搜索找到第一个关健字小于 pivotkey 的记录和枢轴记录互相交换，然后从 low 所指位置起向后搜索，找到第一个关键字大于 pivotkey 的记录和枢轴记录互相交换，重复这两步直至 low=high为止。

```c++
void quick_sort(sqlist & a, int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = quick_partition(a, low, high);
        quick_sort(a, low, pivot - 1);
        quick_sort(a, pivot + 1, high);
    }
}

int quick_partition(sqlist & a, int low, int hign)
{
    int pivot = a[low];
    while(low < high)
    {
        while(low < high && a[high] >= pivot) --high;
        a[low] = a[high];// 将比枢轴记量小的记录移到低端
        while(low < high && a[low] <= pivot) --low;
        a[high] = a[low];// 将比枢轴记录大的记录移到高端
    }
    a[low] = pivot;
    return low;
}
```
<b>[性能]</b><br>
（1）所有同数量级$O(nlogn)$的排序方法中，其<b>平均性能</b>最好<br>
（2）最坏情况：若初始记录序列按关键字有序或基本有序时，快速排序将蜕化为起泡排序，其时间复杂度为 $O(n^2)$

### <a href="#10">10.4 选择排序<a> <a id="104"></a>
选择排序（Selection Sort）的基本思想是∶每一趟在 n-i+1（i=1，2，…，n-1）个记录
中选取关键字最小的记录作为有序序列中第i个记录。
#### <a href="#10">10.4.1 简单选择排序<a> <a id="1041"></a>
一趟简单选择排序的操作为∶通过$n-i$次关键字间的比较，从$n-i+1$个记录中选
出关键字最小的记录，并和第 i（1≤i≤n）个记录交换之
```c++
void simple_select(sqtable & a)
{
    int min;
    for(int i = 0; i < a.length() -1; ++i)
    {
        min = i;
        for(int j = i; j < a.length(); ++j)
            if(a[j] < a[min]) min = j;
        if(min != i) swap(a[min], a[i]);
    }
}
```
（1）时间复杂度为 $O(n^2)$<br>
（2）改进：利用前i-1次比较所得信息，则可减少以后各趟选择排序中所用的比较次数

#### <a href="#10">10.4.2 树形选择排序<a> <a id="1042"></a>
（1）首先对 n 个记录的关键字进行两两比较，然后在其中$\lceil \frac{n}{2} \rceil$个较小者之间再进行两两比较，如此重复，直至选出最小关键字的记录为止。<br>
（2）一棵有n个叶子结点的完全二叉树表示，深度为$\lceil log_2n\rceil + 1$<br>
（3）除了最小关键字之外，每选择一个次小关键字仅需进行$\lceil log_2n \rceil$次比较，因此，它的时间复杂度为 $O(nlogn)$<br>
（4）有辅助存储空间较多、和"最大值"进行多余的比较<br>
<img src="./image/10-9树型选择排序.png" alt="10-9树型选择排序" width="450"><br>

#### <a href="#10">10.4.3 堆排序<a> <a id="1043"></a>
（1）只需要一个记录大小的辅助空间<br>
（2）n个元素的序列{$k_1, k_2,...,k_n$}当且仅当满足下关系时，称之为堆:
$$ 
\left\{
\begin{aligned}
k_i & \le & k_{2i} \\
k_i & \le & k_{2i + 1} \\
\end{aligned}
\right.
\qquad 或 \qquad
\left\{
\begin{aligned}
k_i & \ge & k_{2i} \\
k_i & \ge & k_{2i + 1} \\
\end{aligned}
\right.
\qquad
$$
$$
(i = 1, 2, ..., \lceil \frac{n}{2} \rceil)
$$
（2）完全二叉树中所有非终端结点的值均不大于（或不小于）其左、
右孩子结点的值。<br>
<img src="./image/10-10堆.png" alt="10-9堆" width="450"><br>
{96,83,27,38,11,09}<br>
{12,36,24,85,47,30,53,91}

<b>[建立算法]</b><br>
（1）从一个无序序列建堆的过程就是一个反复"筛选"的过程。若将此序列看成是一个完全二叉树，
则最后一个非终端结点是第$\lfloor \frac{n}{2} \rfloor$个元素，由此"筛选"只需从第$\lfloor \frac{n}{2} \rfloor$个元素开始。<br>
（2）中先建一个"大顶堆"，即先选得一个关键字为量大的记录并与序列中最后一个记录交换，然后对序列中前n-1记录进行筛选，重新将它调整为一个"大顶堆"，如此反复直至排序
结束<br>
（3）堆排序在最坏的情况下，其时间复杂度也为 $O(nlogn)$

```c++
/**
 * 已知[s...m]中记录的关键字除[s]之外均满足堆的定义，本函教调整[s]的关键字，
 * 使[s...m]成为一个大顶堆（对其中记录的关键字而言）
 * */
void heap_adjust(sqtable &a, int s, int m)
{//筛选：应沿关键字较大的孩子结点向下进行
    data_t rc = a[s];
    for (int i = s * 2 + 1; i <= m; i = i * 2 + 1)
    {
        if (i < m && a[i] < a[i + 1]) ++i;//i = max(lchild, rchild)
        if (rc >= a[i]) break;
        a[s] = a[i]; //s is max
        s = i;//s is root
    }
    h[s] = rc;
}
void heap_sort(sqtable &a)
{
    int len = a.length();
    /** 把[0...len-1]建成大顶堆*/
    for (int i = len / 2 - 1; i >= 0; --i)
        heap_adjust(a, i, len - 1);
    for (int i = len - 1; i >= 0; --i)
    {
        swap(H[0], H[i]);
        heap_adjust(a, 0, i - 1);
    }
}
```
从大顶堆开始排序\
<img src="./image/10-xx堆排序.png" alt="10-xx堆排序" width="700"><br>

### <a href="#10">10.5 归并排序<a> <a id="105"></a>
（1）"归并"的含义是将两个或两个以上的有序表组合成一个新的有序表。<br>
（2）实现归并排序需和待排记录等数量的辅助空间，其时间复杂度为O(nlogn)<br>
（3）快速排序和堆排序相比，归并排序的最大特点是，它是—种稳定的排序方法<br>
<img src="./image/10-13归并排序.png" alt="10-13归并排序" width="450"><br>

```c++
void merge(sqtable & a, int low, int mid, int high)
{//合并有序子序列[low...mid]和[mid + 1...high]
    data_t tmp = new data_t[low - high + 1];//辅助空间
    int i, j, k;
    for(i = low, j = mid + 1, k = 0; i <= mid && j <= high;)
    {
        if(a[i] < a[j]) tmp[k++] = a[i++];
        else if(a[i] == a[j]) {tmp[k++] = a[i++]; tmp[k++] = a[j++];}
        else tmp[k++] = a[j++];
    }
    while(i <= mid) tmp[k++] = a[i++];//处理剩余
    while(j <= high) tmp[k++] = a[j++];
    for(i = 0; i < k; ++i) a[low + i] = tmp[i];//保存合并后序列
    delete [] tmp;
}
void merge_sort(sqtable & a, int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}
```

### <a href="#10">10.6 基数排序<a> <a id="106"></a>
#### <a href="#10">10.6.1 多关键字的排序<a> <a id="1061"></a>
（1）最高位优先：逐层分割成若干子序列，然后对各子序列分别进行排序。<br>
（2）最低位优先：不必分成子序列，对每个关键字都是整个序列参加排序。<br>
（3）可以不利用前几节所述各种通过关键字间的比较来实现排序的方法，而是通过
若干次"分配"和"收集"来实现排序。<br>
（4）仍需要n个记录和 2*RADIX 个计数单元的辅助空间<br>

#### <a href="#10">10.6.2 链式基数排序<a> <a id="1062"></a>
<img src="./image/10-14链式计数排序.png" alt="10-14链式计数排序" width="450"><br>

### <a href="#10">10.7 各种内部排序方法的比较讨论<a> <a id="107"></a>
| 排序方法   | 平均时间  | 最坏情况 | 辅助存储 |稳定性|具体算法|
|  :----    | :----    |:----    |:----   | :---- | :---- |
| 简单排序   | $O(n_2)$ | $O(n_2)$ | $O(1)$ |稳定|<a href="#1021">直接插入</a>、<a href="#1022">折半插入</a>、<a href="#1023">2-路插入</a>、<a href="#1031">起泡</a>、<a href="#1041">简单选择</a>|
| <a href="#1032">快速排序</a>  | $O(nlogn)$ | $O(n_2)$ | $O(logn)$ |不稳定||a
| <a href="#1043">堆排序 </a>| $O(nlogn)$ | $O(nlogn)$ | $O(1)$ |不稳定||
| <a href="#105">归并排序</a> | $O(nlogn)$ | $O(nlogn)$ | $O(n)$ |稳定||
| <a href="#106">基数排序</a>| $O((n + rd)d)$ | $O((n + rd)d)$| $O(rd)$|稳定||


（1）记录很大（即每个记录所占空间较多）时，移动时间耗费很大，此时可采用静态链表作存储结构：如表插入排序、链式基数排序，以修改指针代替移动记录。<br>
（2）快速排序和堆排序，无法实现表排序。在这种情况下可以进行"地址排一个地址向量指示相应记录。同时在排序过程中不移动记录而移动地址向量中相应分量的内容<br>
<img src="./image/10-15地址排序.png" alt="10-15地址排序" width="500"><br>
（3）借助于"比较"进行排序的算法在最坏情况下能达到的最好的时间复杂度为 $O(nlogn)$。
