#pragma once

#include "Plane.h"

class Polygon : public Plane {

protected:
	std::unique_ptr<Vector3[]> m_corners;
	int m_nbCorners;

public:
	Polygon();
	Polygon(const Polygon& pCopy);
	Polygon(const std::initializer_list<Vector3>& pCorners, const Material& pMaterial = Material::defaultMaterial);
	~Polygon();

	/**
	 *  \fn     intersect
	 *  \brief  This function returns the intersection points for a given ray.
	 *
	 *  \param[in]      pRay				The Ray we're searching the intersections with the PrimitiveObject.
	 *  \return         const Collision		Collision with pRay.origin() as point if there is no intersection.
	 */
	const Collision intersect(const Ray& pRay) const;

	void print(std::ostream& pFlux) const;

	inline std::unique_ptr<Vector3[]>& corners() { return m_corners; }
	inline const std::unique_ptr<Vector3[]>& corners() const { return m_corners; }

	inline Vector3& corners(int pIndex) { return m_corners[pIndex]; }
	inline const Vector3& corners(int pIndex) const { return m_corners[pIndex]; }

	// Calculate the area. Only if we have time. Not necessary at the moment.
};
