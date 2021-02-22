#pragma once
#include "PrimitiveObject.h"
#include "../Vector3/Vector3.hpp"

class Sphere : public PrimitiveObject {	

private:
	Vector3 m_center;
	double m_radius;
	double m_sqRadius;

public:	
	inline Vector3& center() { return m_center; }
	inline double& radius() { return m_radius; }

	inline const Vector3& center() const { return m_center; }
	inline const double& radius() const { return m_radius; }

	Sphere();
	Sphere(const Vector3& pCenter, double pRadius, const Material& pMaterial = Material::defaultMaterial);

	/**
	 *  \fn     intersect
	 *  \brief  This function returns the intersection points for a given ray.
	 *
	 *  \param[in]      pRay				The Ray we're searching the intersections with the PrimitiveObject.
	 *  \return         const Collision		Collision with pRay.origin() as point if there is no intersection.
	 */
	const Collision intersect(const Ray& pRay) const;

	void print(std::ostream& pFlux) const;
};

std::ostream& operator<<(std::ostream& pFlux, const Sphere& pSphere);