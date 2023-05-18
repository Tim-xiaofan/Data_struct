# 图
* 线性表-元素之间的线性关系
* 树-元素之间的层次关系
* 图-元素之间的任意关系
## 7.1 图的定义和术语
* 无向图边数量e的取值范围[0 - $\frac{n(n-1)}{2}$]，e=$\frac{n(n-1)}{2}$时是**完全图**
* 有向图边数量e的取值范围[0 - $n(n-1)$]，e=n(n-1)时是**完全图**
* 边较少（$e < nlogn$）的图称为**稀疏图**，较多时称为**稠密图**
* 有时图的边或弧具有与它相关的数，这种与图的边或弧相关的数叫做**权（Weight）**。
这些权可以表示从一个顶点到另一个顶点的距离或耗费。这种带权的图通常称为**网(Network)**。
* 假设有两个图$G=(V，{E})$和$G'=(V',{E'})$，如果$V'\in V$且$E' \in E$，则称 G'为G 的**子图（Subgraph）**
* **顶点v的度(Degree)** 是和v相关联的边的数目，有向图分为**入度**和**出度**。图的度d和边数e的关系$e = \frac{d}{2}$
* 路径序列中顶点不重复出现的路径称为**简单路径**。除了第一个顶点和最后一个顶点之外，其余顶点不重复出现的回路，称
为**简单回路**或**简单环**
*  **连通分量**是指在无向图中，将所有节点按照它们之间的连接关系分成的互不相交的子集，指的是无向图中的极大连通子图。每个子集内的节点可以通过边相互连通，而不同子集内的节点则没有直接的边连接。如果一个无向图只有一个连通分量，那么该**图就是连通的**，即**连通图**，也就是说任意两个节点之间都存在路径。如果一个无向图有多个**连通分量**，那么每个连通分量都是一个独立的子图，其中的节点在子图内是相互连通的，但与其他连通分量内的节点没有直接的连接。
*  **强连通图**是指一个有向图中任意两点v1、v2间存在v1到v2的路径（path）及v2到v1的路径的图。强连通图是有向图中的一种特殊情况，它是指对于有向图中的任意两个顶点u和v，都存在一条从u到v的有向路径和一条从v到u的有向路径。有向图中的极大强连通子图称做有向图的**强连通分量**
*  一个**连通图的生成树**是一个极小连通子图，它含有图中全部顶点，但只有足以构成一棵树的n-1条边。如果一个图有n个顶点和小于n-1条边，则是非连通图。如果它多于n-1条边，则一定有环。

## 7.2 图的存储结构
### 7.2.1 数组表示法
用两个数组分别存储数据元素（顶点）的信息和数据元素之间的关系（边或弧）的信息。
* 无向图，顶点vi的度是邻接矩阵中第i行（或第i列）的元素之和。对于有向图，第i行的元素之和为顶点vi的出度OD(v)，第j列的元素之和为顶点vi的入度ID(vi)。
* 构造一个具有n个顶点和e条边的无向网G的时间复杂度是O(n2+e·n)，其中对邻接矩阵 G.ars 的初始化耗费了$O(n^2)$的时间
### 7.2.2 邻接表
**邻接表（Adjacency List）** 是图的一种链式存储结构。在邻接表中，对图中每个顶点建立一个单链表，第i个单链表中的结点表示依附于顶点vi的边（对有向图是以顶点vi为尾的弧）
```c++
template<typename T>
struct ArcNode
{
    int adjvex;
    struct ArcNode* nextArc;
    T info; //例如权重
};
template<typename T>
struct VexNode
{
    T data; //顶点信息
    struct ArcNode* firstArc;
};
```
* 在无向图的邻接表中，顶点vi的度恰为第i个链表中的结点数；而在有向图中，第i个链表中的结点个数只是顶点vi的出度，为求入度，必须遍历整个邻接表。
* 在邻接表上容易找到任一顶点的第一个邻接点和下一个邻接点，但要判定任意两点之间是否有边或弧需要搜索其中一个链表
### 7.2.3 十字链表
**十字链表（Orthogonal List）** 是有向图的另一种链式存储结构。可以看成是将有向图的邻接表和逆邻接表结合起来得到的一种链表。在十字链表中，对应于有向图中每一条弧有一个结点，对应于每个顶点也有一个结点。
* 在十字链表中既容易找到以vi为尾的弧，也容易找到以vi为头的弧，因而**容易求得顶点的出度和入度**。
```c++
template<typename T>
struct ArcBox 
{
    int tailvex, headvex; // 该弧的尾和头顶点的位置
    struct ArcBox *hlink, *tlink; // 分别为弧头相同和弧尾相同的弧的链表
    T info; // 该弧相关信息的指针
};
template<typename T>
struct VexNode
{
    T data; //顶点信息
    struct ArcBox *firstIn, *firstout;
};
```
## 7.2.4 邻接多重表
邻接多重表（Adjacency Multilist）是无向图的另一种链式存储结构。
* 更方便对边的各种操作（删除，访问标记）


##  7.3 图的遍历
从图中某一顶点出发访遍图中其余顶点，且使每一个顶点仅被访问一次。这一过程就叫做**图的遍历（Traversing Graph）**
### 7.3.1 深度优先搜索（Depth-First Search）
类似于数的先根序遍历

DFS stands for Depth-First Search, which is an algorithm used to traverse or search through a graph or tree data structure. It starts at a specific node (often called the "root" node in a tree) and explores as far as possible along each branch before backtracking.

DFS follows a simple principle of exploring deeper into a graph or tree structure before exploring its siblings or neighboring nodes. It uses a stack data structure to keep track of nodes to be visited.

Here's a high-level overview of how DFS works:

1. Start with a specific node (the starting node) and mark it as visited.
2. Explore the node by processing it according to the specific problem or task.
3. Visit an unvisited neighbor of the current node.
4. If there are no unvisited neighbors, backtrack by returning to the previous node.
5. Repeat steps 2-4 until all reachable nodes have been visited.

DFS is often implemented using **recursion** or an explicit **stack** data structure. When implemented recursively, the call stack itself acts as the stack data structure.

DFS has various applications, such as:
- Finding a path or cycle in a graph.
- Topological sorting of nodes in a directed acyclic graph (DAG).
- Generating a spanning tree of a graph.
- Solving puzzles and mazes.
- Detecting connected components in a graph.
- Finding strongly connected components in a graph.

Overall, DFS is a fundamental graph traversal algorithm that helps in exploring and analyzing the structure of a graph or tree.

The **time complexity of DFS** can vary depending on the storage structure used to keep track of visited nodes. The two commonly used storage structures are:

1. Adjacency List:
   - If the graph is represented using an adjacency list, where each node maintains a list of its neighboring nodes, the time complexity of DFS is typically O(|V| + |E|) **, where |V| represents the number of vertices (nodes) in the graph and |E| represents the number of edges.
   - In this case, accessing the neighbors of each node takes O(1) time on average. The overall time complexity depends on the number of nodes and the number of edges in the graph.

2. Adjacency Matrix:
   - If the graph is represented using an adjacency matrix, where a 2D matrix is used to represent the presence or absence of edges between nodes, the time complexity of DFS is typically O(|V|^2).
   - In this case, checking the presence of an edge between two nodes takes constant time (O(1)), but we may need to check all the edges for a particular node, resulting in O(|V|) time complexity for each node.
   - As a result, the overall time complexity becomes O(|V|^2), where |V| is the number of vertices (nodes) in the graph.

### 7.3.2 广度优先搜索
类似于树的按层次遍历的过程

BFS stands for Breadth-First Search, which is another algorithm used to traverse or search through a graph or tree data structure. Unlike DFS, which explores nodes in depth first, **BFS explores the neighboring nodes at the same level before moving on to nodes at the next level**.

BFS follows a simple principle of exploring all the neighbors of a node before moving on to their neighbors. It uses a queue data structure to keep track of nodes to be visited.

Here's a high-level overview of how BFS works:

1. Start with a specific node (the starting node) and enqueue it into a queue.
2. Mark the starting node as visited.
3. Dequeue a node from the front of the queue.
4. Explore the node by processing it according to the specific problem or task.
5. Enqueue all the unvisited neighbors of the current node into the queue.
6. Mark each visited neighbor node and repeat steps 3-5 until the queue is empty.

BFS ensures that nodes are visited in a breadth-wise manner, meaning that all nodes at the same level (or distance from the starting node) are visited before moving on to the nodes at the next level.

BFS is often used to solve problems that require finding the shortest path between two nodes, detecting connected components, or exploring a graph in a systematic manner.

The **time complexity** of BFS is typically O(|V| + |E|), where |V| represents the number of vertices (nodes) in the graph and |E| represents the number of edges. This is because BFS visits each vertex and each edge exactly once, and the time complexity of enqueueing and dequeueing nodes is typically O(1).

In terms of the **space complexity**, BFS requires additional memory to store the visited nodes and the queue. The space complexity is also O(|V|) as it needs to store all the nodes in the worst case scenario.

Overall, BFS is a widely used algorithm for traversing or searching a graph in a breadth-wise manner, exploring nodes level by level.

## 7.4 图的连通性问题
### 7.4.1 无向图的连通分量和生成树
在对无向图进行遍历时，对于连通图，仅需从图中任—顶点出发，进行深度优先搜索或广度优先搜索，便可访问到图中所有顶点。对非连通图，则需从多个顶点出发进行搜
索，而每一次从一个新的起始点出发进行搜索过程中得到的顶点访问序列恰为其各个连通分量中的顶点集。
```sql
--判断一个无向图是否是连通
function isConnected(graph):
    if graph is empty:
        return True
        
    create a set called visited
    select an arbitrary start_node
    
    DFS(graph, start_node, visited)
    
    return len(visited) == total number of nodes in the graph

function DFS(graph, node, visited):
    mark node as visited
    
    for each neighbor in graph.adjacentNodes(node):
        if neighbor is not in visited:
            DFS(graph, neighbor, visited)
```
* 对于连通图，从任意一个顶点出发进行遍历，便可访问图中的所有顶点。加上遍历中经过的边，构成图的一个极小连通子图，也是图的生成树。
* 对于非连通图，需要进行多次遍历，得到若干棵生成树，构成一个生成树森林。

### 7.4.2 有向图的强连通分量
* 强连通，图中任意两点之间都存在互相可达的路径
```sql
--强连通
function isStronglyConnected(graph):
    if graph is empty:
        return True
        
    create a set called visited
    
    for each node in graph.nodes:
        DFS(graph, node, visited)
        
        if len(visited) != total number of nodes in the graph:
            return False
            
        clear the visited set
        
    return True
    

function DFS(graph, node, visited):
    mark node as visited
    
    for each neighbor in graph.adjacentNodes(node):
        if neighbor is not in visited:
            DFS(graph, neighbor, visited)
```
* 强连通分量：可以使用**Kosaraju 算法**和 **Tarjan算法**寻找图的强连通分量，两者的时间复杂度都为O(|V| + |E|)

### 7.4.3 最小生成树
最小生成树问题是指在由m个节点和n条边组成的网络模型中寻找连接所有节点的生成树，使得其所有边的权值之和最小. 最小生成树问题广泛应用于系统设计、选址规划等组合优化问题中. 
常见的最小生成树算法有Kruskal算法和Prim算法. Kruskal算法是一种基于贪心策略的算法，它按照边权值从小到大的顺序选择边，并且保证所选的边不会与已选的边形成环. Prim算法是一种基于贪心策略的算法，它从一个点开始，每次选择一个与当前生成树距离最近的点，并将该点加入到生成树中.
* **MST性质**: 假设 N=(V,{E})是一个连通网，U是顶点集V的一个非空子集。若(u,v)是一条具有最小权值(代价)的边，其中$u \in U$，$v\in(V-U)$，则必存在一棵包含边(u,v)的最小生成树

### 7.4.4 关节点和重连通分量
* 假若在删去顶点v以及和v相关联的各边之后，将图的一个连通分量分割成两个或两个以上的连通分量，则称顶点v为该图的一个**关节点（articulation point）**
* 一个没有关节点的连通图称为是**重连通图（biconnected graph）**，在重连通图上，任意一对顶点之间至少存在两条路径，则在删去某个顶点以及依附于该顶点的各边时也不破坏图的连通性。
* 若在连通图上至少制去k个顶点才能破坏图的连通性，则称此图的**连通度为k**。

## 7.5 有向无环图及其应用
一个无环的有向图称做**有向无环图（directed acycline graph）**，简称DAG图。有向无环图是描述含有公共子式的表达式的有效工具。
### 7.5.1 拓扑排序
**拓扑排序（Topological Sort）**: 简单地说，由某个集合上的一个偏序得到该集合上的一个全序。
* **偏序关系**是指集合中的元素之间存在一种偏序关系，即存在一种元素之间的先后关系，但并不是所有元素之间都有这种先后关系。偏序关系具有自反性、反对称性和传递性。比如集合之间的包含关系，就是一个偏序关系。
* **全序关系**是指集合中的元素之间存在一种先后关系，且所有元素之间都有这种先后关系。全序关系具有自反性、反对称性、传递性和完全性。一个常见的全序关系是自然数集合上的小于等于关系，即对于任意两个自然数a和b，都有a≤b或b≤a
* 用顶点表示活动，用弧表示活动间的优先关系的有向图（Activity On Vertex Network），简称 **AOV-网**
* 如何进行拓扑排序?解决的方法很简单：\
（1）在有向图中选一个没有前驱的顶点且输出之。\
（2）从图中删除该顶点和所有以它为尾的弧。\
重复上述两步，直至全部顶点均已输出，或者当前图中不存在无前驱的顶点为止。后一种惰况则说明有向图中存在环。
### 7.5.2 关键路径
**AOE-网**是一个带权的有向无环图，其中，顶点表示事件（Event），弧表示活动，权表示活动持续的时间。通常，AOE-网可用来估算工程的完成时间。
* 在AOE网中，从源点到汇点最长的路径称为**关键路径**，关键路径上的活动称为**关键活动**

## 7.6 最短路径
* 从某个源点到其余各顶点的最短路径：迪杰斯特拉（Dijkstra）算法
* 每一对顶点之词的最短路径：弗洛伊德（Floyd）算法