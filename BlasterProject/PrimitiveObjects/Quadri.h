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

		/**
		 *  \fn     intersect
		 *  \brief  Search the intersection points between this and a Ray.
		 *
		 *  \param[in]      pRay							The to search the intersection with.
		 *  \return         std::vector<Vector3>			vector containing the intersection points.
		 */
		std::vector<Vector3> intersect(const Ray& pRay) const;

		/**
		 *  \fn     fromPoints
		 *  \brief  Creates a Quadri from points.
		 *
		 *  \param[in]      pCorners            Array containing the points.
		 *  \return         Quadri				The created Quadri
		 */
		static Quadri fromPoints(Vector3 pCorners[4]);
		void print(std::ostream& pFlux) const;
		Quadri& operator=(const Quadri& pOther);

		// Create method that call the parent method that calculates the area.
};
std::ostream& operator<<(std::ostream& pFlux, const Quadri& pQuadri);