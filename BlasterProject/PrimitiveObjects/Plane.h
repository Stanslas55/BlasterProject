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
		Plane(const Vector3& pCenter, const Vector3& pNormal);		
		

		std::vector<Vector3> intersect(const Ray& pRay) const;
		void print(std::ostream& pFlux) const;
};
std::ostream& operator<<(std::ostream& pFlux, const Plane& pPlane);