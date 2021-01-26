#include <iostream>

#include "Vector3.hpp"
#include "Tests.h"

#include <vld.h>

int main(int argc, char* argv[]) {	

	Tests test;
	test.tests();

	Vector3 A(1, 2, 3);

	Vector3 B = A;

	std::cout << B;

	return EXIT_SUCCESS;
}