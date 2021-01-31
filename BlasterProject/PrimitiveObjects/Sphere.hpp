#pragma once
#include "PrimitiveObject.h"
#include "../Vector3/Vector3.hpp"

class Sphere : public PrimitiveObject {	
	private:
		Vector3 center;
		double radius;		

	public:	
		inline Vector3& gCenter() { return center; }
		inline double& gRadius() { return radius; }

		Sphere();
		Sphere(const Vector3& pCenter, double pRadius);
		/**
		 *  \fn     intersect
		 *  \brief  Find the intersection points between the Sphere and the Ray.
		 *
		 *  \param[in]      pRay					The ray we want to know the intersection with the sphere.
		 *  \return         std::vector<Vector3>    A vector of intersection points between the sphere and the ray.
		 */
		std::vector<Vector3> intersect(const Ray& pRay);
		void print(std::ostream& pFlux);
};

std::ostream& operator<<(std::ostream& pFlux, Sphere pSphere);