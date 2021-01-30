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
		/**
		 *  \fn     intersect
		 *  \brief  Brief description of what the function do
		 *
		 *  \param[in]      pRay            The ray we want to know the intersection with the sphere.
		 *  \return         std::vector<Vector3>    A vector of intersection points between the sphere and the ray.
		 */
		std::vector<Vector3> intersect(Ray pRay);
};

