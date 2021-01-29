#pragma once
#include <iostream>
#include <vld.h>

#include "Vector3/Vector3.hpp"
#include "PrimitiveObjects/PrimitiveObject.h"	

#include "Tests.h"

int main(int argc, char* argv[]) {	

	Tests test;
	test.tests();
	
	return EXIT_SUCCESS;
}