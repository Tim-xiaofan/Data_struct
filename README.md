# Data_struct 严蔚敏 吴伟民
## ch-03 stack and queue
### 进制转换
```c++
template <typename T>
std::string base_conversion<T>::
conversion(T t) const
{
	T quotient, remainder;
	sqstack<char> stack(16);
	std::string result;
	char ch;
	quotient = t;
	int i;

	while(t != 0)
	{
		quotient = t / _mode;
		remainder = t % _mode;
		//std::cout << "push : " << remainder << std::endl;
		//stack.push('0' + remainder);
		stack.push(elements[remainder]);
		t = quotient;
	}

	//stack.show();
	//std::cout << "length = " << stack.length() << std::endl;
	int len = stack.length();
	for(i = 0; i < len; i++)
	{
		stack.pop(ch);
		//std::cout << "pop : " << ch << std::endl;
		result.push_back(ch);
	}
	return result;
}
```
![](https://github.com/Tim-xiaofan/Data_struct/blob/06a1118a4498ddfb7edd67e53bd5967f1ef06e4d/ch-03%20stack%20and%20queue/base-conversion/base_conversion.png) 
