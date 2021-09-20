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
  将有序的sr[i...m]和sr[m+1...n]归并为有序的tr[i...n]
 */
template <typename T>
void merge(T * arr, int begin, int mid, int end, bool up = true)
{
    int i, j, k = 0;
    if(!up) return;
    T *tmp = new T[end - begin];

    for(i = begin, j = mid + 1; i <= mid && j <= end;)
    {
        if(arr[i] < arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else if(arr[i] == arr[j])
        {
            tmp[k++] = arr[i++];
            tmp[k++] = arr[j++];
        }
        else
        {
            tmp[k++] = arr[j++];
        }
    }
    
    for(; i <= mid; ++i) tmp[k++] = arr[i++];
    for(; j <= mid; ++j) tmp[k++] = arr[j++];

    for(i = 0; i < k; ++i)
      arr[begin + i] = tmp[i];

    delete tmp;
}

template<typename T>
void merge_sort(T  *arr, int begin, int end, bool up = true)
{
    int mid;
    //cout << "***before : begin = " << begin << ", end = " << end << endl; 
    //cout << "tr : ";
    //show_array(tr, 0, end);
    if(begin >= end) return;
    else
    {
        mid = (begin + end) / 2;
        merge_sort(arr, begin, mid, up);
        //cout << "arr1 :";
        //show_array(arr, begin, mid);
        merge_sort(arr, mid + 1, end, up);
        //cout << "arr2 :";
        //show_array(arr, mid + 1, end);
        merge(arr, begin, mid, end, up);
        //cout << "arr3 : ";
        //show_array(arr, begin, end);
    }
    //cout << "###after : begin = " << begin << ", end = " << end << endl; 
    //cout << endl;
}


/**
  O(nlogn) --> O(2nlogn)
 */
template<typename T>
void merge_sort(T & table, bool up = true)
{
    typedef typename T::elem_type elem_type;
    elem_type  *arr;
    arr = table.get_base();

    merge_sort(arr, 0, table.length() -1, up);
}
#endif
