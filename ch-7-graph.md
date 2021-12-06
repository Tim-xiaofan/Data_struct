## 第七章 图
>><!--ts-->
>>* [7.4 图的遍历](#none)
>>    * [7.4.1 DFS](#none)
>>    * [7.4.2 BFS](#none)
>>* [7.4 图的连通性问题](#none)
>>    * [7.4.1 无向图的连通分量](#none)
>>    * [7.4.2 有向图的强连通分量](#none)
>>    * [7.4.3 最小生成树](#none)
>>    * [7.4.4 连通图关节点](#none)
>>* [7.5 有向无环图及其应用](#none)
>>    * [7.5.1 拓扑排序](#none)
>>    * [7.5.2 关键路径](#none)
>><!--te-->
### 7.4 图的遍历
>>#### 7.4.1 DFS
>>```c++
>>/**
>> * 邻接矩阵：O(n ** 2)
>> * 邻接表：O(n + e)
>> * */
>>void dfs_traverse(const Graph &G)
>>{
>>    for (int v = 0; v < G.vexnum(); ++v)
>>        if (!visited[v])
>>            dfs(G, v, visited);
>>}
>>void dfs(const Graph &G, int v, bool *visited)
>>{
>>    visited[v] = true;
>>    visit(v);
>>    for (auto p = G.first(v); p; p = p.next(v))
>>        if (!visited[p->adj(v)])
>>            dfs(G, p->adj(v), visited);
>>}
>>```
>>#### 7.4.1 BFS
>>```c++
>>/** 广度优先搜索*/
>>void bfs(Graph &G)
>>{
>>    bool visited[MAX_NUM] = {false};
>>    int v, w, u;
>>    queue q(G.vecnum());
>>    for (v = 0; v < G.vexnum; ++v)
>>        if (!visited[v])
>>        {
>>            visited[v] = true;
>>            visit(v);
>>            q.enqueue(v);
>>            while(!q.is_empty())
>>            {
>>                q.dequeue(w);
>>                for(auto p = G.first(w); p; p = p->next(w))
>>                {
>>                    u = p->adj(w);
>>                    if(!visited[u])
>>                    {
>>                        visit(u);
>>                        visited[u] = true;
>>                        q.enqueue(u);
>>                    }
>>                }
>>            }
>>        }
>>}
>>```
### 7.4 图的连通性问题
>>#### 7.4.1 无向图的连通分量
>>```c++
>>/** 无向图的联通分量和生成树*/
>>void dfs_forest(const Graph &G, cstree &T)
>>{
>>    bool visited[MAX_NUM] = {false};
>>    cstree p = nullptr, q = nullptr;
>>    T = nullptr;
>>    for (int v = 0; v < G.vexnum(); ++v)
>>        if (!visited[v])
>>        {
>>            p = new cstree();
>>            p->data = G.data(v);
>>            if (!T)
>>                T = p; //第一棵生成树
>>            else
>>                q->nextsibling = p;
>>            q = p; //指示当前生成树的根
>>            dfs_tree(G, v, p, visited);
>>        }
>>}
>>void dfs_tree(const Graph &G, int v, cstree &t, bool *visited)
>>{/** 第v个顶点出发深度优先遒历图G，建立以T为根的生成树*/
>>    bool fisrt = true;
>>    int w, u;
>>    visited[v] = true;
>>    cstree p = nullptr, q = nullptr;
>>
>>    for (auto arc = G.first(v); arc; arc = arc->next(v))
>>    {
>>        w = arc->adj(v);
>>        if (!visited[w])
>>        {
>>            p = new cstree();
>>            p->data = G.data(w);
>>            if (first)
>>            {
>>                first = tree;
>>                t->firstchild = p;
>>            }
>>            else q->nextsibling = p;
>>            q = p;
>>            dfs_tree(G, w, p, visited);
>>        }
>>    }
>>}
>>```
>>#### 7.4.2 有向图的强连通分量
>>```c++
>>/** 有向图的强连通分量 : kosaraju*/
>>/** 从顶点v进行DFS*/
>>void DFS(const graph &G, int v, bool *visited, stack &finished, bool r)
>>{
>>    int w;
>>    visited[v] = true;
>>    finished.push(v);
>>    if (r)
>>    {//逆向深度优先搜索
>>        for (auto p = G.rfirst(v); p; p = p->rnext(v))
>>        {
>>            w = p->radj(v);
>>            if (!visited[w]) DFS(G, w, visited, finished, true);
>>        }
>>    }
>>    else
>>    {//正向深度优先搜索
>>        for (auto p = G.first(v); p; p = p->next(v))
>>        {
>>            w = p->adj(v);
>>            if (!visited[w]) DFS(G, w, visited, finished, false);
>>        }
>>    }
>>}
>>/** DFS*/
>>void DFS(const graph &G, stack &finished, bool r = false)
>>{
>>    bool visited[MAX_NODE_NB] = {false};
>>    for (int v = 0; v < G.vexnum(); ++v)
>>        if (!visited[v])
>>            DFS(G, v, visited, finished, r);
>>}
>>void kosaraju(const graph &G)
>>{
>>    bool visited[MAX_NODE_NB] = false;
>>    stack finished(G.vexnum());
>>    DSF(G, finished);
>>    int v;
>>    while (finished.pop(v))
>>    {
>>        if (!visited[v]) 
>>        {
>>            finish.clear();
>>            DFS(G, v, visited, finished, true);
>>            finish.show();
>>        }
>>    }
>>}
>>```
>>#### 7.4.3 最小生成树
>>```c++
>>/**  
>> * 最小生成树
>> * O(n * n)边数无关，因此适用于求边稠密的网的最小生成树
>> */
>>int prime(const graph & G, int u)
>>{
>>    int nb = G.vexnum(), ct = 0, min_vex;
>>    G::cost_t min_cost, cost = 0;
>>    closege * closeges  = new closege[nb];
>>    /** 进入初态*/
>>    closeges[u].lowcost = 0;
>>    ++ct;
>>    for(int v = 0; v < nb; ++v)
>>        if(v != u) closeges[v] = {u, G.cost(u,v)};
>>
>>    for(int v = 0; v < nb && ct < nb; ++v)
>>    {
>>        min_cost = INI_MAX;
>>        for(int w = 0 ; w < nb; ++w)//搜寻V-U和U之间最小
>>            if(closeges[w].lowcost != 0 && min_cost > closeges[w].lowcost)
>>            {
>>                min_cost = closeges[w].lowcost;
>>                min_vex = w;
>>            }
>>        cost += min_cost;
>>        closeges[min_vex].lowcost = 0;//并入U
>>        ++ct;
>>        for(int w = 0; w < nb; ++w)//更新closedges
>>            if(G.cost(min_vex, w) < closeges[w].lowcost)
>>                closeges[w] = {min_vex, G.cost(min_vex, w)};
>>    }
>>    print(closeges);
>>    delete [] closeges;
>>    return cost;
>>}
>>```
>>#### 7.4.4 关节点
>>```c++
>> /** 时间复杂度仍O(n+e)：进行了一次DFS*/
>>int DFS_artical(const graph & G, 
>>                int v, 
>>                int * visited, 
>>                int * low, 
>>                int & ct)
>>{
>>    int mim = ++ct, w;
>>    visited[v] = min;
>>    bool fisrt = true;
>>    for(auto p = G.fisrt(v); p; p = p->next(v))
>>    {/** 从v的邻接点开始，做DFS*/
>>        w = p->adj(v);
>>        if(!visited[w])
>>        {
>>            DFS_artical(G, w, visited, low, ct);
>>            if(low[w] < min) min = low[w];
>>            if(low[w] > visited[v] && first)
>>            {//没有到v祖先的回边
>>                cout << v;
>>                first = false;
>>            }
>>        }
>>        else if(low[w] < min) min = low[w];
>>    }
>>    low[v] = min;
>>}
>>int find_artical(const graph & G)
>>{
>>    int visited[grapha::MAX_NODE_NB] = {0}, //v顶点DFS遍历时的位置
>>        low[grapha::MAX_NODE_NB] = {0},//顶点v能回溯到的最浅层的位置
>>        ct = 0;
>>    for(int v = 0; v < G.vexnum(); ++v)
>>      if(!visited)
>>      {
>>          DFS_artical(G, v, visited, low, ct);
>>          if(ct < G.vexnum()) cout << v;
>>      }
>>}
>>```
### 7.5 有向无环图及其应用
>>#### 7.5.1 拓扑排序
>><b>算法描述</b>：<br>
>>（1）在有向图中选一个没有前驱的顶点且输出之。</br>
>>（2）从图中删除该顶点和所有以它为尾的弧。</br>
>>重复上述两步，直至全部顶点均已输出，或者当前图中不存在无前驱的顶点为止。后</br>
>>一种情况则说明有向图中存在环。</br>
>>针对上述两步操作，我们可采用邻接表作有向图的存储结构，<br>
>>且在头结点中增加一个存放顶点入度的数组（indegree）。<b>入度为零的顶点即为没有前驱</b><br>
>>的顶点，删除顶点及以它为尾的弧的操作，则可换以<b>弧头顶点的入度减1来实现</b><br>
>>为了避免重复检测入度为零的顶点，可另设一<b>栈</b>暂存所有入度为零的顶点<br>
>>```c++
>>bool topo_sort(const graph & G)
>>{
>>    int indegree[graph::MAX_NODE_NB], ct = 0, v, w;
>>    stack s(G.vexnum());
>>    G.get_indegrees(indegree, G.vexnum());
>>    for(v = 0; v < G.vexnum(); ++v)
>>        if(indegree[v] == 0) s.push(v);
>>    while(!s.empty())
>>    {
>>        s.pop(v);
>>        cout << v;
>>        ct++;
>>        for(auto p = G.first(v); p; p=p->next(v))
>>        {/** 模拟删除顶点v及以v为弧尾的弧*/
>>            w = p->adj(v);
>>            if((--indegree[w]) == 0)s.push(w);
>>        }
>>    }
>>    return (ct == G.vexnum());
>>}
>>```
>>### 7.5.2 关键路径
>>$e(i)= ve(i)$ --活动最早开始时间<br>
>>$l(i) = vl(k) - dut<j, k>$ --活动最晚开始时间<br>
>>$ve[j] = max\{v[j] + dut<i,j>\}, <i, j> \in edges$ <br>
>>$vl[j] = min\{v[k] - dut<j,k>\}, <j, k> \in edges$ <br>
>>```c++
>>bool topo_sort(const graph & G, stack & T, array & ve)
>>{/** 排序并计算每个活动的最早开始时间ve[j]*/
>>    int indegree[graph::MAX_NODE_NB], ct = 0, v, w;
>>    stack s(G.vexnum());
>>    G.get_indegrees(indegree, G.vexnum());
>>    for(v = 0; v < G.vexnum(); ++v)
>>        if(indegree[v] == 0) s.push(v);
>>    while(!s.empty())
>>    {
>>        T.push(v);
>>        for(auto p = G.first(v); p; p=p->next(v))
>>        {/** 模拟删除顶点v及以v为弧尾的弧*/
>>            w = p->adj(v);
>>            if((--indegree[w]) == 0)s.push(w);
>>            if(ve[v] + p->cost(v) > ve[w]) 
>>                ve[w] = ve[v] + p->cost(v) > ve[w]
>>        }
>>    }
>>}
>>bool critical_path(const graph & G)
>>{
>>    stack T(G.vexnum());
>>    graph::cost_t ee, el, ve[MAX_NODE_NB] = {0}, vl[MAX_NODE_NB], dut;
>>    int v, w;
>>    if(!topo_sort(G, T, ve)) return false;
>>    for(v = 0; v < G.vexnum(); ++v) vl[v] = vl[G.vexnum() -1];
>>    while(!T.is_empty())
>>    {//逆拓扑序列求vl[j]
>>        T.pop(v);
>>        for(auto p = G.fisrt(v); p; p = p->next(v))
>>        {
>>            w = p->adj(v);dut = p->cost(v);
>>            if(vl[v] > vl[w] - dut) vl[v] = vl[w] - dut;
>>        }
>>    }
>>    for(v = 0; v < G.vexnum(); ++v) 
>>    {//输出关键活动
>>        for(auto p = G.fisrt(v); p; p = p->next(v))
>>        {
>>            w = p->adj(v);
>>            dut = p->cost(v);
>>            ee = v[v];
>>            el = v[w] - dut;
>>            cout << {v, w, ee, el, (ee==el)};
>>        }
>>    }
>>}
>>```
### 7.6 最短路径
#### 7.6.1 从某个源点到其余各顶点的最短路径
