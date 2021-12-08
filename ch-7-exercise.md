###  ch-7 exercise<a id="7"></a>
<!--ts-->
* <a href="#01">01 设计一个算法，求图G中距离顶点v的最短路径长度最大的一个顶点，设v可达其余各个顶点</a><br>
* <a href="#02">02 试基于图的深度优先搜索策略写一算法，判别以邻接表方式存储的有向图中是否存在由顶点vi到顶点vj的路径（i≠j）</a><br>
* <a href="#03">03</a><br>
* <a href="#04">04</a><br>
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
>>#### <a href="#7">试基于图的深度优先搜索策略写一算法，判别以邻接表方式存储的有向图中是否存在由顶点>>vi到顶点vj的路径（i≠j）</a> <a id="02"> </a>
>>```c++
>>bool exist_path(const graph & G, int i, int j)
>>{
>>    int nb = G.vexnum(), w;
>>    bool array<int> visited(nb, false);
>>    for(auto p = G.firstarc(i); p; p = p->nextarc)
>>    {
>>        w = p->adj();
>>        if(!visited[w] && exist_path(G, w, j, visited)) return true;//found 
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
>>        if(!visited[w] && exist_path(G, w, j, visited)) return true;//found
>>    }
>>    return false;//not found
>>}
>>```