### ch-03 队列
![](./image/mind/03%E9%98%9F%E5%88%97%E8%84%91%E5%9B%BE.png)
```c
struct s_queue
{//循环队列
    elem_t * base;
    int front, rear;
    int maxsize;
};
```

#### 1. 进队
```c
q.base[q.rear] = e;
q.rear  = (q.rear + 1) % q.maxsize;
```
#### 2. 出队
```c
e = q.base[q.front]
q.front = (q.front + 1) % q.maxsize;
```
#### 3. 判空
```c
q.front == q.rear;
```
#### 4. 判满
```c
(q.rear + 1) % q.maxsize == q.front;
```
#### 5. 长度
```c
(q.rear - q.front + q.maxsize) % q.maxsize;
```