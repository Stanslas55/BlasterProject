#pragma once
#include "Plane.h"
class Polygon : public Plane {
protected:
	Vector3* m_corners;
	int m_size;

public:
	Polygon();
	Polygon(int pCorners, const Vector3& pCenter, const Vector3& pNormal);
	~Polygon();
	std::vector<Vector3> intersect(const Ray& pRay) const;
	void print(std::ostream& pFlux) const;

	inline Vector3* corners() { return m_corners; }
	inline const Vector3* corners() const { return m_corners; }

	inline Vector3& corners(int pIndex) { return m_corners[pIndex]; }
	inline const Vector3& corners(int pIndex) const { return m_corners[pIndex]; }
};
