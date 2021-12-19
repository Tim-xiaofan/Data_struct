/** 20210918, zyj, GuangDong*/
#ifndef _SELECT_SORT
#define _SELECT_SORT

template <typename sqtable_t>
void select_sort(sqtable_t & table, bool up = true)
{
    int len = table.length(), i, j, min;
    typename sqtable_t::elem_type tmp;

    for(i = 0; i < len; ++i)
    {
        min = i;
        for(j = i; j <len; ++j)//当前序列中最小的下标
          if(table[j] < table[min])
            min = j;
        if(min != i) 
        {
            tmp = table[min];
            table[min] = table[i];
            table[i] = tmp;
        }
    }
}

/**
  https://app.yinxiang.com/Home.action?login=true#n=a58bb394-3b78-4c27-b7e5-6dc6434cd77f&s=s18&ses=4&sh=2&sds=5&
  大顶堆：arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]
  小顶堆：arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]  
  最后一个非终端结点是第n/2 - 1个元素(向下取整)
  已知中记录的H[s...m]关键字除H[s]之外均满足堆的定义，本函数调整H[s]
  的关键字，使H[s...m]成为一个大顶堆（对其中记录的关键字而言）
 **/

template <typename sqtable_t>
void heap_adjust(sqtable_t & H, int s, int m, bool up = true)
{
    typename sqtable_t::elem_type rc;
    int j;
    if(!up) return;//TODO : for descending

    rc = H[s];
    for(j = 2 * s + 1; j <= m; j = 2 * j + 1)//key较大的孩子结点向下筛选
    {
        if(j < m && H[j] < H[j + 1])//左孩子不如右孩子大 
          ++j;
        if(rc >= H[j]) break;//rc是三个节点最大的
        H[s] = H[j];
        s = j;
    }
    H[s] = rc;
}

/**
  O(nlogn)
 */
template <typename sqtable_t>
void heap_sort(sqtable_t & H, bool up = true)
{
    int i, len = H.length();
    typename sqtable_t::elem_type tmp;
    
    if(!up) return;//TODO : for descending

    /** 建立大顶堆*/
    for(i = len / 2 -1; i >= 0; --i)
      heap_adjust(H, i, len -1);

    for(i = len -1; i >= 0; --i)
    {
        /** 将堆顶记录和当前未经排序子序列H[0...i]中最后一个记录相互交换*/
        tmp = H[0];
        H[0] = H[i];
        H[i] = tmp;
        /** 将H[0...i-1]重新调整为大顶堆(i之后的节点不用调整) */
        heap_adjust(H, 0, i - 1);
    }
}

#endif
