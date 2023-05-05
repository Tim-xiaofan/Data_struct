// 求幂集
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <utility>
#include <string>
#include <cmath>

using std::cout;
using std::endl;
template<typename T>
using Set = std::vector<T>;
template<typename T>
using SubSets = Set<Set<T>>;
template<typename T>
using List = std::vector<T>;

template<typename T>
static std::ostream& operator<<(std::ostream& os, const Set<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
	return os;
}

template<typename T>
static std::ostream& operator<<(std::ostream& os, const SubSets<T>& v)
{
	for(const auto& s: v)
	{
		os << "{" << s << "} ";
	}
	return os;
}

// Divide and Conquer
template<typename FwdIter>
static SubSets<typename FwdIter::value_type> getPowerSetDAC(FwdIter first, FwdIter last)
{
	using T = typename FwdIter::value_type;
	if(first == last)
	{
		return {{}};
	}
	else if(first + 1 == last)
	{
		return {{}, {*first}}; 
	}
	else
	{
		auto subSets = getPowerSetDAC(first + 1, last);
		//combination
		auto end = subSets.end();
		for(auto p = subSets.begin(); p != end; ++p)
		{
			Set<T> tmp = *p;
			tmp.emplace_back(*first);
			subSets.push_back(tmp);
		}
		return subSets;
	}
}

template<typename FwdIter>
void getPowerSetBacktracking(FwdIter current, FwdIter last, List<typename FwdIter::value_type>& B)
{
	if(current == last)
	{
		cout << '{' <<  B <<"}\n";
	}
	else
	{
		size_t oldLen = B.size();//使用长度而不是迭代器，从而避免迭代器失效问题

		//选择元素
		B.emplace_back(*current);
		getPowerSetBacktracking(current + 1, last, B);

		B.erase(B.begin() + oldLen, B.end());
		//不选择此元素
		getPowerSetBacktracking(current + 1, last, B);
	}
}

template<typename T>
static void  assertGetPowerSetDAC(const Set<T>& s)
{
	cout << "set: " << s << endl;
	auto ret = getPowerSetDAC(s.begin(), s.end());
	cout << "power of set: "<< ret << endl << endl;
	assert(powl(2, s.size()) == ret.size());
}

template<typename T>
static void assertGetPowerSetBacktracking(const Set<T>& s)
{
	cout << "set: " << s << endl;
	List<int> B;
	cout << "power of set: \n";
	getPowerSetBacktracking(s.begin(), s.end(), B);
}

int main(void)
{
	{
		Set<int> s = {1, 2, 3};
		assertGetPowerSetDAC(s);
		assertGetPowerSetBacktracking(s);
	}

	{
		Set<int> s = {};
		assertGetPowerSetDAC(s);
		assertGetPowerSetBacktracking(s);
	}
	
	{
		Set<int> s = {1};
		assertGetPowerSetDAC(s);
		assertGetPowerSetBacktracking(s);
	}

	return 0;
}
