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

template<typename T>
static void  assertGetPowerSetDAC(const Set<T>& s)
{
	cout << "set: " << s << endl;
	auto ret = getPowerSetDAC(s.begin(), s.end());
	cout << "power of set: "<< ret << endl << endl;
	assert(powl(2, s.size()) == ret.size());
}

int main(void)
{
	{
		Set<int> s = {1, 2, 3};
		assertGetPowerSetDAC(s);
	}

	{
		Set<int> s = {};
		assertGetPowerSetDAC(s);
	}
	
	{
		Set<int> s = {1};
		assertGetPowerSetDAC(s);
	}

	return 0;
}
