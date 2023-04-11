#include "Stack.h"
#include <iostream>
#include <string>
#include <cassert>

using std::cout;
using std::endl;
using std::string;

bool isPalindrome(const string& text)
{
	size_t ct = text.size() / 2;
	HOMEWORK_NS::Stack<char> s(ct);
	size_t i;
	for(i = 0; i < ct; ++i)
	{
		s.push(text[i]);
	}
	
	//跳过居中元素
	if(text.size() % 2 != 0) ++i;
	
	for(; i < text.size(); ++i)
	{
		char e;
		s.pop(e);
		if(text[i] == e)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

int main(void)
{
	{
		const string text = "";
		assert(isPalindrome(text));
	}

	{
		const string text = "a";
		assert(isPalindrome(text));
	}

	{
		const string text = "aa";
		assert(isPalindrome(text));
	}
	
	{
		const string text = "ab";
		assert(!isPalindrome(text));
	}

	{
		const string text = "aba";
		assert(isPalindrome(text));
	}

	{
		const string text = "aba";
		assert(isPalindrome(text));
	}
	
	{
		const string text = "abba";
		assert(isPalindrome(text));
	}
	return 0;
}
