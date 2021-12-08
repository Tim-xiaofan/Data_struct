###  ch-7 exercise<a id="7"></a>
<!--ts-->
* <a href="#01">01 设计一个算法，求图G中距离顶点v的最短路径长度最大的一个顶点，设v可达其余各个顶点</a><br>
* <a href="#02">02 试基于图的深度优先搜索策略写一算法，判别以邻接表方式存储的有向图中是否存在由顶点vi到顶点vj的路径（i≠j）</a><br>
* <a href="#03">03 采用邻接表存储结构，编写一个算法，判别无向图中任意给定的两个顶点之间是否存在一条长度为k的简单路径</a><br>
<!--te-->
#### <a href="#7">01 设计一个算法，求图G中距离顶点v的最短路径长度最大的一个顶点，设v可达其余各个顶点</a><a id="01"> </a>
>>```c++
>>int max_shortestpath(const graph & G, int start)
>>{
>>    int nb = G.vexnum(), max_vex;
>>    graph::cost_t max = 0;
>>    array<int> D(nb);
>>    dijkstra(G, start, D);
>>    for(int v = 0; v < nb; ++v)
>>        if(D[v] > max){ max = D[v];max_vex = v;}
>>    return max_vex;
>>}
>>void dijkstra(const graph & G, int start, array<int> & D)
>>{
>>    int nb = G.vexnum(), min_vex;
>>    graph::cost_t min;
>>    array<bool> _final(nb, false);
>>    _final[start] = true;
>>    for(int v = 0; v < nb; ++v)
>>        if(G.cost(start, v) < INF) D[v] = G.cost(start, v);
>>    for(int v = 0; v < nb; ++v)
>>    {
>>        min = INF;
>>        for(int w = 0; w < nb; ++w)//V-S中到距离start最近的点
>>            if(!_final[w] && min < D[w]){min_vex = w; min = D[w];}
>>        _final[min_vex] = true;//min_vex并入S后，
>>        for(int w = 0; w < nb; ++w)//更新最短距离
>>            if(!_final[w] && G.cost(min_vex, w) < INF &&
>>                min + G.cost(min_vex, w) < D[w])
>>                D[w] = G.cost(min_vex, w) + min;
>>    }
>>}
>>```
>>#### <a href="#7">试基于图的深度优先搜索策略写一算法，判别以邻接表方式存储的有向图中是否存在由顶点vi到顶点vj的路径（i≠j）</a> <a id="02"> </a>
>>```c++
>>bool exist_path(const graph & G, int i, int j)
>>{
>>    int nb = G.vexnum(), w;
>>    array<bool> visited(nb, false);
>>    for(auto p = G.firstarc(i); p; p = p->nextarc)
>>    {
>>        w = p->adj();
>>        if(!visited[w] && exist_path(G, w, j, visited)) 
>>          return true;//found 
>>    }
>>    return false;//not found
>>}
>>bool exist_path(const graph & G, int i, int j, array<bool> visited)
>>{
>>    int w;
>>    visited[i] = true;
>>    if(i == j) return true;
>>    for(auto p = G.firstarc(i); p; p = p->nextarc)
>>    {
>>        w = p->adj();
>>        if(!visited[w] && exist_path(G, w, j, visited)) 
>>            return true;//found
>>    }
>>    return false;//not found
>>}
>>```
>>#### <a href="#7">03 采用邻接表存储结构，编写一个算法，判别无向图中任意给定的两个顶点之间是否存在一条长度为k的简单路径</a><a id="03"> </a>
>>```c++
>>int visited[MAXSIZE];
>>int exist_path_len(ALGraph G, int i, int j, int k)
>>//判断邻接表方式存储的有向图G的顶点i到j是否存在长度为k的简单路径
>>{
>>    if (i == j && k == 0)
>>        return 1; //找到了一条路径,且长度符合要求
>>    else if (k > 0)
>>    {
>>        visited[i] = 1;
>>        for (p = G.vertices[i].firstarc; p; p = p->nextarc)
>>        {
>>            l = p->adjvex;
>>            if (!visited[l])
>>                if (exist_path_len(G, l, j, k - 1))
>>                    return 1; //剩余路径长度减一
>>        }// for
>>        visited[i] = 0;//本题允许曾经被访问过的结点出现在另一条路径中
>>    }// else
>>    return 0;                 //没找到
>>} // exist_path_len
>>```