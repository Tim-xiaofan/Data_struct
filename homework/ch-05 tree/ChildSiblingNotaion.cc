/**树：孩子兄弟法 */
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <iterator>
#include <algorithm>

template <typename T>
class TreeNode {
public:
    T data;
	using NodePtr = std::unique_ptr<TreeNode<T>>;
	using RawNodePtr = TreeNode<T>*;
    std::unique_ptr<TreeNode<T>> child;   // Unique pointer to the first child node
    std::unique_ptr<TreeNode<T>> sibling; // Unique pointer to the next sibling node

    TreeNode(T d) : data(d), child(nullptr), sibling(nullptr) {}

    // Function to add a child node
    void addChild(const T& d) {
        auto newNode = std::make_unique<TreeNode<T>>(d);
        if (child == nullptr) {
            child = std::move(newNode);
        } else {
            TreeNode<T>* current = child.get();
            while (current->sibling) {
                current = current->sibling.get();
            }
            current->sibling = std::move(newNode);
        }
    }

	void display(int level = 0) const {
		for (int i = 0; i < level; ++i) {
            std::cout << "   ";
        }
        std::cout << "|_" << data << std::endl;
        if (child != nullptr) {
            child->display(level + 1);
        }
        if (sibling != nullptr) {
            sibling->display(level);
        }
    }
	
	template<typename Unary>
	void preorderTraversal(Unary op) const
	{
		op(data);
		if(child)
		{
			child->preorderTraversal(op);
		}
		if(sibling)
		{
			sibling->preorderTraversal(op);
		}
	}

	template<typename Unary>
	void postorderTraversal(Unary op) const
	{
		if(child)
		{
			child->postorderTraversal(op);
		}
		op(data);
		if(sibling)
		{
			sibling->postorderTraversal(op);
		}
	}
};

static std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	return os;
}

int main() {
    // Create tree nodes using child-sibling notation with smart pointers
	{
		auto root = std::make_unique<TreeNode<int>>(1);
		root->addChild(2);
		root->addChild(3);
		root->addChild(4);

		auto& node2 = root->child;
		node2->addChild(5);
		node2->addChild(6);

		auto& node3 = node2->sibling;
		node3->addChild(7);

		root->display();

		std::vector<int> results;
		root->preorderTraversal([&results](int x) { results.push_back(x); });
		std::vector<int> expected = {1,2,5,6,3,7,4};
		assert(expected == results);
		std::cout << "preorderTraversal: " << results << "\n\n"; 
	}

	{
		auto root = std::make_unique<TreeNode<int>>(1);
		root->addChild(2);
		root->addChild(3);
		root->addChild(4);

		auto& node2 = root->child;
		node2->addChild(5);
		node2->addChild(6);

		auto& node5 = node2->child;
		node5->addChild(8);

		auto& node3 = node2->sibling;
		node3->addChild(7);

		root->display();

		std::vector<int> results;
		root->preorderTraversal([&results](int x) { results.push_back(x); });
		std::vector<int> expected = {1,2,5,8,6,3,7,4};
		assert(expected == results);
		std::cout << "preorderTraversal: " << results << "\n\n"; 
	}

	{
		auto root = std::make_unique<TreeNode<int>>(1);

        root->display();

        std::vector<int> results;
        root->preorderTraversal([&results](int x) { results.push_back(x); });
        std::vector<int> expected = {1};
        assert(expected == results);
		std::cout << "preorderTraversal: " << results << "\n\n"; 
	}

	{
		auto root = std::make_unique<TreeNode<int>>(1);
        root->addChild(2);

        root->display();

        std::vector<int> results;
        root->preorderTraversal([&results](int x) { results.push_back(x); });
        std::vector<int> expected = {1,2};
        assert(expected == results);
		std::cout << "preorderTraversal: " << results << "\n\n"; 
	}

	{
		auto root = std::make_unique<TreeNode<int>>(1);
		root->addChild(2);
		root->addChild(3);
		root->addChild(4);

		auto& node2 = root->child;
		node2->addChild(5);
		node2->addChild(6);

		auto& node3 = node2->sibling;
		node3->addChild(7);

		root->display();

		std::vector<int> results;
		root->postorderTraversal([&results](int x) { results.push_back(x); });
		std::vector<int> expected = {5,6,2,7,3,4,1};
		assert(expected == results);
		std::cout << "postorderTraversal: " << results << "\n\n"; 
	}

	{
		auto root = std::make_unique<TreeNode<int>>(1);
		root->addChild(2);
		root->addChild(3);
		root->addChild(4);

		auto& node2 = root->child;
		node2->addChild(5);
		node2->addChild(6);

		auto& node5 = node2->child;
		node5->addChild(8);

		auto& node3 = node2->sibling;
		node3->addChild(7);

		root->display();

		std::vector<int> results;
		root->postorderTraversal([&results](int x) { results.push_back(x); });
		std::vector<int> expected = {8,5,6,2,7,3,4,1};
		assert(expected == results);
		std::cout << "postorderTraversal: " << results << "\n\n"; 

	}

	{
		auto root = std::make_unique<TreeNode<int>>(1);

        root->display();

        std::vector<int> results;
        root->postorderTraversal([&results](int x) { results.push_back(x); });
        std::vector<int> expected = {1};
        assert(expected == results);
		std::cout << "postorderTraversal: " << results << "\n\n"; 
	}

	{
		auto root = std::make_unique<TreeNode<int>>(1);
        root->addChild(2);

        root->display();

        std::vector<int> results;
        root->postorderTraversal([&results](int x) { results.push_back(x); });
        std::vector<int> expected = {2, 1};
        assert(expected == results);
		std::cout << "postorderTraversal: " << results << "\n\n"; 
	}

	std::cout << "All test passed!\n";

    return 0;
}

