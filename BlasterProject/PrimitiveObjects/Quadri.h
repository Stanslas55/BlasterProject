#pragma once
#include "Polygon.h"
class Quadri : public Polygon {
	private:
		
	public:
		Quadri();
		Quadri(const Quadri& pCopy);
		Quadri(Vector3 pCorners[4], const Vector3& pCenter, const Vector3& pNormal);
		~Quadri();

		inline Vector3& A() { return m_corners[0]; }
		inline Vector3& B() { return m_corners[1]; }
		inline Vector3& C() { return m_corners[2]; }
		inline Vector3& D() { return m_corners[3]; }

		inline const Vector3& A() const { return m_corners[0]; }
		inline const Vector3& B() const { return m_corners[1]; }
		inline const Vector3& C() const { return m_corners[2]; }
		inline const Vector3& D() const { return m_corners[3]; }

		std::vector<Vector3> intersect(const Ray& pRay) const;
		void print(std::ostream& pFlux) const;
		Quadri& operator=(const Quadri& pOther);

		// Calculate the area.
};
std::ostream& operator<<(std::ostream& pFlux, const Quadri& pQuadri);