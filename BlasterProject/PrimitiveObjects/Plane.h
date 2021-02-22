#pragma once
#include "PrimitiveObject.h"
class Plane : public PrimitiveObject {

protected:		
	Vector3 m_center;
	Vector3 m_normal;

public:		

	inline Vector3& center() { return m_center; }
	inline Vector3& normal() { return m_normal; }

	inline const Vector3& center() const { return m_center; }
	inline const Vector3& normal() const { return m_normal; }

	Plane();
	Plane(const Vector3& pCenter, const Vector3& pNormal, const Material& pMaterial = Material::defaultMaterial);		
		
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
std::ostream& operator<<(std::ostream& pFlux, const Plane& pPlane);