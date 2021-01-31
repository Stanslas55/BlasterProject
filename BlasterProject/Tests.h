#pragma once
#include "Vector3/Vector3.hpp"
#include "PrimitiveObjects/Ray.hpp"
#include "PrimitiveObjects/Sphere.hpp"
#include "PrimitiveObjects/Plane.h"
#include "PrimitiveObjects/Quadri.h"


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
		void intersectionPlane();
		void intersectionQuadri();

	public:
		Tests();
		~Tests();
		/**
		 *  \fn     tests
		 *  \brief  Runs unitary tests of all implemented functions.
		 *		 
		 *  \return         void    This function returns nothing.
		 */
		void tests();
};