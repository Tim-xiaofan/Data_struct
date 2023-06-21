#include <iostream>
#include <cassert>
#include "BTree.h"

static void testBTreeNode()
{
	// getKeyInsertIndex
	{// empty
		BTreeNode<int> n;
		assert(n.getKeyInsertIndex(12) == 0);
	}
	{// one
		BTreeNode<int> n;
		n.keys = std::vector<int>({0});
		assert(n.getKeyInsertIndex(-1) == 0);
		assert(n.getKeyInsertIndex(1) == 1);
		assert(n.getKeyInsertIndex(2) == 1);
	}
	{//two
		BTreeNode<int> n;
		n.keys = std::vector<int>({0, 2});
		assert(n.getKeyInsertIndex(-1) == 0);
		assert(n.getKeyInsertIndex(1) == 1);
		assert(n.getKeyInsertIndex(5) == 2);
	}
	{// three
		BTreeNode<int> n;
		n.keys = std::vector<int>({0, 2, 4});
		assert(n.getKeyInsertIndex(-1) == 0);
		assert(n.getKeyInsertIndex(1) == 1);
		assert(n.getKeyInsertIndex(3) == 2);
		assert(n.getKeyInsertIndex(5) == 3);
	}
	{//four
		BTreeNode<int> n;
		n.keys = std::vector<int>({0, 2, 4, 6});
		assert(n.getKeyInsertIndex(-1) == 0);
		assert(n.getKeyInsertIndex(1) == 1);
		assert(n.getKeyInsertIndex(3) == 2);
		assert(n.getKeyInsertIndex(5) == 3);
		assert(n.getKeyInsertIndex(7) == 4);
	}

	//test insertKey
	{//empty
		BTreeNode<int> n;
		n.insertKey(0, 1);
		n.insertKey(1, 2);
		assert(n.keys == std::vector<int>({1, 2}));

		assert(n.findKey(1) == std::make_pair(true, 0));
		assert(n.findKey(2) == std::make_pair(true, 1));
		assert(n.findKey(3) == std::make_pair(false, 2));
	}
	{//one
		BTreeNode<int> n;
		n.keys = std::vector<int>({0});
		n.insertKey(0, 1);
		n.insertKey(2, 2);
		n.insertKey(1, 3);
		assert(n.keys == std::vector<int>({1, 3, 0, 2}));
	}

	// test insertChild
	{
		BTreeNode<int> n;
		BTreeNode<int>* p0 = new BTreeNode<int>();
		BTreeNode<int>* p1 = new BTreeNode<int>();
		n.insertChild(0, p0);
		n.insertChild(1, p1);
		assert(n.children == std::vector<BTreeNode<int>*>({p0, p1}));
	}

	// test spilt
	{// m = 3
		const int m = 3;
		BTreeNode<int> n;
		n.insertKey(0, 0);
		n.insertKey(1, 1);
		n.insertKey(2, 2);
		BTreeNode<int>* p0 = new BTreeNode<int>();
		BTreeNode<int>* p1 = new BTreeNode<int>();
		BTreeNode<int>* p2 = new BTreeNode<int>();
		BTreeNode<int>* p3 = new BTreeNode<int>();
		n.insertChild(0, p0);
		n.insertChild(1, p1);
		n.insertChild(2, p2);
		n.insertChild(3, p3);

		auto r = n.split((m-1)/2);
		assert(n.keys == std::vector<int>({0}));
		assert(r->keys == std::vector<int>({2}));
		assert(n.children == std::vector<BTreeNode<int>*>({p0, p1}));
		assert(r->children == std::vector<BTreeNode<int>*>({p2, p3}));
	}
	{// m = 4
		const int m = 4;
		BTreeNode<int> n;
		n.insertKey(0, 0);
		n.insertKey(1, 1);
		n.insertKey(2, 2);
		n.insertKey(3, 3);
		BTreeNode<int>* p0 = new BTreeNode<int>();
		BTreeNode<int>* p1 = new BTreeNode<int>();
		BTreeNode<int>* p2 = new BTreeNode<int>();
		BTreeNode<int>* p3 = new BTreeNode<int>();
		BTreeNode<int>* p4 = new BTreeNode<int>();
		n.insertChild(0, p0);
		n.insertChild(1, p1);
		n.insertChild(2, p2);
		n.insertChild(3, p3);
		n.insertChild(4, p4);

		auto r = n.split((m-1)/2);
		assert(n.keys == std::vector<int>({0}));
		assert(r->keys == std::vector<int>({2, 3}));
		assert(n.children == std::vector<BTreeNode<int>*>({p0, p1}));
		assert(r->children == std::vector<BTreeNode<int>*>({p2, p3, p4}));
	}
	{// m = 5
		const int m = 5;
		BTreeNode<int> n;
		n.insertKey(0, 0);
		n.insertKey(1, 1);
		n.insertKey(2, 2);
		n.insertKey(3, 3);
		n.insertKey(4, 4);
		BTreeNode<int>* p0 = new BTreeNode<int>();
		BTreeNode<int>* p1 = new BTreeNode<int>();
		BTreeNode<int>* p2 = new BTreeNode<int>();
		BTreeNode<int>* p3 = new BTreeNode<int>();
		BTreeNode<int>* p4 = new BTreeNode<int>();
		BTreeNode<int>* p5 = new BTreeNode<int>();
		n.insertChild(0, p0);
		n.insertChild(1, p1);
		n.insertChild(2, p2);
		n.insertChild(3, p3);
		n.insertChild(4, p4);
		n.insertChild(5, p5);

		auto r = n.split((m-1)/2);
		assert(n.keys == std::vector<int>({0, 1}));
		assert(r->keys == std::vector<int>({3, 4}));
		assert(n.children == std::vector<BTreeNode<int>*>({p0, p1, p2}));
		assert(r->children == std::vector<BTreeNode<int>*>({p3, p4, p5}));
	}

	std::cout << "All BTreeNode tests passed\n";
}

static void
testBTree(void)
{
	//test search
	{// one
		BTree<int, 3> t;
		auto& root = t.root();
		root = new BTreeNode<int>();
		root->insertKey(0, 45);
		root->insertChild(0, nullptr);
		root->insertChild(1, nullptr);

		{
			BTree<int, 3>::Result expected(true, root, 0);
			auto ret = t.search(45);
			assert(ret == expected);
		}
		{
			BTree<int, 3>::Result expected(false, root, 1);
			auto ret = t.search(46);
			assert(ret == expected);
		}
		t.display();
		BTree<int, 3> t1;
		t.copy(t1);
		t1.display();
		assert(t.same(t1));
	}
	{// three
		BTreeNode<int>* p0 = new BTreeNode<int>();
		p0->insertKey(0, 24);
		p0->insertChild(0, nullptr);
		p0->insertChild(1, nullptr);

		BTreeNode<int>* p1 = new BTreeNode<int>();
		p1->insertKey(0, 53);
		p1->insertKey(1, 90);
		p1->insertChild(0, nullptr);
		p1->insertChild(1, nullptr);
		p1->insertChild(2, nullptr);

		BTree<int, 3> t;
		auto& root = t.root();
		root = new BTreeNode<int>();
		root->insertKey(0, 45);
		root->insertChild(0, p0);
		root->insertChild(1, p1);

		p0->parent = root;
		p1->parent = root;

		{//in root
			BTree<int, 3>::Result expected(true, root, 0);
			auto ret = t.search(45);
			assert(ret == expected);
		}
		{// not in p1
			BTree<int, 3>::Result expected(false, p1, 0);
			auto ret = t.search(46);
			assert(ret == expected);
		}
		{// not in p1
			BTree<int, 3>::Result expected(false, p1, 1);
			auto ret = t.search(60);
			assert(ret == expected);
		}
		{// not in p1
			BTree<int, 3>::Result expected(false, p1, 2);
			auto ret = t.search(95);
			assert(ret == expected);
		}
		{//in p1
			BTree<int, 3>::Result expected(true, p1, 0);
			auto ret = t.search(53);
			assert(ret == expected);
		}
		{// in p1
			BTree<int, 3>::Result expected(true, p1, 1);
			auto ret = t.search(90);
			assert(ret == expected);
		}
		{// not in p0
			BTree<int, 3>::Result expected(false, p0, 0);
			auto ret = t.search(3);
			assert(ret == expected);
		}
		{// not in p0
			BTree<int, 3>::Result expected(false, p0, 1);
			auto ret = t.search(25);
			assert(ret == expected);
		}
		{// in p0
			BTree<int, 3>::Result expected(true, p0, 0);
			auto ret = t.search(24);
			assert(ret == expected);
		}
		t.display();
		BTree<int, 3> t1;
		t.copy(t1);
		t1.display();
		assert(t.same(t1));
	}
	
	BTree<int, 3> t1;
	{//eight
		BTreeNode<int>* p0 = new BTreeNode<int>();
		p0->insertKey(0, 3);
		p0->insertKey(1, 12);
		p0->insertChild(0, nullptr);
		p0->insertChild(1, nullptr);
		p0->insertChild(2, nullptr);

		BTreeNode<int>* p1 = new BTreeNode<int>();
		p1->insertKey(0, 37);
		p1->insertChild(0, nullptr);
		p1->insertChild(1, nullptr);

		BTreeNode<int>* p2 = new BTreeNode<int>();
		p2->insertKey(0, 50);
		p2->insertChild(0, nullptr);
		p2->insertChild(1, nullptr);

		BTreeNode<int>* p3 = new BTreeNode<int>();
		p3->insertKey(0, 61);
		p3->insertKey(1, 70);
		p3->insertChild(0, nullptr);
		p3->insertChild(1, nullptr);
		p3->insertChild(2, nullptr);


		BTreeNode<int>* p4 = new BTreeNode<int>();
		p4->insertKey(0, 100);
		p4->insertChild(0, nullptr);
		p4->insertChild(1, nullptr);


		BTreeNode<int>* p5 = new BTreeNode<int>();
		p5->insertKey(0, 24);
		p5->insertChild(0, p0);
		p5->insertChild(1, p1);
		p0->parent = p5;
		p1->parent = p5;


		BTreeNode<int>* p6 = new BTreeNode<int>();
		p6->insertKey(0, 53);
		p6->insertKey(1, 90);
		p6->insertChild(0, p2);
		p6->insertChild(1, p3);
		p6->insertChild(2, p4);
		p2->parent = p6;
		p3->parent = p6;
		p4->parent = p6;

		BTree<int, 3> t2;
		t2.root() = new BTreeNode<int>();
		t2.root()->insertKey(0, 45);
		t2.root()->insertChild(0, p5);
		t2.root()->insertChild(1, p6);
		p5->parent = t2.root();
		p6->parent = t2.root();

		{
			BTree<int, 3>::Result expected(false, p1, 0);
			auto ret = t2.search(30);
			assert(ret == expected);
		}
		{
			BTree<int, 3>::Result expected(true, p3, 0);
			auto ret = t2.search(61);
			assert(ret == expected);
		}
		t2.display();
		t2.copy(t1);
		t1.display();
		assert(t2.same(t1));
		t2.copy(t2);
	}

	//test insert
	{
		t1.insert(30);
		std::cout << "after insert 30\n";
		t1.display();
		
		t1.insert(26);
		std::cout << "after insert 26\n";
		t1.display();

		t1.insert(85);
		std::cout << "after insert 85\n";
		t1.display();

		t1.insert(7);
		std::cout << "after insert 7\n";
		t1.display();
	}

	//test erase
	BTreeNode<int>* p0 = new BTreeNode<int>();
	p0->insertKey(0, 3);
	p0->insertChild(0, nullptr);
	p0->insertChild(1, nullptr);

	BTreeNode<int>* p1 = new BTreeNode<int>();
	p1->insertKey(0, 37);
	p1->insertChild(0, nullptr);
	p1->insertChild(1, nullptr);

	BTreeNode<int>* p2 = new BTreeNode<int>();
	p2->insertKey(0, 50);
	p2->insertChild(0, nullptr);
	p2->insertChild(1, nullptr);

	BTreeNode<int>* p3 = new BTreeNode<int>();
	p3->insertKey(0, 61);
	p3->insertKey(1, 70);
	p3->insertChild(0, nullptr);
	p3->insertChild(1, nullptr);
	p3->insertChild(2, nullptr);

	BTreeNode<int>* p4 = new BTreeNode<int>();
	p4->insertKey(0, 100);
	p4->insertChild(0, nullptr);
	p4->insertChild(1, nullptr);


	BTreeNode<int>* p5 = new BTreeNode<int>();
	p5->insertKey(0, 24);
	p5->insertChild(0, p0);
	p5->insertChild(1, p1);
	p0->parent = p5;
	p1->parent = p5;


	BTreeNode<int>* p6 = new BTreeNode<int>();
	p6->insertKey(0, 53);
	p6->insertKey(1, 90);
	p6->insertChild(0, p2);
	p6->insertChild(1, p3);
	p6->insertChild(2, p4);
	p2->parent = p6;
	p3->parent = p6;
	p4->parent = p6;

	BTree<int, 3> t2;
	t2.root() = new BTreeNode<int>();
	t2.root()->insertKey(0, 45);
	t2.root()->insertChild(0, p5);
	t2.root()->insertChild(1, p6);
	p5->parent = t2.root();
	p6->parent = t2.root();

	{//borrow from left sibling
		std::cout << "*********\n";
		BTree<int, 3> t;
		t2.copy(t);
		t.display();
		t.erase(100);
		std::cout << "after erase 100\n";
		t.display();
	}
	{//borrow from right sibling
		std::cout << "*********\n";
		t2.display();
		t2.erase(50);
		std::cout << "after erase 50\n";
		t2.display();
	}
	{//
		std::cout << "*********\n";
		t2.display();
		t2.erase(53);
		std::cout << "after erase 53\n";
		t2.display();
	}
	{
		std::cout << "*********\n";
		t2.display();
		t2.erase(37);
		std::cout << "after erase 37\n";
		t2.display();
	}
	std::cout << "All BTree tests passed\n";
}

int main(void)
{
	testBTreeNode();
	testBTree();
	return 0;
}
