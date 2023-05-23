#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <map>

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
class ArrayGraph
{
public:
    enum ArrayGraphType { DGRAPH, GRAPH };

    ArrayGraph(ArrayGraphType type);
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
    void DFS(const Unary& op) const;

	// only valid in a directed graph
	int getInDegree(int v) const;

	// only valid in a directed graph
	int getOutDegree(int v) const;

	//only valid in a undirected graph
	int getDegree(int v) const;

	CcList<T> getConnectedComponents(void) const;

private:
    ArrayGraphType type_;
    Matrix<int> edges_;
    NodeList<T> nodes_;

    template<typename Unary>
    void DFSUtil(int node, std::vector<bool>& visited, const Unary& op) const;
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
void ArrayGraph<T>::DFS(const Unary& op) const
{
    std::vector<bool> visited(nodes_.size(), false);

    for (size_t i = 0; i < nodes_.size(); ++i)
    {
        if (!visited[i])
            DFSUtil(i, visited, op);
    }
}

template<typename T>
template<typename Unary>
void ArrayGraph<T>::DFSUtil(int node, std::vector<bool>& visited, const Unary& op) const
{
    visited[node] = true;
    op(nodes_[node]);

    for (size_t neighbor = 0; neighbor < nodes_.size(); ++neighbor)
    {
        if (edges_[node][neighbor] == 1 && !visited[neighbor])
            DFSUtil(neighbor, visited, op);
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
		std::map<T, size_t> toIndex;
		for(size_t i = 0; i < nodes_.size(); ++i)
		{
			toIndex.emplace(nodes_[i], i);
		}
		
		for(size_t i = 0; i < nodes_.size(); ++i)
		{
			if(!visited[i])
			{
				NodeList<T> nodeList;
				DFSUtil(i, visited, [&nodeList](int x) { nodeList.push_back(x); });

				ArrayGraph<T> subGraph(GRAPH);
				subGraph.addNodes(nodeList);
				for(size_t k = 0; k < nodeList.size(); ++k)
				{
					for(size_t s = 0; s < nodeList.size(); ++s)
					{
						if(edges_[toIndex.at(nodes_[k])][toIndex.at(nodes_[s])] == 1)
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
			graph.DFS([&results](int x) { results.push_back(x); });
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
			graph.DFS([&results](int x) { results.push_back(x); });
			assert(results == std::vector<int>({1, 2, 3}));
			
			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

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
			graph.DFS([&results](int x) { results.push_back(x); });
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
			graph.DFS([&results](int x) { results.push_back(x); });
			assert(results == std::vector<int>({1, 2, 3}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

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
			graph.DFS([&results](int x) { results.push_back(x); });
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
			graph.DFS([&results](int x) { results.push_back(x); });
			assert(results == std::vector<int>({1, 2, 3}));

			std::vector<int> results1;
			graph.BFS([&results1](int x) { results1.push_back(x); });
			assert(results1 == std::vector<int>({1, 2, 3}));

			assert(1 == graph.getInDegree(0));
			assert(1 == graph.getOutDegree(0));
			assert(1 == graph.getInDegree(1));
			assert(1 == graph.getOutDegree(1));
			assert(1 == graph.getInDegree(2));
			assert(1 == graph.getOutDegree(2));
		}
	}

	/** test getConnectedComponents*/
	{// single node
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode(1);
		
		auto cc = graph.getConnectedComponents();
		assert(cc.size() == 1);
		assert(cc[0].getNodes() == std::vector<int> ({1}));
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
	}
	
	cout << "All test passed\n";
	return 0;
}
