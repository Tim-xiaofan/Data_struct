/** 树：双亲表示法*/
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct TreeNode {
    T data;
    int parent; // Index of the parent node in the array

    TreeNode(int d, int p) : data(d), parent(p) {}
};

template<typename T>
class Tree {
public:
    vector<TreeNode<T>> nodes; // Array to store the tree nodes

    // Constructor to create an empty tree
    Tree() {}

    // Function to add a node to the tree
    void addNode(int data, int parent) {
        TreeNode<T> newNode(data, parent);
        nodes.push_back(newNode);
    }

    // O(n): Function to display the tree
    void display() const{
        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << "Node: " << i << ", Data: " << nodes[i].data << ", Parent: " << nodes[i].parent << endl;
        }
    }

    // O(n): Function to get the children of a node
    vector<int> getChildren(int nodeIndex) const {
        vector<int> children;
		for(size_t i = 0; i < nodes.size(); ++i)
		{
			if(nodes[i].parent == nodeIndex)
			{
				children.push_back(i);
			}
		}
		return children;
    }
};

int main() {
    // Create a tree
    Tree<int> tree;

    // Add nodes to the tree using parent notation
    tree.addNode(1, -1); // Root node with data 1 and no parent
    tree.addNode(2, 0); // Node with data 2 and parent as node 0 (root)
    tree.addNode(3, 0); // Node with data 3 and parent as node 0 (root)
    tree.addNode(4, 1); // Node with data 4 and parent as node 1
    tree.addNode(5, 1); // Node with data 5 and parent as node 1

    // Display the tree
    tree.display();

    // Get the children of node 1
    vector<int> children = tree.getChildren(1);
    cout << "Children of Node 1: ";
    for (int child : children) {
        cout << child << " ";
    }
    cout << endl;

    return 0;
}

