#pragma once
#include "../Vector3/Vector3.hpp"

class Ray {
	private:
		Vector3 origin;
		Vector3 end;		
		Vector3 direction;

	public:
		inline Vector3& gorigin() { return origin; }
		inline Vector3& gRadius() { return direction; }

		Ray();
		Ray(Vector3 pOrigin, Vector3 pEnd);
};

