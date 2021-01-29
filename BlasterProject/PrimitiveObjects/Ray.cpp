#include "Ray.hpp"

Ray::Ray()
{
	origin = Vector3(0, 0, 0);
	end = Vector3(0, 0, 0);
	direction = Vector3(0, 0, 0);
}

Ray::Ray(Vector3 pOrigin, Vector3 pEnd) {
	Vector3 substraction = pEnd - pOrigin;

	origin = pOrigin;
	end = pEnd;	
	direction = Vector3().normalize(substraction);
}
