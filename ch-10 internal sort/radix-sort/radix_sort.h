/** 20210920, zyj, GuangDong*/
#ifndef _RADIX_SORT
#define _RADIX_SORT

/**只实现了十进制整数（int）的基数排序*/
#define MAX_KEY_MUM     8
#define RADIX           10
#define MAX_SPACE       1000

struct sl_cell
{
    int keys[MAX_KEY_MUM];
    int next;
};

struct sl_list
{
    sl_cell r[MAX_SPACE]; //态链表的可利用空间，r[0]为头结点
    int keynum;//记录的当前关键字个数
    int recnum;//静态链表的当前长度
};//静态链表类型

typedef int arr_t[RADIX]; //指针数组类型

/** 
  静态链表L的r域中记录已按(keye[0] ,..., keys[i-1])有序。
  本算法按第i个关键字key[i]建立RADIX个子表，使同一子表中记录的key[i]相同，
  f[0...RADIX-1]和e[0...RADIX-1分别指向各子表中第一个和最后一个记录，
 */
void distribute(sl_cell * r, int i, arr_t f, arr_t e)
{
    int j, p;

    for(j = 0; j < RADIX; ++j) f[j] = 0;
    for(p = r[0].next; p; p = r[p].next)
    {
    }
}

#endif
