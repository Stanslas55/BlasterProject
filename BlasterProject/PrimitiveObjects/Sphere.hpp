#pragma once
#include "PrimitiveObject.h"
#include "../Vector3/Vector3.hpp"

class Sphere : public PrimitiveObject {	
	private:
		Vector3 m_center;
		double m_radius;		

	public:	
		inline Vector3& center() { return m_center; }
		inline double& radius() { return m_radius; }

		inline const Vector3& center() const { return m_center; }
		inline const double& radius() const { return m_radius; }

		Sphere();
		Sphere(const Vector3& pCenter, double pRadius);
		/**
		 *  \fn     intersect
		 *  \brief  Find the intersection points between the Sphere and the Ray.
		 *
		 *  \param[in]      pRay					The ray we want to know the intersection with the sphere.
		 *  \return         std::vector<Vector3>    A vector of intersection points between the sphere and the ray.
		 */
		std::vector<Vector3> intersect(const Ray& pRay) const;
		void print(std::ostream& pFlux) const;
};

std::ostream& operator<<(std::ostream& pFlux, const Sphere& pSphere);