## 第七章 图
>><!--ts-->
>>* [7.1 图的遍历](#none)
>>    * [DFS](#none)
>>    * [BFS](#none)
>>* [7.2 图的连通性问题](#none)
>>    * [无向图的连通分量](#none)
>>    * [有向图的强连通分量](#none)
>>    * [最小生成树](#none)
>>    * [连通图关节点](#none)
>><!--te-->
### 7.1 图的遍历
>>#### 7.1.1 DFS
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
>>#### 7.1.1 BFS
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
### 7.2 图的连通性问题
>>#### 7.2.1 无向图的连通分量
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
>>            else
>>                q->nextsibling = p;
>>            q = p;
>>            dfs_tree(G, w, p, visited);
>>        }
>>    }
>>}
>>```
>>#### 7.2.2 有向图的强连通分量
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
>>#### 7.2.4 最小生成树
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
>>#### 7.2.5 关节点
>>```c++
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
>>    {
>>        w = p->adj(v);
>>        if(!visited[w])
>>        {
>>            DFS_artical(G, w, visited, low, ct);
>>            if(low[w] < min) min = low[w];
>>            if(low[w] > visited[v] && first)
>>            {
>>                cout << v;
>>                first = false;
>>            }
>>        }
>>        else if(low[w] < min) 
>>            min = low[w];
>>    }
>>    low[v] = min;
>>}
>>int find_artical(const graph & G)
>>{
>>    int visited[grapha::MAX_NODE_NB] = {0}, 
>>        low[grapha::MAX_NODE_NB] = {0}, 
>>        ct = 0;
>>    for(int v = 0; v < G.vexnum(); ++v)
>>    if(!visited)
>>    {
>>        DFS_artical(G, v, visited, low, ct);
>>        if(ct < G.vexnum())
>>            cout << v;
>>    }
>>}
>>```