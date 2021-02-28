#pragma once

#include "Polygon.h"

class Tri : public Polygon {

private:

public:
	Tri();
	Tri(const Tri& pCopy);
	Tri(const std::initializer_list<Vector3>& pCorners, const Material& pMaterial);
	Tri(const Vector3& pA, const Vector3& pB, const Vector3& pC, const Material& pMaterial = Material::defaultMaterial);
	~Tri();

	inline Vector3& A() { return m_corners[0]; }
	inline Vector3& B() { return m_corners[1]; }
	inline Vector3& C() { return m_corners[2]; }

	inline const Vector3& A() const { return m_corners[0]; }
	inline const Vector3& B() const { return m_corners[1]; }
	inline const Vector3& C() const { return m_corners[2]; }
	
	/**
	 *  \fn     intersect
	 *  \brief  This function returns the intersection points for a given ray.
	 *
	 *  \param[in]      pRay				The Ray we're searching the intersections with the PrimitiveObject.
	 *  \return         const Collision		Collision with pRay.origin() as point if there is no intersection.
	 */
	const Collision intersect(const Ray& pRay) const;

	void print(std::ostream& pFlux) const;

	Tri& operator=(const Tri& pOther);

	// Create method that call the parent method that calculates the area.
};

std::ostream& operator<<(std::ostream& pFlux, const Tri& pQuadri);