###  ch-02 线性表
![](./image/mind/02%E7%BA%BF%E6%80%A7%E8%A1%A8%E8%84%91%E5%9B%BE.png)

```c
struct node
{//单向
	data_t data;
	struct node * next;
};
struct node
{//双向
	data_t data;
	struct node * prior, *next;
};
typedef struct node * list;
```

### 2. 运算
#### 2.1 基本运算
1. 插入节点
```c
s->next = p->next;
p->next = s;
```
2. 删除节点
```c
p->next = p->next->next;
```
#### 2.2 应用
1. 逆转
```c
list list_reverse(list l)
{
	if (!l || !l->next)
		return l;
	for (list last = l->next, cur = last->next;
		 last->next; cur = last->next)
	{
		last->next = cur->next; //移除
		cur->next = l->next;	//插入
		l->next = cur;
	}
	return l;
}
```
2. 有序表合并
```c
list list_merge(list A, list B)
{// 不使用原节点
	list C = (list)malloc(sizeof(struct node));
	list pa = A->next, pb = B->next, pc = NULL;
	while (pa && pb)
	{
		list cur = NULL;
		if (pa->data <= pb->data)
		{
			cur = pa;
			pa = pa->next;
		}
		else
		{
			cur = pb;
			pb = pb->next;
		}
		list s = (list)malloc(sizeof(struct node));
		s->next = NULL;
		s->data = cur->data;
		if (pc == NULL)
			C->next = s;
		else
			pc->next = s;
		pc = s;
	}
	list remain = pa ? pa : pb;
	while (remain)//处理余下
	{
		list s = (list)malloc(sizeof(struct node));
		pc->next = s;
		s->next = NULL;
		s->data = remain->data;
		pc = s;
		remain = remain->next;
	}
	return C;
}

list list_merge1(list A, list B)
{//使用原节点
    list C = A;
    list pa = A->next, pb = B->next, pc = NULL;
    while(pa && pb)
    {
        list s = NULL;
        if(pa->data <= pb->data)
        {
            s = pa;
            pa = pa->next;
        }
        else
        {
            s = pb;
            pb = pb->next;
        }
        if(pc == NULL) C->next = s;
        else pc->next = s;
        pc = s;
    }
    list remain = pa ? pa : pb;
    while(remain)
    {
        pc->next = remain;
        pc = remain;
        remain = remain->next;
    }
    free(B);
    return C;
}

```