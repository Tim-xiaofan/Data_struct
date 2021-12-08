## 第九章 查找<a id="9"></a>
>><!--ts-->
>>* <a href="#91">9.1 静态查找表</a><br>
>>   * <a href="#911">9.1.1 顺序表的查找</a><br>
>>   * <a href="#912">9.1.2 有序表的查找</a><br>
>>      * <a href="#9121">折半查找</a><br>
>>      * <a href="#9122">其他：斐波那契查找、插值查找</a><br>
>>   * <a href="#913">9.1.3 静态树的查找</a><br>
>>      * <a href="#9121">次优查找树</a><br>
>>   * <a href="#914">9.1.4 索引顺序表的查找</a><br>
>>* <a href="#92">9.2 动态查找表</a><br>
>>   * <a href="#921">9.2.1 二叉排序树和平衡二叉树</a><br>
>>   * <a href="#922">9.2.2 B-树和B+树</a><br>
>>   * <a href="#923">9.2.3 键树</a><br>
>>* <a href="#93">9.3 哈希表</a><br>
>>    * <a href="#932">9.3.2 哈希函数的构造方法</a><br>
>>    * <a href="#933">9.3.3 处理冲突的方法</a><br>
>>    * <a href="#934">9.3.4 哈希表的查找及其分析</a><br>
>><!--te-->
### <a href="#9">9.1 静态查找表<a> <a id="91"></a>
#### <a href="#9">9.1.1 顺序表的查找<a> <a id="911"></a>
查找操作的性能衡量-均查找长度ASL：<br>
<!--\overset{顶部内容}{正常内容}, \underset{底部内容}{正常内容}-->
ASL = $\underset{i = 1}{\overset{n}{\sum}}P_iC_i$ $\qquad$
$\underset{i = 1}{\overset{n}{\sum}}P_i = 1$ <br>
$P_i$为查找表中第i个记录的概率<br>
$C_i$为找到表中其关键字与给定值相等的第i个记录时，和给定值已进行过比较的关键字个数。<br>
<b>等概率</b>情况下顺序查找的平均查找长度为：<br>
${ASL}_{ss} = \frac{1}{n}\underset{i = 1}{\overset{n}{\sum}}(n - i + 1) 
= \frac{n + 1}{2}$<br>
假设查找成功与不成功的可能性相同，对每个记录的查找<b>概率也相等</b>，则$P=\frac{1}{2n}$，此时顺序查找的平均查找长度为:<br>
$${ASL}_{ss} = \frac{1}{2n}\underset{i = 1}{\overset{n}{\sum}}(n - i + 1) + \frac{n+ 1}{2} = \frac{3}{4}(n + 1)$$

#### <a href="#9">9.2.1 有序表的查找<a> <a id="912"></a>
#### 折半查找--顺序存储结构的有序表 <a id="9121"></a>
性能:<br>
(1)折半查找在查找不成功时和给定值进行比较的关键字个数最多也不超过:     $\lfloor {log}_2n \rfloor + 1$<br>
(2)$ASL = \frac{n+1}{n}{log}_2(n+1) -1 \approx{log}_2(n+1) -1, \quad n > 50$
```c++
int bin_search(const sqtable & tab, const key_t & k)
{
    int low = 0, high = tab.length() - 1 , mid = (low + high) / 2;
    while(low <= high)
    {
        if(tab[mid] == k) return mid;//found
        if(tab[mid] < k) high = mid -1;
        else low  = mid + 1;
    }
    return -1;//not found
}
```
#### 其他：斐波那契查找、插值查找<a id="9122"></a>
#### <a href="#9">9.1.3 静态树的查找<a> <a id="913"></a>
<b>性能</b>：如果只考虑查找成功的情况，则使查找性能达最佳的判定树是其带权内路径长度之和PH值<br>$PH = \underset{i = 1}{\overset{n}{\sum}}w_ih_i$<br>
$h_i$为第i个结点在二叉树上的层次数,结点的权，$w_i=cp_i$（i=1，2，…，n），其中$p_i$为结点的查找概率，c 为某个常量。称 PH 值取最小的二叉树为<b>静态最优查找树</b>

#### <b>次优查找树</b><a id="9131"></a>
l -- low<br>
h -- high<br>
取最小值$\Delta P_i = \underset{l \leq j \leq h}{min}\Delta P_j$
$$\Delta P_i = \lvert\underset{j = i + 1}{\overset{h}{\sum}}w_j - \underset{j = l}{\overset{ i -1}{\sum}}w_j\rvert$$
累计权值和:<br>
$$sw_i = \underset{j = l}{\overset{i}{\sum}}w_j$$
并设$w_{l - 1}=0$和$sw_{l -1}=0$，则
$$\underset{j = l}{\overset{i -1}{\sum}}w_j = sw_{i -1} - sw_{l -1}$$
$$\underset{j = i + 1}{\overset{h}{\sum}}w_j = sw_{h} - sw{i}$$
$$\Delta P_i = \lvert (sw_{h} - sw_{i}) - (sw_{i -1} - sw_{l -1})\rvert = 
\lvert (sw_{h} + sw_{l - 1}) - (sw_{i} + sw_{i -1})\rvert$$