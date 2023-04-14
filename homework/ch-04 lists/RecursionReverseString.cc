#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;

template <typename BiIter>
void recursionReverseString(BiIter begin, BiIter end)
{
	if(begin == end || std::distance(begin, end) < 2)
	{
		return;
	}
	else if(std::distance(begin, end) == 2)
	{
		std::swap(*begin, *(end-1));
	}
	else
	{
		// 反转除去头尾的部分
		recursionReverseString(begin + 1, end - 1);
		std::swap(*begin, *(end-1));
	}
}

int main(void)
{
	// Test case 1: empty string
    std::string s1 = "";
    recursionReverseString(s1.begin(), s1.end());
    assert(s1 == "");

    // Test case 2: string with one character
    std::string s2 = "a";
    recursionReverseString(s2.begin(), s2.end());
    assert(s2 == "a");

    // Test case 3: string with even length
    std::string s3 = "abcd";
    recursionReverseString(s3.begin(), s3.end());
    assert(s3 == "dcba");

    // Test case 4: string with odd length
    std::string s4 = "abcde";
    recursionReverseString(s4.begin(), s4.end());
    assert(s4 == "edcba");

	// Test case 5: string with spaces
    std::string s5 = "Hello World";
    recursionReverseString(s5.begin(), s5.end());
    assert(s5 == "dlroW olleH");

    // Test case 6: string with special characters
    std::string s6 = R"(+_)(!%$^&*#@)";
	std::string a6 = std::string(s6.rbegin(), s6.rend());
    recursionReverseString(s6.begin(), s6.end());
    assert(s6 == a6);

    // Test case 7: long string
    std::string s7(100, 'a');
	std::string a7(s7.rbegin(), s7.rend());
    recursionReverseString(s7.begin(), s7.end());
	assert(s7 == a7);

    // Test case 8: string with repeated characters
    std::string s8 = "aaaabbbb";
    recursionReverseString(s8.begin(), s8.end());
    assert(s8 == "bbbbaaaa");

    std::cout << "All test cases passed." << std::endl;
	return 0;
}
