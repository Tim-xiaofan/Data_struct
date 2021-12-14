/** 20210913, zyj, GuangDong*/
#ifndef _B_TREE
#define _B_TREE
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/** key type, order*/
template <typename key_t, int m = 3>
class b_tree
{
	private:
		/** struct defines*/
		template <typename key_t1>
		struct Node
		{
			int key_num;//number of key
			struct Node * parent;
			key_t1 keys[m + 1]; //vector of key, 0 is reserved
			struct Node * children[m + 1];//vector of children
		};
		template<typename node_t>
		struct Result
		{
			node_t * pt; // node found
			int i;//index of key found
			bool found;// false for not found, true for found
			Result(node_t * mpt, int mi, bool mfound)
				:pt(mpt), i(mi), found(mfound){}
		};

		/** data defines*/
		Node<key_t> * _root;
		int _node_num;

		/** function defines*/
		static key_t default_cmp(const key_t & a, const key_t & b) 
            { return (a - b);}
		template<typename cmp_t>
		int search(const Node<key_t> * p, const key_t & key, 
                    const cmp_t & cmp);
		
	public :
		typedef Node<key_t> node;
		typedef Result<node> result;

		b_tree():_root(nullptr), _node_num(0){}
		
		/** search*/
		template<typename cmp_t = key_t (*)(const key_t &, const key_t &)>
		result search(const key_t & key, const cmp_t & cmp = default_cmp);
};


/**
  p->keys[1..key_num]中查找
 */
template<typename key_t, int m>
template<typename cmp_t>
int b_tree<key_t, m>:: 
search(const node * p, const key_t & key, const cmp_t & cmp)
{
	int i;

	for(i = 1; i <= p->key_num; ++i)
	  if(cmp(key, p->keys[i]) == 0)
		return i;
	return 0;
}

/**
  在m阶B-树上查找关键字k，返回结果（pt，i，tag）。
  若查找成功，则特征值 tag=1，指针 pt
  所指结点中第i个关键字等于k;
  否则特征值 tag=0，等于K的关键字应插入在指针pt所指
  结点中第i和第 i+1个关键字之间
 */
template<typename key_t, int m>
template<typename cmp_t>
typename b_tree<key_t, m>::result b_tree<key_t, m>::
search(const key_t & key, const cmp_t & cmp)
{
	node *p = _root, *q = nullptr;
	bool found = false;
	int i = 0;

	while(p && !found)
	{
		i  = search(p, key, cmp);
		if(i > 0 && (cmp(key, p->keys[i]) == 0)) 
		  found = true;
		else
		{
			q = p; 
			p = p->children[i];//在孩子Ai中查找
		}
	}
	if(found)
		return result(p, i, 1);
	else
		return result(q, i, 0);//查找不成功，返回K 的插人位置信息

}

#endif
