// Math.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "vector.h"
#include "matrix.h"

int main()
{
	constexpr Vector a = {1,2,3};
	Vector b(a);
	b[2] = 7;

	Matrix g(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6);

	std::cout << a[2] << std::endl;

}

