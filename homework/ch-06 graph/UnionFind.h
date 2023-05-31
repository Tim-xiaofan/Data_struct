#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_
#include <vector>

class UnionFind
{
	public:
		UnionFind(int size)
			:count_(size),
			parent_(size)
		{
			//start state: parent is self
			for(size_t i = 0; i < parent_.size(); ++i)
			{
				parent_[i] = i;
			}
		}

		// find parent with path compress
		int find(int x)
		{
			if(x != parent_[x])
			{
				parent_[x] = find(parent_[x]);
			}
			return parent_[x];
		}

		//union operator
		void unite(int x, int y)
		{
			int rootx = find(x);
			int rooty = find(y);
			if(rootx != rooty)
			{
				parent_[rootx] = rooty;
				--count_;
			}
		}

		bool connected(int x, int y)
		{
			return find(x) == find(y);
		}

		int count(void) const
		{ return count_; }

	private:
		int count_; // number of trees
		std::vector<int> parent_;
};

#endif
