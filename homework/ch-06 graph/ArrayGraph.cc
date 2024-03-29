#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <stack>
#include <cassert>
#include <iterator>
#include <queue>
#include <deque>
#include <iomanip>
#include <climits>

#include "UnionFind.h"

using std::cout;
using std::endl;

template<typename T>
using Matrix = std::vector<std::vector<T>>;

template<typename T>
using Array = std::vector<T>;

template<typename T>
using Array2D = Matrix<T>;

template<typename T>
using Array3D = Array<Matrix<T>>;

template<typename T>
using NodeList = std::vector<T>;

using Edge = std::pair<int, int>;

using EdgeList = std::vector<Edge>;

template<typename T> class ArrayGraph;

template<typename T>
using CcList = std::vector<ArrayGraph<T>>;

template<typename T>
using SccList = std::vector<ArrayGraph<T>>;

using WeightList = std::vector<std::pair<Edge, double>>;

const int INF = INT_MAX;

static void displayEdgeList(const EdgeList& edges)
{
	for(const auto& pair: edges)
	{
		std::cout << "<" << pair.first << "," << pair.second << ">";
	}
	std::cout << std::endl;
}

//static void displayWeightList(const WeightList& weightList) {
//    for (const auto& pair : weightList) {
//        const Edge& edge = pair.first;
//        double weight = pair.second;
//        std::cout << "Edge: " << edge.first << " -> " << edge.second << ", Weight: " << weight << std::endl;
//    }
//}

template<typename Q>
void displayQueue(Q q)
{
	while(!q.empty())
	{
		const auto& min = q.top();
		std::cout << "{" << min.first << "," << min.second << "}"<< std::endl;
		q.pop();
	}
}

template<typename T>
bool operator==(const Matrix<T>& a, const Matrix<T>& b)
{
	if(a.size() == b.size())
	{
		for(size_t i = 0; i < a.size(); ++i)
		{
			if(a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename T>
class ArrayGraph
{
public:
    enum ArrayGraphType { DGRAPH, GRAPH };

    ArrayGraph(ArrayGraphType type);
    ArrayGraph(const ArrayGraph&) = default;

    void addNodes(int number);
	void addNode()
	{ addNodes(1); }
    void addEdge(const Edge& edge, double w = 1.0);
    void addEdges(const Matrix<int>& edges);

	int numberOfNodes(void) const
	{ return numberOfNodes_; }

	const Matrix<int>& getEdges(void) const
	{
		return edges_;
	}

    template<typename Unary>
    void BFS(const Unary& op) const;

    template<typename Unary>
    void DFS(const Unary& op, bool post = false) const;

	// only valid in a directed graph
	int getInDegree(int v) const;

	// only valid in a directed graph
	int getOutDegree(int v) const;

	//only valid in a undirected graph
	int getDegree(int v) const;

	CcList<T> getConnectedComponents(void) const;
	bool isConnected(void) const;

	ArrayGraph transpose(void) const;
	/** Kosaraju*/
	SccList<T> getStronglyConnectedComponents(void) const;
	
	/** tarjan*/
	SccList<T> getStronglyConnectedComponentsTarjan(void) const;

	/** Caculate minimum spanning tree by prime algorithm. Only valid for connected graphs*/
	WeightList MSTPrim(void) const;
	
	/** Caculate minimum spanning tree by kruskal algorithm. Only valid for connected graphs*/
	WeightList MSTKruskal(void) const;

	/** Caculate topo sort: Only valid for directed graph*/
	NodeList<T> topoSort(void) const;

	/** Find articul node: Only valid for connected graph. time=O(|V| + |E|), space=O(|V|)*/
	NodeList<bool> findArticulTarjan(void) const;

	/** Fine critical path: Only invalid for directed graph*/
	EdgeList findCriticalPath(void) const;

	/** Single source node min paths */
	void singleSourceMinimumPathDijkstra(int start, std::vector<int>& D, Matrix<bool>& path) const;

	/** Multiple source min path*/
	void multipleSourceMinmunPathFloyd(Array2D<int>& D, Array3D<bool>& path);

private:

    ArrayGraphType type_;
    Matrix<int> edges_;
    int numberOfNodes_;

	static const int UNDEFINED;

    template<typename Unary>
    void DFSUtil(int node, std::vector<bool>& visited, const Unary& op, bool post = false) const;

	void getStronglyConnectedComponentsTarjan(int v, int& index, std::vector<int>& dsn, std::vector<int>& low, std::vector<int>& s, SccList<T>& sccs) const;
	void findArticulTarjanUtil(int v, int& index, std::vector<int>& dsn, std::vector<int>& low, NodeList<bool>& nodes) const;
};

template<typename T>
const int ArrayGraph<T>:: UNDEFINED = -1;

template<typename T>
ArrayGraph<T>::ArrayGraph(ArrayGraphType type) : type_(type), numberOfNodes_(0)
{
}


template<typename T>
void ArrayGraph<T>::addNodes(int number)
{
	for(auto& v: edges_)
	{
		std::fill_n(std::back_inserter(v), number, 0);
	}
	std::fill_n(std::back_inserter(edges_), number, std::vector<int>(number + numberOfNodes_, 0));
	numberOfNodes_ += number;
}

template<typename T>
void displayMatrix(const Matrix<T>& matrix)
{
    for (const auto& row : matrix)
    {
        for (const auto& element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void displayStack(std::stack<T> s)
{
	while(!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << endl;
}

template<typename T>
void displayNodeList(const NodeList<T>& nodes)
{
	for(const T& v: nodes)
	{
		cout << v << " ";
	}
	cout << endl;
}

template<typename T>
void ArrayGraph<T>::addEdge(const Edge& edge, double w)
{
    int from = edge.first;
    int to = edge.second;
    if (from < 0 || from >= (int)edges_.size() ||
        to < 0 || to >= (int)edges_[0].size())
    {
        throw std::out_of_range("Invalid node index");
    }

    edges_[from][to] = w;

    if (type_ == GRAPH)
        edges_[to][from] = w;
}

template<typename T>
void ArrayGraph<T>::addEdges(const Matrix<int>& edges)
{
    for (const auto& edge : edges)
    {
        if (edge.size() != 2)
        {
            throw std::invalid_argument("Invalid edge format");
        }
        addEdge(std::make_pair(edge[0], edge[1]));
    }
}

template<typename T>
template<typename Unary>
void ArrayGraph<T>::BFS(const Unary& op) const
{
    std::vector<bool> visited(numberOfNodes_, false);
    std::queue<int> queue;

    for (int i = 0; i < numberOfNodes_; ++i)
    {
        if (visited[i])
            continue;

        queue.push(i);
        visited[i] = true;

        while (!queue.empty())
        {
            int current = queue.front();
            queue.pop();
            op(current);

            for (int neighbor = 0; neighbor < numberOfNodes_; ++neighbor)
            {
                if (edges_[current][neighbor] && !visited[neighbor])
                {
                    queue.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
}

template<typename T>
template<typename Unary>
void ArrayGraph<T>::DFS(const Unary& op, bool post) const
{
    std::vector<bool> visited(numberOfNodes_, false);

    for (int i = 0; i < numberOfNodes_; ++i)
    {
        if (!visited[i])
            DFSUtil(i, visited, op, post);
    }
}

template<typename T>
template<typename Unary>
void ArrayGraph<T>::DFSUtil(int node, std::vector<bool>& visited, const Unary& op, bool post) const
{
    visited[node] = true;
	if(!post)
	{
		op(node);
	}

    for (int neighbor = 0; neighbor < numberOfNodes_; ++neighbor)
    {
        if (edges_[node][neighbor]  && !visited[neighbor])
            DFSUtil(neighbor, visited, op, post);
    }
	
	if(post)
	{
		op(node);
	}
}

template<typename T>
int ArrayGraph<T>::getInDegree(int v) const
{
	if(type_ == DGRAPH)
	{
		int ID = 0;
		for(const auto& row: edges_)
		{
			ID += (row[v])?1:0;
		}
		return ID;
	}
	else
	{
		throw std::logic_error("Error: getInDegree() is only valid in a directed graph");
	}
}

template<typename T>
int ArrayGraph<T>::getOutDegree(int v) const
{
	if(type_ == DGRAPH)
	{
		int ID = 0;
		for(const auto& e: edges_[v])
		{
			ID += e?1:0;
		}
		return ID;
	}
	else
	{
		throw std::logic_error("Error: getInDegree() is only valid in a directed graph");
	}
}

template<typename T>
int ArrayGraph<T>::getDegree(int v) const
{
	if(type_ == GRAPH)
	{
		int ID = 0;
		for(const auto& e: edges_[v])
		{
			ID += e;
		}
		return ID;
	}
	else
	{
		throw std::logic_error("Error: getInDegree() is only valid in a directed graph");
	}
}

template<typename T>
CcList<T> ArrayGraph<T>::getConnectedComponents(void) const
{
	if(type_ == GRAPH)
	{
		CcList<T> ccList;
		std::vector<bool> visited(numberOfNodes_, 0);
		
		for(int i = 0; i < numberOfNodes_; ++i)
		{
			if(!visited[i])
			{
				std::vector<int> indexList;
				ArrayGraph<T> subGraph(GRAPH);
				DFSUtil(i, visited, [&indexList](int x) { indexList.push_back(x);});
				subGraph.addNodes(indexList.size());

				for(size_t k = 0; k < indexList.size(); ++k)
				{
					for(size_t s = 0; s < indexList.size(); ++s)
					{
						if(edges_[indexList[k]][indexList[s]])
						{
							subGraph.addEdge({k, s});
						}
					}
				}
				ccList.emplace_back(std::move(subGraph));
			}
		}
		return ccList;
	}
	else
	{
		throw std::logic_error("Invalid DGRAPH: getConnectedComponents");
	}
}

template<typename T>
ArrayGraph<T> ArrayGraph<T>::transpose(void) const
{
	assert(type_ == DGRAPH);
	ArrayGraph tGraph(DGRAPH);
	tGraph.addNodes(numberOfNodes_);
	for(int i = 0; i < numberOfNodes_; ++i)
	{
		for(int j = 0; j < numberOfNodes_; ++j)
		{
			if(edges_[i][j])
			{
				tGraph.addEdge({j, i});
			}
		}
	}
	return tGraph;
}

template<typename T>
bool ArrayGraph<T>::isConnected(void) const
{
	if(type_ == GRAPH)
	{
		std::vector<bool> visited(numberOfNodes_, false);
		size_t visited_count = 0;
		DFSUtil(0, visited, [&visited_count](int) { ++visited_count;});
		return visited_count == visited.size();
	}
	else
	{
		throw std::logic_error("Error: isConnected is only valid in a undirected graph");
	}
}


template<typename T>
SccList<T> ArrayGraph<T>::getStronglyConnectedComponents(void) const
{
	assert(type_ == DGRAPH);

	/** DFS on original graph and get finished*/
	std::stack<int> finished;
	DFS([&finished](int x) { finished.push(x); }, true);

	/** Get transpose graph*/
	auto tGraph = transpose();

	std::vector<bool> visited(numberOfNodes_, false);
	SccList<T> sccList;
	/** DFS on the reversed graph according to finished*/
	while(!finished.empty())
	{
		size_t index = finished.top();
		if(!visited[index])
		{
			std::vector<size_t> subIndexs;
			ArrayGraph<T> subGraph(DGRAPH);
			tGraph.DFSUtil(index, visited, [&subIndexs, &subGraph](int x) 
						{ subIndexs.push_back(x);});
			subGraph.addNodes(subIndexs.size());
			for(size_t k = 0; k < subIndexs.size(); ++k)
			{
				for(size_t s = 0; s < subIndexs.size(); ++s)
				{
					if(edges_[subIndexs[k]][subIndexs[s]])
					{
						subGraph.addEdge({k, s});
					}
				}
			}
			sccList.emplace_back(std::move(subGraph));
		}
		finished.pop();
	}
	return sccList;
}


template<typename T>
void ArrayGraph<T>::getStronglyConnectedComponentsTarjan(int v, int& index, std::vector<int>& dsn, std::vector<int>& low, std::vector<int>& s, SccList<T>& sccs) const
{
	dsn[v] = low[v] = index++;
	s.push_back(v);
	for(int w = 0; w < numberOfNodes_; ++w)
	{
		if(edges_[v][w])
		{
			if(dsn[w] == UNDEFINED)
			{// 后继节点未访问
				getStronglyConnectedComponentsTarjan(w, index, dsn, low, s, sccs);
				low[v] = std::min(low[v], low[w]);

			}
			else if(std::find(s.begin(), s.end(), w) != s.end())
			{//w已在栈S中，则其也在当前的强连通分量中
				low[v] = std::min(low[v], dsn[w]);
			}
		}

	}
	
	if(dsn[v] == low[v])
	{
		ArrayGraph<T> subGraph(DGRAPH);
		std::vector<int> subIndexs;
		int w;
		do
		{
			w = s.back();
			s.pop_back();
			subIndexs.push_back(w);
		}while(w != v);
		subGraph.addNodes(subIndexs.size());
		for(size_t i = 0; i < subIndexs.size(); ++i)
		{
			for(size_t j = 0; j < subIndexs.size(); ++j)
			{
				if(edges_[subIndexs[i]][subIndexs[j]])
				{
					subGraph.addEdge({i, j});
				}
			}
		}
		sccs.emplace_back(std::move(subGraph));
	}
}

template<typename T>
SccList<T> ArrayGraph<T>::getStronglyConnectedComponentsTarjan(void) const
{
	assert(type_ == DGRAPH);
	int index = 0;
	std::vector<int> dsn(numberOfNodes_, UNDEFINED);
	std::vector<int> low(numberOfNodes_, UNDEFINED);
	std::vector<int> s;
	SccList<T> sccs;
	for(int v = 0; v < numberOfNodes_; ++v)
	{
		if(dsn[v] == UNDEFINED)
		{
			getStronglyConnectedComponentsTarjan(v, index, dsn, low, s, sccs);
		}
	}
	return sccs;
}

template<typename T>
void ArrayGraph<T>::findArticulTarjanUtil(int v, int& index, std::vector<int>& dsn, std::vector<int>& low, NodeList<bool>& nodes) const
{
	dsn[v] = low[v] = index++;
	for(int w = 0; w < numberOfNodes_; ++w)
	{
		if(edges_[v][w])
		{
			if(dsn[w] == UNDEFINED)
			{// 后继节点w未访问
				findArticulTarjanUtil(w, index, dsn, low, nodes);
				low[v] = std::min(low[v], low[w]);
				if(low[w] >= dsn[v])
				{//w[w]≥dsn[v]，表明w及其子孙均无指向v的祖先的回边
					nodes[v] = true;
				}
			}
			else
			{// 祖先节点w
				low[v] = std::min(low[v], dsn[w]);
			}
		}
	}
}

template<typename T>
NodeList<bool> ArrayGraph<T>::findArticulTarjan(void) const
{
	int index = 0;
	std::vector<int> dsn(numberOfNodes_, UNDEFINED);
	std::vector<int> low(numberOfNodes_, UNDEFINED);
	NodeList<bool> nodes(numberOfNodes_, false);
	findArticulTarjanUtil(0, index, dsn, low, nodes);
	if(static_cast<int>(nodes.size()) < numberOfNodes_)
	{
		nodes.push_back(0);
	}
	for(int w = 1; w < numberOfNodes_; ++w)
	{
		if(edges_[0][w])
		{
			if(dsn[w] == UNDEFINED)
			{
				findArticulTarjanUtil(w, index, dsn, low, nodes);
			}
		}
	}
	return nodes;
}

/**O(V^2 + E log E) */
template<typename T>
WeightList ArrayGraph<T>::MSTPrim(void) const
{
	assert(type_ == GRAPH);

	WeightList results;
	if(numberOfNodes_ == 0)
	{
		return results;
	}
	std::vector<bool> inU(numberOfNodes_, false);
	inU[0] = true;
	int inUCount = 1;
	auto cmp = [this](const Edge& a, const Edge& b) { return edges_[a.first][a.second] > edges_[b.first][b.second]; };
	/** min cost between  U and V - U*/
	std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> q(cmp);

	while(inUCount < numberOfNodes_)
	{
		for(int v = 0; v < numberOfNodes_; ++v)
		{
			if(inU[v])
			{
				for(int w = 0; w < numberOfNodes_; ++w)
				{
					if(!inU[w] && edges_[v][w])// v in U and w in V-U
					{
						q.emplace(Edge(v, w));
					}
				}
			}
		}
		//displayQueue(q);
		while(!q.empty())
		{
			const Edge& min = q.top();
			if(inU[min.second] == true) 
			{//avoid cycle
				q.pop();
				continue;
			}
			//std::cout << "min: {" << min.first.first << "," << min.first.second << "}:" << min.second << std::endl;
			inU[min.second] = true;
			//std::cout << "add: " << min.first.second << std::endl;
			results.emplace_back(min, edges_[min.first][min.second]);
			q.pop();
			++inUCount;
			break;
		}
	}
	return results;
}

/**time: O(E log E + E log V), space: O(E + V) */
template<typename T>
WeightList ArrayGraph<T>::MSTKruskal(void) const
{
	assert(type_ == GRAPH);

	WeightList results;
	if(numberOfNodes_ == 0)
	{
		return results;
	}
	auto cmp = [this](const Edge& a, const Edge& b) { return edges_[a.first][a.second] > edges_[b.first][b.second]; };
	std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> q(cmp);
	for(int v = 0; v < numberOfNodes_; ++v)
	{//O(E log E)
		for(int w = 0; w < numberOfNodes_; ++w)
		{
			if(v <= w && edges_[v][w])
			{
				q.emplace(v, w);
			}
		}
	}
	UnionFind uf(numberOfNodes_);//O(V)

	while(uf.count() != 1 && !q.empty())
	{//O(E log V)
		const Edge& min = q.top();
		//displayQueue(q);
		if(uf.connected(min.first, min.second)) 
		{
			q.pop();
			continue;
		}
		uf.unite(min.first, min.second);
		results.emplace_back(min, edges_[min.first][min.second]);
		q.pop();
	}
	return results;
}

template<typename T>
NodeList<T> ArrayGraph<T>::topoSort(void) const
{
	std::deque<int> q;
	std::vector<int> IDs(numberOfNodes_);
	NodeList<T> nodes;
	for(int v = 0; v < numberOfNodes_; ++v)
	{
		int ID = getInDegree(v);
		//std::cout << "v=" << v << ": " << ID << std::endl;
		IDs[v] = ID;
		if(ID == 0)
		{
			q.push_back(v);
		}
	}

	while(!q.empty())
	{
		int v = q.front();
		q.pop_front();
		nodes.push_back(v);
		for(int w = 0; w < numberOfNodes_; ++ w)
		{
			if(edges_[v][w] && (--IDs[w]) == 0)
			{
				q.push_back(w);
			}
		}
	}
	return nodes;
}

template<typename T>
EdgeList ArrayGraph<T>::findCriticalPath(void) const
{
	assert(type_ == DGRAPH);
	std::vector<Edge> criticals;
	std::vector<int> ve(numberOfNodes_, 0);
	std::vector<int> vl(numberOfNodes_, INT_MAX);

	// get topo sort
	NodeList<int> topos = topoSort();
	assert(static_cast<int>(topos.size()) == numberOfNodes_); //不能存在环
	std::cout << "topos: ";
	displayNodeList(topos);

	// ve[j] = max{ve[i] + weight<i, j>}, <i, j> in E
	ve[topos.front()] = 0;
	for(size_t x = 0; x < topos.size(); ++x)
	{
		int i = topos[x];
		for(int j = 0; j < numberOfNodes_; ++j)
		{
			if(edges_[i][j])
			{
				ve[j] = std::max(ve[j], ve[i] + edges_[i][j]);
			}
		}
	}
	std::cout << "ve:";
	displayNodeList(ve);

	// vl[i] = min{vl[j] - weight<i, j>}, <i, j> in E
	vl[topos.back()] = ve[topos.back()];
	for(int x = topos.size() - 1; x >= 0; --x)
	{
		int j = topos[x];
		for(int i = 0; i < numberOfNodes_; ++i)
		{
			if(edges_[i][j])
			{
				vl[i] = std::min(vl[i], vl[j] - edges_[i][j]);
			}
		}
	}
	std::cout << "vl:";
	displayNodeList(vl);

	// e[i] = ve[i]
	// l[i] = vl[k] - weight<i, k>, <i, k> in E
	// e[i] == l[i], critical activity
	for(int i = 0; i < numberOfNodes_; ++i)
	{
		int ei = ve[i];
		for(int k = 0; k < numberOfNodes_; ++k)
		{
			if(edges_[i][k])
			{
				int li = vl[k] - edges_[i][k];
				if(ei == li)
				{
					criticals.emplace_back(i, k);
				}
			}
		}
	}
	return criticals;
}

template<typename T>
void ArrayGraph<T>::singleSourceMinimumPathDijkstra(int start, std::vector<int>& D, Matrix<bool>& path) const
{
	std::vector<bool> inS(numberOfNodes_, false);
	D = std::move(std::vector<int>(numberOfNodes_, INF));
	path = std::move(Matrix<bool>(numberOfNodes_, std::vector<bool>(numberOfNodes_, false)));
	int count = 0;

	//start state
	inS[start] = true;
	D[start] = 0;
	path[start][start] = true;
	++count;
	for(int v = 0; v < numberOfNodes_; ++v)
	{
		if(edges_[start][v])
		{
			D[v] = edges_[start][v];
			path[v][start] = true;
			path[v][v] = true;
		}
	}

	while(count < numberOfNodes_)
	{
		//find min
		int minj = 0;
		int min = INF;
		for(int j = 0; j < numberOfNodes_; ++j)
		{
			if(!inS[j] && D[j] != INF && D[j] < min)
			{
				minj = j;
				min = D[j];
			}
		}
		inS[minj] = true;
		++count;

		//update D and path
		for(int k = 0; k < numberOfNodes_; ++k)
		{
			if(!inS[k] && edges_[minj][k])
			{
				bool updated = false;
				if(D[k] != INF)
				{
					if(edges_[minj][k] + D[minj] < D[k])
					{
						updated = true;
						D[k] = D[minj] + edges_[minj][k];
					}
				}
				else
				{
					updated = true;
					D[k] = D[minj] + edges_[minj][k];
				}
				if(updated)
				{
					path[k] = path[minj];
					path[k][k] = true;
				}
			}
		}
	}
}

template<typename T>
void ArrayGraph<T>::multipleSourceMinmunPathFloyd(Array2D<int>& D, Array3D<bool>& path)
{
	D = std::move(Array2D<int>(numberOfNodes_, Array<int>(numberOfNodes_, INF)));
	path = std::move(Array3D<bool>(numberOfNodes_, Array2D<bool>(numberOfNodes_, Array<bool>(numberOfNodes_, false))));

	//start state
	for(int v = 0; v < numberOfNodes_; ++v)
	{
		for(int w = 0; w < numberOfNodes_; ++w)
		{
			if(edges_[v][w])
			{
				D[v][w] = edges_[v][w];
				path[v][w][v] = true;
				path[v][w][w] = true;
			}
			else if(v == w)
			{
				D[v][w] = 0;
				path[v][w][w] = true;
			}
		}
	}
	//std::cout << "start state: \n";
	//displayMatrix(D);

	//scan n times
	for(int x = 0; x < numberOfNodes_; ++x)
	{
		for(int v = 0; v < numberOfNodes_; ++v)
		{
			for(int w = 0; w < numberOfNodes_; ++w)
			{
				//there is a shorter path(v,...,x,...,w) 
				if(D[v][x] != INF &&  D[x][w] != INF && D[v][x] + D[x][w] < D[v][w]) 
				{
					D[v][w] = D[v][x] + D[x][w];
					for(int k = 0; k < numberOfNodes_; ++k)
					{
						path[v][w][k] = path[v][x][k] | path[x][w][k];
					}
				}
			}
		}
		//std::cout << "x = " << x << std::endl;
		//displayMatrix(D);
	}
}

int main(void)
{
	/** test graph constructor */
	{//empty
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		assert(graph.numberOfNodes() == 0);
		const Matrix<int>& E = graph.getEdges();
		assert(E == Matrix<int>({}));
	}
	{//one at a time
		{
			ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
			graph.addNode();
			graph.addNode();
			graph.addNode();
			graph.addEdge({0, 1});
			graph.addEdge({1, 2});
			graph.addEdge({2, 0});
			assert(graph.numberOfNodes() == 3);
			const Matrix<int>& E = graph.getEdges();
			assert(E[0] == std::vector<int>({0, 1, 1}));
			assert(E[1] == std::vector<int>({1, 0, 1}));
			assert(E[2] == std::vector<int>({1, 1, 0}));

			std::vector<int> results;
			graph.DFS([&results](int x) { results.push_back(x); });
			assert(results == std::vector<int>({0,1,2}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({0,1,2}));

			assert(2 == graph.getDegree(0));
			assert(2 == graph.getDegree(1));
			assert(2 == graph.getDegree(2));

		}
		{
			ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
			graph.addNode();
			graph.addNode();
			graph.addNode();
			graph.addEdge({0, 1});
			graph.addEdge({1, 2});
			graph.addEdge({2, 0});
			const Matrix<int>& E = graph.getEdges();
			assert(graph.numberOfNodes() == 3);
			assert(E[0] == std::vector<int>({0, 1, 0}));
			assert(E[1] == std::vector<int>({0, 0, 1}));
			assert(E[2] == std::vector<int>({1, 0, 0}));

			std::vector<int> results;
			graph.DFS([&results](int x) { results.push_back(x); });
			assert(results == std::vector<int>({0,1,2}));

			std::vector<int> results2;
			graph.DFS([&results2](int x) { results2.push_back(x); }, true);
			assert(results2 == std::vector<int>({2,1,0}));
			
			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({0,1,2}));

			assert(1 == graph.getInDegree(0));
			assert(1 == graph.getOutDegree(0));
			assert(1 == graph.getInDegree(1));
			assert(1 == graph.getOutDegree(1));
			assert(1 == graph.getInDegree(2));
			assert(1 == graph.getOutDegree(2));
		}
	}
	{//multiple at a time
		{
			ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
			graph.addNodes(3);
			graph.addEdges({{0, 1}, {1, 2}, {2, 0}});
			assert(graph.numberOfNodes() == 3);
			const Matrix<int>& E = graph.getEdges();
			assert(E[0] == std::vector<int>({0, 1, 1}));
			assert(E[1] == std::vector<int>({1, 0, 1}));
			assert(E[2] == std::vector<int>({1, 1, 0}));

			std::vector<int> results;
			graph.DFS([&results](int x) { results.push_back(x); });
			assert(results == std::vector<int>({0,1,2}));
			
			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({0,1,2}));

			assert(2 == graph.getDegree(0));
			assert(2 == graph.getDegree(1));
			assert(2 == graph.getDegree(2));
		}
		{
			ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
			graph.addNodes(3);
			graph.addEdges({{0, 1}, {1, 2}, {2, 0}});
			assert(graph.numberOfNodes() == 3);
			const Matrix<int>& E = graph.getEdges();
			assert(E[0] == std::vector<int>({0, 1, 0}));
			assert(E[1] == std::vector<int>({0, 0, 1}));
			assert(E[2] == std::vector<int>({1, 0, 0}));

			std::vector<int> results;
			graph.DFS([&results](int x) { results.push_back(x); });
			assert(results == std::vector<int>({0,1,2}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({0,1,2}));

			std::vector<int> results2;
			graph.DFS([&results2](int x) { results2.push_back(x); }, true);
			assert(results2 == std::vector<int>({2,1,0}));

			assert(1 == graph.getInDegree(0));
			assert(1 == graph.getOutDegree(0));
			assert(1 == graph.getInDegree(1));
			assert(1 == graph.getOutDegree(1));
			assert(1 == graph.getInDegree(2));
			assert(1 == graph.getOutDegree(2));
		}
	}


	/** test getConnectedComponents and isConnected*/
	{// single node
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode();
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 1);
		assert(cc[0].numberOfNodes() == 1);

		assert(graph.isConnected());
	}
	{// 2 + 1
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addEdge({0, 1});
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 2);
		assert(cc[0].numberOfNodes() == 2);
		assert(cc[0].getEdges()[0] == std::vector<int>({0, 1}));
		assert(cc[0].getEdges()[1] == std::vector<int>({1, 0}));
		assert(cc[1].numberOfNodes() == 1);
		assert(cc[1].getEdges()== Matrix<int>({{0}}));

		assert(!graph.isConnected());
	}
	{//2 + 2
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addEdge({0, 1});
		graph.addEdge({2, 3});
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 2);
		assert(cc[0].numberOfNodes() == 2);
		assert(cc[0].getEdges()[0] == std::vector<int>({0, 1}));
		assert(cc[0].getEdges()[1] == std::vector<int>({1, 0}));
		assert(cc[0].numberOfNodes() == 2);
		assert(cc[1].getEdges()[0] == std::vector<int>({0, 1}));
		assert(cc[1].getEdges()[1] == std::vector<int>({1, 0}));

		assert(!graph.isConnected());
	}
	{//connected graph
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addEdge({0, 1});
		graph.addEdge({1, 2});
		graph.addEdge({2, 0});
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 1);
		assert(cc[0].numberOfNodes() == 3);
		assert(cc[0].getEdges()[0] == std::vector<int>({0, 1, 1}));
		assert(cc[0].getEdges()[1] == std::vector<int>({1, 0, 1}));
		assert(cc[0].getEdges()[2] == std::vector<int>({1, 1, 0}));

		assert(graph.isConnected());
	}

	/** test transpose*/
	{// zero edge
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode();
		
		auto tGraph = graph.transpose();
		assert(tGraph.numberOfNodes() == 1);
		assert(tGraph.getEdges() == Matrix<int>({{0}}));
	}
	{//one
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addEdge({0, 1});

		auto tGraph = graph.transpose();
		assert(tGraph.numberOfNodes() == 3);
		assert(tGraph.getEdges() == Matrix<int>({{0,0,0}, {1,0,0}, {0,0,0}}));
	}
	{// two
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addEdge({0, 1});
		graph.addEdge({2, 3});
		
		auto tGraph = graph.transpose();
		assert(tGraph.numberOfNodes() == 4);
		assert(tGraph.getEdges() == Matrix<int>({{0,0,0,0}, {1,0,0,0}, {0,0,0,0}, {0,0,1,0}}));
	}
	{// three
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode();
		graph.addNode();
		graph.addNode();
		graph.addEdge({0, 1});
		graph.addEdge({1, 2});
		graph.addEdge({2, 0});
		
		auto tGraph = graph.transpose();
		assert(tGraph.numberOfNodes() == 3);
		assert(tGraph.getEdges() == Matrix<int>({{0,0,1},{1,0,0},{0,1,0}}));
	}

	/** test getStronglyConnectedComponents*/
	{// single node
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode();
		
		auto scc = graph.getStronglyConnectedComponents();
		assert(scc.size() == 1);
		assert(scc[0].numberOfNodes() == 1);
		assert(scc[0].getEdges() == Matrix<int>({{0}}));
	}
	{// 2 + 1
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(3);
		graph.addEdge({0, 1});
		graph.addEdge({1, 0});
		
		auto scc = graph.getStronglyConnectedComponents();
		assert(scc.size() == 2);
		assert(scc[1].numberOfNodes() == 2);
		assert(scc[1].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		assert(scc[0].numberOfNodes() == 1);
		assert(scc[0].getEdges() == Matrix<int>({{0}}));
	}
	{// 2 + 2
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(4);
		graph.addEdge({0, 1});
		graph.addEdge({1, 0});
		graph.addEdge({2, 3});
		graph.addEdge({3, 2});
		{

			auto scc = graph.getStronglyConnectedComponents();
			assert(scc.size() == 2);
			assert(scc[1].numberOfNodes() == 2);
			assert(scc[1].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
			assert(scc[0].numberOfNodes() == 2);
			assert(scc[0].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		}

		{//connect
			graph.addEdge({1, 2});

			std::vector<int> results;
			graph.DFS([&results](int x) { results.push_back(x); }, true);
			assert(results == std::vector<int>({3,2,1,0}));

			auto scc = graph.getStronglyConnectedComponents();
			assert(scc.size() == 2);
			assert(scc[0].numberOfNodes() == 2);
			assert(scc[0].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
			assert(scc[1].numberOfNodes() == 2);
			assert(scc[1].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		}
	}
	
	{// 5 + 5
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(10);

		graph.addEdge({0, 1});
		graph.addEdge({1, 2});
		graph.addEdge({2, 3});
		graph.addEdge({3, 4});
		graph.addEdge({4, 0});

		graph.addEdge({5, 6});
		graph.addEdge({6, 7});
		graph.addEdge({7, 8});
		graph.addEdge({8, 9});
		graph.addEdge({9, 5});

		{
			auto scc = graph.getStronglyConnectedComponents();
			assert(scc.size() == 2);
			assert(scc[0].numberOfNodes() == 5);
			assert(scc[0].getEdges() == Matrix<int>({
							{0,0,0,0,1},
							{1,0,0,0,0},
							{0,1,0,0,0},
							{0,0,1,0,0},
							{0,0,0,1,0}}));
			assert(scc[1].numberOfNodes() == 5);
			assert(scc[1].getEdges() == Matrix<int>({
							{0,0,0,0,1},
							{1,0,0,0,0},
							{0,1,0,0,0},
							{0,0,1,0,0},
							{0,0,0,1,0}}));
		}
		{
			graph.addEdge({4, 5});
			auto scc = graph.getStronglyConnectedComponents();
			assert(scc.size() == 2);
			assert(scc[0].numberOfNodes() == 5);
			assert(scc[0].getEdges() == Matrix<int>({
							{0,0,0,0,1},
							{1,0,0,0,0},
							{0,1,0,0,0},
							{0,0,1,0,0},
							{0,0,0,1,0}}));
			assert(scc[1].numberOfNodes() == 5);
			assert(scc[1].getEdges() == Matrix<int>({
							{0,0,0,0,1},
							{1,0,0,0,0},
							{0,1,0,0,0},
							{0,0,1,0,0},
							{0,0,0,1,0}}));
		}
	}

	/** test getStronglyConnectedComponents tarjan version*/
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode();
		
		auto scc = graph.getStronglyConnectedComponentsTarjan();
		assert(scc[0].numberOfNodes() == 1);
	}

	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(7);
		
		graph.addEdge({0, 1});
		graph.addEdge({1, 2});
		graph.addEdge({1, 4});
		graph.addEdge({1, 6});
		graph.addEdge({2, 3});
		graph.addEdge({3, 2});
		graph.addEdge({3, 4});
		graph.addEdge({3, 5});
		graph.addEdge({4, 5});
		graph.addEdge({5, 4});
		graph.addEdge({6, 0});
		graph.addEdge({6, 2});
		
		auto scc = graph.getStronglyConnectedComponentsTarjan();
		//5,4
		assert(scc.size() == 3);
		assert(scc[0].numberOfNodes() == 2);
		assert(scc[0].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		//3,2
		assert(scc[1].numberOfNodes() == 2);
		assert(scc[1].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		//6,1,0
		assert(scc[2].numberOfNodes() == 3);
		assert(scc[2].getEdges() == Matrix<int>({
						{0, 0, 1},
						{1, 0, 0},
						{0, 1, 0}
						}));
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		
		graph.addEdge({0, 1});
		graph.addEdge({0, 2});
		graph.addEdge({1, 3});
		graph.addEdge({2, 3});
		graph.addEdge({2, 4});
		graph.addEdge({3, 0});
		graph.addEdge({3, 5});
		graph.addEdge({4, 5});
		
		auto scc = graph.getStronglyConnectedComponentsTarjan();
		assert(scc.size() == 3);
		//5
		assert(scc[0].numberOfNodes() == 1);
		//4
		assert(scc[1].numberOfNodes() == 1);
		//2,3,1,0
		assert(scc[2].numberOfNodes() == 4);
		assert(scc[2].getEdges() == Matrix<int>({
						{0, 1, 0, 0},
						{0, 0, 0, 1},
						{0, 1, 0, 0},
						{1, 0, 1, 0}
						}));
	}

	/** test MSTPrim*/
	{//single node
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(1);
		WeightList expected;
		assert(expected == graph.MSTPrim());
	}
	{//double nodes
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(2);
		graph.addEdge({0,1},6);
		WeightList expected;
		expected.emplace_back(Edge(0, 1), 6);
		assert(expected == graph.MSTPrim());
	}
	{//normal 1
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(6);
		graph.addEdge({0,1},6);
		graph.addEdge({0,2},1);
		graph.addEdge({0,3},5);
		graph.addEdge({1,2},5);
		graph.addEdge({1,4},3);
		graph.addEdge({2,3},5);
		graph.addEdge({2,4},6);
		graph.addEdge({2,5},4);
		graph.addEdge({3,5},2);
		graph.addEdge({4,5},6);

		WeightList expected;
		expected.emplace_back(Edge(0, 2), 1);
		expected.emplace_back(Edge(3, 5), 2);
		expected.emplace_back(Edge(1, 4), 3);
		expected.emplace_back(Edge(2, 5), 4);
		expected.emplace_back(Edge(1, 2), 5);
		WeightList result = graph.MSTKruskal();
		//displayWeightList(result);
		assert(expected == result);
	}
	{//normal 2
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(9);
		graph.addEdge({0,1},4);
		graph.addEdge({0,7},8);
		graph.addEdge({1,2},8);
		graph.addEdge({1,7},11);
		graph.addEdge({2,3},7);
		graph.addEdge({2,5},4);
		graph.addEdge({2,8},2);
		graph.addEdge({3,4},9);
		graph.addEdge({3,5},14);
		graph.addEdge({4,5},10);
		graph.addEdge({5,6},2);
		graph.addEdge({6,7},1);
		graph.addEdge({6,8},6);
		graph.addEdge({7,8},7);
		
		WeightList expected;
		expected.emplace_back(Edge(0, 1), 4);
		expected.emplace_back(Edge(0, 7), 8);
		expected.emplace_back(Edge(7, 6), 1);
		expected.emplace_back(Edge(6, 5), 2);
		expected.emplace_back(Edge(5, 2), 4);
		expected.emplace_back(Edge(2, 8), 2);
		expected.emplace_back(Edge(2, 3), 7);
		expected.emplace_back(Edge(3, 4), 9);
		WeightList results = graph.MSTPrim();
		//displayWeightList(results);
		assert(expected == results);
	}

	/** test MSTKruskal*/
	{//single node
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(1);
		WeightList expected;
		assert(expected == graph.MSTKruskal());
	}
	{//double nodes
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(2);
		graph.addEdge({0,1},6);
		WeightList expected;
		expected.emplace_back(Edge(0, 1), 6);
		WeightList result = graph.MSTKruskal();
		//displayWeightList(result);
		assert(expected == result);
	}
	{//normal 1
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(6);
		graph.addEdge({0,1},6);
		graph.addEdge({0,2},1);
		graph.addEdge({0,3},5);
		graph.addEdge({1,2},5);
		graph.addEdge({1,4},3);
		graph.addEdge({2,3},5);
		graph.addEdge({2,4},6);
		graph.addEdge({2,5},4);
		graph.addEdge({3,5},2);
		graph.addEdge({4,5},6);

		//displayWeightList(graph.MSTPrim());
		WeightList expected;
		expected.emplace_back(Edge(0, 2), 1);
		expected.emplace_back(Edge(2, 5), 4);
		expected.emplace_back(Edge(5, 3), 2);
		expected.emplace_back(Edge(2, 1), 5);
		expected.emplace_back(Edge(1, 4), 3);
		assert(expected == graph.MSTPrim());
	}
	{//normal 2
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(9);
		graph.addEdge({0,1},4);
		graph.addEdge({0,7},8);
		graph.addEdge({1,2},8);
		graph.addEdge({1,7},11);
		graph.addEdge({2,3},7);
		graph.addEdge({2,5},4);
		graph.addEdge({2,8},2);
		graph.addEdge({3,4},9);
		graph.addEdge({3,5},14);
		graph.addEdge({4,5},10);
		graph.addEdge({5,6},2);
		graph.addEdge({6,7},1);
		graph.addEdge({6,8},6);
		graph.addEdge({7,8},7);
		
		WeightList expected;
		expected.emplace_back(Edge(6, 7), 1);
		expected.emplace_back(Edge(2, 8), 2);
		expected.emplace_back(Edge(5, 6), 2);
		expected.emplace_back(Edge(2, 5), 4);
		expected.emplace_back(Edge(0, 1), 4);
		expected.emplace_back(Edge(2, 3), 7);
		expected.emplace_back(Edge(0, 7), 8);
		expected.emplace_back(Edge(3, 4), 9);
		WeightList results = graph.MSTKruskal();
		//displayWeightList(results);
		assert(expected == results);
	}

	/** test topoSort*/
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		graph.addEdge({0,1},4);
		graph.addEdge({0,2},8);
		graph.addEdge({0,3},8);
		graph.addEdge({2,4},11);
		graph.addEdge({3,4},7);
		graph.addEdge({5,3},2);
		graph.addEdge({5,4},9);
		assert(graph.topoSort() == NodeList<int>({0,5,1,2,3,4}));
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(12);
		graph.addEdge({0,1},4);
		graph.addEdge({0,2},8);
		graph.addEdge({0,3},8);
		graph.addEdge({0,11},8);
		graph.addEdge({1,2},8);
		graph.addEdge({2,4},8);
		graph.addEdge({2,6},8);
		graph.addEdge({2,7},8);
		graph.addEdge({3,4},8);
		graph.addEdge({4,6},8);
		graph.addEdge({5,7},8);
		graph.addEdge({8,9},8);
		graph.addEdge({8,10},8);
		graph.addEdge({8,11},8);
		graph.addEdge({9,11},8);
		graph.addEdge({10,5},8);
		assert(graph.topoSort() == NodeList<int>({0,8,1,3,9,10,2,11,5,4,7,6}));
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		graph.addEdge({2,3});
		graph.addEdge({3,1});
		graph.addEdge({4,0});
		graph.addEdge({4,1});
		graph.addEdge({5,0});
		graph.addEdge({5,2});
		assert(graph.topoSort() == NodeList<int>({4,5,0,2,3,1}));
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(4);
		graph.addEdge({0,1});
		graph.addEdge({1,2});
		graph.addEdge({2,3});
		graph.addEdge({3,1});
		assert(graph.topoSort() == NodeList<int>({0}));
	}

	/** test findArticulTarjanUtil*/
	{//single node
		{
			ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
			graph.addNodes(1);
			assert(graph.findArticulTarjan() == std::vector<bool>({false}));
		}
		{
			ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
			graph.addNodes(1);
			assert(graph.findArticulTarjan() == std::vector<bool>({false}));
		}
	}
	{//double nodes
		{
			ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
			graph.addNodes(2);
			assert(graph.findArticulTarjan() == std::vector<bool>({false, false}));
		}
		{
			ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
			graph.addNodes(2);
			assert(graph.findArticulTarjan() == std::vector<bool>({false, false}));
		}
	}
	{//normal
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(13);
		graph.addEdge({0,1});
		graph.addEdge({0,2});
		graph.addEdge({0,5});
		graph.addEdge({0,11});
		graph.addEdge({1,2});
		graph.addEdge({1,3});
		graph.addEdge({1,5});
		graph.addEdge({1,6});
		graph.addEdge({1,7});
		graph.addEdge({1,12});
		graph.addEdge({3,4});
		graph.addEdge({6,7});
		graph.addEdge({6,8});
		graph.addEdge({6,10});
		graph.addEdge({7,10});
		graph.addEdge({9,11});
		graph.addEdge({9,12});
		graph.addEdge({11,12});
		//0,1,3,6
		std::vector<bool> expected(graph.numberOfNodes(), false);
		expected[0] = true;
		expected[1] = true;
		expected[3] = true;
		expected[6] = true;
		assert(graph.findArticulTarjan() == expected);
	}

	/** test findCriticalPath*/
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(9);
		graph.addEdge({0, 1}, 6);
		graph.addEdge({0, 2}, 4);
		graph.addEdge({0, 3}, 5);
		graph.addEdge({1, 4}, 1);
		graph.addEdge({2, 4}, 1);
		graph.addEdge({3, 5}, 2);
		graph.addEdge({4, 6}, 9);
		graph.addEdge({4, 7}, 7);
		graph.addEdge({5, 7}, 4);
		graph.addEdge({6, 8}, 2);
		graph.addEdge({7, 8}, 4);
		EdgeList result = graph.findCriticalPath();
		displayEdgeList(result);
		std::cout << endl;
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		graph.addEdge({0, 1}, 3);
		graph.addEdge({0, 2}, 2);
		graph.addEdge({1, 3}, 2);
		graph.addEdge({1, 4}, 3);
		graph.addEdge({2, 3}, 4);
		graph.addEdge({2, 5}, 3);
		graph.addEdge({3, 5}, 2);
		graph.addEdge({4, 5}, 1);
		EdgeList result = graph.findCriticalPath();
		displayEdgeList(result);
		std::cout << endl;
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		graph.addEdge({0, 1}, 3);
		graph.addEdge({0, 2}, 2);
		graph.addEdge({1, 3}, 2);
		graph.addEdge({1, 4}, 3);
		graph.addEdge({2, 3}, 3);
		graph.addEdge({2, 5}, 3);
		graph.addEdge({3, 5}, 2);
		graph.addEdge({4, 5}, 1);
		EdgeList result = graph.findCriticalPath();
		displayEdgeList(result);
		std::cout << endl;
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		graph.addEdge({0, 1}, 3);
		graph.addEdge({0, 2}, 2);
		graph.addEdge({1, 3}, 2);
		graph.addEdge({1, 4}, 4);
		graph.addEdge({2, 3}, 3);
		graph.addEdge({2, 5}, 3);
		graph.addEdge({3, 5}, 2);
		graph.addEdge({4, 5}, 1);
		EdgeList result = graph.findCriticalPath();
		displayEdgeList(result);
		std::cout << endl;
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		graph.addEdge({0, 1}, 3);
		graph.addEdge({0, 2}, 2);
		graph.addEdge({1, 3}, 2);
		graph.addEdge({1, 4}, 4);
		graph.addEdge({2, 3}, 3);
		graph.addEdge({2, 5}, 3);
		graph.addEdge({3, 5}, 2);
		graph.addEdge({4, 5}, 1);
		EdgeList result = graph.findCriticalPath();
		displayEdgeList(result);
		std::cout << endl;
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(10);
		graph.addEdge({0, 1}, 3);
		graph.addEdge({0, 2}, 5);
		graph.addEdge({0, 3}, 10);
		graph.addEdge({1, 4}, 10);
		graph.addEdge({2, 5}, 4);
		graph.addEdge({3, 5}, 9);
		graph.addEdge({4, 6}, 2);
		graph.addEdge({5, 6}, 3);
		graph.addEdge({5, 7}, 20);
		graph.addEdge({5, 8}, 4);
		graph.addEdge({6, 9}, 7);
		graph.addEdge({7, 8}, 1);
		graph.addEdge({7, 9}, 10);
		graph.addEdge({8, 9}, 4);
		EdgeList result = graph.findCriticalPath();
		displayEdgeList(result);
		std::cout << endl;
	}

	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(6);
		graph.addEdge({0, 2}, 10);
		graph.addEdge({0, 4}, 30);
		graph.addEdge({0, 5}, 100);
		graph.addEdge({1, 2}, 5);
		graph.addEdge({2, 3}, 50);
		graph.addEdge({3, 5}, 10);
		graph.addEdge({4, 3}, 20);
		graph.addEdge({4, 5}, 60);

		std::vector<int> D;
		Matrix<bool> path;
		graph.singleSourceMinimumPathDijkstra(0, D, path);
		assert(D == std::vector<int>({0, INF, 10, 50, 30, 60}));
		assert(path == Matrix<bool>({
						{true, false, false, false, false, false},
						{false, false, false, false, false, false},
						{true, false, true, false, false, false},
						{true, false, false, true, true, false},
						{true, false, false, false, true, false},
						{true, false, false, true, true, true}
						}));
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes(7);
		graph.addEdge({0, 1}, 12);
		graph.addEdge({0, 5}, 16);
		graph.addEdge({0, 6}, 14);
		graph.addEdge({1, 2}, 10);
		graph.addEdge({1, 5}, 7);
		graph.addEdge({2, 3}, 3);
		graph.addEdge({2, 4}, 5);
		graph.addEdge({2, 5}, 6);
		graph.addEdge({3, 4}, 4);
		graph.addEdge({4, 5}, 2);
		graph.addEdge({4, 6}, 8);
		graph.addEdge({5, 6}, 9);
		std::vector<int> D;
		Matrix<bool> path;
		graph.singleSourceMinimumPathDijkstra(0, D, path);
		assert(D == std::vector<int>({0, 12, 22, 22, 18, 16, 14}));
		assert(path == Matrix<bool>({
						{true, false, false, false, false, false, false},
						{true, true, false, false, false, false, false},
						{true, true, true, false, false, false, false},
						{true, false, false, true, true, true, false},
						{true, false, false, false, true, true, false},
						{true, false, false, false, false, true, false},
						{true, false, false, false, false, false, true}
						}));
	}

	/** test multipleSourceMinmunPathFloyd*/
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(3);
		graph.addEdge({0, 1}, 4);
		graph.addEdge({0, 2}, 11);
		graph.addEdge({1, 0}, 6);
		graph.addEdge({1, 2}, 2);
		graph.addEdge({2, 0}, 3);

		Array2D<int> D;
		Array3D<bool> path;
		graph.multipleSourceMinmunPathFloyd(D, path);
		assert(D == decltype(D)({
						{0, 4, 6},
						{5, 0, 2},
						{3, 7, 0}}));
		assert(path == decltype(path)({
					{{true, false, false}, {true , true, false}, {true, true, true}},
					{{true, true,  true }, {false, true, false}, {false, true, true}},
					{{true, false, true}, {true, true, true}, {false, false, true}}}));
	}
	{
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNodes(4);
		graph.addEdge({0, 1}, 5);
		graph.addEdge({0, 2}, 3);
		graph.addEdge({1, 2}, 2);
		graph.addEdge({1, 3}, 6);
		graph.addEdge({2, 3}, 7);

		Array2D<int> D;
		Array3D<bool> path;
		graph.multipleSourceMinmunPathFloyd(D, path);
		assert(D == decltype(D)({
						{0, 5, 3, 10},
						{INF, 0, 2, 6},
						{INF, INF, 0, 7},
						{INF, INF, INF, 0}}));
		assert(path == decltype(path)({
						{{true, false, false, false}, {true, true, false, false}, {true, false, true, false}, {true, false, true, true}},
						{{false, false, false, false}, {false, true, false, false}, {false, true, true, false}, {false, true, false, true}},
						{{false, false, false, false}, {false, false, false, false}, {false, false, true, false}, {false, false, true, true}},
						{{false, false, false, false}, {false, false, false, false}, {false, false, false, false}, {false, false, false, true}}
						}));

	}
	cout << "All test passed\n";
	return 0;
}
