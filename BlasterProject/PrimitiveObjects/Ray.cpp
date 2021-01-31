#include "Ray.hpp"

Ray::Ray()
{
	origin = Vector3(0, 0, 0);
	end = Vector3(0, 0, 0);
	direction = Vector3(0, 0, 0);
}

Ray::Ray(const Vector3& pOrigin, const Vector3& pDirection) {
	
	origin = pOrigin;
	end = Vector3(0, 0, 0);
	direction = pDirection;
}

Ray Ray::fromLine(const Vector3& pOrigin, const Vector3& pEnd)
{
	Ray ray;
	Vector3 substraction = pEnd - pOrigin;

	ray.origin = pOrigin;
	ray.end = pEnd;
	ray.direction = Vector3::normalize(substraction);
	return ray;
}

void Ray::print(std::ostream& pFlux)
{
	pFlux << "Ray: {Origin: " << origin << ", Direction: " << direction << "}";
}

std::ostream& operator<<(std::ostream& pFlux, Ray pRay)
{
	pRay.print(pFlux);
	return pFlux;
}
