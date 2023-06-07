#include "ArrayN.h"

int main(void)
{
	Array3D<int> arr = {
		{{1, 2, 3}, {4, 5, 6}},
		{{7, 8, 9}, {10, 11, 12}},
		{{13, 14, 15}, {16, 17, 18}}
	};
	arr.display();

	std::vector<size_t> dims = arr.getDims();
	std::cout << "Dimensions: " << dims[0] << " x " << dims[1] << " x " << dims[2] << std::endl;

	Array3D<int> arr1(3,2,3);
	arr1[0] = arr[1];
	arr1[1] = arr[2];
	arr1[2] = arr[0];
	arr1.display();
	return 0;
}
