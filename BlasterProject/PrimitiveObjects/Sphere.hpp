#pragma once
#include "PrimitiveObject.h"
#include "../Vector3/Vector3.hpp"

class Sphere : protected PrimitiveObject {	
	private:
		Vector3 center;
		double radius;
		// Maybe add a Material class ?

	public:	
		inline Vector3& gCenter() { return center; }
		inline double& gRadius() { return radius; }

		Sphere();
		Sphere(Vector3 pCenter, double pRadius);

		std::vector<Vector3> intersect(Ray pRay);
};

