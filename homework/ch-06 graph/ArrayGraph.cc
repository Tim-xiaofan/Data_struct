#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using std::cout;
using std::endl;

template<typename T>
using Matrix = std::vector<std::vector<T>>;

template<typename T>
using NodeList = std::vector<T>;

using Edge = std::pair<int, int>;

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
    nodes_.push_back(node);
	edges_.push_back(std::vector<int>(nodes_.size(), 0));
	for(size_t i = 0; i < edges_.size() - 1; ++i)
	{
		edges_[i].push_back(0);
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

    for (int i = 0; i < nodes_.size(); ++i)
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

            for (int neighbor = 0; neighbor < nodes_.size(); ++neighbor)
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

    for (int i = 0; i < nodes_.size(); ++i)
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

    for (int neighbor = 0; neighbor < nodes_.size(); ++neighbor)
    {
        if (edges_[node][neighbor] == 1 && !visited[neighbor])
            DFSUtil(neighbor, visited, op);
    }
}


int main(void)
{
	{
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNode(1);
		graph.addNode(2);
		graph.addNode(3);
		graph.addEdge({0, 1});
		graph.addEdge({1, 2});
		graph.addEdge({2, 0});
		displayNodeList(graph.getNodes());
		displayMatrix(graph.getEdges());
		cout << endl << endl;
	}

	{
		ArrayGraph<int> graph(ArrayGraph<int>::GRAPH);
		graph.addNodes({1, 2, 3});
		graph.addEdges({{0, 1}, {1, 2}, {2, 0}});
		displayNodeList(graph.getNodes());
		displayMatrix(graph.getEdges());
	}
	return 0;
}
