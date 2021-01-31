#pragma once
#include "PrimitiveObject.h"
class Plane : public PrimitiveObject {
	private:
		Vector3 corners[4];
		Vector3 center;
		Vector3 normal;

	public:
		inline Vector3& A() { return corners[0]; }
		inline Vector3& B() { return corners[1]; }
		inline Vector3& C() { return corners[2]; }
		inline Vector3& D() { return corners[3]; }

		inline Vector3& gCenter() { return center; }
		inline Vector3& gNormal() { return normal; }

		Plane();
		Plane(const Vector3& pCenter, const Vector3& pNormal);		
		static Plane fromCorners(Vector3 pCorners[4]);

		std::vector<Vector3> intersect(const Ray& pRay);
		void print(std::ostream& pFlux);
};
std::ostream& operator<<(std::ostream& pFlux, Plane pPlane);

/*
(a, b, c) . (x, y, z) = 0

ax + by + cz = 0

x = 1
y = 1

a + b + cz = 0
cz = - ( a + b )
z = -(a+b)/c


(a - b)
X
(c - b)
*/