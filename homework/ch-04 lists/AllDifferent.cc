#include <iostream>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <array>

using std::cout;
using std::endl;
using std::vector;

template<typename T, size_t n, size_t m>
using matrix=std::array<std::array<T, n>, m>;

template <typename T, size_t n, size_t m>
bool allDifferent(const matrix<T, m, n>& mat)
{
	std::unordered_set<T> values;
	for(const auto& row: mat)
	{
		for(const auto& element: row)
		{
			if(values.find(element)!= values.end())
			{
				return false;
			}
			else
			{
				values.insert(element);
			}
		}
	}
	return true;
}

template <typename T, size_t m, size_t n>
class Matrix {
public:
	Matrix() {}

	template <typename... Args>
	Matrix(Args... args) : data{args...} {}

	T* operator[](size_t i) {
		return data + i * n;
	}

	const T* operator[](size_t i) const {
		return data + i * n;
	}

	bool allDifferent() const {
		std::unordered_set<T> s;
		for (size_t i = 0; i < m; i++) {
			for (size_t j = 0; j < n; j++) {
				if (s.find(data[i * n + j]) != s.end()) {
					return false; // Found a repeated value
				}
				s.insert(data[i * n + j]);
			}
		}
		return true; // All values are different
	}

private:
	T data[m * n];
};

int main(void)
{
	matrix<int, 3, 3> mat = { {{1, 2, 3}, {4, 5, 6}, {7, 8, 9} }};
	assert(allDifferent(mat));
    matrix<int, 2, 2> mat2 = { {{1, 2}, {2, 3}} };
	assert(!allDifferent(mat2)); // false

	Matrix<int, 3, 3> M1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for(int i = 0; i< 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			cout << M1[i][j] << ' ';
		}
		cout << endl;
	}

    return 0;
}
