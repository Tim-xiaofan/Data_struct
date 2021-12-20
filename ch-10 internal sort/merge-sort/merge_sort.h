/** 20210919, zyj, GuangDong*/
#ifndef _MERGE_SORT
#define _MERGE_SORT
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

template <typename T>
void show_array(const T * a, int start, int end)
{
    int i;

    for(i = start; i <= end; ++i)
      cout << a[i] << " ";
    cout << endl;
}

/**
  O(m + n)
  将有序的sr[i...m]和sr[m+1...n]归并为有序的sr[i...n]
 */
template <typename T>
void merge(T * arr, int begin, int mid, int end)
{
    int i, j, k = 0;
    T *tmp = new T[end - begin + 1];

    for(i = begin, j = mid + 1; i <= mid && j <= end;)
    {
        if(arr[i] < arr[j]) tmp[k++] = arr[i++];
        else if(arr[i] == arr[j])
        {
            tmp[k++] = arr[i++];
            tmp[k++] = arr[j++];
        }
        else tmp[k++] = arr[j++];
    }
    
    for(; i <= mid; ++i) tmp[k++] = arr[i];
    for(; j <= end; ++j) tmp[k++] = arr[j];

    for(i = 0; i < k; ++i)
      arr[begin + i] = tmp[i];

    delete tmp;
}

template<typename T>
void merge_sort(T  *arr, int begin, int end)
{
    int mid;
    if(begin >= end) return;
    else
    {
        mid = (begin + end) / 2;
        merge_sort(arr, begin, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, begin, mid, end);
    }
}


/**
  O(nlogn) --> O(2nlogn)
 */
template<typename T>
void merge_sort(T & table)
{
    typedef typename T::elem_type elem_type;
    elem_type  *arr;
    arr = table.get_base();

    merge_sort(arr, 0, table.length() -1);
}
#endif
