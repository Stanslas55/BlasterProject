#pragma once
#include "Plane.h"
class Polygon : public Plane {
protected:
	Vector3* m_corners;
	int m_nbCorners;

public:
	Polygon();
	Polygon(int pCorners, const Vector3& pCenter, const Vector3& pNormal);
	~Polygon();
	/**
	 *  \fn     intersect
	 *  \brief  Search the intersection points between this and a Ray.
	 *
	 *  \param[in]      pRay							The to search the intersection with.
	 *  \return         std::vector<Vector3>			vector containing the intersection points.
	 */
	std::vector<Vector3> intersect(const Ray& pRay) const;
	void print(std::ostream& pFlux) const;

	inline Vector3* corners() { return m_corners; }
	inline const Vector3* corners() const { return m_corners; }

	inline Vector3& corners(int pIndex) { return m_corners[pIndex]; }
	inline const Vector3& corners(int pIndex) const { return m_corners[pIndex]; }

	// Calculate the area. Only if we have time. Not necessary at the moment.
};
