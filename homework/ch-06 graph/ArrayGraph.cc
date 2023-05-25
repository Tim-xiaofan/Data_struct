#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <stack>
#include <cassert>

using std::cout;
using std::endl;

template<typename T>
using Matrix = std::vector<std::vector<T>>;

template<typename T>
using NodeList = std::vector<T>;

using Edge = std::pair<int, int>;


template<typename T> class ArrayGraph;

template<typename T>
using CcList = std::vector<ArrayGraph<T>>;

template<typename T>
using SccList = std::vector<ArrayGraph<T>>;

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

    void addNode(const T& node);
    void addNodes(const NodeList<T>& nodes);
    void addEdge(const Edge& edge);
    void addEdges(const Matrix<int>& edges);

	const Matrix<int>& getEdges(void) const
	{
		return edges_;
	}

	const NodeList<T>& getNodes(void) const
	{
		return nodes_;
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
	SccList<T> getStronglyConnectedComponents(void) const;

private:
    ArrayGraphType type_;
    Matrix<int> edges_;
    NodeList<T> nodes_;

    template<typename Unary>
    void DFSUtil(int node, std::vector<bool>& visited, const Unary& op, bool post = false) const;
};

template<typename T>
ArrayGraph<T>::ArrayGraph(ArrayGraphType type) : type_(type)
{
}

template<typename T>
void ArrayGraph<T>::addNode(const T& node)
{
	if(std::find(nodes_.begin(), nodes_.end(), node) == nodes_.end())
	{
		nodes_.push_back(node);
		for(size_t i = 0; i < edges_.size(); ++i)
		{
			edges_[i].push_back(0);
		}
		edges_.push_back(std::vector<int>(nodes_.size(), 0));
	}
}

template<typename T>
void ArrayGraph<T>::addNodes(const NodeList<T>& nodes)
{
    for (const auto& node : nodes)
        addNode(node);
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
void ArrayGraph<T>::addEdge(const Edge& edge)
{
    int from = edge.first;
    int to = edge.second;
    if (from < 0 || from >= (int)nodes_.size() ||
        to < 0 || to >= (int)nodes_.size())
    {
        throw std::out_of_range("Invalid node index");
    }

    edges_[from][to] = 1;

    if (type_ == GRAPH)
        edges_[to][from] = 1;
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
    std::vector<bool> visited(nodes_.size(), false);
    std::queue<int> queue;

    for (size_t i = 0; i < nodes_.size(); ++i)
    {
        if (visited[i])
            continue;

        queue.push(i);
        visited[i] = true;

        while (!queue.empty())
        {
            int current = queue.front();
            queue.pop();
            op(nodes_[current]);

            for (size_t neighbor = 0; neighbor < nodes_.size(); ++neighbor)
            {
                if (edges_[current][neighbor] == 1 && !visited[neighbor])
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
    std::vector<bool> visited(nodes_.size(), false);

    for (size_t i = 0; i < nodes_.size(); ++i)
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
		op({nodes_[node], node});
	}

    for (size_t neighbor = 0; neighbor < nodes_.size(); ++neighbor)
    {
        if (edges_[node][neighbor] == 1 && !visited[neighbor])
            DFSUtil(neighbor, visited, op, post);
    }
	
	if(post)
	{
		op({nodes_[node], node});
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
			ID += row[v];
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
		std::vector<bool> visited(nodes_.size(), 0);
		
		for(size_t i = 0; i < nodes_.size(); ++i)
		{
			if(!visited[i])
			{
				std::vector<int> indexList;
				ArrayGraph<T> subGraph(GRAPH);
				DFSUtil(i, visited, [&indexList, &subGraph](const std::pair<T, int>&x) { indexList.push_back(x.second); subGraph.addNode(x.first);});

				for(size_t k = 0; k < indexList.size(); ++k)
				{
					for(size_t s = 0; s < indexList.size(); ++s)
					{
						if(edges_[indexList[k]][indexList[s]] == 1)
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
	tGraph.addNodes(nodes_);
	for(size_t i = 0; i < nodes_.size(); ++i)
	{
		for(size_t j = 0; j < nodes_.size(); ++j)
		{
			if(edges_[i][j] == 1)
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
		std::vector<bool> visited(nodes_.size(), false);
		size_t visited_count = 0;
		DFSUtil(0, visited, [&visited_count](const std::pair<T, size_t>& ) { ++visited_count;});
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
	DFS([&finished](const std::pair<T, size_t>& x) { finished.push(x.second); }, true);

	/** Get transpose graph*/
	auto tGraph = transpose();

	std::vector<bool> visited(nodes_.size(), false);
	SccList<T> sccList;
	/** DFS on the reversed graph according to finished*/
	while(!finished.empty())
	{
		size_t index = finished.top();
		if(!visited[index])
		{
			std::vector<size_t> subIndexs;
			ArrayGraph<T> subGraph(DGRAPH);
			tGraph.DFSUtil(index, visited, [&subIndexs, &subGraph](const std::pair<T, size_t>& x) 
						{ subIndexs.push_back(x.second); subGraph.addNode(x.first);});
			for(size_t k = 0; k < subIndexs.size(); ++k)
			{
				for(size_t s = 0; s < subIndexs.size(); ++s)
				{
					if(edges_[subIndexs[k]][subIndexs[s]] == 1)
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

int main(void)
{
	/** test graph constructor */
	{//empty
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		const Matrix<int>& E = graph.getEdges();
		const NodeList<int>& V = graph.getNodes();
		assert(V == NodeList<int>({}));
		assert(E == Matrix<int>({}));
	}
	{//one at a time
		{
			ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
			graph.addNode(1);
			graph.addNode(2);
			graph.addNode(3);
			graph.addEdge({0, 1});
			graph.addEdge({1, 2});
			graph.addEdge({2, 0});
			const Matrix<int>& E = graph.getEdges();
			const NodeList<int>& V = graph.getNodes();
			assert(V == NodeList<int>({1, 2, 3}));
			assert(E[0] == std::vector<int>({0, 1, 1}));
			assert(E[1] == std::vector<int>({1, 0, 1}));
			assert(E[2] == std::vector<int>({1, 1, 0}));

			std::vector<int> results;
			graph.DFS([&results](const std::pair<int, int>& x) { results.push_back(x.first); });
			assert(results == std::vector<int>({1, 2, 3}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

			assert(2 == graph.getDegree(0));
			assert(2 == graph.getDegree(1));
			assert(2 == graph.getDegree(2));

		}
		{
			ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
			graph.addNode(1);
			graph.addNode(2);
			graph.addNode(3);
			graph.addEdge({0, 1});
			graph.addEdge({1, 2});
			graph.addEdge({2, 0});
			const Matrix<int>& E = graph.getEdges();
			const NodeList<int>& V = graph.getNodes();
			assert(V == NodeList<int>({1, 2, 3}));
			assert(E[0] == std::vector<int>({0, 1, 0}));
			assert(E[1] == std::vector<int>({0, 0, 1}));
			assert(E[2] == std::vector<int>({1, 0, 0}));

			std::vector<int> results;
			graph.DFS([&results](const std::pair<int, int>& x) { results.push_back(x.first); });
			assert(results == std::vector<int>({1, 2, 3}));

			std::vector<int> results2;
			graph.DFS([&results2](const std::pair<int, int>& x) { results2.push_back(x.first); }, true);
			assert(results2 == std::vector<int>({3,2,1}));
			
			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1,2,3}));

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
			graph.addNodes({1, 2, 3});
			graph.addEdges({{0, 1}, {1, 2}, {2, 0}});
			const Matrix<int>& E = graph.getEdges();
			const NodeList<int>& V = graph.getNodes();
			assert(V == NodeList<int>({1, 2, 3}));
			assert(E[0] == std::vector<int>({0, 1, 1}));
			assert(E[1] == std::vector<int>({1, 0, 1}));
			assert(E[2] == std::vector<int>({1, 1, 0}));

			std::vector<int> results;
			graph.DFS([&results](const std::pair<int, int>& x) { results.push_back(x.first); });
			assert(results == std::vector<int>({1, 2, 3}));
			
			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

			assert(2 == graph.getDegree(0));
			assert(2 == graph.getDegree(1));
			assert(2 == graph.getDegree(2));
		}
		{
			ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
			graph.addNodes({1, 2, 3});
			graph.addEdges({{0, 1}, {1, 2}, {2, 0}});
			const Matrix<int>& E = graph.getEdges();
			const NodeList<int>& V = graph.getNodes();
			assert(V == NodeList<int>({1, 2, 3}));
			assert(E[0] == std::vector<int>({0, 1, 0}));
			assert(E[1] == std::vector<int>({0, 0, 1}));
			assert(E[2] == std::vector<int>({1, 0, 0}));

			std::vector<int> results;
			graph.DFS([&results](const std::pair<int, int>& x) { results.push_back(x.first); });
			assert(results == std::vector<int>({1, 2, 3}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

			std::vector<int> results2;
			graph.DFS([&results2](const std::pair<int, int>& x) { results2.push_back(x.first); }, true);
			assert(results2 == std::vector<int>({3,2,1}));

			assert(1 == graph.getInDegree(0));
			assert(1 == graph.getOutDegree(0));
			assert(1 == graph.getInDegree(1));
			assert(1 == graph.getOutDegree(1));
			assert(1 == graph.getInDegree(2));
			assert(1 == graph.getOutDegree(2));
		}
	}
	{//duplicate vertices
		{
			ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
			graph.addNodes({1, 1, 2, 3, 3});
			graph.addEdges({{0, 1}, {1, 2}, {2, 0}});
			const Matrix<int>& E = graph.getEdges();
			const NodeList<int>& V = graph.getNodes();
			assert(V == NodeList<int>({1, 2, 3}));
			assert(E[0] == std::vector<int>({0, 1, 1}));
			assert(E[1] == std::vector<int>({1, 0, 1}));
			assert(E[2] == std::vector<int>({1, 1, 0}));

			std::vector<int> results;
			graph.DFS([&results](const std::pair<int, int>& x) { results.push_back(x.first); });
			assert(results == std::vector<int>({1, 2, 3}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

			assert(2 == graph.getDegree(0));
			assert(2 == graph.getDegree(1));
			assert(2 == graph.getDegree(2));
		}
		{
			ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
			graph.addNodes({1, 1, 2, 3, 3});
			graph.addEdges({{0, 1}, {1, 2}, {2, 0}});
			const Matrix<int>& E = graph.getEdges();
			const NodeList<int>& V = graph.getNodes();
			assert(V == NodeList<int>({1, 2, 3}));
			assert(E[0] == std::vector<int>({0, 1, 0}));
			assert(E[1] == std::vector<int>({0, 0, 1}));
			assert(E[2] == std::vector<int>({1, 0, 0}));

			std::vector<int> results;
			graph.DFS([&results](const std::pair<int, int>& x) { results.push_back(x.first); });
			assert(results == std::vector<int>({1, 2, 3}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

			std::vector<int> results2;
			graph.DFS([&results2](const std::pair<int, int>& x) { results2.push_back(x.first); }, true);
			assert(results2 == std::vector<int>({3,2,1}));

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
		graph.addNode(1);
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 1);
		assert(cc[0].getNodes() == std::vector<int> ({1}));

		assert(graph.isConnected());
	}
	{// 2 + 1
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addEdge({0, 1});
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 2);
		assert(cc[0].getNodes() == std::vector<int> ({1, 2}));
		assert(cc[0].getEdges()[0] == std::vector<int>({0, 1}));
		assert(cc[0].getEdges()[1] == std::vector<int>({1, 0}));
		assert(cc[1].getNodes() == std::vector<int> ({3}));
		assert(cc[1].getEdges()== Matrix<int>({{0}}));

		assert(!graph.isConnected());
	}
	{//2 + 2
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addNode(4);
		graph.addEdge({0, 1});
		graph.addEdge({2, 3});
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 2);
		assert(cc[0].getNodes() == std::vector<int> ({1, 2}));
		assert(cc[0].getEdges()[0] == std::vector<int>({0, 1}));
		assert(cc[0].getEdges()[1] == std::vector<int>({1, 0}));
		assert(cc[1].getNodes() == std::vector<int> ({3, 4}));
		assert(cc[1].getEdges()[0] == std::vector<int>({0, 1}));
		assert(cc[1].getEdges()[1] == std::vector<int>({1, 0}));

		assert(!graph.isConnected());
	}
	{//connected graph
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addEdge({0, 1});
		graph.addEdge({1, 2});
		graph.addEdge({2, 0});
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 1);
		assert(cc[0].getNodes() == std::vector<int> ({1, 2, 3}));
		assert(cc[0].getEdges()[0] == std::vector<int>({0, 1, 1}));
		assert(cc[0].getEdges()[1] == std::vector<int>({1, 0, 1}));
		assert(cc[0].getEdges()[2] == std::vector<int>({1, 1, 0}));

		assert(graph.isConnected());
	}

	/** test transpose*/
	{// zero edge
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		
		auto tGraph = graph.transpose();
		assert(tGraph.getNodes() == NodeList<int>({1}));
		assert(tGraph.getEdges() == Matrix<int>({{0}}));
	}
	{//one
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addEdge({0, 1});

		auto tGraph = graph.transpose();
		assert(tGraph.getNodes() == NodeList<int>({1,2,3}));
		assert(tGraph.getEdges() == Matrix<int>({{0,0,0}, {1,0,0}, {0,0,0}}));
	}
	{// two
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addNode(4);
		graph.addEdge({0, 1});
		graph.addEdge({2, 3});
		
		auto tGraph = graph.transpose();
		assert(tGraph.getNodes() == NodeList<int>({1,2,3,4}));
		assert(tGraph.getEdges() == Matrix<int>({{0,0,0,0}, {1,0,0,0}, {0,0,0,0}, {0,0,1,0}}));
	}
	{// three
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addEdge({0, 1});
		graph.addEdge({1, 2});
		graph.addEdge({2, 0});
		
		auto tGraph = graph.transpose();
		assert(tGraph.getNodes() == NodeList<int>({1,2,3}));
		assert(tGraph.getEdges() == Matrix<int>({{0,0,1},{1,0,0},{0,1,0}}));
	}

	/** test getStronglyConnectedComponents*/
	{// single node
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		
		auto scc = graph.getStronglyConnectedComponents();
		assert(scc.size() == 1);
		assert(scc[0].getNodes() == NodeList<int>({1}));
		assert(scc[0].getEdges() == Matrix<int>({{0}}));
	}
	{// 2 + 1
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addEdge({0, 1});
		graph.addEdge({1, 0});
		
		auto scc = graph.getStronglyConnectedComponents();
		assert(scc.size() == 2);
		assert(scc[1].getNodes() == std::vector<int> ({1, 2}));
		assert(scc[1].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		assert(scc[0].getNodes() == std::vector<int> ({3}));
		assert(scc[0].getEdges() == Matrix<int>({{0}}));
	}
	{// 2 + 2
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addNode(4);
		graph.addEdge({0, 1});
		graph.addEdge({1, 0});
		graph.addEdge({2, 3});
		graph.addEdge({3, 2});
		{

			auto scc = graph.getStronglyConnectedComponents();
			assert(scc.size() == 2);
			assert(scc[1].getNodes() == std::vector<int> ({1, 2}));
			assert(scc[1].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
			assert(scc[0].getNodes() == std::vector<int> ({3, 4}));
			assert(scc[0].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		}

		{//connect
			graph.addEdge({1, 2});

			std::vector<int> results;
			graph.DFS([&results](const std::pair<int, int>& x) { results.push_back(x.first); }, true);
			assert(results == std::vector<int>({4, 3, 2, 1}));

			auto scc = graph.getStronglyConnectedComponents();
			assert(scc.size() == 2);
			assert(scc[0].getNodes() == std::vector<int> ({1, 2}));
			assert(scc[0].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
			assert(scc[1].getNodes() == std::vector<int> ({3, 4}));
			assert(scc[1].getEdges() == Matrix<int>({{0, 1}, {1, 0}}));
		}
	}
	
	{// 5 + 5
		ArrayGraph<int> graph(ArrayGraph<int>::DGRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addNode(4);
		graph.addNode(5);
		graph.addNode(6);
		graph.addNode(7);
		graph.addNode(8);
		graph.addNode(9);
		graph.addNode(10);

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
			assert(scc[0].getNodes() == std::vector<int>({6,10,9,8,7}));
			assert(scc[0].getEdges() == Matrix<int>({
							{0,0,0,0,1},
							{1,0,0,0,0},
							{0,1,0,0,0},
							{0,0,1,0,0},
							{0,0,0,1,0}}));
			assert(scc[1].getNodes() == std::vector<int>({1,5,4,3,2}));
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
			assert(scc[0].getNodes() == std::vector<int>({1,5,4,3,2}));
			assert(scc[0].getEdges() == Matrix<int>({
							{0,0,0,0,1},
							{1,0,0,0,0},
							{0,1,0,0,0},
							{0,0,1,0,0},
							{0,0,0,1,0}}));
			assert(scc[1].getNodes() == std::vector<int>({6,10,9,8,7}));
			assert(scc[1].getEdges() == Matrix<int>({
							{0,0,0,0,1},
							{1,0,0,0,0},
							{0,1,0,0,0},
							{0,0,1,0,0},
							{0,0,0,1,0}}));
		}
	}

	
	cout << "All test passed\n";
	return 0;
}
