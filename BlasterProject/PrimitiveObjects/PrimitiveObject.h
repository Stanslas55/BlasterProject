#pragma once
#include <vector>

#include "../Vector3/Vector3.hpp"
#include "Ray.hpp"

class PrimitiveObject {
	public:

	protected:
		// This function returns the number of intersection for a given radius.
		virtual std::vector<Vector3> intersect(Ray pRay) = 0;
};

