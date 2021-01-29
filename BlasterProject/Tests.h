#pragma once
#include "Vector3/Vector3.hpp"

class Tests
{
	private:
		void addition();
		void substraction();
		void multiplication();
		void division();
		void dot();
		void cross();
		void normalize();		

	public:
		Tests();
		~Tests();

		void tests();
};