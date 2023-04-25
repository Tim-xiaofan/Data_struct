//HuffmanTree: 一维数组作为存储结构
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <queue>
#include <utility>
#include <string>
#include <unordered_map>
#include <deque>

using std::cout;
using std::endl;

template<typename T>
static std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
	return os;
}

using WeightList = std::vector<double>;
using CharList = std::vector<char>;
using Bit = char;
using Code = std::vector<Bit>;
using CharCodeMap = std::unordered_map<char, Code>;

const Bit BIT_ZERO = '0';
const Bit BIT_ONE = '1';

class HuffmanTree
{
	public:
		HuffmanTree(const WeightList& weights, const CharList& chars);

		CharCodeMap encode() const;

		double wpl() const;


	private:
		struct HuffmanTreeNode
		{
			HuffmanTreeNode(double w = 0.0, char ch = 0, size_t p = 0, size_t l = 0, size_t r = 0);

			friend std::ostream& operator<<(std::ostream& os, const HuffmanTreeNode& i)
			{
				os << "<weight=" << i.weight << ",ch=" << i.ch << ":parent=" << i.parent << ",lchild=" << i.lchild << ",rchild=" << i.rchild << ">";
				return os;
			}
			
			double weight;
			char ch;
			size_t parent; // for encode
			size_t lchild; // for decode
			size_t rchild; // for decode
		};

		std::vector<HuffmanTreeNode> nodes_;

		size_t numberOfLeaves() const { return nodes_.size() / 2; }

		const HuffmanTreeNode* root() const { return &nodes_.back(); }
};

HuffmanTree::HuffmanTreeNode::HuffmanTreeNode(double w, char c, size_t p, size_t l, size_t r)
		:weight(w),
		ch(c),
		parent(p),
		lchild(l),
		rchild(r)
{}

HuffmanTree::HuffmanTree(const WeightList& weights, const CharList& chars)
		:nodes_(2 * weights.size()) // unused index 0
{
	size_t n = weights.size();
	size_t m = 2 * n;
	//init all leaf nodes and create a min queue
	using NodeIndex = std::pair<HuffmanTreeNode*, size_t>;
	struct Greater
	{
		bool operator()(const NodeIndex& a, const NodeIndex& b) const
		{ return a.first->weight > b.first->weight; }
	};
	std::priority_queue<NodeIndex,
		std::vector<NodeIndex>,
		Greater> minQueue;
	for(size_t i = 1; i <= n; ++i)
	{
		nodes_[i] = HuffmanTreeNode(weights[i-1], chars[i-1]);
		minQueue.emplace(&nodes_[i], i);
	}

	// create tree
	NodeIndex s1;
	NodeIndex s2;
	for(size_t i = n + 1; i < m; ++i)
	{
		s1 = minQueue.top();
		minQueue.pop();
		s2 = minQueue.top();
		minQueue.pop();
		nodes_[i].lchild = s1.second;
		nodes_[i].rchild = s2.second;
		nodes_[i].weight = s1.first->weight + s2.first->weight;
		s1.first->parent = i;
		s2.first->parent = i;
		minQueue.emplace(&nodes_[i], i);
	}
}

double HuffmanTree::wpl() const
{
	size_t n = numberOfLeaves();
	double sum = 0.0;
	for(size_t i = 1; i <= n; ++i)
	{
		const HuffmanTreeNode* p = &nodes_[i];
		double w = p->weight;
		while(p->parent != 0)
		{
			sum += w;
			p = &nodes_[p->parent];
		}
	}
	return sum;
}

CharCodeMap HuffmanTree::encode() const
{
	CharCodeMap charCode;
	size_t n = numberOfLeaves();
	for(size_t i = 1; i <= n; ++i)
	{
		Code code;
		const HuffmanTreeNode* p = &nodes_[i];
		char ch = p->ch;
		while(p->parent != 0)
		{
			if(&nodes_[nodes_[p->parent].lchild] == p)
			{
				code.push_back(BIT_ZERO);
			}
			else
			{
				code.push_back(BIT_ONE);
			}
			p = &nodes_[p->parent];
		}
		std::reverse(code.begin(), code.end());
		charCode.emplace(ch, code);
	}
	return charCode;
}

static std::ostream& operator<<(std::ostream& os, const CharCodeMap& m)
{
	for(const auto& e: m)
	{
		os << "<"<< e.first << ":" << std::string(e.second.data(), e.second.size()) << "> ";
	}
	return os;
}

static void assertHuffmanTree(const WeightList& weights, const CharList& chars, double expectedWpl, const std::string& caseName)
{
	cout << "weights: " << weights << endl;
	cout << "chars: " << chars << endl;
	HuffmanTree tree(weights, chars);
	auto code = tree.encode();
	cout << "code: " << code << endl; 
	assert(tree.wpl() == expectedWpl);
	cout << caseName << " passed\n\n";
}

int main(void)
{
	{
		WeightList weights = {1, 2, 3, 4};
		CharList chars = {'A', 'B', 'C', 'D'};
		double expectedWpl = 19;
		assertHuffmanTree(weights, chars, expectedWpl, "case 1");
	}

	{
		WeightList weights = {7, 5, 2, 4};
		CharList chars = {'A', 'B', 'C', 'D'};
		double expectedWpl = 35;
		assertHuffmanTree(weights, chars, expectedWpl, "case 2");
	}
	return 0;
}
