#include <iostream>
#include <cassert>
#include "UnionFind.h"

int main(void)
{
	// Create a UnionFind object with 6 elements
    UnionFind uf(6);

    // Perform union operations
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(4, 5);
    uf.unite(1, 3);

	assert(uf.count() == 2);
	assert(uf.connected(0, 1) == true);
	assert(uf.connected(2, 0) == true);
	assert(uf.connected(1, 3) == true);
	assert(uf.connected(3, 1) == true);
	assert(uf.connected(0, 3) == true);
	assert(uf.connected(3, 0) == true);
	assert(uf.connected(0, 4) == false);
	assert(uf.connected(4, 0) == false);
	assert(uf.connected(4, 5) == true);
	assert(uf.connected(5, 4) == true);

	uf.unite(3, 4);
	assert(uf.count() == 1);
	return 0;
}
