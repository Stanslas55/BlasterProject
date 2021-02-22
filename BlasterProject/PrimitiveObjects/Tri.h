#pragma once

#include "Polygon.h"

class Tri : public Polygon {

private:

public:
	Tri();
	Tri(const Tri& pCopy);
	Tri(Vector3 pCorners[3], const Vector3& pCenter, const Vector3& pNormal, const Material& pMaterial = Material::defaultMaterial);
	~Tri();

	inline Vector3& A() { return m_corners[0]; }
	inline Vector3& B() { return m_corners[1]; }
	inline Vector3& C() { return m_corners[2]; }
	inline Vector3& D() { return m_corners[3]; }

	inline const Vector3& A() const { return m_corners[0]; }
	inline const Vector3& B() const { return m_corners[1]; }
	inline const Vector3& C() const { return m_corners[2]; }
	inline const Vector3& D() const { return m_corners[3]; }


	/**
	 *  \fn     intersect
	 *  \brief  This function returns the intersection points for a given ray.
	 *
	 *  \param[in]      pRay				The Ray we're searching the intersections with the PrimitiveObject.
	 *  \return         const Collision		Collision with pRay.origin() as point if there is no intersection.
	 */
	const Collision intersect(const Ray& pRay) const;

	/**
		*  \fn     fromPoints
		*  \brief  Creates a Quadri from points.
		*
		*  \param[in]      pCorners            Array containing the points.
		*  \return         Tri					The created Tri
		*/
	static Tri fromPoints(Vector3 pCorners[3]);
	void print(std::ostream& pFlux) const;
	Tri& operator=(const Tri& pOther);

	// Create method that call the parent method that calculates the area.
};
std::ostream& operator<<(std::ostream& pFlux, const Tri& pQuadri);