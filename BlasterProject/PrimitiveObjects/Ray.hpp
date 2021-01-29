#pragma once
#include "../Vector3/Vector3.hpp"

class Ray {
	private:
		Vector3 origin;
		Vector3 end;		
		Vector3 direction;

	public:
		inline Vector3& gOrigin() { return origin; }
		inline Vector3& gEnd() { return end; }
		inline Vector3& gDirection() { return direction; }

		Ray();
		Ray(Vector3 pOrigin, Vector3 pEnd);
		// Origin + Direction * t = Point 
		Vector3 point(double pT) const { return origin + direction * pT; }
};

