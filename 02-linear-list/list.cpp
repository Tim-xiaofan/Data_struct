#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
using std::cerr;

struct lnode
{
    int data;
    struct lnode * next;
    lnode(int d = 0, lnode *n = nullptr):data(d), next(n){}
};
typedef struct lnode * list;

/** inverse a list*/
static list &  
list_inverse(list & l)
{
    list cur = l->next, next;
    l->next = nullptr;
    while(cur)
    {
        next = cur->next;
        cur->next = l->next;
        l->next = cur;
        cur = next;
    }
    return l;
}

/** compute intersection of la and lb*/
static int 
list_intersection(list & la, list & lb)
{
    int n = 0;
    list pre, pa = la->next, pb = lb->next, tmp;
    while(pa && pb)
    {
        //cout << "pa : " << pa->data << endl;
        //cout << "pb : " << pb->data << endl;
        if(pa->data == pb ->data)
        {
            pre = pa;
            pa = pa->next;
            pb = pb->next;
            ++n;
        }
        else if(pb->data < pa->data) pb = pb->next;
        else
        {
            //cout << "delete " << pa->data << endl;
            pre->next = pa->next;
            tmp = pa;
            pa = pa->next;
            delete tmp;
        }
    }
    while(pa) {tmp = pa; pa = pa->next; delete pa;}
    return n;
}


list list_construct(int *a, int size)
{
    list head = new lnode;
    list cur = nullptr, tmp = nullptr;
    for(int i = 0; i < size; ++ i)
    {
        if(i == 0)
        {
            cur = new lnode(a[0], nullptr);
            head->next = cur;
        }
        else
        {
            tmp = new lnode(a[i], nullptr);
            cur->next = tmp;
            cur = tmp;
        }
    }
    return head;
}

void list_print(const list & l)
{
    if(l == nullptr) return;
    list p = l->next;
    while(p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void test_inverse(void)
{
    int a[5] ={0, 1, 2, 3, 4}; 
    list l = list_construct(a, 5);
    cout << "original list:";
    list_print(l);
    cout << "inversed list:";
    list_print(list_inverse(l));
}

void test_intersection()
{
    int a[5] ={0, 1, 2, 3, 4}; 
    int b[3] ={0, 2, 4};
    list la = list_construct(a, 5);
    list lb = list_construct(b, 3);
    cout << "original list:" << endl;
    list_print(la);
    list_print(lb);
    cout << "intersection list:" << endl;
    list_intersection(la, lb);
    list_print(la);
}

/**TODO : list detroy */
int main(int ac, char * av[])
{
    if(ac != 2)
    {
        cerr << "usage : " << av[0];
        cerr << " mode" << endl;
        return -1;
    }
    if(strcmp(av[1], "inverse") == 0) test_inverse();
    else if(strcmp(av[1], "intersection") == 0) test_intersection();
    else cerr << "unkown mode" << endl;
    return 0;
}
