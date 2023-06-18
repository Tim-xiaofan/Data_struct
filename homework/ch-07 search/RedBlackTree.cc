#include "RedBlackTree.h"
#include <iostream>
#include <vector>
#include <cassert>

int main(void)
{
	//test leftRotate
	{//case 1: no child and no root change
		RedBlackTree<int> t;
		auto& root = t.root();
		root = new RedBlackTreeNode<int>(2);
		RedBlackTreeNodePtr<int> n = root->addLchild(0)->addRchild(1);
		//root->display();
		//std::cout << std::endl;
		
		t.leftRotate(n);
		n = n->lchild;
		
		RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(2);
		expected->addLchild(1)->addLchild(0);
		
		assert(expected->same(root));
		assert(n->data == 0);
		assert(n->parent->data == 1);
		assert(n->parent->parent->data  == 2);
	}
	{//case 2: no child and root change
		RedBlackTree<int> t;
		auto& root = t.root();
		root = new RedBlackTreeNode<int>(0);
		root->addRchild(1)->addRchild(2);
		RedBlackTreeNodePtr<int> n = root->rchild; 
		//root->display();
		//std::cout << std::endl;
		
		t.leftRotate(n);
		assert(root->data == 1);
		
		RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(1);
		expected->addLchild(0);
		expected->addRchild(2);
		
		assert(expected->same(root));
	}
	{//case 3: with child
		RedBlackTree<int> t;
		auto& root = t.root();
		root  = new RedBlackTreeNode<int>(5);
		root->addLchild(1)->addLchild(0);
		RedBlackTreeNodePtr<int> n = root->lchild->addRchild(3);
		n->addLchild(2);
		n->addRchild(4);
		root->addRchild(7)->addRchild(8);
		root->rchild->addLchild(6);
		//root->display();
		//std::cout << std::endl;

		t.leftRotate(n);
		n = n->lchild;

		RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(5);
		expected->addRchild(7)->addRchild(8);
		expected->rchild->addLchild(6);
		expected->addLchild(3)->addLchild(1)->addLchild(0);
		expected->lchild->addRchild(4);
		expected->lchild->lchild->addRchild(2);

		assert(expected->same(root));
		assert(n->data == 1);
	}

	//test rightRotate
	{//case 1: no child
		RedBlackTree<int> t;
		RedBlackTreeNodePtr<int>& root = t.root() ;
		root =  new RedBlackTreeNode<int>(0);
		RedBlackTreeNodePtr<int> n = root->addRchild(2)->addLchild(1);
		//root->display();
		//std::cout << std::endl;

		t.rightRotate(n);
		n = n->rchild;

		RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(0);
		expected->addRchild(1)->addRchild(2);

		assert(expected->same(root));
		assert(n->data == 2);
	}
	{//case 2: no child
		RedBlackTree<int> t;
		RedBlackTreeNodePtr<int>& root = t.root();
		root =  new RedBlackTreeNode<int>(2);
		auto n = root->addLchild(1);
		n->addLchild(0);
		//root->display();
		//std::cout << "\n";

		t.rightRotate(n);
		//root->display();
		//std::cout << "\n";
	}
	{//case 3: with child
		RedBlackTree<int> t;
		RedBlackTreeNodePtr<int>& root = t.root();
		root =  new RedBlackTreeNode<int>(3);
		root->addLchild(1)->addRchild(2);
		root->lchild->addLchild(0);
		root->addRchild(7)->addRchild(8);
		RedBlackTreeNodePtr<int> n = root->rchild->addLchild(5);
		n->addLchild(4);
		n->addRchild(6);
		//root->display();
		//std::cout << std::endl;

		t.rightRotate(n);
		n = n->rchild;

		RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(3);
		expected->addLchild(1)->addLchild(0);
		expected->lchild->addRchild(2);
		expected->addRchild(5)->addRchild(7)->addRchild(8);
		expected->rchild->rchild->addLchild(6);
		expected->rchild->addLchild(4);

		assert(expected->same(root));
		assert(n->data == 7);
	}

	//test insert
	{//case 1
		//std::cout << "case 1\n";
		RedBlackTree<int> t;
		assert(t.isRedBlackTree());
		
		t.insert(0);
		assert(t.isRedBlackTree());
		
		RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(0, BLACK);
		assert(expected->same(t.root()));
		std::cout << std::endl;
	}
	{// case 2
		//std::cout << "case 2\n";
		RedBlackTree<int> t;
		t.root() = new RedBlackTreeNode<int>(1, BLACK);
		//t.root()->display();
		assert(t.isRedBlackTree());
		
		t.insert(0);
		t.insert(3);
		assert(t.isRedBlackTree());

		RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(1, BLACK);
		expected->addLchild(0, RED);
		expected->addRchild(3, RED);

		assert(expected->same(t.root()));
	}
	{//case 3
		//std::cout << "case 3\n";
		{//grandparent is root
			RedBlackTree<int> t;
			t.root() = new RedBlackTreeNode<int>(2, BLACK);
			t.root()->addLchild(1, RED);
			t.root()->addRchild(3, RED);
			//t.root()->display();
			assert(t.isRedBlackTree());

			t.insert(0);
			assert(t.isRedBlackTree());

			RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(2, BLACK);
			expected->addLchild(1, BLACK)->addLchild(0, RED);
			expected->addRchild(3, BLACK);

			assert(expected->same(t.root()));
		}
		{//grandparent is not root and grandparent's parent is red
			RedBlackTree<int> t;
			t.root() = new RedBlackTreeNode<int>(6, BLACK);
			auto p = t.root()->addLchild(4, RED)->addLchild(2, BLACK);
			t.root()->lchild->addRchild(5, BLACK);
			p->addLchild(1, RED);
			p->addRchild(3, RED);
			t.root()->addRchild(8, RED)->addRchild(9, BLACK);
			t.root()->rchild->addLchild(7, BLACK);
			//t.root()->display();
			assert(t.isRedBlackTree());
			
			t.insert(0);
			assert(t.isRedBlackTree());

			RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(6, BLACK);
			expected->addRchild(8, BLACK)->addRchild(9, BLACK);
			expected->rchild->addLchild(7, BLACK);
			p = expected->addLchild(4, BLACK)->addLchild(2, RED);
			p->addLchild(1, BLACK)->addLchild(0, RED);
			p->addRchild(3, BLACK);
			expected->lchild->addRchild(5, BLACK);

			assert(expected->same(t.root()));
		}
	}
	{//test case 4 and case 5
		{
			RedBlackTree<int> t;
			t.root() = new RedBlackTreeNode<int>(2, BLACK);
			t.root()->addLchild(0, RED);
			assert(t.isRedBlackTree());

			t.insert(1);
			
			RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(1, BLACK);
			expected->addLchild(0, RED);
			expected->addRchild(2, RED);

			assert(expected->same(t.root()));
		}

		{
			RedBlackTree<int> t;
			t.root() = new RedBlackTreeNode<int>(0, BLACK);
			t.root()->addRchild(2, RED);
			assert(t.isRedBlackTree());

			t.insert(1);

			RedBlackTreeNodePtr<int> expected = new RedBlackTreeNode<int>(1, BLACK);
			expected->addLchild(0, RED);
			expected->addRchild(2, RED);

			assert(expected->same(t.root()));
		}
	}
	std::cout << "All tests passed\n";
	return 0;
}
