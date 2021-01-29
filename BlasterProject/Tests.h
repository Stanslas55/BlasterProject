#pragma once
#include "Vector3/Vector3.hpp"
#include "PrimitiveObjects/Ray.hpp"
#include "PrimitiveObjects/Sphere.hpp"


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
		void intersectionSphere();

	public:
		Tests();
		~Tests();

		void tests();
};